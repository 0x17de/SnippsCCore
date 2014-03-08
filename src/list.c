#include <stdlib.h>
#include "list.h"

struct _ListItem_Functions ListItem_Functions = {
    .free = ListItem_free
};

struct _List_Functions List_Functions = {
    .free = List_free,
    .pushBack = List_pushBack,
    .erase = List_erase
};

struct _ListItem* ListItem_initialize(void* data)
{
    struct _ListItem* item = malloc(sizeof(struct _ListItem));
    item->func = &ListItem_Functions;

    item->data = data;

    return item;
}

void ListItem_free(struct _ListItem* item, void (*itemDataDestructor)(void*))
{
    if (itemDataDestructor)
        itemDataDestructor(item->data);

    free(item);
}

struct _List* List_initialize(void (*itemDataDestructor)(void*))
{
    struct _List* list = malloc(sizeof(struct _List));
    list->func = &List_Functions;

    list->first = 0;
    list->last = 0;
    list->itemDataDestructor = itemDataDestructor;

    return list;
}

void List_free(struct _List* list)
{
    struct _ListItem* item = list->first;

    /* free each element with provided destructor */
    while (item != 0)
    {
        struct _ListItem* next = item->next;
        item->func->free(item, list->itemDataDestructor);
        item = next;
    }

    free(list);
}

struct _ListItem* List_pushBack(struct _List* list, void* data)
{
    struct _ListItem* item = ListItem_initialize(data);

    /* if list empty set as first */
    if (!list->first)
    {
        list->first = item;
    }
    /* append if not empty and set as last item */
    if (!list->last)
    {
        list->last = item;
    }
    else
    {
        list->last->next = item;
        list->last = item;
    }

    return item;
}

struct _ListItem* List_erase(struct _List* list, struct _ListItem* item)
{
    struct _ListItem* previous = item->previous;
    struct _ListItem* next = item->next;

    /* adjust previous or first item */
    if (list->first == item)
    {
        list->first = next;
    }
    else
    {
        previous->next = next;
    }
    /* adjust last or next item */
    if (list->last == item)
    {
        list->last = previous;
    }
    else
    {
        next->previous = previous;
    }

    /* cleanup memory */
    item->func->free(item, list->itemDataDestructor);

    return next;
}
