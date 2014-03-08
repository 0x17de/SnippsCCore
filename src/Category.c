#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "Category.h"

struct _Category_Functions Category_Functions = {
    .free = Category_free
};

struct _Category* Category_initialize(int categoryId, const char* categoryTitle, int subitemCount)
{
    /* initialize class */
    struct _Category* category = malloc(sizeof(struct _Category));
    category->func = &Category_Functions;

    /* initialize variables */
    category->categoryId = categoryId;
    category->categoryTitle = strdup(categoryTitle); /* create a copy */
    category->subitemCount = subitemCount;

    return category;
}

void Category_free(struct _Category* category)
{
    /* cleanup memory */
    free(category->categoryTitle);
    free(category);
}
