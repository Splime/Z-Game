/*
 * human.h: The Human class, holds info about a human in the world
 */

#ifndef __HUMAN_H_
#define __HUMAN_H_

#include "world.h"
#include "chapGlobals.h"
using namespace std;

class Human {

public:
	Human(); //Default Constructor: Puts a boring human at 0,0
	Human(int ax, int ay); //Constructor: Puts a boring human at ay,ax
	int getX() { return x; } //Gets X
	int getY() { return y; } //Gets Y
	void makeMove(World& w); //Figures out how to move based on looking at the world

private:
	int x;
	int y;
	int turnsPast;
	int waitTime;

};

#endif