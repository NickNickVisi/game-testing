#include "../include/gameplay.h"

unsigned current_time(void)
{
	struct timespec ts;
	clock_gettime(1, &ts);
	return (ts.tv_sec * 1000UL) + (ts.tv_nsec / 1000000UL);
}

void spawn_rain(int width, rain_drops *rain)
{
	for (int i = 0; i < MAX_RAIN; i++) {
		if (!rain[i].not_hit) {
			rain[i].rain_cords.x = rand() % width - 1;
			if (!rain[i].rain_cords.x)
				rain[i].rain_cords.x = 1;
			rain[i].rain_cords.y = 2;
			rain[i].not_hit = 1;
			break;
		}
	}
}

void update_rain(room_node *room, rain_drops *rain) {
	spawn_rain(room->width, rain);
	for (int i = 0; i < MAX_RAIN; i++) {
		if (rain[i].not_hit) {
			int x = rain[i].rain_cords.x;
			int y = rain[i].rain_cords.y;
			mvaddch(y, x, room->matrix[y - 1][x]);
			y = ++rain[i].rain_cords.y;
			x = --rain[i].rain_cords.x;
			if (y >= 10 || x == 0 || room->matrix[y - 1][x] == 'o')
				rain[i].not_hit = 0;
			else
				mvaddch(y, x, '/');
		}
	}
}

void flashlight(coordinates *p, room_node *room, int x, int y, int radius)
{
	if (!radius || x < 0 || y < 0 || y >= 10 || x >= room->width)
		return;
	int dx = x - p->x;
	int dy = y - p->y;
	int sqr_distance = dx * dx + dy * dy;
	int sqr_rad = radius * radius;

	if (sqr_distance > sqr_rad) 
		mvaddch(y + 1, x, '#');
	else
		mvaddch(y + 1, x, room->matrix[y][x]);

	flashlight(p, room, x + 1, y, radius - 1);
	flashlight(p, room, x, y + 1, radius - 1);
	flashlight(p, room, x - 1, y, radius - 1);
	flashlight(p, room, x, y - 1, radius - 1);
}
