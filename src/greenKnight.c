#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "greenKnight.h"

void greenKnight_think(Entity *self);
void greenKnight_update(Entity *self);
void greenKnight_collide(Entity*self);
void greenKnight_free(Entity *self);

Entity *greenKnight_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a greenKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/greenKnight.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    self->type = 5;
    self->attack = 2;
    self->health = 10;


    self->think = greenKnight_think;
    self->update = greenKnight_update;
    self->collide = greenKnight_collide;
    self->free = greenKnight_free;


    return self;
}

void greenKnight_think(Entity *self)
{
    if(!self)return;
}
void greenKnight_update(Entity *self)
{
    if(!self)return;
    GFC_Vector2D w;
    GFC_Vector3D forward = {0};
    w = gfc_vector2d_from_angle(self->rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    gfc_vector3d_set_magnitude(&forward,0.6);
    gfc_vector3d_add(self->position,self->position,forward);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    //need to keep bounding box moving
}
void greenKnight_collide(Entity *self)
{
    gfc_vector3d_add(self->rotation,self->rotation,gfc_vector3d(0,0,270));
}
void greenKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
