#ifndef _PIT_
#define _PIT_

#include "event.hpp"

class Pit: public Event {
	private:
	public:
		Pit();
		~Pit();
		
		void nearby();
		int inside();
};
#endif