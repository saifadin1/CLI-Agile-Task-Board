#pragma once

#include <iostream>
#include <string>

using namespace std;


class TaskForm
{
private:
    void displayHeader();
    void displayMenu();
    string getInput(const string& prompt);
    int getIntInput(const string& prompt, int min, int max);
    void clearScreen();
    void printSeparator();
    bool userExists(int assigneeId);

public:
    void run();
    void createTask();
};