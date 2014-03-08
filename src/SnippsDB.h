#ifndef SNIPPSDB_H_INCLUDED
#define SNIPPSDB_H_INCLUDED

#include <sqlite3.h>

/* --- STRUCTS --- */

struct _SnippsDB {
    const struct _SnippsDB_Functions* func;

    sqlite3* db;
};

/* --- METHODS --- */

struct _SnippsDB_Functions {
    void (*free)(struct _SnippsDB* db);
    struct _List* (*getCategoryList)(struct _SnippsDB* db, int parent);
    struct _List* (*watchCategories)(struct _SnippsDB* db, int parent);
};

/* --- FUNCTIONS --- */

extern struct _SnippsDB_Functions SnippsDB_Functions;

struct _SnippsDB* SnippsDB_initialize(const char* fileName);
void SnippsDB_free(struct _SnippsDB* db);

struct _List* SnippsDB_getCategoryList(struct _SnippsDB* db, int parent);
struct _List* SnippsDB_watchCategories(struct _SnippsDB* db, int parent);

#endif /* SNIPPSDB_H_INCLUDED */
