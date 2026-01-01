#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include "DatabaseManager.h"
#include "TaskDAO.h"
#include "User.h"
#include "Task.h"

using namespace std;

TaskDAO::TaskDAO()
{
    db = DatabaseManager::getInstance();
    db->connect();
}

TaskDAO::~TaskDAO()
{
    db->disconnect();
}

bool TaskDAO::updateUser(const User& _user)
{
    string query = "UPDATE user SET userName = '" + _user.getUserName() + "', hashedPassword = '" + _user.getHashedPassword() + "' WHERE id = " + to_string(_user.getId());
    return db->exec(query.c_str());
}

bool TaskDAO::updateTask(const Task& _task)
{
    string query = "UPDATE task SET title = '" + _task.getTitle() + "', description = '" + _task.getDescription() + "', dueDate = '" + to_string(_task.getDueDate().year) + "-" + to_string(_task.getDueDate().month) + "-" + to_string(_task.getDueDate().day) + "', priority = " + to_string((int)_task.getPriority()) + ", status = " + to_string((int)_task.getStatus()) + ", assigneeId = " + to_string(_task.getAssigneeId())  +" WHERE id = "  + to_string(_task.getId());
    return db->exec(query.c_str());
}

bool TaskDAO::createUser(const User& _user)
{
    string query = "INSERT INTO user (userName, hashedPassword) VALUES ('" + _user.getUserName() + "', '" + _user.getHashedPassword() + "')";
    return db->exec(query.c_str());
}

bool TaskDAO::createTask(const Task& _task)
{
    string query = "INSERT INTO task (title, description, dueDate, priority, status, assigneeId) VALUES ('" + _task.getTitle() + "', '" + _task.getDescription() + "', '" + to_string(_task.getDueDate().year) + "-" + to_string(_task.getDueDate().month) + "-" + to_string(_task.getDueDate().day) + "', " + to_string((int)_task.getPriority()) + ", " + to_string((int)_task.getStatus()) + ", " + to_string(_task.getAssigneeId()) + ")";
    return db->exec(query.c_str());
}

bool TaskDAO::deleteUser(const User& _user)
{
    string query = "DELETE FROM user WHERE id = " + to_string(_user.getId());
    return db->exec(query.c_str());
}

bool TaskDAO::deleteTask(const Task& _task)
{
    string query = "DELETE FROM task WHERE id = " + to_string(_task.getId());
    return db->exec(query.c_str());
}

User* TaskDAO::selectUser(int _userId)
{
    string query = "SELECT id, userName, hashedPassword FROM user WHERE id = " + to_string(_userId);
    vector<User> result;
    if(db->select(query.c_str(), result))
    {
        if(result.size() > 0)
        {
            return new User(result[0]);
        }
    }
    return nullptr;
}

vector<Task> TaskDAO::selectAllTasks()
{
    string query = "SELECT * FROM task";
    vector<Task> result;
    db->select(query.c_str(), result);
    return result;
}

vector<Task> TaskDAO::selectTasksByUserId(int _userId)
{
    string query = "SELECT * FROM task WHERE assigneeId = " + to_string(_userId);
    vector<Task> result; 
    db->select(query.c_str(), result);
    return result;
}

Task* TaskDAO::selectTask(int _taskId)
{
    string query = "SELECT * FROM task WHERE id = " + to_string(_taskId);
    vector<Task> result;
    if(db->select(query.c_str(), result)) 
    {
        if(!result.empty())
        {
            return new Task(result[0]);
        }
    }
}

User* TaskDAO::selectUser(string _userName, string _hashedPassword)
{
    string query = "SELECT id, userName, hashedPassword FROM user WHERE userName = '" + _userName + "' AND hashedPassword = '" + _hashedPassword + "'";

    vector<User> result;
    if(db->select(query.c_str(), result))
    {
        if(result.size() > 0)
        {
            return new User(result[0]);
        }
    }
    return nullptr;
}