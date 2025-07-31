#ifndef __DS_HELPERS__
#define __DS_HELPERS__

#include "data_structures.h"

room_node *init_room(void);

room_list *generate_list(void);

void free_list_node(room_node *room);

void free_list(room_list *list);

#endif