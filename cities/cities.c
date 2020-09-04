#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CITIES 15000

#define CITY_NOT_FOUND -1
#define CITY_NAMED     -2

#define last_char(s)       (s)[strlen((s)) - 1]
#define randint(low, high) rand() % ((high) - (low) + 1) + (low)

typedef struct {
    char* name;
    bool named;
} city_t;

city_t** load_cities(const char* fname);
city_t* new_city(const char* name);
void free_cities(void);
void user_says_city(void);
void ai_says_city(void);
bool validate_city(const char* city);
void print_ai_city(int pos);
city_t* city_lsearch(const char* name);
char* my_fgets(char* s, int n, FILE* stream);
void strlow(char* s);

city_t** g_cities = NULL;
city_t* g_cur_city = NULL;
int g_len = 0;

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [--user|--ai]\n", __FILE__);
        return 1;
    }

    g_cities = load_cities("cities.txt");

    for (;;) {
        if (strcmp(argv[1], "--user") == 0) {
            user_says_city();
            ai_says_city();
        } else if (strcmp(argv[1], "--ai") == 0) {
            ai_says_city();
            user_says_city();
        } else {
            fprintf(stderr, "Usage: %s [--user|--ai]\n", __FILE__);
            return 1;
        }
    }

    free_cities();
    return 0;
}

city_t** load_cities(const char* fname) {
    FILE* in;
    char line[64];

    if ((in = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "Error: file %s does not exist.\n", fname);
        exit(1);
    }

    g_cities = malloc(sizeof(city_t*) * MAX_CITIES);
    assert(g_cities);

    while (my_fgets(line, sizeof(line), in)) {
        strlow(line);
        g_cities[g_len++] = new_city(line);
    }

    fclose(in);
    return g_cities;
}

city_t* new_city(const char* name) {
    city_t* city = malloc(sizeof(city_t));
    assert(city);
    city->name = strdup(name);
    city->named = false;
    return city;
}

void free_cities(void) {
    for (int i = 0; i < g_len; ++i) {
        free(g_cities[i]->name);
        free(g_cities[i]);
    }
    free(g_cities);
}

void user_says_city(void) {
    char city[32];
    for (;;) {
        printf("Enter city: ");
        my_fgets(city, sizeof(city), stdin);
        strlow(city);
        if (validate_city(city))
            return;
    }
}

bool validate_city(const char* city) {
    char c;

    if (g_cur_city != NULL) {
        if ((c = last_char(g_cur_city->name)) != city[0]) {
            printf("City's name must start with %c\n", toupper(c));
            return false;
        }
    }

    city_t* res = city_lsearch(city);

    if (res == NULL) {
        puts("This city doesn't exist.");
        return false;
    }

    if (res->named) {
        puts("This city has already been named.");
        return false;
    }

    g_cur_city = res;
    res->named = true;

    return true;
}

void ai_says_city(void) {
    int pos;
    if (g_cur_city == NULL) {
        pos = randint(0, g_len);
        print_ai_city(pos);
        g_cur_city = g_cities[pos];
        g_cities[pos]->named = true;
        return;
    }

    char c = last_char(g_cur_city->name);
    for (int i = 0; i < g_len; ++i) {
        if (g_cities[i]->name[0] == c) {
            print_ai_city(i);
            g_cur_city = g_cities[i];
            g_cities[i]->named = true;
            return;
        }
    }
}

city_t* city_lsearch(const char* name) {
    city_t* res = NULL;
    for (int i = 0; i < g_len; ++i) {
        if (strcmp(g_cities[i]->name, name) == 0) {
            res = g_cities[i];
            break;
        }
    }
    return res;
}

void print_ai_city(int pos) {
    char buff[strlen(g_cities[pos]->name) + 1];
    strcpy(buff, g_cities[pos]->name);
    buff[0] = toupper(buff[0]);
    printf("AI's city: %s\n", buff);
}

char* my_fgets(char* s, int n, FILE* stream) {
    int len;

    if (fgets(s, n, stream) == NULL) {
        return NULL;
    }

    len = strlen(s);
    if (s[len - 1] == '\n')
        s[len - 1] = '\0';

    return s;
}

void strlow(char* s) {
    for (int i = 0; (s[i] = tolower(s[i])); ++i)
        ;
}
