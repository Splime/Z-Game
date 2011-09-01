/*
 * chapGlobals.h: A compilation of a few headers used everywhere,
 * plus *gasp* some global variables (Don't worry! They're constants!)
 */

#ifndef __GLOBALS_H_
#define __GLOBALS_H_

#include "human.h"
#include "world.h"
#include "viewer.h"
#include <curses.h>
#include <Windows.h>
#include <WinBase.h>
#include <ctime>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>

const int WINDOW_XSIZE = 80;
const int WINDOW_YSIZE = 32;

const int PANEL_WIDTH = 24;

class World;
class Human;

#endif