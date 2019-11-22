CC = gcc
CFLAGS = -Wall -ansi -pedantic --std=c99
OBJS = initGame.o fight.o commands.o colors.o fightMode.o endGame.o displayGame.o tools.o strat.o main.o

game: $(OBJS)
	gcc -o game main.o initGame.o fight.o commands.o colors.o fightMode.o endGame.o displayGame.o strat.o tools.o

.PHONY: clean

initGame.o: initGame.c initGame.h
	$(CC) $(CFLAGS) -c $<

fight.o: fight.c fight.h initGame.h displayGame.h tools.h
	$(CC) $(CFLAGS) -c $<

commands.o: commands.c commands.h initGame.h fight.h colors.h fightMode.h endGame.h tools.h
	$(CC) $(CFLAGS) -c $<

colors.o: colors.c colors.h
	$(CC) $(CFLAGS) -c $<

fightMode.o : fightMode.c fightMode.h initGame.h fight.h commands.h colors.h displayGame.h tools.h
	$(CC) $(CFLAGS) -c $<

endGame.o: endGame.c endGame.h initGame.h
	$(CC) $(CFLAGS) -c $<

displayGame.o: displayGame.c displayGame.h initGame.h colors.h tools.h
	$(CC) $(CFLAGS) -c $<

tools.o: tools.c tools.h initGame.h
	$(CC) $(CFLAGS) -c $<

strat.o: strat.c strat.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c fight.h fightMode.h commands.h initGame.h endGame.h displayGame.h strat.h
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *.o
	@rm -f game
	@echo "Clean done"