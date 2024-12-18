#ifndef __REDKNIGHT_H__
#define __REDKNIGHT_H__

#include "entity.h"

/**
 * @brief spawn player
 * @return NULL on error, or pointer to player.
 */
Entity *redKnight_new(int y);

#endif
