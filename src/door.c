#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "door.h"

void door_think(Entity *self);
void door_update(Entity *self);
void door_free(Entity *self);

Entity *door_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a door entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/door.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, 10000, 1.0f, 1.0f, 1.0f);


    self->think = door_think;
    self->update = door_update;
    self->free = door_free;


    return self;
}

void door_think(Entity *self)
{
    if(!self)return;
}
void door_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void door_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/

