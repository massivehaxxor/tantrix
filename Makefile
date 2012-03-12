CC=gcc
OBJS=input.o logic.o main.o
CFLAGS=-lpthread -g

tantrix: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

main.o: main.c
	$(CC) -c main.c

input.o: input.c input.h
	$(CC) -c input.c

logic.o: logic.c logic.h
	$(CC) -c logic.c

clean:
	rm -f $(OBJS) tantrix

