PROG = test
OBJS = test.o PredictionSolver.o ./Prediction2/prediction2.o ./Prediction1/prediction1.o
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
