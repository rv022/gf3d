#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "player.h"

void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);

Entity *player_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a player entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/dino.model"); /**<Entity's model if it has one.*/
    gfc_matrix4_identity(self->modelMat);/**<Entity's model mat.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/

    self->think = player_think;
    self->update = player_update;
    self->free = player_free;

    return self;
}

void player_think(Entity *self)
{
    if(!self)return;
}
void player_update(Entity *self)
{
    if(!self)return;
}
void player_free(Entity *self)
{
    if(!self)return;
}

/*eol@eof*/
