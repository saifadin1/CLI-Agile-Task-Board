#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include "TaskForm.h"
#include "taskDAO.h"
#include "Task.h"
#include "DatabaseManager.h"

using namespace std;

// Color definitions
const string TaskForm::RESET = "\033[0m";
const string TaskForm::BOLD = "\033[1m";
const string TaskForm::DIM = "\033[2m";
const string TaskForm::CYAN = "\033[36m";
const string TaskForm::GREEN = "\033[32m";
const string TaskForm::YELLOW = "\033[33m";
const string TaskForm::RED = "\033[31m";
const string TaskForm::BLUE = "\033[34m";
const string TaskForm::MAGENTA = "\033[35m";

void TaskForm::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

TaskForm::TaskForm()
{
}


void TaskForm::printLine()
{
    cout << CYAN << "  " << string(58, '-') << RESET << "\n";
}

void TaskForm::displayHeader()
{
    cout << "\n";
    cout << BOLD << CYAN << "  +======================================================+\n";
    cout << "  |                       ADDING TASK                                    |\n";
    cout << "  +======================================================+" << RESET << "\n";
}

void TaskForm::displayMenu()
{
    printLine();
    cout << "\n";
    cout << GREEN << "    1. " << RESET << "Add New Task\n";
    cout << RED << "    2. " << RESET << "Exit\n";
    cout << "\n";
    printLine();
}

bool TaskForm::userExists(int assigneeId)
{
    if (assigneeId == 0)
    {
        return true;
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

string TaskForm::getInput(const string& prompt)
{
    string input;
    cout << CYAN << " -> " << RESET << prompt << ": ";
    getline(cin, input);
    return input;
}

int TaskForm::getIntInput(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << CYAN << "  -> " << RESET << prompt << " " << DIM << "(" << min << "-" << max << ")" << RESET << ": ";
        
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= min && value <= max)
            {
                return value;
            }
            cout << RED << "  [X] Invalid! Enter a number between " << min << " and " << max << RESET << "\n";
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "  [X] Invalid input! Please enter a number." << RESET << "\n";
        }
    }
}

void TaskForm::displayTaskSummary(const string& title, const string& description, 
                                   int year, int month, int day,
                                   int priorityChoice, int statusChoice, int assigneeId)
{
    printLine();
    cout << "\n" << BOLD << CYAN << "  TASK SUMMARY" << RESET << "\n";
    printLine();
    cout << GREEN << "  [1]" << RESET << " Title:       " << title << "\n";
    cout << GREEN << "  [2]" << RESET << " Description: " << description << "\n";
    cout << GREEN << "  [3]" << RESET << " Due Date:    " << MAGENTA << year << "-" << setfill('0') << setw(2) << month << "-" << setw(2) << day << RESET << "\n";
    cout << GREEN << "  [4]" << RESET << " Priority:    " << (priorityChoice == 0 ? GREEN + "Low" : priorityChoice == 1 ? YELLOW + "Medium" : RED + "High") << RESET << "\n";
    cout << GREEN << "  [5]" << RESET << " Status:      " << (statusChoice == 0 ? BLUE + "To Do" : statusChoice == 1 ? YELLOW + "In Progress" : GREEN + "Done") << RESET << "\n";
    cout << GREEN << "  [6]" << RESET << " Assignee:    " << (assigneeId == 0 ? YELLOW + "Unassigned" : to_string(assigneeId)) << RESET << "\n";
    printLine();
    cout << "\n";
    cout << YELLOW << "  [S]" << RESET << " Save Task\n";
    cout << YELLOW << "  [C]" << RESET << " Cancel\n";
    cout << CYAN << "  [1-6]" << RESET << " Edit Field\n";
    printLine();
}

void TaskForm::createTask()
{
    // Initialize task data
    string title = "";
    string description = "";
    int year = 2025;
    int month = 1;
    int day = 1;
    int priorityChoice = 0;
    int statusChoice = 0;
    int assigneeId = 0;
    
    bool editMode = true;
    int currentField = 1;
    
    while (editMode)
    {
        clearScreen();
        displayHeader();
        
        // Input phase - collect all fields first time
        if (title.empty() && currentField == 1)
        {
            cout << "\n" << BOLD << CYAN << "  NEW TASK" << RESET << "\n";
            printLine();
            
            // Get task details
            title = getInput("Title");
            if (title.empty())
            {
                cout << RED << "\n  [X] Task title cannot be empty!\n" << RESET;
                cout << DIM << "\n  Press Enter to continue..." << RESET;
                cin.get();
                return;
            }
            
            description = getInput("Description");
            
            // Due date
            cout << "\n" << BOLD << "  Due Date:" << RESET << "\n";
            year = getIntInput("Year", 2025, 2030);
            month = getIntInput("Month", 1, 12);
            day = getIntInput("Day", 1, 31);
            
            // Priority
            cout << "\n" << BOLD << "  Priority:" << RESET << "\n";
            cout << GREEN << "    0. Low\n" << RESET;
            cout << YELLOW << "    1. Medium\n" << RESET;
            cout << RED << "    2. High\n" << RESET;
            priorityChoice = getIntInput("Select", 0, 2);
            
            // Status
            cout << "\n" << BOLD << "  Status:" << RESET << "\n";
            cout << BLUE << "    0. To Do\n" << RESET;
            cout << YELLOW << "    1. In Progress\n" << RESET;
            cout << GREEN << "    2. Done\n" << RESET;
            statusChoice = getIntInput("Select", 0, 2);
            
            // Assignee
            assigneeId = getIntInput("\nAssignee ID (0 = unassigned)", 0, 100);
            
            currentField = 0; // Move to review mode
        }
        
        // Review and edit phase
        if (currentField == 0)
        {
            displayTaskSummary(title, description, year, month, day, priorityChoice, statusChoice, assigneeId);
            
            cout << CYAN << "\n  -> " << RESET << "Your choice: ";
            string choice;
            getline(cin, choice);
            
            if (choice.empty()) continue;
            
            char ch = toupper(choice[0]);
            
            if (ch == 'S')
            {
                // Validate assignee
                if (assigneeId != 0 && !userExists(assigneeId))
                {
                    cout << RED << "\n  [X] Error: Assignee ID " << assigneeId << " does not exist!\n" << RESET;
                    cout << DIM << "\n  Press Enter to continue..." << RESET;
                    cin.get();
                    continue;
                }
                
                // Save to database
                Date dueDate{year, month, day};
                Priority priority = static_cast<Priority>(priorityChoice);
                TaskStatus status = static_cast<TaskStatus>(statusChoice);
                
                Task newTask(0, title, description, dueDate, priority, status, assigneeId);
                TaskDAO dao;
                
                if (dao.createTask(newTask))
                {
                    cout << GREEN << "\n  [SUCCESS] Task saved successfully!\n" << RESET;
                }
                else
                {
                    cout << RED << "\n  [ERROR] Failed to save task.\n" << RESET;
                }
                
                cout << DIM << "\n  Press Enter to continue..." << RESET;
                cin.get();
                editMode = false;
            }
            else if (ch == 'C')
            {
                cout << YELLOW << "\n  Task creation cancelled.\n" << RESET;
                cout << DIM << "\n  Press Enter to continue..." << RESET;
                cin.get();
                editMode = false;
            }
            else if (ch >= '1' && ch <= '6')
            {
                currentField = ch - '0';
                clearScreen();
                displayHeader();
                cout << "\n" << BOLD << CYAN << "  EDIT FIELD" << RESET << "\n";
                printLine();
                
                switch (currentField)
                {
                    case 1:
                        title = getInput("New Title");
                        if (title.empty())
                        {
                            cout << RED << "  [X] Title cannot be empty! Keeping old value.\n" << RESET;
                            title = "Untitled Task";
                            cout << DIM << "\n  Press Enter to continue..." << RESET;
                            cin.get();
                        }
                        break;
                        
                    case 2:
                        description = getInput("New Description");
                        break;
                        
                    case 3:
                        cout << "\n" << BOLD << "  New Due Date:" << RESET << "\n";
                        year = getIntInput("Year", 2025, 2030);
                        month = getIntInput("Month", 1, 12);
                        day = getIntInput("Day", 1, 31);
                        break;
                        
                    case 4:
                        cout << "\n" << BOLD << "  New Priority:" << RESET << "\n";
                        cout << GREEN << "    0. Low\n" << RESET;
                        cout << YELLOW << "    1. Medium\n" << RESET;
                        cout << RED << "    2. High\n" << RESET;
                        priorityChoice = getIntInput("Select", 0, 2);
                        break;
                        
                    case 5:
                        cout << "\n" << BOLD << "  New Status:" << RESET << "\n";
                        cout << BLUE << "    0. To Do\n" << RESET;
                        cout << YELLOW << "    1. In Progress\n" << RESET;
                        cout << GREEN << "    2. Done\n" << RESET;
                        statusChoice = getIntInput("Select", 0, 2);
                        break;
                        
                    case 6:
                        assigneeId = getIntInput("New Assignee ID (0 = unassigned)", 0, 100);
                        break;
                }
                
                currentField = 0; // Back to review mode
                cout << GREEN << "\n  [✓] Field updated!\n" << RESET;
                cout << DIM << "  Press Enter to continue..." << RESET;
                cin.get();
            }
            else
            {
                cout << RED << "\n  [X] Invalid choice!\n" << RESET;
                cout << DIM << "  Press Enter to continue..." << RESET;
                cin.get();
            }
        }
    }
}

void TaskForm::run()
{
    // Connect to database
    DatabaseManager* db = DatabaseManager::getInstance();
    if (!db->connect("data/agile_board.db"))
    {
        cout << RED << "Failed to connect to database!" << RESET << endl;
        return;
    }
    
    bool running = true;
    
    while (running)
    {
        clearScreen();
        displayHeader();
        displayMenu();
        
        int choice = getIntInput("Choose option", 1, 2);
        
        switch (choice)
        {
            case 1:
                clearScreen();
                createTask();
                break;
                
            case 2: // back to board
                cout << "\n" << CYAN << "  Goodbye!\n" << RESET << "\n";
                running = false;
                break;
        }
    }
    
    db->disconnect();
}