/*********************************************************************
** Program Filename: room.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/

#include <iostream>

#include "room.hpp"
#include "wumpus.hpp"
#include "bats.hpp"
#include "pit.hpp"
#include "gold.hpp"
#include "event.hpp"

Room::Room(){
	event = NULL;
	setEmpty();

}
Room::~Room(){
	delete event;
}
void Room::print(){
	std::cout << "hello\n";
}
Event* Room::getEvent(){return event;}
void Room::setWumpus(){
	setEmpty();
	event = new Wumpus();
}
void Room::setBats(){
	setEmpty();
	event = new Bats();
}
void Room::setPit(){
	setEmpty();
	event = new Pit();
}
void Room::setGold(){
	setEmpty();
	event = new Gold();
}
void Room::setEmpty(){
	if(event != NULL){
		delete event;
	}
	event = NULL;
}