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

    void updateUser(const User& _user);
    void updateTask(const Task& _task);

    void createUser(const User& _user);
    void createTask(const Task& _task);

    void deleteUser(const User& _user);
    void deleteTask(const Task& _task);

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