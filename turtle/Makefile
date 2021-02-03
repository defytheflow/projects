C_FLAGS = -W -Wall -Wextra
C_LIBS = -lcurses

turtle.o: turtle.c
	gcc -c $(C_FLAGS) $^ $(C_LIBS)

menu.o: menu.c
	gcc -c $(C_FLAGS) $^ $(C_LIBS)

sprite.o: sprite.c
	gcc -c $(C_FLAGS) $^ $(C_LIBS)

enemy.o: enemy.c
	gcc -c $(C_FLAGS) $^ $(C_LIBS)

turtle: main.c turtle.o menu.o sprite.o enemy.o
	gcc $(C_FLAGS) $^ $(C_LIBS) -o $@