#ifndef _ROOM_
#define _ROOM_

#include "event.hpp"

class Room {
	private:
		Event* event;
		
	public:
		Room();
		~Room();
		void print();
		
		Event* getEvent();
		
		void setWumpus();
		void setBats();
		void setPit();
		void setGold();
		void setEmpty();
};
#endif