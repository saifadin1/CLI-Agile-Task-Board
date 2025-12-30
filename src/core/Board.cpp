#include "Board.h"
#include "../../include/utils/ANSIhelpers.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;


void displayer (vector<Task> tasks)
{
    moveCursor(2,1);
    setColor(37, 44); // White text on blue background
    cout << "                              AGILE BOARD                              ";
    resetColor();

    // Column headers
    moveCursor(4, 1);
    setColor(30, 47); // Black text on white background
    cout << setw(30) << left << "TODO";
    cout << setw(30) << left << "IN PROGRESS";
    cout << setw(30) << left << "DONE";
    resetColor();
    
    // Separate tasks by status
    vector<Task> todoTasks, inProgressTasks, doneTasks;
    for (const Task& task : tasks) {
        switch (task.getStatus()) {
            case TaskStatus::ToDo:
                todoTasks.push_back(task);
                break;
            case TaskStatus::InProgress:
                inProgressTasks.push_back(task);
                break;
            case TaskStatus::Done:
                doneTasks.push_back(task);
                break;
        }
    }
    
        // Display tasks in columns
    int maxRows = max({todoTasks.size(), inProgressTasks.size(), doneTasks.size()});
    for (int i = 0; i < maxRows; i++) {
        moveCursor(6 + i, 1);
        
        // TODO column
        if (i < todoTasks.size()) {
            setColor(31); // Red for TODO
            cout << setw(28) << left << (to_string(todoTasks[i].getId()) + ": " + todoTasks[i].getTitle().substr(0, 24));
        } else {
            cout << setw(28) << " ";
        }
        cout << "  ";
        
        // IN PROGRESS column
        if (i < inProgressTasks.size()) {
            setColor(33); // Yellow for IN PROGRESS
            cout << setw(28) << left << (to_string(inProgressTasks[i].getId()) + ": " + inProgressTasks[i].getTitle().substr(0, 24));
        } else {
            cout << setw(28) << " ";
        }
        cout << "  ";
        
        // DONE column
        if (i < doneTasks.size()) {
            setColor(32); // Green for DONE
            cout << setw(28) << left << (to_string(doneTasks[i].getId()) + ": " + doneTasks[i].getTitle().substr(0, 24));
        }
        resetColor();
        cout << endl;
    }
}
void Board::displayBoard(vector<Task> tasks)
{
    clearScreen();
    displayer(tasks);
}

void Board::showTaskDetails(Task ts)
{
}

void Board::showError(string mesg)
{
}