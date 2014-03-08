#include <string.h>

char* strdup(const char* str)
{
    int len = strlen(str);

    char* out = malloc(len + 1);
    memcpy(out, str, len + 1);

    return out;
}
