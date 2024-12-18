#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "chest.h"

void chest_think(Entity *self);
void chest_update(Entity *self);
void chest_free(Entity *self);

Entity *chest_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a chest entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/chest.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    self->type = 1;


    self->think = chest_think;
    self->update = chest_update;
    self->free = chest_free;


    return self;
}

void chest_think(Entity *self)
{
    if(!self)return;
}
void chest_update(Entity *self)
{
    if(!self)return;
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    //need to keep bounding box moving
}
void chest_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
