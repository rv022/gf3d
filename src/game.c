#include <SDL.h>            

#include "simple_json.h"
#include "simple_logger.h"

#include "gfc_input.h"
#include "gfc_config_def.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gfc_audio.h"
#include "gfc_string.h"
#include "gfc_actions.h"

#include "gf2d_sprite.h"
#include "gf2d_font.h"
#include "gf2d_draw.h"
#include "gf2d_actor.h"
#include "gf2d_mouse.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_draw.h"
#include "entity.h"
#include "player.h"
#include "orangeKnight.h"

extern int __DEBUG;

static int _done = 0;
static Uint32 frame_delay = 33;
static float fps = 0;

void parse_arguments(int argc,char *argv[]);
void game_frame_delay();

void exitGame()
{
    _done = 1;
}

void make_dungeon()
{
    Entity *backWall, *throne, *door, *frontRightWall, *frontLeftWall, *leftWall, *rightWall, *floor;
    backWall = backWall_new(0);
    floor = floor_new(0);
    throne = throne_new();
    leftWall = leftWall_new(0);
    rightWall = rightWall_new(0);
    frontLeftWall = frontLeftWall_new(0);
    frontRightWall = frontRightWall_new(0);
    door = door_new(0);

    floor = floor_new(40);
    leftWall = leftWall_new(40);
    rightWall = rightWall_new(40);
    frontLeftWall = frontLeftWall_new(40);
    frontRightWall = frontRightWall_new(40);
    door = door_new(40);

    floor = floor_new(80);
    leftWall = leftWall_new(80);
    rightWall = rightWall_new(80);
    frontLeftWall = frontLeftWall_new(80);
    frontRightWall = frontRightWall_new(80);
    door = door_new(80);

    floor = floor_new(120);
    leftWall = leftWall_new(120);
    rightWall = rightWall_new(120);
    frontLeftWall = frontLeftWall_new(120);
    frontRightWall = frontRightWall_new(120);
    door = door_new(120);

    floor = floor_new(160);
    leftWall = leftWall_new(160);
    rightWall = rightWall_new(160);
    frontLeftWall = frontLeftWall_new(160);
    frontRightWall = frontRightWall_new(160);
    door = door_new(160);


    backWall = backWall_new(240);
    floor = floor_new(200);
    leftWall = leftWall_new(200);
    rightWall = rightWall_new(200);
}

void draw_origin()
{
    gf3d_draw_edge_3d(
        gfc_edge3d_from_vectors(gfc_vector3d(-100,0,0),gfc_vector3d(100,0,0)),
        gfc_vector3d(0,0,0),gfc_vector3d(0,0,0),gfc_vector3d(1,1,1),0.1,gfc_color(1,0,0,1));
    gf3d_draw_edge_3d(
        gfc_edge3d_from_vectors(gfc_vector3d(0,-100,0),gfc_vector3d(0,100,0)),
        gfc_vector3d(0,0,0),gfc_vector3d(0,0,0),gfc_vector3d(1,1,1),0.1,gfc_color(0,1,0,1));
    gf3d_draw_edge_3d(
        gfc_edge3d_from_vectors(gfc_vector3d(0,0,-100),gfc_vector3d(0,0,100)),
        gfc_vector3d(0,0,0),gfc_vector3d(0,0,0),gfc_vector3d(1,1,1),0.1,gfc_color(0,0,1,1));
}


int main(int argc,char *argv[])
{
    //local variables
    Model *sky,*dino;
    GFC_Matrix4 skyMat,dinoMat;
    Entity *player, *orangeKnight, *backWall, *throne, *door, *frontRightWall, *frontLeftWall, *leftWall, *rightWall, *floor;
    GFC_Rect screenTest, square1,square2,square3,square4,square5;
    int mainMenuOn = 0;
    int buildMenuOn = 0;
    const Uint8 * keys;

    //initializtion    
    parse_arguments(argc,argv);
    init_logger("gf3d.log",0);
    slog("gf3d begin");
    //gfc init
    gfc_input_init("config/input.cfg");
    gfc_config_def_init();
    gfc_action_init(1024);
    //gf3d init
    gf3d_vgraphics_init("config/setup.cfg");
    gf3d_materials_init();
    gf2d_font_init("config/font.cfg");
    gf2d_actor_init(1000);
    gf3d_draw_init();//3D
    gf2d_draw_manager_init(1000);//2D
    entity_system_initialize(1024);
    
    //game init
    srand(SDL_GetTicks());
    slog_sync();

    //game setup
    screenTest = gfc_rect(0, 0, 10000.0, 10000.0);
    square1 = gfc_rect(400,300,50,50);
    square2 = gfc_rect(500,300,50,50);
    square3 = gfc_rect(600,300,50,50);
    square4 = gfc_rect(700,300,50,50);
    square5 = gfc_rect(800,300,50,50);
    keys = SDL_GetKeyboardState(NULL);
    gf2d_mouse_load("actors/mouse.actor");
    sky = gf3d_model_load("models/sky.model");
    gfc_matrix4_identity(skyMat);
    dino = gf3d_model_load("models/dino.model");
    gfc_matrix4_identity(dinoMat);
    player = player_new();
    orangeKnight = orangeKnight_new(0);
    make_dungeon();



        //camera
    gf3d_camera_set_scale(gfc_vector3d(1,1,1));
    gf3d_camera_set_position(gfc_vector3d(15,-15,10));
    gf3d_camera_look_at(gfc_vector3d(0,0,0),NULL);
    gf3d_camera_set_move_step(0.2);
    gf3d_camera_set_rotate_step(0.05);
    
    gf3d_camera_enable_free_look(1);
    //windows

    // main game loop    
    while(!_done)
    {
        gfc_input_update();
        gf2d_mouse_update();
        gf2d_font_update();
        //camera updaes
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        entity_system_think();
        entity_system_update();
        entity_system_collide();

        gf3d_vgraphics_render_start();
        if (keys[SDL_SCANCODE_O])
        {
           mainMenuOn=1;
        }
        if (keys[SDL_SCANCODE_P])
        {
            buildMenuOn=1;
        }

            //3D draws
        
                gf3d_model_draw_sky(sky,skyMat,GFC_COLOR_WHITE);


                entity_system_draw();
/*
                gf3d_model_draw(
                    dino,
                    dinoMat,
                    GFC_COLOR_WHITE,
                    0);
*/
                    //draw_origin();
            //2D draws
                if(mainMenuOn==0)
                {
                    gf2d_draw_rect_filled(screenTest,GFC_COLOR_BLACK);
                    gf2d_font_draw_line_tag("Night Knight",FT_H1,GFC_COLOR_WHITE, gfc_vector2d(550,300));
                }
                if(buildMenuOn==1)
                {
                    gf2d_draw_rect_filled(screenTest,GFC_COLOR_BLACK);
                    gf2d_font_draw_line_tag("Train of Thought",FT_H1,GFC_COLOR_WHITE, gfc_vector2d(100,300));
                    gf2d_draw_rect(square1,GFC_COLOR_WHITE);
                    gf2d_draw_rect(square2,GFC_COLOR_WHITE);
                    gf2d_draw_rect(square3,GFC_COLOR_WHITE);
                    gf2d_draw_rect(square4,GFC_COLOR_WHITE);
                    gf2d_draw_rect(square5,GFC_COLOR_WHITE);
                }
                //gf2d_mouse_draw();
        gf3d_vgraphics_render_end();
        if (gfc_input_command_down("exit"))_done = 1; // exit condition
        game_frame_delay();
    }    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    entity_free(player);
    slog("gf3d program end");
    exit(0);
    slog_sync();
    return 0;
}

void parse_arguments(int argc,char *argv[])
{
    int a;

    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"--debug") == 0)
        {
            __DEBUG = 1;
        }
    }    
}

void game_frame_delay()
{
    Uint32 diff;
    static Uint32 now;
    static Uint32 then;
    then = now;
    slog_sync();// make sure logs get written when we have time to write it
    now = SDL_GetTicks();
    diff = (now - then);
    if (diff < frame_delay)
    {
        SDL_Delay(frame_delay - diff);
    }
    fps = 1000.0/MAX(SDL_GetTicks() - then,0.001);
//     slog("fps: %f",fps);
}
/*eol@eof*/
