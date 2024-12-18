#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "orangeKnight.h"

void orangeKnight_think(Entity *self);
void orangeKnight_update(Entity *self);
void orangeKnight_free(Entity *self);

Entity *orangeKnight_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a orangeKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/orangeKnight.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);


    self->think = orangeKnight_think;
    self->update = orangeKnight_update;
    self->free = orangeKnight_free;


    return self;
}

void orangeKnight_think(Entity *self)
{
    if(!self)return;
}
void orangeKnight_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void orangeKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
