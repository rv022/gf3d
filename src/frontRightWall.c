#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "frontRightWall.h"

void frontRightWall_think(Entity *self);
void frontRightWall_update(Entity *self);
void frontRightWall_free(Entity *self);

Entity *frontRightWall_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a frontRightWall entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/frontRightWall.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box((self->position.x)+6, (self->position.y)+20, self->position.z, 16.0f, 1.0f, 1.0f);


    self->think = frontRightWall_think;
    self->update = frontRightWall_update;
    self->free = frontRightWall_free;


    return self;
}

void frontRightWall_think(Entity *self)
{
    if(!self)return;
}
void frontRightWall_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void frontRightWall_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
