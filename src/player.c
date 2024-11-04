#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
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
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);


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
    GFC_Vector3D cameraPosition;
    gfc_vector3d_add(cameraPosition,self->position,gfc_vector3d(0,-25,25));
    gf3d_camera_set_position(cameraPosition);
    gf3d_camera_look_at(self->position, NULL);
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W])
    {
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,1,0));
    }
    if (keys[SDL_SCANCODE_S])
    {
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,-1,0));
    }
    if (keys[SDL_SCANCODE_D])
    {
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(1,0,0));
    }
    if (keys[SDL_SCANCODE_A])
    {
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(-1,0,0));
    }

}
void player_free(Entity *self)
{
    if(!self)return;
}

/*eol@eof*/
