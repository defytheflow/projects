#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOW          1
#define HIGH         100
#define MAX_ATTEMPTS 7

#define randint(low, high) rand() % ((high) - (low) + 1) + (low)

int get_int();
void print_rules();
void ask_to_play_again();

int g_attempts = 1;

int main() {
    int num, guess;

    srand(time(NULL));
    num = randint(LOW, HIGH);

    print_rules();
    while (g_attempts <= MAX_ATTEMPTS) {
        guess = get_int();
        ++g_attempts;
        if (guess > num)
            puts("Your guess is too high.");
        else if (guess < num)
            puts("Your guess is too low.");
        else {
            puts("Correct! You won!");
            ask_to_play_again();
        }
    }

    printf("Sorry, you lost. The correct number was %d\n", num);
    ask_to_play_again();

    return 0;
}

int get_int() {
    int num;
    char* endptr;
    char input[32];

    do {
        printf("Guess #%d: ", g_attempts);
        fgets(input, sizeof(input), stdin);
        num = strtol(input, &endptr, 10);
    } while (strcmp(input, endptr) == 0);

    return num;
}

void ask_to_play_again() {
    char input[32];

    for (;;) {
        printf("Would you like to play again (y/n)? ");
        fgets(input, sizeof(input), stdin);

        switch (*input) {
        case 'y':
        case 'Y':
            g_attempts = 1;
            main();
            break;
        case 'n':
        case 'N':
            puts("Thank you for playing.");
            exit(0);
            break;
        }
    }
}

void print_rules() {
    printf("Let's play a game. "
           "I'm thinking of a number between (%d - %d).\n"
           "You have %d attempts to guess what it is.\n",
           LOW, HIGH, MAX_ATTEMPTS);
}
