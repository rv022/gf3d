#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "leftWall.h"

void leftWall_think(Entity *self);
void leftWall_update(Entity *self);
void leftWall_free(Entity *self);

Entity *leftWall_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a leftWall entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/leftWall.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box((self->position.x)-20, (self->position.y)-20, self->position.z, 3.0f, 40.0f, 3.0f);


    self->think = leftWall_think;
    self->update = leftWall_update;
    self->free = leftWall_free;


    return self;
}

void leftWall_think(Entity *self)
{
    if(!self)return;
}
void leftWall_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void leftWall_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/

