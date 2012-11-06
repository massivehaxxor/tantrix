CC=gcc
OBJS=logic.o thread_unix.o

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

thread_unix.o: thread_unix.c tantrix_thread.h
	$(CC) -c thread_unix.c

clean:
	rm -f $(OBJS) tantrix_curses *.o

