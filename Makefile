CC = gcc
CFLAGS = -Wall -ansi -pedantic --std=c99
OBJS = initGame.o fight.o commands.o fightMode.o endGame.o main.o

game: $(OBJS)
	gcc -o game main.o initGame.o fight.o commands.o fightMode.o endGame.o

.PHONY: clean

initGame.o: initGame.c initGame.h
	$(CC) $(CFLAGS) -c $<

fight.o: fight.c fight.h initGame.h
	$(CC) $(CFLAGS) -c $<

commands.o: commands.c commands.h initGame.h fight.h fightMode.h endGame.h
	$(CC) $(CFLAGS) -c $<

fightMode.o : fightMode.c fightMode.h initGame.h fight.h commands.h
	$(CC) $(CFLAGS) -c $<

endGame.o: endGame.c endGame.h initGame.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c main.h fight.h fightMode.h commands.h initGame.h endGame.h
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *.o
	@rm -f game
	@echo "Clean done"