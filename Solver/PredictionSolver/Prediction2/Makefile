PROG = test
OBJS = test.o prediction2.o
CC = gcc
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow -g
LDFLAGS =

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
