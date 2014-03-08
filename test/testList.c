#include <assert.h>
#include "list.h"

/* @TODO:
- destructor test
- free test - uses destructor? no leak?
*/

void testList()
{
    int insertableItem = 2;
    struct _ListItem* insertItem;

    struct _List* list = List_initialize(0);

    /* check for empty list */
    {
        int itemcount = 0;
        struct _ListItem* item = list->first;
        while(item != 0)
        {
            ++itemcount;
            item = item->next;
        }
        assert(itemcount == 0);
    }

    /* insert one item and check for existance */
    {
        int itemcount = 0;
        insertItem = list->func->pushBack(list, &insertableItem);
        struct _ListItem* item = list->first;
        while(item != 0)
        {
            ++itemcount;
            /* only one item -> so check */
            assert(item->previous == 0);
            assert(item->next == 0);

            /* check it's value */
            assert(item->data == &insertableItem);

            item = item->next;
        }
        assert(itemcount == 1);
    }

    /* remove item and check if list empty */
    {
        int itemcount = 0;
        list->func->erase(list, insertItem);
        struct _ListItem* item = list->first;
        while(item != 0)
        {
            ++itemcount;
            item = item->next;
        }

        /* pointers must be resetted */
        assert(list->first == 0);
        assert(list->last == 0);

        /* no item in list */
        assert(itemcount == 0);
    }

    list->func->free(list);
}
