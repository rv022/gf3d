#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "indigoKnight.h"

void indigoKnight_think(Entity *self);
void indigoKnight_update(Entity *self);
void indigoKnight_free(Entity *self);

Entity *indigoKnight_new(int y)
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a indigoKnight entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/indigoKnight.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,5+y,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);


    self->think = indigoKnight_think;
    self->update = indigoKnight_update;
    self->free = indigoKnight_free;


    return self;
}

void indigoKnight_think(Entity *self)
{
    if(!self)return;
}
void indigoKnight_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
}
void indigoKnight_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
