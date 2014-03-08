#include <assert.h>
#include <stdio.h>
#include "SnippsDB.h"
#include "list.h"

void testSnippsDB()
{
    FILE* f;
    const char* fileName = "_temp.db";

    /* remove if database already exists */
    f = fopen(fileName, "r");
    if (f)
    {
        fclose(f);
        remove(fileName);
    }

    /* initialize and deinitialize */
    struct _SnippsDB* db = SnippsDB_initialize(fileName);
    assert(db != 0);
    db->func->free(db);

    /* file must exist */
    f = fopen(fileName, "r");
    assert(f != 0); /* file exists */
    if (f)
    {
        fclose(f);
        /* cleanup */
        remove(fileName);
    }
}
