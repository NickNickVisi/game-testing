#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include "data_structures.h"
#include "ds_init_free.h"
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

unsigned current_time(void);

void spawn_rain(int width, rain_drops *rain);

void update_rain(room_node *room, rain_drops *rain);

void flashlight(coordinates *p, room_node *room, int x, int y, int radius);

#endif