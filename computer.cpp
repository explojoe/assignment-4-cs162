/*********************************************************************
** Program Filename: computer.cpp
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
#include "computer.hpp"

/* computer brain logic
whenever wumpus is near, shoot an arrow in a random valid direction
whenever gold is near, walk in random valid direction and retrace steps until acquired

ignore bats
ignore pits

roam
*/
Computer::Computer(){
	//cave = myCave;
	
	wumpusNear = false;
	batsNear = false;
	pitNear = false;
	goldNear = false;
	
	triedNorth = false;
	triedEast = false;
	triedSouth = false;
	triedWest = false;
	
	wallNorth = false;
	wallEast = false;
	wallSouth = false;
	wallWest = false;
	
	pursuingGold = false;
	
	lastDir = -1;
	
	
}
Computer::~Computer(){}
char Computer::pickDirection(bool isShooting){
	bool canGoNorth = true;
	bool canGoEast = true;
	bool canGoSouth = true;
	bool canGoWest = true;
	
	int numDirections = 4;
	
	if(triedNorth || wallNorth){
		canGoNorth = false;
		numDirections--;
	}
	if(triedEast || wallEast){
		canGoEast = false;
		numDirections--;
	}
	if(triedSouth || wallSouth){
		canGoSouth = false;
		numDirections--;
	}
	if(triedWest || wallWest){
		canGoWest = false;
		numDirections--;
	}
	if(!isShooting){
		wallNorth = false;
		wallEast = false;
		wallSouth = false;
		wallWest = false;
	}
	while(true){
		int dir = rand()%4;
		if(dir == 0){
			if(canGoNorth){
				if(isShooting){
					return 'N';
				}else{
					return 'n';
				}
			}else{
				continue;
			}
		}else if(dir == 1){
			if(canGoEast){
				if(isShooting){
					return 'E';
				}else{
					return 'e';
				}
			}else{
				continue;
			}
		}else if(dir == 2){
			if(canGoSouth){
				if(isShooting){
					return 'S';
				}else{
					return 's';
				}
			}else{
				continue;
			}
		}else{
			if(canGoWest){
				if(isShooting){
					return 'W';
				}else{
					return 'w';
				}
			}else{
				continue;
			}
		}
		
	}
	
}
char Computer::makeDecision(){
	if(wumpusNear){
		return pickDirection(true); // shoot him
	}else if(goldNear){
		// gold is near
		pursuingGold = true;
		
		if(lastDir == 0){
			triedSouth = true;
		}
		if(lastDir == 1){
			triedWest = true;
		}
		if(lastDir == 2){
			triedNorth = true;
		}
		if(lastDir == 3){
			triedEast = true;
		}
	}else{
		// gold is not near
		if(pursuingGold){
			// the direction we just went was bad, go back
			if(lastDir == 0){
				triedSouth = true;
			}
			if(lastDir == 1){
				triedWest = true;
			}
			if(lastDir == 2){
				triedNorth = true;
			}
			if(lastDir == 3){
				triedEast = true;
			}
		}
		//return pickDirection(false);
	}
	return pickDirection(false);
}
void Computer::batTransport(){
	// forget everything
	
	wumpusNear = false;
	batsNear = false;
	pitNear = false;
	goldNear = false;
	
	triedNorth = false;
	triedEast = false;
	triedSouth = false;
	triedWest = false;
	
	wallNorth = false;
	wallEast = false;
	wallSouth = false;
	wallWest = false;
	
	pursuingGold = false;
	
	lastDir = -1;
}
void Computer::goldAcquired(){
	pursuingGold = false;
	acquiredGold = true;
}