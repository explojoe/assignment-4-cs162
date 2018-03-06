/*********************************************************************
** Program Filename: cave.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "cave.hpp"
#include "room.hpp"
#include "computer.hpp"

Cave::Cave(){
	size = 4;
	rooms = std::vector<std::vector<Room>>(size, std::vector<Room>(size, Room()));
}
Cave::Cave(int roomsOnASide){
	size = roomsOnASide;
	rooms = std::vector<std::vector<Room>>(size, std::vector<Room>(size, Room()));
}
Cave::~Cave(){
	/*
	for(int r = 0; r < size; r++){
		for(int c = 0; c < size; c++){
			rooms[r][c].
		}
	}
	*/
}
void Cave::print(){
	std::cout << std::endl;
	
	for(int r = 0; r < size; r++){
		for(int c = 0; c < size; c++){
			if(rooms[r][c].getEvent() != NULL){
				//if((r == playerRow)&&(c == playerCol)){
					//std::cout << tolower(rooms[r][c].getEvent()->id);
				//}else{
				std::cout << rooms[r][c].getEvent()->id;
					//std::cout << "-";
				//}
			}else{
				if((r == playerRow)&&(c == playerCol)){
					std::cout << "+";
				}else{
					std::cout << "-";
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Cave::generateRooms(){
	games = 0;
	wins = 0;
	wumpusSlain = false;
	goldCollected = false;
	gameIsOver = false;
	
	arrows = 3;
	
	placePlayer();
	
	
	Room* rm;
	
	rm = findEmptyRoom();
	rm->setGold();
	
	rm = findEmptyRoom();
	rm->setPit();
	rm = findEmptyRoom();
	rm->setPit();
	
	rm = findEmptyRoom();
	rm->setBats();
	rm = findEmptyRoom();
	rm->setBats();
	
	rm = findEmptyRoom();
	rm->setWumpus();
	//delete rm;
}
int Cave::scanForEvent(){
	// look in the room the player is in for an event
	//print();
	
	if(rooms[playerRow][playerCol].getEvent() != NULL){
		// room needs to contain an event
		
		int key = rooms[playerRow][playerCol].getEvent()->inside();
		
		if(key == 0){
			// deadly wumpus key
			std::cout << "You stumble into the monster's room." << std::endl;
			std::cout << "You bump into the Wumpus and it eats you whole." << std::endl;
			std::cout << "You join the ranks of adventurers ";
			std::cout << "that never returned." << std::endl;
			gameIsOver = true;
		}else if(key == 1){
			// bat movement key
			std::cout << "You walk into a room filled with the sound of wings ";
			std::cout << "flapping." << std::endl;
			std::cout << "You are greeted with a pair of large red eyes." << std::endl;
			std::cout << "An angry superbat grabs you and carries you to another ";
			std::cout << "room." << std::endl;
			batGrabPlayer(); // move the player
			scanForEvent();  // scan the new room for events
			return 1;
		}else if(key == 2){
			// deadly pit key
			std::cout << "You find yourself in a room with no floor." << std::endl;
			std::cout << "During your one minute free fall, you consider ";
			std::cout << "just how deep the deathpit is." << std::endl;
			std::cout << "You join the ranks of adventurers ";
			std::cout << "that never returned." << std::endl;
			gameIsOver = true;
		}else if(key == 3){
			// gold collected key
			std::cout << "You spot a cube made of gold on a pedestal." << std::endl;
			std::cout << "You're suprised by its perfect uniformity." << std::endl;
			std::cout << "You find a spot for it in your backpack." << std::endl;
			removeGold();
			goldCollected = true;
			return 2;
		}else{
			// invalid key
			std::cout << "You find something you shouldn't" << std::endl;
		}
	}else{
		// empty room
		std::cout << "You find yourself in an empty room of little signifigance.\n";
		if((playerRow == exitRow)&&(playerCol == exitCol)){
			// escape rope will only be usable in an empty room
			// player is in the room with the escape rope
			if(goldCollected && wumpusSlain){
				// player has completed the objectives, they win!
				
				std::cout << "You spot the escape rope.\n" << std::endl;
				std::cout << "---------OBJECTIVES---------" << std::endl;
				std::cout << "[X] Slay Wumpus" << std::endl;
				std::cout << "[X] Collect the gold" << std::endl;
				std::cout << "[X] Return to escape rope and Make it out alive\n";
				std::cout << "----------------------------" << std::endl;
				std::cout << "You climb up the rope victorious." << std::endl;
				std::cout << "Congratulations!" << std::endl;
				gameIsOver = true;
				wins++;
			}
		}
	}
	return 0;
}
void Cave::scanForPercepts(){
	// look in adjacent rooms for events to display percepts
	if((playerRow - 1) >= 0){
		if(rooms[playerRow - 1][playerCol].getEvent() != NULL){
			rooms[playerRow - 1][playerCol].getEvent()->nearby();
		}
	}
	if((playerCol + 1) < size){
		if(rooms[playerRow][playerCol + 1].getEvent() != NULL){
			rooms[playerRow][playerCol + 1].getEvent()->nearby();
		}
	}
	if((playerRow + 1) < size){
		if(rooms[playerRow + 1][playerCol].getEvent() != NULL){
			rooms[playerRow + 1][playerCol].getEvent()->nearby();
		}
	}
	if((playerCol - 1) >= 0){
		if(rooms[playerRow][playerCol - 1].getEvent() != NULL){
			rooms[playerRow][playerCol - 1].getEvent()->nearby();
		}
	}
}
void Cave::transferPercepts(Computer& comp){
	// look in adjacent rooms for events to display percepts
	// computer controlled version
	
	comp.wumpusNear = false;
	comp.batsNear = false;
	comp.pitNear = false;
	comp.goldNear = false;
	
	if((playerRow - 1) >= 0){
		if(rooms[playerRow - 1][playerCol].getEvent() != NULL){
			int key = rooms[playerRow - 1][playerCol].getEvent()->inside();
			if(key == 0){
				// deadly wumpus key
				comp.wumpusNear = true;
			}else if(key == 1){
				// bat movement key
				comp.batsNear = true;
			}else if(key == 2){
				// deadly pit key
				comp.pitNear = true;
			}else{
				// gold collected key
				comp.goldNear = true;
			}
		}
	}else{
		comp.wallNorth = true;
	}
	if((playerCol + 1) < size){
		if(rooms[playerRow][playerCol + 1].getEvent() != NULL){
			int key = rooms[playerRow][playerCol + 1].getEvent()->inside();
			if(key == 0){
				// deadly wumpus key
				comp.wumpusNear = true;
			}else if(key == 1){
				// bat movement key
				comp.batsNear = true;
			}else if(key == 2){
				// deadly pit key
				comp.pitNear = true;
			}else{
				// gold collected key
				comp.goldNear = true;
			}
		}
	}else{
		comp.wallEast = true;
	}
	if((playerRow + 1) < size){
		if(rooms[playerRow + 1][playerCol].getEvent() != NULL){
			int key = rooms[playerRow + 1][playerCol].getEvent()->inside();
			if(key == 0){
				// deadly wumpus key
				comp.wumpusNear = true;
			}else if(key == 1){
				// bat movement key
				comp.batsNear = true;
			}else if(key == 2){
				// deadly pit key
				comp.pitNear = true;
			}else{
				// gold collected key
				comp.goldNear = true;
			}
		}
	}else{
		comp.wallSouth = true;
	}
	if((playerCol - 1) >= 0){
		if(rooms[playerRow][playerCol - 1].getEvent() != NULL){
			int key = rooms[playerRow][playerCol - 1].getEvent()->inside();
			if(key == 0){
				// deadly wumpus key
				comp.wumpusNear = true;
			}else if(key == 1){
				// bat movement key
				comp.batsNear = true;
			}else if(key == 2){
				// deadly pit key
				comp.pitNear = true;
			}else{
				// gold collected key
				comp.goldNear = true;
			}
		}
	}else{
		comp.wallWest = true;
	}
}
void Cave::placePlayer(){
	int row = rand()%size;
	int col = rand()%size;
	
	exitRow = row;
	exitCol = col;
	
	playerRow = row;
	playerCol = col;
}
bool Cave::gameShouldEnd(){
	if((arrows == 0) && (wumpusSlain == false)){
		// check to see if they ran out of arrows
		std::cout << std::endl << std::endl;
		std::cout << "You ran out of arrows. With no way to vanquish your enemy, ";
		std::cout << "you lose your mind." << std::endl;
		std::cout << "You join the ranks of adventurers ";
		std::cout << "that never returned." << std::endl;
		gameIsOver = true;
	}
	games++;
	return gameIsOver;
}
void Cave::printOptions(){
	if(!wumpusSlain)
	{
		if(arrows != 1)
		{
			std::cout << "You have " << arrows << " arrows left." << std::endl;
		}else{
			std::cout << "You have 1 arrow left, make it count!" << std::endl;
		}
	}
	
	if((playerRow - 1) >= 0){
		std::cout << "To walk north, enter 'n'" << std::endl;
	}else{
		std::cout << "There is a wall to your north." << std::endl;
	}	
	
	if((playerCol + 1) < size){
		std::cout << "To walk east, enter 'e'" << std::endl;
	}else{
		std::cout << "There is a wall to your east." << std::endl;
	}
	
	if((playerRow + 1) < size){
		std::cout << "To walk south, enter 's'" << std::endl;
	}else{
		std::cout << "There is a wall to your south." << std::endl;
	}
	
	if((playerCol - 1) >= 0){
		std::cout << "To walk west, enter 'w'" << std::endl;
	}else{
		std::cout << "There is a wall to your west." << std::endl;
	}
	
	if(wumpusSlain == false)
	{
		if((playerRow - 1) >= 0){
			std::cout << "To shoot an arrow north, enter 'N'" << std::endl;
		}
		if((playerCol + 1) < size){
			std::cout << "To shoot an arrow east, enter 'E'" << std::endl;
		}
		if((playerRow + 1) < size){
			std::cout << "To shoot an arrow south, enter 'S'" << std::endl;
		}
		if((playerCol - 1) >= 0){
			std::cout << "To shoot an arrow west, enter 'W'" << std::endl;
		}
	}else{
		if(arrows == 0){
			std::cout << "You have no arrows left, good thing you already killed ";
			std::cout << "the Wumpus." << std::endl;
		}else{
			std::cout << "You see no reason in shooting arrows since you already ";
			std::cout << "defeated the Wumpus." << std::endl;
		}
	}
}
void Cave::printObjectives(){
	std::cout << "---------OBJECTIVES---------" << std::endl;
	std::cout << "Complete the first two in any order." << std::endl;
	std::cout << "You cannot complete the third without the first two." << std::endl;
	if(wumpusSlain){
		std::cout << "[X] Slay Wumpus" << std::endl;
	}else{
		std::cout << "[ ] Slay Wumpus" << std::endl;
	}
	if(goldCollected){
		std::cout << "[X] Collect the gold" << std::endl;
	}else{
		std::cout << "[ ] Collect the gold" << std::endl;
	}
	std::cout << "[ ] Return to escape rope and Make it out alive" << std::endl;
	std::cout << "----------------------------" << std::endl;
}
void Cave::killWumpus(){
	// go through all rooms and delete the wumpus
	std::cout << "A piercing cry reverberates throughout the cave." << std::endl;
	std::cout << "Your arrow pierces the monster's heart." << std::endl;
	std::cout << "You have slain the Wumpus!" << std::endl;
	
	for(int r = 0; r < size; r++){
		for(int c = 0; c < size; c++){
			if(rooms[r][c].getEvent() != NULL){
				if(rooms[r][c].getEvent()->id == 'W'){
					rooms[r][c].setEmpty();
				}
			}
		}
	}
	
	wumpusSlain = true;
}
void Cave::removeGold(){
	// go through all rooms and delete the gold
	for(int r = 0; r < size; r++){
		for(int c = 0; c < size; c++){
			if(rooms[r][c].getEvent() != NULL){
				if(rooms[r][c].getEvent()->id == 'G'){
					rooms[r][c].setEmpty();
				}
			}
		}
	}
}
void Cave::moveWumpus(){
	// find a new home for the wumpus
	std::cout << "A deep growl fills the cave." << std::endl;
	std::cout << "By missing your shot, the Wumpus has awoken and ";
	std::cout << "found a new room to sleep in." << std::endl;
	
	
	int wumpusOldRow;
	int wumpusOldCol;
	
	for(int r = 0; r < size; r++){
		for(int c = 0; c < size; c++){
			if(rooms[r][c].getEvent() != NULL){
				if(rooms[r][c].getEvent()->id == 'W'){
					wumpusOldRow = r;
					wumpusOldCol = c;
				}
			}
		}
	}
	
	Room* rm;
	rm = findEmptyRoom();
	rm->setWumpus();
	//delete rm;
	
	rooms[wumpusOldRow][wumpusOldCol].setEmpty();
	
}
bool Cave::travelInDirection(int dir){
		if((dir == 0) && ((playerRow - 1) >= 0)){
			// walking north
			playerRow--;
		}else if((dir == 1) && ((playerCol + 1) < size)){
			// walking east
			playerCol++;
		}else if((dir == 2) && ((playerRow + 1) < size)){
			// walking south
			playerRow++;
		}else if((dir == 3) && ((playerCol - 1) >= 0)){
			// walking west
			playerCol--;
		}else{
			return false;
		}
	return true;
}
bool Cave::shootInDirection(int dir){
	if(wumpusSlain == true){
		return false;	// wumpus was already slain, invalid shoot instruction
	}
	
	bool hitWumpus = false;
	for(int i = 1; i < 4; i++){
		if((dir == 0) && ((playerRow - i) >= 0)){
			// shooting north
			if(rooms[playerRow - i][playerCol].getEvent() != NULL){
				if(rooms[playerRow - i][playerCol].getEvent()->id == 'W'){
					// hit the wumpus
					hitWumpus = true;
				}
			}
		}else if((dir == 1) && ((playerCol + i) < size)){
			// shooting east
			if(rooms[playerRow][playerCol + i].getEvent() != NULL){
				if(rooms[playerRow][playerCol + i].getEvent()->id == 'W'){
					// hit the wumpus
					hitWumpus = true;
				}
			}
		}else if((dir == 2) && ((playerRow + i) < size)){
			// shooting south
			if(rooms[playerRow + i][playerCol].getEvent() != NULL){
				if(rooms[playerRow + i][playerCol].getEvent()->id == 'W'){
					// hit the wumpus
					hitWumpus = true;
				}
			}
		}else if((dir == 3) && ((playerCol - i) >= 0)){
			// shooting west
			if(rooms[playerRow][playerCol - i].getEvent() != NULL){
				if(rooms[playerRow][playerCol - i].getEvent()->id == 'W'){
					// hit the wumpus
					hitWumpus = true;
				}
			}
		}else{
			if(i == 1){
				// if the user tried to fire an arrow into a wall, return invalid input
				return false;
			}
		}
	}
	if(hitWumpus){
		// you killed him
		killWumpus();
	}else{
		// see if he gets up and moves
		int num = rand()%4;
		if(num != 0){
			moveWumpus();
		}else{
			std::cout << "You missed the Wumpus." << std::endl;
			std::cout << "The cave seems still." << std::endl;
		}
	}
	arrows--;
	return true;
}
Room* Cave::findEmptyRoom(){
	int row = rand()%size;
	int col = rand()%size;
	
	if((row != playerRow) || (col != playerCol)){
		if(rooms[row][col].getEvent() == NULL){
			return &rooms[row][col];
		}
	}
	return findEmptyRoom();
}
void Cave::batGrabPlayer(){
	int row = rand()%size;
	int col = rand()%size;
	
	playerRow = row;
	playerCol = col;
}