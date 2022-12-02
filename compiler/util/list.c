#include "list.h"

#include <stdlib.h>

List* list_create(size_t item_size)
{
	List* list = malloc(1 * sizeof(List));
	list->item_size = item_size;
	list->size = 0;
	list->items = NULL;
	return list;
}

void list_realloc(List* list)
{
	list->items = list->items == NULL ? calloc(list->size, list->item_size) : realloc(list->items, list->size * list->item_size);
}

void list_add(List* list, void* item)
{
	list->size += 1;
	list_realloc(list);
	list->items[list->size] = item;
}