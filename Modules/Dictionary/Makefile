PROG = test
OBJS = test.o Dictionary.o
CC = gcc
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow
LDFLAGS = 

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
