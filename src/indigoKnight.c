#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "indigoKnight.h"

void indigoKnight_think(Entity *self);
void indigoKnight_update(Entity *self);
void indigoKnight_collide(Entity*self);
void indigoKnight_free(Entity *self);

Entity *indigoKnight_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a indigoKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/indigoKnight.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    self->type = 5;
    self->attack = 1;
    self->health = 10;


    self->think = indigoKnight_think;
    self->update = indigoKnight_update;
    self->collide = indigoKnight_collide;
    self->free = indigoKnight_free;


    return self;
}

void indigoKnight_think(Entity *self)
{
    if(!self)return;
}
void indigoKnight_update(Entity *self)
{
    if(!self)return;
    GFC_Vector2D w;
    GFC_Vector3D forward = {0};
    w = gfc_vector2d_from_angle(self->rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    gfc_vector3d_set_magnitude(&forward,0.7);
    gfc_vector3d_add(self->position,self->position,forward);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    //need to keep bounding box moving
}
void indigoKnight_collide(Entity *self)
{
    gfc_vector3d_add(self->rotation,self->rotation,gfc_vector3d(0,0,180));
}
void indigoKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
