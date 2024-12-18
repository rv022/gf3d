#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "nightKnight.h"

void nightKnight_think(Entity *self);
void nightKnight_update(Entity *self);
void nightKnight_collide(Entity*self);
void nightKnight_free(Entity *self);


Entity *nightKnight_new(GFC_Vector3D position, GFC_Vector3D rotation, int attack)
{
    Entity *self;
    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a nightKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/player.model"); /**<Entity's model if it has one.*/
    self->position = position; /**<where entity will be drawn*/
    self->rotation = rotation;
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 3.0f, 3.0f, 3.0f);
    self->type = 30;
    self->attack = attack;


    self->think = nightKnight_think;
    self->update = nightKnight_update;
    self->free = nightKnight_free;
    self->collide = nightKnight_collide;


    return self;
}

void nightKnight_think(Entity *self)
{
    if(!self)return;
}
void nightKnight_update(Entity *self)
{
    if(!self)return;
    GFC_Vector2D w;
    GFC_Vector3D forward = {0};
    w = gfc_vector2d_from_angle(self->rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    gfc_vector3d_set_magnitude(&forward,0.5);
    gfc_vector3d_add(self->position,self->position,forward);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    //need to keep bounding box moving
}
void nightKnight_collide(Entity *self)
{
    gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,0,90));
}
void nightKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
