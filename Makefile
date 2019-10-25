CC = gcc
CFLAGS = -Wall -ansi -pedantic --std=c99
OBJS = initGame.o fight.o commands.o endGame.o main.o

game: $(OBJS)
	gcc -o game main.o initGame.o fight.o commands.o endGame.o

.PHONY: clean

initGame.o: initGame.c initGame.h
	$(CC) $(CFLAGS) -c $<

fight.o: fight.c fight.h initGame.h
	$(CC) $(CFLAGS) -c $<

commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c $<

endGame.o: endGame.c endGame.h initGame.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c main.h fight.h commands.h initGame.h endGame.h
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *.o
	@echo "Clean done"