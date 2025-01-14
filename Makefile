CC = gcc
CFLAGS = -Wall -ansi -pedantic --std=c99
OBJS = initGame.o fight.o commands.o colors.o fightMode.o endGame.o displayGame.o tools.o strat.o main.o

game: $(OBJS)
	gcc -o game main.o initGame.o strat.o fight.o commands.o colors.o fightMode.o endGame.o displayGame.o tools.o

.PHONY: clean

initGame.o: initGame.c initGame.h
	$(CC) $(CFLAGS) -c -o $@ $<

fight.o: fight.c fight.h initGame.h displayGame.h tools.h
	$(CC) $(CFLAGS) -c -o $@ $<

commands.o: commands.c commands.h initGame.h strat.h fight.h colors.h fightMode.h endGame.h tools.h
	$(CC) $(CFLAGS) -c -o $@ $<

colors.o: colors.c colors.h
	$(CC) $(CFLAGS) -c -o $@ $<

fightMode.o : fightMode.c fightMode.h initGame.h fight.h commands.h colors.h displayGame.h tools.h strat.h
	$(CC) $(CFLAGS) -c -o $@ $<

endGame.o: endGame.c endGame.h initGame.h
	$(CC) $(CFLAGS) -c -o $@ $<

displayGame.o: displayGame.c displayGame.h initGame.h colors.h tools.h
	$(CC) $(CFLAGS) -c -o $@ $<

tools.o: tools.c tools.h initGame.h
	$(CC) $(CFLAGS) -c -o $@ $<

strat.o: strat.c strat.h initGame.h fight.h tools.h displayGame.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c fight.h fightMode.h commands.h initGame.h endGame.h displayGame.h strat.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f *.o
	@rm -f game
	@echo "Clean done"
