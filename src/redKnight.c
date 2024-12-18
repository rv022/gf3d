#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "redKnight.h"

void redKnight_think(Entity *self);
void redKnight_update(Entity *self);
void redKnight_collide(Entity*self);
void redKnight_free(Entity *self);

Entity *redKnight_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a redKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/redKnight.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 2.0f, 1.0f, 1.0f);
    self->type = 6;
    self->attack = 4;
    self->health = 30;


    self->think = redKnight_think;
    self->update = redKnight_update;
    self->collide = redKnight_collide;
    self->free = redKnight_free;


    return self;
}

void redKnight_think(Entity *self)
{
    if(!self)return;
}
void redKnight_update(Entity *self)
{
    if(!self)return;
    GFC_Vector2D w;
    GFC_Vector3D forward = {0};
    w = gfc_vector2d_from_angle(self->rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    gfc_vector3d_set_magnitude(&forward,0.1);
    gfc_vector3d_add(self->position,self->position,forward);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 2.0f, 1.0f, 1.0f);
    //need to keep bounding box moving
}
void redKnight_collide(Entity *self)
{
    gfc_vector3d_add(self->rotation,self->rotation,gfc_vector3d(0,0,90));
}
void redKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
