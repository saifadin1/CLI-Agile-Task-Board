#pragma once

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

    int getId() const;
    string getTitle() const;
    string getDescription() const;
    Date getDueDate() const;
    Priority getPriority() const;
    TaskStatus getStatus() const;
    int getAssigneeId() const;
    void setId(int id);
    void setTitle(const string& title);
    void setDescription(const string& description);
    void setDueDate(const Date& dueDate);
    void setPriority(const Priority& priority);
    void setStatus(const TaskStatus& status);
    void setAssigneeId(int assigneeId);
    
};

// NOTE: THIS HOW THE TABLE WILL LOOK IN THE DATEBASE!!
// id int PK, title varchar, description varchar, dueDate varchar, priority int, status varchar(1), assigneeId int FK
// 0 --> ToDo, 1 --> InProgress, 2 --> Done 
// 0 --> Low, 1 --> Mid, 2 --> High
// YYYY-MM-DD