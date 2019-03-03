# flags
F = -O3 -c -std=c++11
S = main.o student.o

all: bubble min_sort lin_sort bin_sort merge quick heap
# sorts
bubble: $S bubble.o
	g++ $S bubble.o -o bubble
bubble.o: bubble.cpp
	g++ $F bubble.cpp

min_sort: $S min_sort.o
	g++ $S min_sort.o -o min_sort
min_sort.o: min_sort.cpp
	g++ $F min_sort.cpp

lin_sort: $S lin_sort.o
	g++ $S lin_sort.o -o lin_sort
lin_sort.o: lin_sort.cpp
	g++ $F lin_sort.cpp

bin_sort: $S bin_sort.o
	g++ $S bin_sort.o -o bin_sort
bin_sort.o: bin_sort.cpp
	g++ $F bin_sort.cpp

merge: $S merge.o
	g++ $S merge.o -o merge
merge.o: merge.cpp
	g++ $F merge.cpp

quick: $S quick.o
	g++ $S quick.o -o quick 
quick.o: quick.cpp
	g++ $F quick.cpp

heap: $S heap.o
	g++ $S heap.o -o heap 
heap.o: heap.cpp
	g++ $F heap.cpp

# main
main.o: main.cpp array.h student.h errors.h
	g++ $F main.cpp
student.o: student.cpp student.h
	g++ $F student.cpp
clear:
	rm *.o

