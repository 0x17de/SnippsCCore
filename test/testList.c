#include <assert.h>
#include "list.h"

static void testList_1()
{
    int insertableItem = 2;
    struct _ListItem* insertItem;

    struct _List* list = List_initialize(0);
    assert(list != 0);

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

static void testList_2_destructor(void* data)
{
    *(int*)data -= 1;
}

static void testList_2()
{
    /* the destructor decrements the value */
    int useCount = 1;

    struct _List* list = List_initialize(testList_2_destructor);
    list->func->pushBack(list, &useCount);
    list->func->free(list);

    assert(useCount == 0);
}

void testList()
{
    testList_1();
    testList_2();
}
