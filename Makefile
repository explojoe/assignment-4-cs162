CC=g++
EXE_FILE=program
HEADERS=room.hpp event.hpp wumpus.hpp bats.hpp pit.hpp gold.hpp cave.hpp computer.cpp
OBJS=wumpus.o bats.o pit.o gold.o cave.o room.o computer.o main.o
CXXFLAGS=-std=c++11 -g

all: $(EXE_FILE)

$(EXE_FILE): $(OBJS)
	$(CC) $^ -o $@ $(CXXFLAGS)

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@ $(CXXFLAGS)
	
clean: 
	rm -f $(OBJS) $(EXE_FILE)