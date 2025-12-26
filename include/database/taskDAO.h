#pragma once

#include <vector>
#include <string>
#include <databaseManager.h>
#include "User.h"
#include "Task.h"

using namespace std;

class TaskDAO
{
private:
    DatabaseManager* db;
public:
    TaskDAO();

    ~TaskDAO();

    bool updateUser(const User& _user);
    bool updateTask(const Task& _task);

    bool createUser(const User& _user);
    bool createTask(const Task& _task);

    bool deleteUser(const User& _user);
    bool deleteTask(const Task& _task);

    User* selectUser(int _userId);
    Task* selectTask(int _taskId);

    /*
        for user:
        select id, name, pass
        from user

        for task:
        select due_date, asginee, desc, 
        from task

    */

    vector<Task> selectTasksByUserId(int _userId);
    vector<Task> selectAllTasks();

    // We are going to use this function to validate the user while login.
    User* selectUser(string _hashedPassword, string _userName);
};

/*
select id
form user 
where userName = @user and pass = @pass
*/


// CURRENTUSER this will be the user that is currently using the systme (like a session).