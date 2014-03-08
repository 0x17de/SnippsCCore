#ifndef SNIPPSDB_H_INCLUDED
#define SNIPPSDB_H_INCLUDED

#include <sqlite3.h>

/* --- STRUCTS --- */

struct _SnippsDB {
    const struct _SnippsDB_Functions* func;

    sqlite3* db;
    struct _List* categoryWatchers;
};

/* --- METHODS --- */

struct _CategoryWatcherHandle;
struct _SnippsDB_Functions {
    void (*free)(struct _SnippsDB* db);
    struct _List* (*getCategoryList)(struct _SnippsDB* db, int parent);
    void (*watchCategories)(struct _SnippsDB* db, struct _CategoryWatcherHandle* handle);
    void (*unwatchCategories)(struct _SnippsDB* db, struct _CategoryWatcherHandle* handle);
};

/* --- FUNCTIONS --- */

extern struct _SnippsDB_Functions SnippsDB_Functions;

struct _SnippsDB* SnippsDB_initialize(const char* fileName);
void SnippsDB_free(struct _SnippsDB* db);

struct _List* SnippsDB_getCategoryList(struct _SnippsDB* db, int parent);
void SnippsDB_watchCategories(struct _SnippsDB* db, struct _CategoryWatcherHandle* handle);
void SnippsDB_unwatchCategories(struct _SnippsDB* db, struct _CategoryWatcherHandle* handle);

#endif /* SNIPPSDB_H_INCLUDED */
