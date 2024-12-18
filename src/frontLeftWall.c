#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "frontLeftWall.h"

void frontLeftWall_think(Entity *self);
void frontLeftWall_update(Entity *self);
void frontLeftWall_free(Entity *self);

Entity *frontLeftWall_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a frontLeftWall entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/frontLeftWall.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box((self->position.x)-22, (self->position.y)+20, self->position.z, 16.0f, 3.0f, 3.0f);


    self->think = frontLeftWall_think;
    self->update = frontLeftWall_update;
    self->free = frontLeftWall_free;


    return self;
}

void frontLeftWall_think(Entity *self)
{
    if(!self)return;
}
void frontLeftWall_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void frontLeftWall_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/

