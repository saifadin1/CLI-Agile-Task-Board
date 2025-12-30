#include "Board.h"
#include "../../include/utils/ANSIhelpers.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <User.h>

using namespace std;

User *CURRUSER = new User(1, "", "");

void displayer(vector<Task> tasks)
{
    moveCursor(2, 1);
    setColor(37, 44); // White text on blue background
    cout << "                                       AGILE BOARD                                       ";
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
    for (const Task &task : tasks)
    {
        switch (task.getStatus())
        {
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
    for (int i = 0; i < maxRows; i++)
    {
        moveCursor(6 + i, 1);

        // TODO column
        if (i < todoTasks.size())
        {
            setColor(31); // Red for TODO
            cout << setw(28) << left << (to_string(todoTasks[i].getId()) + ": " + todoTasks[i].getTitle().substr(0, 24));
        }
        else
        {
            cout << setw(28) << " ";
        }
        cout << "  ";

        // IN PROGRESS column
        if (i < inProgressTasks.size())
        {
            setColor(33); // Yellow for IN PROGRESS
            cout << setw(28) << left << (to_string(inProgressTasks[i].getId()) + ": " + inProgressTasks[i].getTitle().substr(0, 24));
        }
        else
        {
            cout << setw(28) << " ";
        }
        cout << "  ";

        // DONE column
        if (i < doneTasks.size())
        {
            setColor(32); // Green for DONE
            cout << setw(28) << left << (to_string(doneTasks[i].getId()) + ": " + doneTasks[i].getTitle().substr(0, 24));
        }
        resetColor();
        cout << endl;
    }
}

void displayButtons(int selectedButton = 0)
{
    // Store current cursor position and move to buttons area
    moveCursor(20, 1);
    cout << "Navigate with Arrow Keys/Tab, Press Enter to select:" << endl;

    // Button 1
    relativeCursor(0, 2, 0, 0);
    if (selectedButton == 0)
    {
        setColor(30, 47);
    }
    cout << "[ My Tasks ]" << endl;
    resetColor();

    // Button 2
    relativeCursor(0, 1, 0, 0);
    if (selectedButton == 1)
    {
        setColor(30, 47);
    }
    cout << "[ Other Person ]" << endl;
    resetColor();

    // Button 3
    relativeCursor(0, 1, 0, 0);
    if (selectedButton == 2)
    {
        setColor(30, 47);
    }
    cout << "[ Move to Next State ]" << endl;
    resetColor();
}
void handleNavigation(vector<Task> tasks, int selectedButton = 0)
{
    bool buttonsDisplayed = false;

    while (true)
    {
        // Display buttons only once at the beginning
        if (!buttonsDisplayed)
        {
            displayButtons(selectedButton);
            buttonsDisplayed = true;
        }

        char key = _getch(); // Use _getch() instead of getche() to avoid echoing

        if (key == 27) // Escape key
        {
            break;
        }
        else if (key == '\t') // Tab key
        {
            selectedButton = (selectedButton + 1) % 3;
            displayButtons(selectedButton); // Redraw buttons with new selection
        }
        else if (key == '\r' || key == '\n') // Enter key
        {
            // Handle button selection here
            switch (selectedButton)
            {
            case 0:
                // show my task & won't end unless escape is clicked
                system("cls");
                displayer(tasks);
                while (_getch() != 27)
                {
                    continue;
                }
                // show old board
                system("cls");
                displayer(tasks);
                displayButtons(selectedButton);
                break;
            case 1:
                // show other person tasks & won't end unless escape is clicked
                system("cls");
                displayer(tasks);
                while (_getch() != 27)
                {
                    continue;
                }
                // show old board
                system("cls");
                displayer(tasks);
                displayButtons(selectedButton);
                break;
            case 2:
                // show other person tasks & won't end unless escape is clicked
                system("cls");
                // call move to next state function
                // show old board
                system("cls");
                displayer(tasks);
                displayButtons(selectedButton);
                break;
            }
        }
        else if (key == -32 || key == 0) // Arrow keys (Windows specific)
        {
            key = _getch(); // Get the actual arrow key code
            if (key == 72)  // Up arrow
            {
                selectedButton = (selectedButton - 1 + 3) % 3;
                displayButtons(selectedButton);
            }
            else if (key == 80) // Down arrow
            {
                selectedButton = (selectedButton + 1) % 3;
                displayButtons(selectedButton);
            }
        }
    }
}

void Board::displayBoard(vector<Task> tasks)
{
    clearScreen();
    displayer(tasks);
    handleNavigation(tasks); // This will now handle displaying buttons and navigation
}

void Board::showTaskDetails(Task ts)
{
}

void Board::showError(string mesg)
{
}