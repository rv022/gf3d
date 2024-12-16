#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "entity.h"
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
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);


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
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    GFC_Vector3D cameraPosition;
    gfc_vector3d_add(cameraPosition,self->position,gfc_vector3d(0,-15,15));
    gf3d_camera_set_position(cameraPosition);
    gf3d_camera_set_rotation(self->rotation);
    gf3d_camera_look_at(self->position, NULL);


    //Player controls
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W])
    {
        GFC_Vector2D w;
        GFC_Vector3D forward = {0};
        w = gfc_vector2d_from_angle(self->rotation.z);
        forward.x = w.x;
        forward.y = w.y;
        gfc_vector3d_set_magnitude(&forward,1);
        gfc_vector3d_add(self->position,self->position,forward);
    }
    if (keys[SDL_SCANCODE_S])
    {
        GFC_Vector2D w;
        GFC_Vector3D forward = {0};
        w = gfc_vector2d_from_angle(self->rotation.z);
        forward.x = w.x;
        forward.y = w.y;
        gfc_vector3d_set_magnitude(&forward,-1);
        gfc_vector3d_add(self->position,self->position,forward);
    }
    if (keys[SDL_SCANCODE_D])
    {
        GFC_Vector2D w;
        GFC_Vector3D right = {0};
        w = gfc_vector2d_from_angle(self->rotation.z - GFC_HALF_PI);
        right.x = w.x;
        right.y = w.y;
        gfc_vector3d_set_magnitude(&right,1);
        gfc_vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_A])
    {
        GFC_Vector2D w;
        GFC_Vector3D right = {0};
        w = gfc_vector2d_from_angle(self->rotation.z - GFC_HALF_PI);
        right.x = w.x;
        right.y = w.y;
        gfc_vector3d_set_magnitude(&right,-1);
        gfc_vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_RIGHT])gfc_vector3d_add(self->rotation,self->rotation,gfc_vector3d(0,0,-0.1));
    if (keys[SDL_SCANCODE_LEFT])gfc_vector3d_add(self->rotation,self->rotation,gfc_vector3d(0,0,0.1));

}
void player_free(Entity *self)
{
    if(!self)return;
}

void player_move(Entity *self, GFC_Vector3D translation)
{
    gfc_vector3d_sub(self->position,self->position,translation);
}

void player_walk_forward(Entity *self, float magnitude)
{
    GFC_Vector2D w;
    GFC_Vector3D forward = {0};
    w = gfc_vector2d_from_angle(-(self->rotation.z));
    forward.x = w.x;
    forward.y = w.y;
    gfc_vector3d_set_magnitude(&forward,magnitude);
    player_move(self,forward);

}

void player_walk_right(Entity *self, float magnitude)
{
    GFC_Vector2D w;
    GFC_Vector3D right = {0};
    w = gfc_vector2d_from_angle(-self->rotation.z - GFC_HALF_PI);
    right.x = w.x;
    right.y = w.y;
    gfc_vector3d_set_magnitude(&right,magnitude);
    player_move(self,right);

}
/*eol@eof*/
