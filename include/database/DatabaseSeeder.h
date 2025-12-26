#pragma once

#include <string>
#include <vector>
#include "TaskDAO.h"
#include "User.h"
#include "Task.h"
#include "Date.h"

class DatabaseSeeder
{
private:
    TaskDAO* dao;
    DatabaseManager* db;

public:
    DatabaseSeeder();
    ~DatabaseSeeder();

    bool initializeDatabase();
    bool seedData();
    void createTables();
    void createSampleUsers();
    void createSampleTasks();
};