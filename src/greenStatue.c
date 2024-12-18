#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "greenStatue.h"

void greenStatue_think(Entity *self);
void greenStatue_update(Entity *self);
void greenStatue_free(Entity *self);

Entity *greenStatue_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a greenStatue entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/greenStatue.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    self->type = 3;
    self->attack = 1;


    self->think = greenStatue_think;
    self->update = greenStatue_update;
    self->free = greenStatue_free;


    return self;
}

void greenStatue_think(Entity *self)
{
    if(!self)return;
}
void greenStatue_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void greenStatue_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
