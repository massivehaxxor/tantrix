CC=gcc
OBJS=logic.o

CFLAGS=-pthread -Wall -O0 

## client executable

tantrix_curses: $(OBJS) tantrix_curses.o
	$(CC) $(CFLAGS) -lncursesw $(OBJS) tantrix_curses.o -o $@

## client obj

tantrix_curses.o: tantrix_curses.c 
	$(CC) -c tantrix_curses.c -std=c99 -Wno-implicit

## OBJS

logic.o: logic.c logic.h
	$(CC) -c logic.c

clean:
	rm -f $(OBJS) tantrix_curses *.o

