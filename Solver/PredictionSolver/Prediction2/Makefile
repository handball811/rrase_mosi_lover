PROG = test
OBJS = test.o prediction2.o ../../ConfirmSolver/SolveCertainString.c ../../ConfirmSolver/sort.c ../../ConfirmSolver/MiddleStructureHandler.c ../../ConfirmSolver/InsertConfirmParts.c ../../ConfirmSolver/InsertPartsRoughly.c ../../ConfirmSolver/CalculateCorrectAnswerRate.c ../../../Generator/ReadDataFile.c ../../../Settings/confirm_solver_setting.c
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
