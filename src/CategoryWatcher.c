#include <stdlib.h>
#include "CategoryWatcher.h"

struct _CategoryWatcherHandle_Functions CategoryWatcherHandle_Functions = {
    .free = CategoryWatcherHandle_free
};

struct _CategoryWatcherHandle* CategoryWatcherHandle_initialize(void(*callback)(int type, struct _Category* category, void* userdefined), void* userdefined)
{
    /* initialize class */
    struct _CategoryWatcherHandle* handle = malloc(sizeof(struct _CategoryWatcherHandle));
    handle->func = &CategoryWatcherHandle_Functions;

    /* initialize variables */
    handle->callback = callback;
    handle->userdefined = userdefined;

    return handle;
}

void CategoryWatcherHandle_free(struct _CategoryWatcherHandle* handle)
{
    free(handle);
}
