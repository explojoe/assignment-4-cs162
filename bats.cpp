/*********************************************************************
** Program Filename: bats.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/

#include <iostream>

#include "bats.hpp"

using namespace std;

Bats::Bats(){
	id = 'B';
}
Bats::~Bats(){

}
void Bats::nearby(){
	std::cout << "You hear wings flapping." << std::endl;
}
int Bats::inside(){
	// return bat movement key
	return 1;
}