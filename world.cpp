/*
 * world.cpp: Implementation of the World class
 */

#include "chapGlobals.h"
using namespace std;

World::World() {
	xSize = 128;
	ySize = 64;
	clock = 0;
	//Memory Stuff
	grid = new int*[ySize];
	for (int i = 0; i < ySize; i++)
		grid[i] = new int[xSize];
	//Fill 'er up
	for (int i = 0; i < ySize; i++)
		for (int j = 0; j < xSize; j++)
			grid[i][j] = ',';
}

World::World(string filename) {
	ifstream input(filename.c_str());
	if (!input) {
		cerr << "ERROR! " << filename << " not found, or there was an error opening it!\n";
		exit(1);
	}
	input >> xSize;
	input >> ySize;
	clock = 0;
	//Memory Stuff
	grid = new int*[ySize];
	for (int i = 0; i < ySize; i++)
		grid[i] = new int[xSize];
	//Fill 'er up
	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++) {
			char c;
			input >> c;
			if (c == 'L') {
				grid[i][j] = ',';
			}
			else if (c == 'W') {
				grid[i][j] = 247;
			}
			else if (c == 'T') {
				grid[i][j] = 5+A_ALTCHARSET;
			}
			else {
				grid[i][j] = c;
			}
			
		}
	}
	input.close();
}

World::~World() {
	for (int i = 0; i < ySize; i++)
		delete grid[i];
	delete grid;
}

int World::get(int y, int x) {
	return grid[y][x];
}

int World::getXSize() {
	return xSize;
}

int World::getYSize() {
	return ySize;
}

void World::addHuman(Human& h) {
	people.push_back(h);
}

void World::runMoves() {
	for (int i = 0; i < people.size(); i++) {
		people[i].makeMove(*this);
	}
	clock++;
}

bool World::isBlocked(int y, int x) {
	//Check for out of bounds
	if (y >= getYSize() || y < 0 || x >= getXSize() || x < 0)
		return false;
	//Normal
	int ch = get(y, x);
	if (ch == 247 || ch == 5+A_ALTCHARSET)
		return true;
	else
		return false;
}