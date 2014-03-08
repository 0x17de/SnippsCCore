#include <assert.h>
#include "SnippsDB.h"
#include "list.h"

void testSnippsDB()
{
    struct _SnippsDB* db = SnippsDB_initialize("_temp.db");
    assert(db != 0);

    db->func->free(db);
}
