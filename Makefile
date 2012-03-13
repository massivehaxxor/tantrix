CC=gcc
OBJS=input.o logic.o

CFLAGS=-lpthread -s

## client executable

tantrix_curses: $(OBJS) tantrix_curses.o
	$(CC) $(CFLAGS) -lncurses $(OBJS) tantrix_curses.o -o $@

tantrix_test: $(OBJS) main.o
	$(CC) $(CFLAGS) $(OBJS) main.o -o $@

## client obj

tantrix_curses.o: tantrix_curses.c 
	$(CC) -c tantrix_curses.c

main.o: main.c
	$(CC) -c main.c

## OBJS

input.o: input.c input.h
	$(CC) -c input.c

logic.o: logic.c logic.h
	$(CC) -c logic.c

clean:
	rm -f $(OBJS) tantrix_test tantrix_curses *.o

