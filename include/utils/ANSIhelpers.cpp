
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <termios.h>

using namespace std;
void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

void moveCursor(int row, int col)
{
    cout << "\033[" << row << ";" << col << "H";
}

void setColor(int color)
{
    cout << "\033[" << color << "m";
}

void resetColor()
{
    cout << "\033[0m";
}
