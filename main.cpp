/*
 * CHAP'S GAME v0.01e
 * Started 2011/07/22
 *
 * main.cpp: Main driver of the program
 *
 * TODO: Now that world1.txt is complete, make the world loader, and add fancy graphics
 */

#include "chapGlobals.h"
using namespace std;

void delay(int ms); //Delays the process by ms milliseconds
void startCurses(); //Does the init stuff
void moveCursor(int& y, int& x, int c, Viewer& ui); //Moves the cursor based on input
vector<int> getInput(); //Obtains all of the input since the last turn

int main() {
	//Get curses started
	system("mode 80,32");
	startCurses();
	//Some variables
	int c = 0;
	move(1,1);
	Human h(30, 10);
	//Generate a grid to play on
	World w("world1.txt");
	w.addHuman(h);
	Viewer ui(w);
	//The game loop
	while (1) {
		//Get the input
		vector<int> input = getInput();
		if (input.size() == 0)
			c = ERR;
		else
			c = input[0];
		//TO DO: Parse input more meaningfully
		//Break on ENTER
		if (c == 10) {
			break;
		}
		//B triggers "Build-Mode" - TODO Later
		if (c == 'b') {
			ui.flipViewMode();
		}
		//P triggers "Panel-Mode" - Adds a panel to the side
		if (c == 'p') {
			ui.flipPanelMode();
		}
		//Store prev. cursor location
		int row, col;
		getyx(stdscr, row, col);
		//Move cursor coords based on keys
		ui.moveCursor(row, col, c);
		//Adjust row, col based on position	
		//ui.scrollScreen(row, col);
		//Setup the main grid display
		ui.display();
		move(row, col); //Actual cursor move, just resets after print
		refresh();
		//Delay, then setup for next round
		delay(50);
		w.runMoves();
	}

	endwin();
	return 0;
}

void delay(int ms) {
	Sleep(ms);
}

void startCurses() {
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);
	timeout(0);
	curs_set(0); //CHANGE when we fix cursor movement (again...)
	start_color();
	//Now set up some color pairs
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

vector<int> getInput() {
	vector<int> inputStream;
	int c = getch();
	while (c != ERR) {
		inputStream.push_back(c);
		c = getch();
	}
	return inputStream;
}
