/*********************************************************************
** Program Filename: pit.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/

#include <iostream>

#include "pit.hpp"

using namespace std;

Pit::Pit(){
	id = 'P';
}
Pit::~Pit(){

}
void Pit::nearby(){
	std::cout << "You feel a breeze." << std::endl;
}
int Pit::inside(){
	// return deadly pit key
	return 2;
}