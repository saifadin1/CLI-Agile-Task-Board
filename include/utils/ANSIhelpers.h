#pragma once

void clearScreen();
void moveCursor(int row, int col);
void setColor(int color, int background = 0);
void resetColor();
void relativeCursor(int up, int right, int down, int left);
