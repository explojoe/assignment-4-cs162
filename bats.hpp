#ifndef _BATS_
#define _BATS_

#include "event.hpp"

class Bats: public Event {
	private:
	public:
		Bats();
		~Bats();
		
		void nearby();
		int inside();
};
#endif