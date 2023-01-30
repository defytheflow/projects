#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*
 * Reads a character from stdin without echoing and waiting for <Enter> press.
 */
int getch(void)
{
    int ch;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;

    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

/*
 * Returns a random integer in range [low, high].
 */
int random_range(int low, int high)
{
    return rand() % (high - low + 1) + low;
}
