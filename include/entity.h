#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gf3d_model.h"

typedef struct Entity_S
{
    uint8 _inuse; /**<Flag for keeping track of memory usage*/
    Model *model; /**<Entity's model if it has one.*/
    Vector3D position; /**<where entity will be drawn*/
    void (think*)(struct Entity_S *self);
    void (update*)(struct Entity_S *self);
    void (free*)(struct Entity_S *self);
    void *data;
}Entity;

void entity_system_initialize(Uint32 max);

void entity_clear_all(Entity *ignore);

Entity *entity_new();

void entity_free(Entity *self);

void entity_system_think();

void entity_system_update();

void entity_system_draw();


#endif
