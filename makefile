CC = clang++
CFLAGS = -Wall -g -std=c++11

all: PEA-Projekt1

start: PEA-Projekt1
	./PEA-Projekt1

PEA-Projekt1: bin bin/main.o bin/StackImpl.o bin/Graph.o bin/BruteForce.o bin/BranchAndBound.o bin/DynamicProgramming.o bin/MainMenu.o bin/TestsAutomation.o bin/Tests.o
	$(CC) $(CFLAGS) -o PEA-Projekt1 bin/main.o bin/StackImpl.o bin/Graph.o bin/BruteForce.o bin/BranchAndBound.o bin/DynamicProgramming.o bin/MainMenu.o bin/TestsAutomation.o bin/Tests.o

bin:
	mkdir bin

bin/main.o: src/main.cpp
	$(CC) -c $(CFLAGS) -o bin/main.o src/main.cpp

bin/StackImpl.o: src/StackImpl.cpp inc/StackImpl.hh
	$(CC) -c $(CFLAGS) -o bin/StackImpl.o src/StackImpl.cpp
	
bin/Graph.o: src/Graph.cpp inc/Graph.hh
	$(CC) -c $(CFLAGS) -o bin/Graph.o src/Graph.cpp

bin/BruteForce.o: src/BruteForce.cpp inc/BruteForce.hh
	$(CC) -c $(CFLAGS) -o bin/BruteForce.o src/BruteForce.cpp

bin/BranchAndBound.o: src/BranchAndBound.cpp inc/BranchAndBound.hh
	$(CC) -c $(CFLAGS) -o bin/BranchAndBound.o src/BranchAndBound.cpp

bin/DynamicProgramming.o: src/DynamicProgramming.cpp inc/DynamicProgramming.hh
	$(CC) -c $(CFLAGS) -o bin/DynamicProgramming.o src/DynamicProgramming.cpp

bin/MainMenu.o: src/MainMenu.cpp inc/MainMenu.hh
	$(CC) -c $(CFLAGS) -o bin/MainMenu.o src/MainMenu.cpp

bin/TestsAutomation.o: src/TestsAutomation.cpp inc/TestsAutomation.hh
	$(CC) -c $(CFLAGS) -o bin/TestsAutomation.o src/TestsAutomation.cpp

bin/Tests.o: src/Tests.cpp inc/Tests.hh
	$(CC) -c $(CFLAGS) -o bin/Tests.o src/Tests.cpp

clean:
	rm -rf *.o bin PEA-Projekt1