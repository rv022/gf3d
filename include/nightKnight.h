#ifndef __NIGHTKNIGHT_H__
#define __NIGHTKNIGHT_H__

#include "entity.h"

/**
 * @brief spawn player
 * @return NULL on error, or pointer to player.
 */
Entity *nightKnight_new(GFC_Vector3D position, GFC_Vector3D rotation, int attack);

#endif
