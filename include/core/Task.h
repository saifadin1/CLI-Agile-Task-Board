#include <string>
#include <iostream>
#include <chrono>
#include <TaskStatus.h>
#include <Date.h>

using namespace std;
using namespace std::chrono;

class Task
{
private:
    int _id, _assigneeId;
    string _title, _description;
    Date _dueDate;
    TaskStatus _status;
    Priority _priority;

public:
    Task(int id, string title, string description, Date dueDate, Priority priority, TaskStatus TaskStatus, int assigneeId);
    ~Task();
};

// NOTE: THIS HOW THE TABLE WILL LOOK IN THE DATEBASE!!
// id int PK, title varchar, description varchar, dueDate varchar, priority int, status varchar(1), assigneeId int FK
// 0 --> ToDo, 1 --> InProgress, 2 --> Done 
// 0 --> Low, 1 --> Mid, 2 --> High
// YYYY-MM-DD