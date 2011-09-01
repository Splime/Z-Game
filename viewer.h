/*
 * viewer.h: The Viewer class, responsible for displaying stuff
 */

#ifndef __VIEWER_H_
#define __VIEWER_H_

#include "chapGlobals.h"

class Viewer {
public:
	Viewer(World& inWorld);
	void display();
	void setViewMode(bool view);
	void flipViewMode();
	bool isViewMode();
	void flipPanelMode();
	bool isPanelMode();
	void scrollScreen(int& row, int& col);
	int getYSize() { return currYSize; }
	int getXSize() { return currXSize; }
	void moveCursor(int& y, int& x, int c);

private:
	bool viewMode;
	bool panelMode;
	World& w;
	int currY, currX;
	int currYSize;
	int currXSize;

};

#endif