#include "../include/data_structures.h"
#include "../include/gameplay.h"
#include "../include/ds_init_free.h"

// has_colors(); useful

/*
IDEAS:
Same chase mechanics yet better room generating by using some pathfinder algorithm
Code guesser with 4 exits


*/

typedef struct a_star_node a_star_node;

struct a_star_node {
	int x, y;
	/* f is total cost(g + h), g is the cost from start, h is heuristic */
	int f, g, h;
	a_star_node *parent;
	int is_obstacle;
	int is_open_list;
	int is_closed_list;
};

static int abs_val(int x)
{
	if (x < 0)
		return -x;
	return x;
}

static int heuristic(a_star_node *a, a_star_node *b)
{
	return abs_val(a->x - a->y) + abs_val(b->x - b->y);
}



// attempted A* implementation
static void update_chase(coordinates *player, coordinates *enemy, room_node *room)
{
	
}

// Break up into more functions
int main(void)
{
	coordinates *p = malloc(sizeof(coordinates));
	coordinates *enemy = malloc(sizeof(coordinates));
	enemy->y = 5;

	initscr();
	nodelay(stdscr, TRUE);
	noecho();
	cbreak();
	curs_set(0);
	srand(time(0));
	int counter = 0;
	unsigned long last_tick = current_time();
	char command = '\0';
	room_list *list = generate_list();

	printw("%d\n", counter);
	if (list->head->event != 3) {
		for (int i = 0; i < list->head->height; i++) {
			for (int j = 0; j < list->head->width; j++)
				addch(list->head->matrix[i][j]);
			addch('\n');
		}
	} else {
		for (int i = 0; i < list->head->height; i++) {
			for (int j = 0; j < list->head->width; j++)
				addch('#');
			addch('\n');
		}
	}
	p->x = list->head->entrance->x;
	p->y = list->head->entrance->y;
	mvaddch(p->y + 1, p->x, 'o');
	refresh();
	int running = 1;
	rain_drops *rain = malloc(sizeof(rain_drops) * MAX_RAIN);

	while(running && command != 'q')
	{
		enemy->x = list->head->width - 2;
		unsigned long now = current_time();
		command = getch();
		
		if (command != -1) {
			mvaddch(p->y + 1, p->x, ' ');
			list->head->matrix[p->y][p->x] = ' ';
			switch(command)
			{
				case 'w': {
					if (p->y - 1 > 0 && list->head->matrix[p->y - 1][p->x] != '#')
						p->y--;
					break;
				}
				case 's': {
					if (p->y + 1 < 10 && list->head->matrix[p->y + 1][p->x] != '#')
						p->y++;
					break;
				}
				case 'a': {
					if (p->x > 0 && list->head->matrix[p->y][p->x - 1] != '#')
						p->x--;
					break;
				}
				case 'd': {
					if (p->x < list->head->width - 1 && list->head->matrix[p->y][p->x + 1] != '#')
						p->x++;
					break;
				}
			}
			if (list->head->event == 3) {
				flashlight(p, list->head, p->x, p->y, 4);
			}
			list->head->matrix[p->y][p->x] = 'o';
			mvaddch(p->y + 1, p->x, 'o');
		}
		if (now - last_tick >= TICK) {
			last_tick = now;
			if (list->head->event == 2) {
				update_rain(list->head, rain);
			}
			// update_chase(p, enemy, list->head);
		}
		if (p->x == list->head->exit->x && p->y == list->head->exit->y) {
			room_node *delete = list->head;

			if (list->head->next) {
				list->head = list->head->next;
				free_list_node(delete);
			}
			if (!(counter % 5)) {
				free_list(list);
				list = generate_list();
			}
			for (int i = 0; i < MAX_RAIN; i++) {
				rain[i].not_hit = 0;
			}
			clear();
			counter++;
			printw("%d\n", counter);
			if (list->head->event != 3) {
				for (int i = 0; i < list->head->height; i++) {
					for (int j = 0; j < list->head->width; j++)
						addch(list->head->matrix[i][j]);
					addch('\n');
				}
			} else {
				for (int i = 0; i < list->head->height; i++) {
					for (int j = 0; j < list->head->width; j++)
						addch('#');
					addch('\n');
				}
			}
			p->x = list->head->entrance->x;
			p->y = list->head->entrance->y;
			mvaddch(p->y + 1, p->x, 'o');
		}
		refresh();
		// give processor a break
		usleep(1000);
	}
	free(p);
	free_list(list);
	endwin();
}
