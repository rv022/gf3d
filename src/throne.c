#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "throne.h"

void throne_think(Entity *self);
void throne_update(Entity *self);
void throne_free(Entity *self);

Entity *throne_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a throne entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/throne.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box((self->position.x)-5, (self->position.y)-17, self->position.z, 11.0f, 2.0f, 2.0f);
    self->type=20;


    self->think = throne_think;
    self->update = throne_update;
    self->free = throne_free;


    return self;
}

void throne_think(Entity *self)
{
    if(!self)return;
}
void throne_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void throne_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
