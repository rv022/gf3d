#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "enemy.h"

void enemy_think(Entity *self);
void enemy_update(Entity *self);
void enemy_free(Entity *self);

Entity *enemy_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a enemy entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/dino.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,10,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,110);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 2.0f, 2.0f, 2.0f);


    self->think = enemy_think;
    self->update = enemy_update;
    self->free = enemy_free;


    return self;
}

void enemy_think(Entity *self)
{
    if(!self)return;
}
void enemy_update(Entity *self)
{
    if(!self)return;
    //need to keep bounding box moving
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
}
void enemy_free(Entity *self)
{
    if(!self)return;
}


/*eol@eof*/
