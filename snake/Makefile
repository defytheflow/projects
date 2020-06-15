CC = gcc
CFLAGS =
LDFLAGS = -lncurses

default: snake

snake.o: snake.c snake.h
	$(CC) -c $(CFLAGS) snake.c $(LDFLAGS)

error.o: error.c error.h
	$(CC) -c $(CFLAGS) error.c $(LDFLAGS)

food.o: food.c food.h
	$(CC) -c $(CFLAGS) food.c $(LDFLAGS)

utils.o: utils.c utils.h
	$(CC) -c $(CFLAGS) utils.c $(LDFLAGS)

game_window.o: game_window.c game_window.h
	$(CC) -c $(CFLAGS) game_window.c $(LDFLAGS)

snake: main.c game_window.o snake.o food.o utils.o error.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) *.o snake
