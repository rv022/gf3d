#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "rightWall.h"

void rightWall_think(Entity *self);
void rightWall_update(Entity *self);
void rightWall_free(Entity *self);

Entity *rightWall_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a rightWall entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/rightWall.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box((self->position.x)+20, (self->position.y)-20, self->position.z, 1.0f, 40.0f, 1.0f);


    self->think = rightWall_think;
    self->update = rightWall_update;
    self->free = rightWall_free;


    return self;
}

void rightWall_think(Entity *self)
{
    if(!self)return;
}
void rightWall_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void rightWall_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/

