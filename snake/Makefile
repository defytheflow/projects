CC = gcc
CFLAGS = -g -W -Wall -Wextra
LDFLAGS = -lncurses

default: snake

snake.o: snake.c
	$(CC) -c $(CFLAGS) $^ $(LDFLAGS)

food.o: food.c
	$(CC) -c $(CFLAGS) $^ $(LDFLAGS)

game_window.o: game_window.c
	$(CC) -c $(CFLAGS) $^ $(LDFLAGS)

snake: main.c game_window.o snake.o food.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) *.o snake
