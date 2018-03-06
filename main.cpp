/*********************************************************************
** Program Filename: main.cpp
** Author: Joshua Wentzel
** Date: 3/4/2018
** Description: Enter the cave, fight the Wumpus, and steal the gold.
** Input: Movement orders
** Output: Hunt the Wumpus gameplay
*********************************************************************/

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <time.h> 

#include <typeinfo>

#include "cave.hpp"
#include "room.hpp"
#include "computer.hpp"


using namespace std;

int main(int argc, char *argv[]){
	//cout << argc << endl;
	if(argc == 2){
		int size = atoi(argv[1]);
		//cout << size << endl;
		if(size > 3){
			int levelSeed = time(NULL);
			int gameSeed = time(NULL);
			
			bool keepSeed = false;
			while(true){
				cout << endl << endl << endl << endl << endl << endl << endl;
				cout << "Welcome to Hunt the Wumpus!" << endl;
				cout << "Don't cave in, you can do it!" << endl;
				if(!keepSeed){
					levelSeed = time(NULL);
				}else{
					keepSeed = false;
				}
				
				Cave cave(size);
				
				
				srand(levelSeed);		// for generating the level
				cave.generateRooms();
				srand(gameSeed);		// for additional "random" events
				
				cout << "To have an AI play for you, enter 'Y'" << endl;
				char input;
				cin >> input;
				if((input == 'y')||(input == 'Y')){
					// AI will play
					Computer* comp = new Computer();
					
					cout << endl;
					cout << "You've climbed down into a square " << size << " by ";
					cout << size << " cave." << endl;
					
					cout << "You must avoid the hazards, kill the wumpus, ";
					cout << "grab the gold, and return to this room." << endl;
					cout << "Only then can you climb the escape rope, and emerge ";
					cout << "victorious!" << endl << endl;
					while(true){
						// game loop
						int outcome = cave.scanForEvent();
						if(outcome == 1){
							comp->batTransport();
						}else if(outcome == 2){
							comp->goldAcquired();
						}
						if(cave.gameShouldEnd()){
							break;
						}
						
						cave.transferPercepts(*comp);
						
						cout << endl;
						while(true){
							// input loop
							
							cave.printObjectives();
							cave.printOptions();
							
							std::string unused;
							
							cout << "Enter something to continue." << endl;
							cin >> unused;
							
							// AI control
							input = comp->makeDecision();
							
							printf("%c\n", input);
							cout << endl;
							cout << endl;
							cout << endl;
							switch(input){
								case 'n':
									if(!cave.travelInDirection(0)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'e':
									if(!cave.travelInDirection(1)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 's':
									if(!cave.travelInDirection(2)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'w':
									if(!cave.travelInDirection(3)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'N': 
									if(!cave.shootInDirection(0)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'E': 
									if(!cave.shootInDirection(1)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'S':
									if(!cave.shootInDirection(2)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'W':
									if(!cave.shootInDirection(3)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								default:
									std::cout << "Invalid choice, choose again.\n";
									continue;
							}
							break;
						}
						
						
					}
					delete comp;
				}else{
					// Human controlled
					cout << endl;
					cout << "You've climbed down into a square " << size << " by ";
					cout << size << " cave." << endl;
					
					cout << "You must avoid the hazards, kill the wumpus, ";
					cout << "grab the gold, and return to this room." << endl;
					cout << "Only then can you climb the escape rope, and emerge ";
					cout << "victorious!" << endl << endl;
					while(true){
						// game loop
						cave.scanForEvent();
						if(cave.gameShouldEnd()){
							break;
						}
						cave.scanForPercepts();
						cout << endl;
						cout << endl;
						cout << endl;
						while(true){
							// input loop
							
							cave.printObjectives();
							cave.printOptions();
							cin >> input;
							switch(input){
								case 'n':
									if(!cave.travelInDirection(0)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'e':
									if(!cave.travelInDirection(1)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 's':
									if(!cave.travelInDirection(2)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'w':
									if(!cave.travelInDirection(3)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'N': 
									if(!cave.shootInDirection(0)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'E': 
									if(!cave.shootInDirection(1)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'S':
									if(!cave.shootInDirection(2)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								case 'W':
									if(!cave.shootInDirection(3)){
										std::cout << "Invalid choice, choose again.\n";
										continue;
									}
									break;
								default:
									std::cout << "Invalid choice, choose again.\n";
									continue;
							}
							break;
						}
					}
				}
				cout << "To play again, enter 'Y'" << endl;
				cin >> input;
				if((input != 'y') && (input != 'Y')){
					break;
				}else{
					cout << "To keep the same cave configuration, enter 'Y'" << endl;
					cin >> input;
					if((input == 'y')||(input == 'Y')){
						keepSeed = true;
					}
				}
			}
			cout << "Thanks for playing, see you next time!" << endl;
		}else
		{
			cout << "Cave must be at least four rooms to a side." << endl;
		}
	}else{
		cout << "Please specify a cave size with a whole number." << endl;
	}
	return 0;
}