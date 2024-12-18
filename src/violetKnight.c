#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "violetKnight.h"

void violetKnight_think(Entity *self);
void violetKnight_update(Entity *self);
void violetKnight_free(Entity *self);

Entity *violetKnight_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a violetKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/violetKnight.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);


    self->think = violetKnight_think;
    self->update = violetKnight_update;
    self->free = violetKnight_free;


    return self;
}

void violetKnight_think(Entity *self)
{
    if(!self)return;
}
void violetKnight_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void violetKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
