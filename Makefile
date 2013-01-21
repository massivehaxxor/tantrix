CC=gcc
OBJS=logic.o thread_unix.o socket_unix.o 

CFLAGS=-lpthread -Wall -O0 

## client executable

tantrix_curses: $(OBJS) tantrix_curses.o
	$(CC) $(CFLAGS) $(OBJS) tantrix_curses.o `ncurses6-config --libs` -o $@

## client obj

tantrix_curses.o: tantrix_curses.c 
	$(CC) -c tantrix_curses.c -std=c99 -Wno-implicit `ncurses6-config --cflags`


## OBJS

logic.o: logic.c logic.h
	$(CC) -c logic.c

thread_unix.o: thread_unix.c tantrix_thread.h
	$(CC) -c thread_unix.c

socket_unix.o: socket_unix.c tantrix_socket.h
	$(CC) -c socket_unix.c


clean:
	rm -f $(OBJS) tantrix_curses *.o

