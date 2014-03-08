#include <stdlib.h>
#include "SnippsDB.h"

struct _SnippsDB_Functions SnippsDB_Functions = {
    .free = SnippsDB_free,
    .watchCategory = SnippsDB_watchCategory
};

struct _SnippsDB* SnippsDB_initialize()
{
    /* initialize class */
    struct _SnippsDB* db = malloc(sizeof(struct _SnippsDB));
    db->func = &SnippsDB_Functions;

    /* initialize vars */
    db->db = 0;

    /* open database */
    if (!sqlite3_open("_test.db", &db->db) == SQLITE_OK)
    {
        db->func->free(db);
        return 0;
    }
    return db;
}

void SnippsDB_free(struct _SnippsDB* db)
{
    /* cleanup database */
    if (db->db)
    {
        sqlite3_close(db->db);
    }

    /* cleanup memory */
    free(db);
}

struct _Category* SnippsDB_watchCategory(struct _SnippsDB* db, int categoryId)
{
    /* @TODO */
    return 0;
}
