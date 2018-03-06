/*********************************************************************
** Program Filename: wumpus.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/

#include <iostream>

#include "wumpus.hpp"

using namespace std;

Wumpus::Wumpus(){
	id = 'W';
}
Wumpus::~Wumpus(){

}
void Wumpus::nearby(){
	std::cout << "You smell a terrible stench." << std::endl;
}
int Wumpus::inside(){
	// return deadly wumpus key
	return 0;
}