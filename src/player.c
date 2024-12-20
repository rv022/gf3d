#include <SDL.h>

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gf3d_camera.h"
#include "entity.h"
#include "player.h"
#include "gf2d_font.h"

void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);
void player_collide(Entity *self);
int direction = 0;
int frontCollision = 0;
int leftCollision = 0;
int rightCollision = 0;
int backCollision = 0;
int anim = 0;

Entity *player_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn a player entity");
        return NULL;
    }
    self->model = gf3d_model_load("models/player.model"); /**<Entity's model if it has one.*/
    self->position = gfc_vector3d(0,0,0); /**<where entity will be drawn*/
    self->rotation = gfc_vector3d(0,0,0);
    self->scale = gfc_vector3d(1,1,1);
    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    self->doorNum = 10;
    self->roomNum = 10;
    self->health = 5;
    self->maxHealth=5;
    self->essence = 0;
    self->speed = 1;
    self->speedBuffStatus=0;
    self->speedDebuffStatus=0;
    self->attackBuffStatus=0;
    self->attackDebuffStatus=0;
    self->healthBuffStatus=0;
    self->attack=4;

    self->think = player_think;
    self->update = player_update;
    self->free = player_free;
    self->collide = player_collide;

    return self;
}

void player_think(Entity *self)
{
    if(!self)return;
}

void player_collide(Entity *self)
{
    slog("reached this");
    if(!self)return;
    slog("reached this");
    if(direction == 1)
    {
     frontCollision=1;
     gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,self->speed*-0.7,0));
    }
    else if(direction == 2)
    {
        backCollision =1;
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,self->speed*0.7,0));
    }
    else if(direction == 3)
    {
        rightCollision=1;
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(self->speed*-0.7,0,0));
    }
    else if(direction == 4)
    {
        leftCollision=1;
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(self->speed*0.7,0,0));
    }
}

void player_update(Entity *self)
{
    if(!self)return;
    if(self->health<0)
    {
        self->position = gfc_vector3d(0,0,0);
        self->health = 5;
    }

    self->body = gfc_box(self->position.x, self->position.y, self->position.z, 1.0f, 1.0f, 1.0f);
    GFC_Vector3D cameraPosition;
    gfc_vector3d_add(cameraPosition,self->position,gfc_vector3d(0,-15,15));
    gf3d_camera_set_position(cameraPosition);
    gf3d_camera_set_rotation(self->rotation);
    gf3d_camera_look_at(self->position, NULL);
    gf2d_font_draw_line_tag("Night Knight",FT_H1,GFC_COLOR_WHITE, gfc_vector2d(550,300));


    //Player controls
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W] && frontCollision==0)
    {
        /*GFC_Vector2D w; old movement
        GFC_Vector3D forward = {0};
        w = gfc_vector2d_from_angle(self->rotation.z);
        forward.x = w.x;
        forward.y = w.y;
        gfc_vector3d_set_magnitude(&forward,1);
        gfc_vector3d_add(self->position,self->position,forward);*/
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,0.7,0));
        direction = 1;
        backCollision=0;
        leftCollision=0;
        rightCollision=0;
    }
    if (keys[SDL_SCANCODE_S] && backCollision==0)
    {
        /*GFC_Vector2D w;
        GFC_Vector3D forward = {0};
        w = gfc_vector2d_from_angle(self->rotation.z);
        forward.x = w.x;
        forward.y = w.y;
        gfc_vector3d_set_magnitude(&forward,-1);
        gfc_vector3d_add(self->position,self->position,forward);*/
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(0,-0.7,0));
        direction = 2;
        frontCollision=0;
        leftCollision=0;
        rightCollision=0;
    }
    if (keys[SDL_SCANCODE_D] && rightCollision==0)
    {
        /*GFC_Vector2D w;
        GFC_Vector3D right = {0};
        w = gfc_vector2d_from_angle(self->rotation.z - GFC_HALF_PI);
        right.x = w.x;
        right.y = w.y;
        gfc_vector3d_set_magnitude(&right,1);
        gfc_vector3d_add(self->position,self->position,right);*/
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(0.7,0,0));
        direction = 3;
        backCollision=0;
        leftCollision=0;
        frontCollision=0;
    }
    if (keys[SDL_SCANCODE_A] && leftCollision==0)
    {
        /*GFC_Vector2D w;
        GFC_Vector3D right = {0};
        w = gfc_vector2d_from_angle(self->rotation.z - GFC_HALF_PI);
        right.x = w.x;
        right.y = w.y;
        gfc_vector3d_set_magnitude(&right,-1);
        gfc_vector3d_add(self->position,self->position,right);*/
        gfc_vector3d_add(self->position,self->position,gfc_vector3d(-0.7,0,0));
        direction = 4;
        backCollision=0;
        frontCollision=0;
        rightCollision=0;
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
