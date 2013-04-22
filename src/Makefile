CC		    = gcc
CFLAGS	    = -I. -Wall -g -O0 
LDFLAGS	    = -g -O0
OBJS	    = logic.o util.o socket_unix.o tantrix_curses.o

DEPS		= ncursesw

## client executable

CFLAGS		+= $(shell pkg-config $(DEPS) --cflags)
LDFLAGS		+= $(shell pkg-config $(DEPS) --libs)

all: tantrix

tantrix: $(OBJS) 
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) tantrix_curses *.o

