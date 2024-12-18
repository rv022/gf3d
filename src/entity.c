#include "simple_logger.h"
#include "gfc_vector.h"
#include "entity.h"

typedef struct
{
    Entity *entity_list;
    Uint32 entity_max;
}EntityManager;

void entity_system_close();

static EntityManager _entity_manager = {0};

void entity_system_initialize(Uint32 max)
{
    if(_entity_manager.entity_list)
    {
        slog("cannot have two instances of an entity manager, one is already active");
        return;
    }
    if(!max)
    {
        slog("Cannot allocate 0 entities!");
        return;
    }
    _entity_manager.entity_list = gfc_allocate_array(sizeof(Entity),max);
    if(!_entity_manager.entity_list)
    {
        slog("failed to allocate global entity list.");
        return;
    }
    _entity_manager.entity_max = max;
    atexit(entity_system_close);
}

void entity_system_close()
{
    entity_clear_all(NULL);
    if(_entity_manager.entity_list)free(_entity_manager.entity_list);
    memset(&_entity_manager,0,sizeof(EntityManager));
}

void entity_clear_all(Entity *ignore)
{
    int i;
    for(i=0; i<_entity_manager.entity_max;i++)
    {
        if(&_entity_manager.entity_list[i] == ignore)continue;
        if(!_entity_manager.entity_list[i]._inuse)continue;
        entity_free(&_entity_manager.entity_list[i]);
    }

}

Entity *entity_new()
{
    int i;
    for(i=0; i<_entity_manager.entity_max;i++)
    {
        if(_entity_manager.entity_list[i]._inuse)continue;
        memset(&_entity_manager.entity_list[i],0,sizeof(Entity));
        _entity_manager.entity_list[i]._inuse = 1;
        //set default color and scale
        return &_entity_manager.entity_list[i];
    }
    slog("No more available entities");
    return NULL;
}

void entity_free(Entity *self)
{
    if(!self)return; //can't do work on nothing.
    gf3d_model_free(self->model);
    if(self->free)self->free(self->data);

}

void entity_think(Entity *self)
{
    if(!self)return;
    //boilerplate think stuff here
    if(self->think)self->think(self);
}

void entity_system_think()
{
    int i;
    for(i=0; i<_entity_manager.entity_max;i++)
    {
        if(!_entity_manager.entity_list[i]._inuse)continue;
        entity_think(&_entity_manager.entity_list[i]);
    }
}

void entity_update(Entity *self)
{
    if(!self)return;
    //boilerplate update stuff here
    if(self->update)self->update(self);
}

void entity_system_update()
{
    int i;
    for(i=0; i<_entity_manager.entity_max;i++)
    {
        if(!_entity_manager.entity_list[i]._inuse)continue;
        entity_update(&_entity_manager.entity_list[i]);
    }
}

void entity_draw(Entity *self)
{
    if(!self)return;
    if(self->model)
    {
        gfc_matrix4_from_vectors(self->modelMat,self->position,self->rotation,self->scale);
        gf3d_model_draw(
            self->model,
            self->modelMat,
            GFC_COLOR_WHITE,//TODO pass a material instead
            0);
    }

}

void entity_system_draw()
{
    int i;
    for(i=0; i<_entity_manager.entity_max;i++)
    {
        if(!_entity_manager.entity_list[i]._inuse)continue;
        entity_draw(&_entity_manager.entity_list[i]);
    };

}

void entity_collide(Entity *self)
{
    if(!self)return;
    if(self->collide)self->collide(self);

}

void entity_system_collide()
{
    int i,j,k;
    for(i=1; i<_entity_manager.entity_max;i++)
    {
        if(!_entity_manager.entity_list[i]._inuse)continue;
        if(gfc_box_overlap(_entity_manager.entity_list[0].body,_entity_manager.entity_list[i].body) == 1)
        {
            slog("collision");
            entity_collide(&_entity_manager.entity_list[0]);
            if(_entity_manager.entity_list[i].type==10)
            {
                if(_entity_manager.entity_list[0].doorNum==_entity_manager.entity_list[0].roomNum)
                {
                    while(_entity_manager.entity_list[i].position.z<30)
                        gfc_vector3d_add(_entity_manager.entity_list[i].position,_entity_manager.entity_list[i].position,gfc_vector3d(0,0,0.001));
                    _entity_manager.entity_list[0].doorNum+=1;
                }
            }
            if(_entity_manager.entity_list[i].type==5)
            {
                _entity_manager.entity_list[0].health = _entity_manager.entity_list[0].health - _entity_manager.entity_list[i].attack;
            }
            if(_entity_manager.entity_list[i].type==6)
            {
                _entity_manager.entity_list[0].health = _entity_manager.entity_list[0].health - _entity_manager.entity_list[i].attack;
                _entity_manager.entity_list[0].speed-=0.3;
                _entity_manager.entity_list[0].speedDebuffStatus=1;
            }
            if(_entity_manager.entity_list[i].type==7)
            {
                _entity_manager.entity_list[0].health = _entity_manager.entity_list[0].health - _entity_manager.entity_list[i].attack;
                _entity_manager.entity_list[0].attack-=1;
                _entity_manager.entity_list[0].attackDebuffStatus=1;
            }
            if(_entity_manager.entity_list[i].type==2)
            {
                _entity_manager.entity_list[0].speed+=0.3;
                _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
                _entity_manager.entity_list[0].speedBuffStatus=1;
            }
            if(_entity_manager.entity_list[i].type==3)
            {
                if(_entity_manager.entity_list[0].maxHealth<8)
                {
                    _entity_manager.entity_list[0].maxHealth+=1;
                    _entity_manager.entity_list[0].health+=1;
                }
                _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
                _entity_manager.entity_list[0].healthBuffStatus=1;
            }
            if(_entity_manager.entity_list[i].type==4)
            {
                _entity_manager.entity_list[0].attack+=1;
                _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
                _entity_manager.entity_list[0].attackBuffStatus=1;
            }
            if(_entity_manager.entity_list[i].type==1)
            {
                _entity_manager.entity_list[0].essence+=3;
                while(_entity_manager.entity_list[i].position.z<30)
                    gfc_vector3d_add(_entity_manager.entity_list[i].position,_entity_manager.entity_list[i].position,gfc_vector3d(0,0,0.001));
                _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
            }
            if(_entity_manager.entity_list[i].type==20)
            {
                if(_entity_manager.entity_list[0].essence>=2)
                {
                _entity_manager.entity_list[0].essence-=2;
                _entity_manager.entity_list[0].maxHealth+=1;
                _entity_manager.entity_list[0].health=_entity_manager.entity_list[0].maxHealth;
                _entity_manager.entity_list[0].attack+=1;
                }
            }
        }
    };
    for(j=1; j<_entity_manager.entity_max;j++)
    {
        if(!_entity_manager.entity_list[j]._inuse)continue;
        for(k=1; k<_entity_manager.entity_max;k++)
        {
        if(!_entity_manager.entity_list[k]._inuse)continue;
        if(j==k)continue;
        if(gfc_box_overlap(_entity_manager.entity_list[j].body,_entity_manager.entity_list[k].body) == 1)
        {
            entity_collide(&_entity_manager.entity_list[j]);
            if(_entity_manager.entity_list[k].type==30 && _entity_manager.entity_list[j].type==5)
            {
                _entity_manager.entity_list[j].health-=_entity_manager.entity_list[k].attack;
                if(_entity_manager.entity_list[j].health<0)
                {
                    gfc_vector3d_add(_entity_manager.entity_list[j].position,_entity_manager.entity_list[j].position,gfc_vector3d(0,0,1000000));
                    _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
                    _entity_manager.entity_list[0].attackBuffStatus=0;
                    _entity_manager.entity_list[0].attack-=1;
                    _entity_manager.entity_list[0].attackDebuffStatus=0;
                    _entity_manager.entity_list[0].attack-=1;
                    _entity_manager.entity_list[0].healthBuffStatus=0;
                    _entity_manager.entity_list[0].maxHealth-=1;
                    _entity_manager.entity_list[0].speedDebuffStatus=0;
                    _entity_manager.entity_list[0].speed-=0.3;
                    _entity_manager.entity_list[0].speedBuffStatus=0;
                    _entity_manager.entity_list[0].speed-=0.3;
                    _entity_manager.entity_list[0].essence+=1;

                }


            }
            if(_entity_manager.entity_list[k].type==30 && _entity_manager.entity_list[j].type==6)
            {
                _entity_manager.entity_list[j].health-=_entity_manager.entity_list[k].attack;
                if(_entity_manager.entity_list[j].health<0)
                {
                    gfc_vector3d_add(_entity_manager.entity_list[j].position,_entity_manager.entity_list[j].position,gfc_vector3d(0,0,1000000));
                    _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
                    _entity_manager.entity_list[0].attackBuffStatus=0;
                    _entity_manager.entity_list[0].attack-=1;
                    _entity_manager.entity_list[0].attackDebuffStatus=0;
                    _entity_manager.entity_list[0].attack-=1;
                    _entity_manager.entity_list[0].healthBuffStatus=0;
                    _entity_manager.entity_list[0].maxHealth-=1;
                    _entity_manager.entity_list[0].speedDebuffStatus=0;
                    _entity_manager.entity_list[0].speed-=0.3;
                    _entity_manager.entity_list[0].speedBuffStatus=0;
                    _entity_manager.entity_list[0].speed-=0.3;
                    _entity_manager.entity_list[0].essence+=2;

                }


            }
            if(_entity_manager.entity_list[k].type==30 && _entity_manager.entity_list[j].type==7)
            {
                _entity_manager.entity_list[j].health-=_entity_manager.entity_list[k].attack;
                if(_entity_manager.entity_list[j].health<0)
                {
                    gfc_vector3d_add(_entity_manager.entity_list[j].position,_entity_manager.entity_list[j].position,gfc_vector3d(0,0,1000000));
                    _entity_manager.entity_list[0].roomNum=_entity_manager.entity_list[0].doorNum;
                    _entity_manager.entity_list[0].attackBuffStatus=0;
                    _entity_manager.entity_list[0].attack-=1;
                    _entity_manager.entity_list[0].attackDebuffStatus=0;
                    _entity_manager.entity_list[0].attack-=1;
                    _entity_manager.entity_list[0].healthBuffStatus=0;
                    _entity_manager.entity_list[0].maxHealth-=1;
                    _entity_manager.entity_list[0].speedDebuffStatus=0;
                    _entity_manager.entity_list[0].speed-=0.3;
                    _entity_manager.entity_list[0].speedBuffStatus=0;
                    _entity_manager.entity_list[0].speed-=0.3;
                    _entity_manager.entity_list[0].essence+=2;

                }


            }
        }}};

}
/*eol@eof*/
