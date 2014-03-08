#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

/* --- STRUCTS --- */

struct _Category {
    const struct _Category_Functions* func;

    int categoryId;
    char* categoryTitle;
};

/* --- METHODS --- */

struct _Category_Functions {
    void (*free)(struct _Category* list);
};

/* --- FUNCTIONS --- */

struct _Category* Category_initialize(int categoryId, const char* categoryTitle);
void Category_free(struct _Category* category);


#endif /* CATEGORYLIST_H_INCLUDED */
