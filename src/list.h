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
    struct _ListItem* first;
    struct _ListItem* last;
};

/* --- METHODS --- */

struct _ListItem_Functions {
    void (*free)(struct _ListItem* list);
};
extern struct _ListItem_Functions _ListItem_Functions;

struct _List_Functions {
    void (*free)(struct _List* list);
};
extern struct _List_Functions List_Functions;

/* --- FUNCTIONS --- */

struct _ListItem* ListItem_initialize();
void ListItem_free(struct _ListItem* list);

struct _List* List_initialize();
void List_free(struct _List* list);

#endif /* LIST_H_INCLUDED */
