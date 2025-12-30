#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include "TaskForm.h"
#include "taskDAO.h"
#include "Task.h"
#include "DatabaseManager.h"

using namespace std;

void TaskForm::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TaskForm::printSeparator()
{
    cout << "\n" << string(60, '=') << "\n";
}

bool TaskForm::userExists(int assigneeId)
{
    if (assigneeId == 0)
    {
        return true;  // 0 means unassigned, which is always valid
    }
    
    TaskDAO dao;
    User* user = dao.selectUser(assigneeId);
    
    if (user != nullptr)
    {
        delete user;
        return true;
    }
    
    return false;
}

void TaskForm::displayHeader()
{
    printSeparator();
    cout << "               CREATE NEW TASK" << endl;
    printSeparator();
}

void TaskForm::displayMenu()
{
    cout << "\n";
    cout << "  [1] Add New Task" << endl;
    cout << "  [2] Cancel and Exit" << endl;
    printSeparator();
}

string TaskForm::getInput(const string& prompt)
{
    string input;
    cout << "  " << prompt << ": ";
    getline(cin, input);
    return input;
}

int TaskForm::getIntInput(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << "  " << prompt << " (" << min << "-" << max << "): ";
        
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= min && value <= max)
            {
                return value;
            }
            cout << "  [!] Invalid input! Please enter a number between " << min << " and " << max << ".\n";
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Invalid input! Please enter a valid number.\n";
        }
    }
}

void TaskForm::createTask()
{
    displayHeader();
    
    // Get task details from user
    cout << "\n>> ENTER TASK DETAILS:\n" << endl;
    
    string title = getInput("Task Title");
    if (title.empty())
    {
        cout << "\n  [!] Task title cannot be empty!" << endl;
        return;
    }
    
    string description = getInput("Description");
    
    // Get due date
    cout << "\n>> DUE DATE:\n";
    int year = getIntInput("  Year", 2025, 2030);
    int month = getIntInput("  Month", 1, 12);
    int day = getIntInput("  Day", 1, 31);
    Date dueDate{year, month, day};
    
    // Get priority
    cout << "\n>> PRIORITY LEVEL:\n";
    cout << "  [0] Low\n  [1] Medium\n  [2] High\n";
    int priorityChoice = getIntInput("  Select Priority", 0, 2);
    Priority priority = static_cast<Priority>(priorityChoice);
    
    // Get status
    cout << "\n>> TASK STATUS:\n";
    cout << "  [0] To Do\n  [1] In Progress\n  [2] Done\n";
    int statusChoice = getIntInput("  Select Status", 0, 2);
    TaskStatus status = static_cast<TaskStatus>(statusChoice);
    
    // Get assignee ID
    cout << "\n>> ASSIGNEE:\n";
    int assigneeId = getIntInput("  Assignee ID (0 for unassigned)", 0, 100);
    
    // Confirm before saving
    printSeparator();
    cout << "\n>> TASK SUMMARY:\n";
    cout << "  Title:       " << title << endl;
    cout << "  Description: " << description << endl;
    cout << "  Due Date:    " << year << "-" << setfill('0') << setw(2) << month << "-" << setw(2) << day << endl;
    cout << "  Priority:    " << (priorityChoice == 0 ? "Low" : priorityChoice == 1 ? "Medium" : "High") << endl;
    cout << "  Status:      " << (statusChoice == 0 ? "To Do" : statusChoice == 1 ? "In Progress" : "Done") << endl;
    cout << "  Assignee ID: " << assigneeId << endl;
    printSeparator();
    
    cout << "\n  Save this task? (Y/N): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (confirm != 'Y' && confirm != 'y')
    {
        cout << "\n  [X] Task creation cancelled.\n";
        return;
    }
    
    // Validate assignee exists in database
    if (assigneeId != 0 && !userExists(assigneeId))
    {
        cout << "\n  [ERROR] Assignee with ID " << assigneeId << " does not exist in database!\n";
        return;
    }
    
    // Save to database
    Task newTask(0, title, description, dueDate, priority, status, assigneeId);
    TaskDAO dao;
    
    if (dao.createTask(newTask))
    {
        cout << "\n  [SUCCESS] Task saved successfully!\n";
    }
    else
    {
        cout << "\n  [ERROR] Failed to save task.\n";
    }
}

void TaskForm::run()
{
    // Connect to database
    DatabaseManager* db = DatabaseManager::getInstance();
    if (!db->connect("data/agile_board.db"))
    {
        cout << "Failed to connect to database!" << endl;
        return;
    }
    
    bool running = true;
    
    while (running)
    {
        clearScreen();
        displayHeader();
        displayMenu();
        
        int choice = getIntInput("Select an option", 1, 2);
        
        switch (choice)
        {
            case 1:
                clearScreen();
                createTask();
                
                cout << "\n  Press Enter to continue...";
                cin.get();
                break;
                
            case 2:
                cout << "\n  Exiting Task Form. Goodbye!\n";
                running = false;
                break;
        }
    }
    
    db->disconnect();
}