#ifndef _WUMPUS_
#define _WUMPUS_

#include "event.hpp"

class Wumpus: public Event {
	private:
	public:
		Wumpus();
		~Wumpus();
		
		void nearby();
		int inside();
};
#endif