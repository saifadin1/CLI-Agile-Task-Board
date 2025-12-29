#include "TaskDetails.h"
#include <iomanip>
#include <iostream>
#include "TaskDetails.h"
#include "Priority.h"
#include "TaskStatus.h"
#include "Task.h"
#include "Date.h"

TaskDetails::TaskDetails() {}
TaskDetails::~TaskDetails() {}


using namespace std;

string priorityToString(Priority p) {
    // Assuming Priority is an enum or int casting
    // 0 --> Low, 1 --> Mid, 2 --> High
    switch ((int)p) {
        case 0: return "Low";
        case 1: return "Mid";
        case 2: return "High";
        default: return "Unknown";
    }
}

string statusToString(TaskStatus s) {
    // 0 --> ToDo, 1 --> InProgress, 2 --> Done
    switch ((int)s) {
        case 0: return "To Do";
        case 1: return "In Progress";
        case 2: return "Done";
        default: return "Unknown";
    }
}

// Helper to center text (optional, adds polish)
void printCentered(string text, int width) {
    int padding = (width - text.length()) / 2;
    cout << "| " << string(padding, ' ') << text << string(width - padding - text.length(), ' ') << " |" << endl;
}

void TaskDetails::displayTaskInfo(int taskId) const {
    // 1. FETCH THE TASK (Mock logic - replace with your DAO call)
    // Task task = taskDAO.getTaskById(taskId);
    // For now, I'll create a dummy task to show the visualization
    Date d = {2025, 12, 30};
    Task task(taskId, "Fix Login Bug", "The submit button crashes the app when clicked.", d, Priority::High, TaskStatus::InProgress, 5);

    // 2. DEFINE WIDTHS
    const int LABEL_WIDTH = 15;
    const int VALUE_WIDTH = 50;
    const int TOTAL_WIDTH = LABEL_WIDTH + VALUE_WIDTH + 3; // +3 for separators "| " and " |"

    // 3. DRAW THE TABLE
    cout << endl;
    cout << "+" << string(TOTAL_WIDTH, '-') << "+" << endl;
    
    // Header
    printCentered("TASK DETAILS (ID: " + to_string(task.getId()) + ")", TOTAL_WIDTH);
    
    cout << "+" << string(TOTAL_WIDTH, '-') << "+" << endl;

    // Row 1: Title
    cout << "| " << left << setw(LABEL_WIDTH) << "Title" 
         << "| " << setw(VALUE_WIDTH) << task.getTitle() << " |" << endl;
    
    // Separator
    cout << "+" << string(LABEL_WIDTH + 1, '-') << "+" << string(VALUE_WIDTH + 1, '-') << "+" << endl;

    // Row 2: Status
    cout << "| " << left << setw(LABEL_WIDTH) << "Status" 
         << "| " << setw(VALUE_WIDTH) << statusToString(task.getStatus()) << " |" << endl;

    // Row 3: Priority
    cout << "| " << left << setw(LABEL_WIDTH) << "Priority" 
         << "| " << setw(VALUE_WIDTH) << priorityToString(task.getPriority()) << " |" << endl;

    // Row 4: Due Date
    // assuming your Date object overloads << or has a toString method
    cout << "| " << left << setw(LABEL_WIDTH) << "Due Date" 
         << "| " << setw(VALUE_WIDTH) << "2025-12-30" /* replace with task.getDueDate() */ << " |" << endl; 

    // Row 5: Assignee
    cout << "| " << left << setw(LABEL_WIDTH) << "Assignee ID" 
         << "| " << setw(VALUE_WIDTH) << task.getAssigneeId() << " |" << endl;

    cout << "+" << string(TOTAL_WIDTH, '-') << "+" << endl;

    // Description Box (Separate because it might be long)
    cout << "| " << left << setw(TOTAL_WIDTH) << "Description:" << " |" << endl;
    cout << "| " << left << setw(TOTAL_WIDTH) << task.getDescription() << " |" << endl;
    
    cout << "+" << string(TOTAL_WIDTH, '-') << "+" << endl;
    cout << endl;
}

void TaskDetails::backButton() const {
    

}

