#pragma once

#include <iostream>
#include <string>

using namespace std;

class TaskForm
{
private:
    // Color codes
    static const string RESET;
    static const string BOLD;
    static const string DIM;
    static const string CYAN;
    static const string GREEN;
    static const string YELLOW;
    static const string RED;
    static const string BLUE;
    static const string MAGENTA;
    
    // UI Methods
    void displayHeader();
    void displayMenu();
    void printLine();
    void displayTaskSummary(const string& title, const string& description, 
                           int year, int month, int day,
                           int priorityChoice, int statusChoice, int assigneeId);
    
    // Input Methods
    string getInput(const string& prompt);
    int getIntInput(const string& prompt, int min, int max);
    
    // Utility Methods
    void clearScreen();
    bool userExists(int assigneeId);

public:
    void run();
    void createTask();
};