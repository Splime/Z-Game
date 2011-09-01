/*
 * human.cpp: Implementation of the Human class
 */

#include "chapGlobals.h"

Human::Human() {
	x = 0; y = 0; waitTime = 4; turnsPast = waitTime-1;
}

Human::Human(int ax, int ay) {
	x = ax; y = ay; waitTime = 4; turnsPast = waitTime-1;
}

void Human::makeMove(World& w) {
	turnsPast++;
	//Check if we can move
	if (turnsPast < waitTime)
		return;
	//Move
	turnsPast = 0;
	if (!w.isBlocked(y, x+1))
	{
		x++;
	}
	else if (!w.isBlocked(y+1, x))
	{
		y++;
	}
}