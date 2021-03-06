#ifndef CATEGORYWATCHER_H_INCLUDED
#define CATEGORYWATCHER_H_INCLUDED

/* --- STRUCTS --- */

struct _ListItem;

struct _Category;
struct _CategoryWatcherHandle {
    struct _CategoryWatcherHandle_Functions* func;

    struct _ListItem* item;
    void(*callback)(int type, struct _Category* category, void* userdefined);
    void* userdefined;
};

/* --- METHODS --- */

struct _CategoryWatcherHandle_Functions {
    void (*free)(struct _CategoryWatcherHandle* handle);
};

/* --- FUNCTIONS --- */

struct _CategoryWatcherHandle* CategoryWatcherHandle_initialize(void(*callback)(int type, struct _Category* category, void* userdefined), void* userdefined);
void CategoryWatcherHandle_free(struct _CategoryWatcherHandle* handle);

#endif /* CATEGORYWATCHER_H_INCLUDED */
