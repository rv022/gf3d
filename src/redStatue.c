#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "redStatue.h"

void redStatue_think(Entity *self);
void redStatue_update(Entity *self);
void redStatue_free(Entity *self);

Entity *redStatue_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a redStatue entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/redStatue.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);


    self->think = redStatue_think;
    self->update = redStatue_update;
    self->free = redStatue_free;


    return self;
}

void redStatue_think(Entity *self)
{
    if(!self)return;
}
void redStatue_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void redStatue_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
