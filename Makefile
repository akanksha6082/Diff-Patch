run: diff.o LCS.o help.o list.o que1.o
	gcc -o ./diff diff.o LCS.o help.o list.o que1.o
diff.o: diff.c LCS.o help.o list.o que1.o
	gcc -c diff.c
LCS.o: LCS.c help.o list.o que1.o
	gcc -c LCS.c
help.o: help.c
	gcc -c help.c
list.o: list.c list.h
	gcc -c list.c
que1.o: que1.c que1.h
	gcc -c que1.c
