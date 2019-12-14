PROG = test
OBJS = test.o confirm_solver_v2.o ../../../Modules/Vector/vector.o ../../../Modules/Queue/queue.o ../../../Modules/Stopwatch/stopwatch.o ../../../Generator/ReadDataFile.o
CC = gcc
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow
LDFLAGS =

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^
.c.o../../../Modules/Vector/%.o../../../Generator/%.o../../../Modules/Queue/%.o../../../Modules/Stopwatch/%.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
