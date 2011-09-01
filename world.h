/*
 * world.h: The World class, holds info on the game's world
 */

#ifndef __WORLD_H_
#define __WORLD_H_

#include "human.h"
#include <vector>
#include "chapGlobals.h"
using namespace std;

class Human;

class World {
public:
	World(); //Default Constructor, makes a boring world
	World(string filename); //Constructor, loads map from file
	~World(); //Destructor, cuz we've got dynamic memories

	int get(int y, int x); //Obtains the character at the y,x coords
	int getXSize(); //Obtains the width of the grid
	int getYSize(); //Obtains the height of the grid
	void addHuman(Human& h); //Adds a human to the World
	void runMoves(); //Makes all of the people in the world do stuff
	vector<Human> getPeople() { return people; } //Returns a nice vector of people for display uses
	int getClock() { return clock; } //Returns the turn# for display uses
	bool isBlocked(int y, int x); //Returns if a spot is walkable or not

private:
	int** grid;
	int xSize;
	int ySize;
	vector<Human> people;
	int clock;
};

#endif