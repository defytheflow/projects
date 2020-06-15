#include "error.h"

#include <stdio.h>


void print_error(int status)
{
    switch (status) {
    case MEMORY_ALLOCATION_ERROR:
        fprintf(stderr, "snake: error: memory allocation.\n");
        break;
    case TERMINAL_SIZE_ERROR:
        fprintf(stderr, "snake: error: terminal size is too small.\n");
        break;
    }
}
