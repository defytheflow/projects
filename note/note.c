#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define flush() while (getchar() != '\n');
#define array_size(arr) sizeof(arr) / sizeof(arr[0])

#define SAVE_FORMAT "%d,%s,%ld,%s\n"
#define DB_FILE "notes.csv"

#define MAX_NAME 32
#define MAX_BODY 140
#define MAX_NOTES 64
#define NEW_LINE '~'

typedef struct {
	int id;
	time_t time;
	char name[MAX_NAME];
	char body[MAX_BODY];
} note_t;

volatile int g_is_running = true;
note_t* g_notes[MAX_NOTES];
int g_len = 0;

void load_notes(void);
void serialize_note(note_t* note);
void save_note(note_t* note);
void free_notes(void);
void create_note(void);
char* my_fgets(char* s, int n, FILE* stream);
void list_notes(void);

void list_notes(void) {
	char buffer[25];

	if (g_len == 0) {
		printf("There are no notes\n");
		return;
	}

	puts("---------------------------------------------------------------------");
	printf("| %-3s | %-32s | %-23s  |\n", "id", "name", "date");
	puts("---------------------------------------------------------------------");

	for (int i = 0; i < g_len; ++i) {
		strcpy(buffer, ctime(&g_notes[i]->time));
		buffer[array_size(buffer) - 1] = '\0';
		printf("| %-3d | %-32s | %-23s |\n", g_notes[i]->id, g_notes[i]->name, buffer);
		puts("---------------------------------------------------------------------");
	}
}

char* my_fgets(char* s, int n, FILE* stream) {
	fgets(s, n, stream);
	if (s[strlen(s) - 1] == '\n') {
		s[strlen(s) - 1] = '\0';
	}
	return s;
}

void create_note(void)
{
	note_t* new_note;
	if ((new_note = malloc(sizeof(note_t))) == NULL) {
		perror("");
		exit(1);
	}

	printf("Name of note: ");
	my_fgets(new_note->name, MAX_NAME, stdin);
	
	puts("Note body:");
	char c;
	int i = 0;
	while(((c = getchar()) != EOF) && (i <= MAX_BODY)) {
		new_note->body[i++] = c;
	}

	new_note->time = time(NULL);

	serialize_note(new_note);
	save_note(new_note);

	free(new_note);
}

void save_note(note_t* note) {
	FILE* out;
	char buffer[256];

	if (access("notes.csv", F_OK) != 0) {
		note->id = 1;
		out = fopen("notes.csv", "w");
		fprintf(out, "id,name,time,body\n");
		fprintf(out, SAVE_FORMAT, note->id, note->name, note->time, note->body);

	} else {
		out = fopen("notes.csv", "r");
		while (fgets(buffer, sizeof(buffer), out));
		sscanf(buffer, "%d", &note->id);
		++note->id;
		out = fopen("notes.csv", "a");
		fprintf(out, SAVE_FORMAT, note->id, note->name, note->time, note->body);
	}

	fclose(out);
}

// void free_notes(void) {
// 	for (int i = 0; i < g_len; ++i)
// 		free(g_notes[i]);
// }

void serialize_note(note_t* note) {
	for (int i = 0; note->body[i] != '\0'; ++i) {
		if (note->body[i] == '\n') {
			note->body[i] = NEW_LINE;
		}
	}
}

void load_notes(void) {
	FILE* in;
	note_t* note;
	char buffer[256];

	if (access(DB_FILE, F_OK) != 0)
		return;
		
	if ((in = fopen(DB_FILE, "r")) == NULL) {
		perror("");
		exit(1);
	}

	fgets(buffer, sizeof(buffer), in);
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		if ((note = malloc(sizeof(note_t))) == NULL) {
			perror("");
			exit(1);
		}

		sscanf(buffer, SAVE_FORMAT, &note->id, note->name, &note->time, note->body);
	}

	fclose(in);
}

int main(int argc, char* argv[])
{
	const char* command;

	if (argc < 2) {
		fprintf(stderr, "Usage: note <[create|list|read|delete]>\n");
		return EXIT_FAILURE;
	}

	// load_notes();
	command = argv[1];

	if (strcmp(command, "create") == 0) {
		create_note();
	} else if (strcmp(command, "list") == 0) {
		list_notes();
	} else if (strcmp(command, "read") == 0) {
		puts("read");
	} else if (strcmp(command, "delete") == 0) {
		puts("delete");
	} else {
		fprintf(stderr, "Unkown command\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}