CXX := g++
CXXFLAGS := -Wall -pedantic -std=c++17
LDLIBS := -lncurses

debug: CXXFLAGS += -g -fsanitize=address

all: main.o algorithms.o maze.o
	${CXX} ${CXXFLAGS} -o main.out main.o algorithms.o maze.o ${LDLIBS}

debug: all

main.o: main.cpp maze.h algorithms.h
	${CXX} ${CXXFLAGS} -c -o main.o main.cpp

algorithms.o: algorithms.cpp algorithms.h maze.h
	${CXX} ${CXXFLAGS} -c -o algorithms.o algorithms.cpp

maze.o: maze.cpp maze.h
	${CXX} ${CXXFLAGS} -c -o maze.o maze.cpp

clean:
	rm -f *.o main.out
