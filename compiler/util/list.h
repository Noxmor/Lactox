#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct List
{
	void** items;
	size_t item_size;
	size_t size;
} List;

List* list_create(size_t item_size);
void list_add(List* list, void* item);

#endif