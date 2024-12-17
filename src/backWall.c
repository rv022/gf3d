#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "backWall.h"

void backWall_think(Entity *self);
void backWall_update(Entity *self);
void backWall_free(Entity *self);

Entity *backWall_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a backWall entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/backWall.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box((self->position.x)-22, (self->position.y)-18, self->position.z, 44.0f, 1.0f, 1.0f);

    self->think = backWall_think;
    self->update = backWall_update;
    self->free = backWall_free;


    return self;
}

void backWall_think(Entity *self)
{
    if(!self)return;
}
void backWall_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void backWall_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
