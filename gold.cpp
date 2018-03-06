/*********************************************************************
** Program Filename: gold.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/
#include <iostream>

#include "gold.hpp"

using namespace std;

Gold::Gold(){
	id = 'G';
}
Gold::~Gold(){

}
void Gold::nearby(){
	std::cout << "You see a glimmer nearby." << std::endl;
}
int Gold::inside(){
	// return gold collected key
	return 3;
}