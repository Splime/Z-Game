/*
 * viewer.cpp: Implementation of the Viewer class
 * New Plan as of 08/31/2011: Change Movement Setup to the following:
 * If we're in build mode, move cursor as normal
 * Otherwise, when we press the arrow keys, we're changing currX and currY
 */

#include "viewer.h"

Viewer::Viewer(World &inWorld) : w(inWorld) {
	viewMode = true;
	panelMode = false;
	currY = 0;
	currX = 0;
	currYSize = WINDOW_YSIZE;
	currXSize = WINDOW_XSIZE;
}

void Viewer::display() {
	//Print World
	int wy = 1;
	for (int gy = currY; gy < w.getYSize() && wy < currYSize-1; gy++, wy++) {
		int wx = 1;
		for (int gx = currX; gx < w.getXSize() && wx < currXSize-1; gx++, wx++) {
			int ch = w.get(gy, gx);
			//Color On
			if (ch == 247)
				attron(COLOR_PAIR(1));
			if (ch == ',' || ch == 5+A_ALTCHARSET)
				attron(COLOR_PAIR(2));
			//Print
			mvaddch(wy, wx, ch);
			//Color Off
			if (ch == 247)
				attroff(COLOR_PAIR(1));
			if (ch == ',' || ch == 5+A_ALTCHARSET)
				attroff(COLOR_PAIR(2));

		}
	}
	//Then Print Humans
	vector<Human> peeps = w.getPeople();
	for (int i = 0; i < peeps.size(); i++) {
		if(peeps[i].getY()>=currY && peeps[i].getY()<currY+currYSize-1 && peeps[i].getX()>=currX && peeps[i].getX()<currX+currXSize-1)
			mvaddch(peeps[i].getY()-currY+1, peeps[i].getX()-currX+1, 1 + A_ALTCHARSET);
	}
	//Border is next
	//Top Part
	for (int i = 0; i < currXSize; i++) {
		mvaddch(0, i, 48 + A_ALTCHARSET);
	}
	//Mids
	for (int i = 1; i < currYSize-1; i++) {
		mvaddch(i, 0, 48 + A_ALTCHARSET);
		mvaddch(i, currXSize-1, 48 + A_ALTCHARSET);
	}
	//Bottom Part
	for (int i = 0; i < currXSize; i++) {
		mvaddch(currYSize-1, i, 48 + A_ALTCHARSET);
	}
	mvprintw(0,0,"%i",w.getClock());
	mvprintw(0,34,"Chap\'s Game!");
	

	//Panel Time!
	if (panelMode) {
		int panelStartX = WINDOW_XSIZE-PANEL_WIDTH;
		//Fill in panel with blanks
		for (int i = panelStartX; i < WINDOW_XSIZE; i++) {
			for (int j = 0; j < WINDOW_YSIZE; j++) {
				mvaddch(j, i, ' ');
			}
		}
		//And some fun shtuff
		mvprintw(2, panelStartX+1, "'ello guvna!");
		mvprintw(4, panelStartX+1, "TODO for v0.02:");
		mvprintw(6, panelStartX+1, "Zombies!");
		mvprintw(7, panelStartX+1, "  (We'll want some");
		mvprintw(8, panelStartX+1, "  inheritance!)");
		mvprintw(10, panelStartX+1, "Actual Pathing!");
		mvprintw(11, panelStartX+1, "  (Sorta)");

		mvprintw(27, panelStartX+1, "Created 2011-07-22");
		mvprintw(28, panelStartX+1, "v0.01d  2011-08-17");
		mvprintw(29, panelStartX+1, "v0.01e  2011-08-31");

		//New Border!
		//Top Part
		for (int i = panelStartX; i < WINDOW_XSIZE; i++) {
			mvaddch(0, i, 48 + A_ALTCHARSET);
		}
		//Mids
		for (int i = 1; i < currYSize-1; i++) {
			mvaddch(i, panelStartX-1, 48 + A_ALTCHARSET);
			mvaddch(i, WINDOW_XSIZE-1, 48 + A_ALTCHARSET);
		}
		//Bottom Part
		for (int i = panelStartX; i < WINDOW_XSIZE; i++) {
			mvaddch(currYSize-1, i, 48 + A_ALTCHARSET);
		}
	}
}

void Viewer::setViewMode(bool view) {
	viewMode = view;
	if (viewMode)
		curs_set(0);
	else
		curs_set(2);
}

void Viewer::flipViewMode() {
	viewMode = !viewMode;
	if (viewMode)
		curs_set(0);
	else
		curs_set(2);
}

bool Viewer::isViewMode() {
	return viewMode;
}

void Viewer::flipPanelMode() {
	panelMode = !panelMode;
	if (panelMode) {
		currXSize = WINDOW_XSIZE - PANEL_WIDTH;
	}
	else {
		currXSize = WINDOW_XSIZE;
		//If we're in build mode, fix the cursor position
		if (!isViewMode()) {
			currXSize = WINDOW_XSIZE - PANEL_WIDTH;
			int r, c;
			getyx(stdscr, r, c);
			//First, a quick screen check
			
			if (currX + getXSize() > w.getXSize()) {
				int spec = currX + getXSize() - w.getXSize() - 2;
				currX -= spec;
				c += PANEL_WIDTH;
				c -= spec;
			}
			move(r, c);
			currXSize = WINDOW_XSIZE;
			scrollScreen(r, c);
		}
		else if (currX + getXSize() > w.getXSize()) 
			currX = w.getXSize() - getXSize() + 2;
	}
}

bool Viewer::isPanelMode() {
	return panelMode;
}

void Viewer::scrollScreen(int& row, int& col) {
	


	int yBuf = 4;
	int yScroll = 8;
	int wy = currY + row - 1;
	int xBuf = 8;
	int xScroll = 16;
	int wx = currX + col - 1;
	
	//Down
	if (row > currYSize-1-yBuf) {
		if (currY + currYSize-2 + yScroll >= w.getYSize()-1) {
			yScroll = w.getYSize() - currY - currYSize+2;
		}
		row-=yScroll;
		currY+=yScroll;
	}
	//Up
	else if (row < yBuf+1) {
		if (currY - yScroll <= 0) {
			yScroll = currY;
		}
		row+=yScroll;
		currY-=yScroll;
	}
	
	//Right
	if (col > currXSize-1-xBuf) {
		if (currX + currXSize-2 + xScroll >= w.getXSize()-1) {
			xScroll = w.getXSize() - currX - currXSize+2;
		}
		col-=xScroll;
		currX+=xScroll;
	}
	//Left
	else if (col < xBuf+1) {
		if (currX - xScroll <= 0) {
			xScroll = currX;
		}
		col+=xScroll;
		currX-=xScroll;
	}
}

void Viewer::moveCursor(int& y, int& x, int c) {
	int amnt = 1;
	if (isViewMode())
		amnt = 8;
	//If we're in view mode, just change currY/X
	if (isViewMode()) {
		if (c == KEY_LEFT) {
			currX -= amnt;
			if (currX < 0)
				currX = 0;
		}
		else if (c == KEY_RIGHT) {
			currX += amnt;
			if (currX + getXSize() > w.getXSize())
				currX = w.getXSize() - getXSize() + 2;
		}
		else if (c == KEY_UP) {
			currY -= amnt;
			if (currY < 0)
				currY = 0;
		}
		else if (c == KEY_DOWN) {
			currY += amnt;
			if (currY + getYSize() > w.getYSize())
				currY = w.getYSize() - getYSize() + 2;
		}
	}
	//Otherwise, just change x and y and then scroll
	else {
		if (c == KEY_LEFT) {
			if (x > amnt)
				x-=amnt;
			else
				x = 1;
		}
		else if (c == KEY_RIGHT) {
			if (x < getXSize()-1-amnt)
				x+=amnt;
			else
				x = getXSize()-2;
		}
		else if (c == KEY_UP) {
			if (y > amnt)
				y-=amnt;
			else
				y = 1;
		}
		else if (c == KEY_DOWN) {
			if (y < getYSize()-1-amnt)
				y+=amnt;
			else
				y = getYSize()-2;
		}
		scrollScreen(y, x);
	}
	
}