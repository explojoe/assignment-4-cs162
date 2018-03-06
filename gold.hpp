#ifndef _GOLD_
#define _GOLD_

#include "event.hpp"

class Gold: public Event {
	private:
	public:
		Gold();
		~Gold();
		
		void nearby();
		int inside();
};
#endif