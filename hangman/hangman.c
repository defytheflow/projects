/*
 * Hangman Game.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIVES          6
#define LOCKED_LETTER '_'
#define PROMPT "GUESS: "

const char* get_random_word(void);
char get_letter(const char* prompt);

void print_rules(void);
void print_hangman(int lives);

void unlock_letter(const char* word, char* unlocked_letters, char letter);
void init_unlocked_letters(char* unlocked_letters, int size, int val);
void print_unlocked_letters(const char* unlocked_letters);

void append(char* dest, int n, char val);
void print_misses(const char* misses);

int main(void)
{
    int lives = LIVES;
    char misses[LIVES + 1] = {0};
    const char* word = get_random_word();

    char unlocked_letters[strlen(word) + 1];
    init_unlocked_letters(unlocked_letters, sizeof(unlocked_letters) - 1, LOCKED_LETTER);

    print_rules();

    char letter;
    bool won = false;
    for (;;) {
        system("clear");

        print_hangman(lives);
        print_misses(misses);
        print_unlocked_letters(unlocked_letters);

        letter = get_letter(PROMPT);
        if (strchr(word, letter)) {
            unlock_letter(word, unlocked_letters, letter);
            if (!strchr(unlocked_letters, LOCKED_LETTER)) {
                won = true;
                break;
            }
        } else {
            --lives;
            append(misses, LIVES, letter);
            if (lives == 0)
                break;
        }
    }

    system("clear");
    (won) ? puts("YOU WON") : puts("YOU LOST");

    print_hangman(lives);
    print_misses(misses);
    print_unlocked_letters(unlocked_letters);

    if ((letter = tolower(get_letter("Repeat? [y/Y]: "))) == 'y')
        main();

    return 0;
}

char get_letter(const char* prompt)
{
    int ch;
    while (printf("%s", prompt) && (ch = getchar()) != EOF) {
        while (getchar() != '\n')
            ;
        if (isalpha(ch))
            return ch;
    }
    return EOF;
}

void init_unlocked_letters(char* unlocked_letters, int size, int val)
{
    memset(unlocked_letters, val, size);
    unlocked_letters[size] = '\0';
}

void print_rules(void)
{
    puts("Rules:");
    puts("I will pick a random word.");
    printf("%s %d %s\n", "You will have", LIVES,
            "attempts to guess it, otherwise you will get hanged.");
    puts("Press <Enter> to begin...");
    getchar();
}

/*
 * Returns a pointer to a random word picked from 'words' array.
 */
const char* get_random_word(void)
{
    srand(time(NULL));
    const char* words[] = {
        "apple",
        "king",
        "lemon",
        "lion",
        "sandwich",
        "quarantine",
        "queue",
        "zebra",
        "penguin",
    };

    int rand_pos = rand() % (sizeof(words) / sizeof(words[1]));
    return words[rand_pos];
}

void print_unlocked_letters(const char* unlocked_letters)
{
    printf("\n%s", "WORD: ");
    for (; *unlocked_letters; ++unlocked_letters)
        printf("%c ", *unlocked_letters);
    puts("");
}

void print_hangman(int lives)
{
    switch (lives) {
    case 0:
        puts("|-----");
        puts("|  |  ");
        puts("|  O  ");
        puts("| /|\\");
        puts("| / \\");
        break;
    case 1:
        puts("|-----");
        puts("|  |  ");
        puts("|  O  ");
        puts("| /|\\");
        puts("| /   ");
        break;
    case 2:
        puts("|-----");
        puts("|  |  ");
        puts("|  O  ");
        puts("| /|\\");
        puts("|     ");
        break;
    case 3:
        puts("|-----");
        puts("|  |  ");
        puts("|  O  ");
        puts("| /|  ");
        puts("|     ");
        break;
    case 4:
        puts("|-----");
        puts("|  |  ");
        puts("|  O  ");
        puts("|  |  ");
        puts("|     ");
        break;
    case 5:
        puts("|-----");
        puts("|  |  ");
        puts("|  O  ");
        puts("|     ");
        puts("|     ");
        break;
    case 6:
        puts("|-----");
        puts("|  |  ");
        puts("|     ");
        puts("|     ");
        puts("|     ");
        break;
    }
}

void unlock_letter(const char* word, char* unlocked_letters, char letter)
{
    for (int i = 0; word[i] != '\0'; ++i) {
        if (letter == word[i]) {
            unlocked_letters[i] = letter;
        }
    }
}

void append(char* dest, int n, char val)
{
    for (int i = 0; i < n; ++i) {
        if (!dest[i]) {
            dest[i] = val;
            return;
        }
    }
}

void print_misses(const char* misses)
{
    printf("MISSES: ");
    for (; *misses; ++misses) {
        printf("%c ", *misses);
    }
}
