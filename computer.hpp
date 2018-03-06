#ifndef _COMPUTER_
#define _COMPUTER_

class Computer {
	private:
	public:
		bool wumpusNear;
		bool batsNear;
		bool pitNear;
		bool goldNear;
		
		bool triedNorth;
		bool triedEast;
		bool triedSouth;
		bool triedWest;
		
		bool wallNorth;
		bool wallEast;
		bool wallSouth;
		bool wallWest;
		
		bool pursuingGold;
		
		bool acquiredGold;
		
		int lastDir; // which direction were we heading last time
	
	
	
		Computer();
		~Computer();
		void print();
		
		char pickDirection(bool);
		char makeDecision();
		
		void batTransport();
		
		void goldAcquired();

};
#endif