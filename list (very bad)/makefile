# flags
F = -O3 -c -std=c++11
S = main.o student.o

all: a
a: $S
	g++ $S -o a
main.o: main.cpp list.h node.h student.h errors.h
	g++ $F main.cpp
student.o: student.cpp student.h
	g++ $F student.cpp
clear:
	rm *.o

