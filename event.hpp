#ifndef _EVENT_
#define _EVENT_

class Event {
	private:
	public:
		virtual void nearby() = 0;
		virtual int inside() = 0;
		
		char id;
};
#endif