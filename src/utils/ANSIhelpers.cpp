#include "../../include/utils/ANSIhelpers.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

void moveCursor(int row, int col)
{
    cout << "\033[" << row << ";" << col << "H";
}

void setColor(int color, int background)
{
    cout << "\033[" << color << ";" << background << "m";
}

void resetColor()
{
    cout << "\033[0m";
}