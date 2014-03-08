#include "list.h"

struct _ListItem_Functions _ListItem_Functions = {
    .free = ListItem_free
};

struct _List_Functions List_Functions = {
    .free = List_free
};

struct _List* List_initialize()
{
    return 0;
}

void List_free(struct _List* list)
{

}
