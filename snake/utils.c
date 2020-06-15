#include "utils.h"

#include <stdlib.h>
#include <string.h>


int str_center(const char* s, int width)
{
    return (width - strlen(s)) / 2;
}


int random_range(int low, int high)
{
    return rand() % (high - low + 1) + low;
}
