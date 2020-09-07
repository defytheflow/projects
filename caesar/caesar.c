/*
 * File:     caesar.c
 * Created:  25.06.2020
 * Usage:    caesar <mode> <msg> <key>
 * Args:
 *   mode    [decrypt|encrypt]
 *   key     [0-26]
 */


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECRYPT 0
#define ENCRYPT 1


bool string_to_integer(int* dest, char* src);
int string_compare(const char* s1, const char* s2);
char* decrypt(char* dest, const char* src, int key);
char* encrypt(char* dest, const char* src, int key);


int main(int argc, char** argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: caesar <mode> <msg> <key>\n");
        return EXIT_FAILURE;
    }

    bool mode;
    if (string_compare(argv[1], "decrypt") == 0)
        mode = DECRYPT;
    else if (string_compare(argv[1], "encrypt") == 0)
        mode = ENCRYPT;
    else {
        fprintf(stderr, "Error: unknown mode '%s', must be encrypt or decrypt\n", argv[1]);
        return EXIT_FAILURE;
    }

    int key;
    if (!(string_to_integer(&key, argv[3]))) {
        fprintf(stderr, "Error: key must be an integer.\n");
        return EXIT_FAILURE;
    }

    if (key < 0 || key > 26) {
        fprintf(stderr, "Error: key must be in range 0..26\n");
        return EXIT_FAILURE;
    }

    char res[strlen(argv[2]) + 1];

    if (mode == DECRYPT)
        decrypt(res, argv[2], key);
    else
        encrypt(res, argv[2], key);

    puts(res);

    return EXIT_SUCCESS;
}

/*
 * Implementation of strcmp function for learning purposes.
 */
int string_compare(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}


bool string_to_integer(int* dest, char* src)
{
    int res = 0;
    int sign = 1;

    if (*src == '-') {
        sign = -1;
        ++src;
    }

    for (; *src != '\0'; ++src) {
        if (!isdigit(*src)) return false;
        res = res * 10 + (*src - '0');
    }

    *dest = res * sign;
    return true;
}


char* encrypt(char* dest, const char* src, int key)
{
    char shift;
    int i;

    for (i = 0; src[i] != '\0'; ++i) {
        if (isalpha(src[i])) {
            shift = islower(src[i]) ? 'a' : 'A';
            dest[i] = (src[i] - shift + key) % 26 + shift;
        } else
            dest[i] = src[i];
    }

    dest[i] = src[i];
    return dest;
}

char* decrypt(char* dest, const char* src, int key)
{
    char shift;
    int i;

    for (i = 0; src[i] != '\0'; ++i) {
        if (isalpha(src[i])) {
            shift = islower(src[i]) ? 'a' : 'A';
            dest[i] = (src[i] - key < shift) ? src[i] - key + 26 : src[i] - key;
        } else
            dest[i] = src[i];
    }

    dest[i] = src[i];
    return dest;
}
