CXX := g++
override CXXFLAGS += -Wall -pedantic -std=c++17
LDLIBS := -lncurses
OBJS := main.o algorithms.o maze.o
BINARY := main.out

.PHONY: all clean debug

debug: CXXFLAGS += -g -fsanitize=address

all: ${OBJS}
	${CXX} ${CXXFLAGS} -o ${BINARY} ${OBJS} ${LDLIBS}

debug: all

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $*.o $*.cpp

clean:
	-rm -f *.o ${BINARY}
