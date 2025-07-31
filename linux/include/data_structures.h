#ifndef __DATA_STRUCTURES__
#define __DATA_STRUCTURES__


#define LONG_ROOM_LENGTH 64
#define SHORT_ROOM_LENGTH 32
#define TICK 60
#define MAX_RAIN 100

#include <string.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} coordinates;

typedef struct {
	coordinates rain_cords;
	int not_hit;
} rain_drops;

typedef struct room_node room_node;

struct room_node {
	char **matrix;
	int width;
	int height;
	int event;
	coordinates *exit;
	coordinates *entrance;
	room_node *next;
};

typedef struct {
	room_node *head;
	room_node *tail;
} room_list;

#endif