#ifndef _CAVE_
#define _CAVE_

#include <vector>

#include "room.hpp"
#include "computer.hpp"

class Cave {
	private:
		std::vector<std::vector<Room>> rooms;
		int size;
		
		int exitRow;
		int exitCol;
		
		int playerRow;
		int playerCol;
		
		int arrows;
		
		bool gameIsOver;
		
		bool goldCollected;
		bool wumpusSlain;
		

		
	public:
		int wins;
		int games;
	
		Cave();
		Cave(int);
		~Cave();
		
		void print();
		
		void generateRooms();
		
		int scanForEvent();
		
		void scanForPercepts();
		void transferPercepts(Computer&);
		
		void placePlayer();
		
		bool gameShouldEnd();
		
		void printOptions();
		void printObjectives();
		
		void killWumpus();
		void moveWumpus();
		
		void removeGold();
		
		bool travelInDirection(int);
		bool shootInDirection(int);
		
		Room* findEmptyRoom();
		void batGrabPlayer();
};
#endif