#include <stdlib.h>
#include <stdio.h>
#include "SnippsDB.h"
#include "Category.h"
#include "CategoryWatcher.h"
#include "list.h"

struct _SnippsDB_Functions SnippsDB_Functions = {
    .free = SnippsDB_free,
    .getCategoryList = SnippsDB_getCategoryList,
    .watchCategories = SnippsDB_watchCategories,
    .unwatchCategories = SnippsDB_unwatchCategories
};

struct _SnippsDB* SnippsDB_initialize(const char* fileName)
{
    /* initialize class */
    struct _SnippsDB* db = malloc(sizeof(struct _SnippsDB));
    db->func = &SnippsDB_Functions;

    /* initialize vars */
    db->db = 0;

    /* open database */
    if (!sqlite3_open(fileName, &db->db) == SQLITE_OK)
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

static void freeCategory(void* data)
{
    ((struct _Category*)data)->func->free(data);
}

struct _List* SnippsDB_getCategoryList(struct _SnippsDB* db, int parent)
{
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db->db, "SELECT id, text, (SELECT COUNT(*) FROM categories WHERE parent = id) as subitems FROM categories WHERE parent = ?", 0, &stmt, 0);
    sqlite3_bind_int(stmt, 1, parent);

    struct _List* categoryList = List_initialize(freeCategory);

    while(1) /* while lines available */
    {
        int s = sqlite3_step(stmt);
        if (s == SQLITE_ROW) /* a single row */
        {
            int id = sqlite3_column_int(stmt, 1);
            const char* text = (const char*)sqlite3_column_text(stmt, 2);
            int subitemCount = sqlite3_column_int(stmt, 3);

            struct _Category* category = Category_initialize(id, text, subitemCount);
            categoryList->func->pushBack(categoryList, category);
        }
        else if (s == SQLITE_DONE) /* done */
        {
            break;
        }
        else /* error */
        {
            fputs("SnippsDB_watchCategory: sqlite3 error\n", stderr);
            break;
        }
    }

    sqlite3_finalize(stmt);

    return categoryList;
}

void SnippsDB_watchCategories(struct _SnippsDB* db, struct _CategoryWatcherHandle* handle)
{
    db->categoryWatchers->func->pushBack(db->categoryWatchers, handle);
    handle->item = db->categoryWatchers->last;
}

void SnippsDB_unwatchCategories(struct _SnippsDB* db, struct _CategoryWatcherHandle* handle)
{
    db->categoryWatchers->func->erase(db->categoryWatchers, handle->item);
}
