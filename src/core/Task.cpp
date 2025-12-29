#include "Task.h"


Task::Task(int id, string title, string description, Date dueDate, Priority priority, TaskStatus status, int assigneeId)
    : _id(id), 
      _title(title), 
      _description(description), 
      _dueDate(dueDate), 
      _priority(priority), 
      _status(status), 
      _assigneeId(assigneeId)
{
}


Task::~Task() {}


int Task::getId() const {
    return _id;
}

string Task::getTitle() const {
    return _title;
}

string Task::getDescription() const {
    return _description;
}

Date Task::getDueDate() const {
    return _dueDate;
}

Priority Task::getPriority() const {
    return _priority;
}

TaskStatus Task::getStatus() const {
    return _status;
}

int Task::getAssigneeId() const {
    return _assigneeId;
}



void Task::setId(int id) {
    _id = id;
}

void Task::setTitle(const string& title) {
    _title = title;
}

void Task::setDescription(const string& description) {
    _description = description;
}

void Task::setDueDate(const Date& dueDate) {
    _dueDate = dueDate;
}

void Task::setPriority(const Priority& priority) {
    _priority = priority;
}

void Task::setStatus(const TaskStatus& status) {
    _status = status;
}

void Task::setAssigneeId(int assigneeId) {
    _assigneeId = assigneeId;
}