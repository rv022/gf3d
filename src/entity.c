#include "simple_logger.h"
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
    }

}

/*eol@eof*/
