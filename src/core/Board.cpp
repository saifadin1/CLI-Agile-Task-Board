#include "Board.h"
#include "../../include/utils/ANSIhelpers.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <User.h>
#include "taskDAO.h"

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

void displayButtons(int selectedButton = 0,string userInput="")
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
    cout << "[ Other Person ]"; 
    cout << "  User ID: [";
    cout << setw(5) << left;
    if(selectedButton==1)
        cout  << userInput;
    cout << "]" << endl;
    resetColor();
    // Button 3
    relativeCursor(0, 1, 0, 0);
    if (selectedButton == 2)
    {
        setColor(30, 47);
    }
    cout << "[ Move to Next State ]" ;
    cout << "  Task ID: [";
    cout << setw(5) << left;
    if(selectedButton==2)
        cout << userInput;
    cout << "]" << endl;
    resetColor();
    // Button 4
    relativeCursor(0, 1, 0, 0);
    if (selectedButton == 3)
    {
        setColor(30, 47);
    }
    cout << "[ Task Details ]" ;
    cout << "  Task ID: [";
    cout << setw(5) << left;
    if(selectedButton==3) 
        cout << userInput;
    cout << "]" << endl;
    resetColor();

    // Button 5
    relativeCursor(0, 1, 0, 0);
    if (selectedButton == 4)
    {
        setColor(30, 47);
    }
    cout << "[ Task Form ]" ;
    cout << endl;
    resetColor();
}
void showMessage(string mesg,bool flag)
{
    /// UI for Message
    char key=_getch();
    while (key != '\r' && key != '\n')
    {
        key=_getch();
        continue;
    }
    
}
TaskStatus moveStatus(TaskStatus ts){
    if(ts==TaskStatus::ToDo)
        return TaskStatus::InProgress;
    else
        return TaskStatus::Done;
}
void handleNavigation(vector<Task> tasks, int selectedButton = 0)
{
    bool buttonsDisplayed = false;
    string userInput = "";
    TaskDAO dao;
    while (true)
    {
        // Display buttons only once at the beginning
        if (!buttonsDisplayed)
        {
            displayButtons(selectedButton,userInput);
            buttonsDisplayed = true;
        }

        char key = _getch(); // Use _getch() instead of getche() to avoid echoing

        if (key == 27) // Escape key
        {
            break;
        }
        else if (key == '\t') // Tab key
        {
            selectedButton = (selectedButton + 1) % 5;
            userInput="";
            displayButtons(selectedButton,userInput); // Redraw buttons with new selection
        }
        else if (key == '\r' || key == '\n') // Enter key
        {
            // Handle button selection here
            switch (selectedButton)
            {
            case 0:
                {
                    // show my task & won't end unless escape is clicked
                    vector<Task> myTasks = dao.selectTasksByUserId(CURRUSER->getId());
                    system("cls");
                    displayer(myTasks);
                    while (_getch() != 27)
                    {
                        continue;
                    }
                    // show old board
                    system("cls");
                    displayer(tasks);
                    displayButtons(selectedButton,userInput);
                    break;
                }
            case 1:
                {
                    // show other person tasks & won't end unless escape is clicked
                    if (userInput.empty())
                    {
                        // Show error or do nothing if no ID entered
                        break;
                    }

                    int userId =  stoi(userInput);
                    vector<Task> otherPersonTasks = dao.selectTasksByUserId(userId);
                    system("cls");
                    displayer(otherPersonTasks);
                    while (_getch() != 27)
                    {
                        continue;
                    }
                    // show old board
                    userInput="";
                    system("cls");
                    displayer(tasks);
                    displayButtons(selectedButton,userInput);
                    break;
                }
            case 2: /// Move Next State
                {
                    if (userInput.empty())
                    {
                        break;
                    }
                    int taskId = stoi(userInput);
                    auto task = dao.selectTask(taskId);
                    if(task==nullptr){
                        showMessage("No Task with this Id",0);
                    }else{
                        task->setStatus(moveStatus(task->getStatus()));
                        dao.updateTask(*task);
                        tasks=dao.selectAllTasks();
                        showMessage("Task Moved Correctly\n",1);
                    }
                    // show old board
                    userInput="";
                    system("cls");
                    displayer(tasks);
                    displayButtons(selectedButton,userInput);
                    break;
                }
                case 3: /// Show Task Details (Saif)
                {
                    if (userInput.empty())
                    {
                        break;
                    }
                    int taskId = stoi(userInput);
                    auto task = dao.selectTask(taskId);
                    if(task==nullptr){
                        showMessage("No Task with this Id",0);
                    }else{
                        // Call Saif Function
                    }
                    // show old board
                    userInput="";
                    system("cls");
                    displayer(tasks);
                    displayButtons(selectedButton,userInput);
                    break;
                }
                case 4: /// Task Form (Fahi)
                {
                    // Call Fathi Function
                    system("cls");
                    displayer(tasks);
                    displayButtons(selectedButton,userInput);
                    break;
                }
            }
        }
        else if (key == -32 || key == 0) // Arrow keys (Windows specific)
        {
            key = _getch(); // Get the actual arrow key code
            if (key == 72)  // Up arrow
            {
                selectedButton = (selectedButton - 1 + 5) % 5;
                userInput="";
                displayButtons(selectedButton,userInput);
            }
            else if (key == 80) // Down arrow
            {
                selectedButton = (selectedButton + 1) % 5;
                userInput="";
                displayButtons(selectedButton,userInput);
            }
        }
        else if (selectedButton == 1 || selectedButton == 2 || selectedButton==3) // Handle text input for buttons 2 and 3
        {
            string* currentInput = &userInput;
            
            if (key >= '0' && key <= '9') // Number keys
            {
                if (currentInput->length() < 5) // Limit to 5 digits
                {
                    *currentInput += key;
                    displayButtons(selectedButton, userInput);
                }
            }
            else if (key == 8) // Backspace
            {
                if (!currentInput->empty())
                {
                    currentInput->pop_back();
                    displayButtons(selectedButton, userInput);
                }
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

