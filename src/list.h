#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/* --- STRUCTS --- */

struct _ListItem_Functions;
struct _ListItem {
    const struct _ListItem_Functions* func;

    void* data;
    struct _ListItem* previous;
    struct _ListItem* next;
};

struct _List_Functions;
struct _List {
    const struct _List_Functions* func;

    struct _ListItem* first;
    struct _ListItem* last;
    void (*itemDataDestructor)(void* item);
};

/* --- METHODS --- */

struct _ListItem_Functions {
    void (*free)(struct _ListItem* item, void (*itemDataDestructor)(void*));
};
extern struct _ListItem_Functions _ListItem_Functions;

struct _List_Functions {
    void (*free)(struct _List* list);
    struct _ListItem* (*pushBack)(struct _List* list, void* data);
    struct _ListItem* (*erase)(struct _List* list, struct _ListItem* item);
};
extern struct _List_Functions List_Functions;

/* --- FUNCTIONS --- */

struct _ListItem* ListItem_initialize(void* data);
void ListItem_free(struct _ListItem* item, void (*itemDataDestructor)(void*));


struct _List* List_initialize(void (*itemDataDestructor)(void*));
void List_free(struct _List* list);

struct _ListItem* List_pushBack(struct _List* list, void* data);
struct _ListItem* List_erase(struct _List* list, struct _ListItem* item);

#endif /* LIST_H_INCLUDED */
