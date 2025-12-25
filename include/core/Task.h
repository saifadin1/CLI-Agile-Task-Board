#include <string>
#include <iostream>
#include <chrono>
#include <TaskStatus.h>

using namespace std;
using namespace std::chrono;

class Task
{
private:
    int _id, _priority, _assigneeId;
    string _title, _description, _status;
    // year_month_day _dueDate;
    TaskStatus _status;

public:
    Task(/* args */);
    ~Task();
};
