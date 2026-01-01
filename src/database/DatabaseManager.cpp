#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>
#include "Task.h"
#include "Date.h"
#include "TaskStatus.h"
#include "Priority.h"
#include "User.h"
#include "DatabaseManager.h"

using namespace std;

DatabaseManager* DatabaseManager::instance = nullptr;

int rc = 0;
char* errMsg = 0;

// The actual SQLite connection object
sqlite3* dbConnection;

// Private Constructor (so no one can create a second instance)
DatabaseManager::DatabaseManager()
{
    dbConnection = nullptr;
}

DatabaseManager* DatabaseManager::instance = nullptr;

int rc = 0;
char* errMsg = 0;

// The actual SQLite connection object
sqlite3* dbConnection;

// Private Constructor (so no one can create a second instance)
DatabaseManager::DatabaseManager()
{
    dbConnection = nullptr;
}

// 1. Singleton Access
DatabaseManager* DatabaseManager::getInstance()
{
    if (instance == nullptr)
        instance = new DatabaseManager();

    return instance;
}

// 2. Lifecycle Management
// Opens the database file. Returns true if successful.
bool DatabaseManager::connect(const string& dbPath)
{
    if(dbConnection != nullptr)
    {
        return true;
    }

    int result = sqlite3_open(dbPath.c_str(), &dbConnection);

    if (result != SQLITE_OK) 
    {
        cerr << "Connection Error: " << sqlite3_errmsg(dbConnection) << endl;
        
        sqlite3_close(dbConnection);
        dbConnection = nullptr;
            
        return false;
    }

    cout << "Successfully connected to database: " << dbPath << endl;
    return true;
}

// Closes the connection.
void DatabaseManager::disconnect()
{
    if(dbConnection == nullptr)
        return;
    
    sqlite3_close(dbConnection);
    dbConnection = nullptr;
    cout << "Database disconnected." << endl;
}

// 3. Write Operations (INSERT, UPDATE, DELETE, CREATE)
// Executes a query that changes data. Returns true if successful.
bool DatabaseManager::exec(const char* query)
{   
    char* errMsg = 0;
    int rc = sqlite3_exec(dbConnection, query, nullptr, nullptr, &errMsg);

    if(rc != SQLITE_OK)
    {
        cerr << "SQL Error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    else
        cout << "Query excuted successfully\n";
    return true;
}

// 4. Read Operations (SELECT)
// Executes a query and stores the result in the 'result' vector.
// Result format: Vector of Rows, where each Row is a Vector of Strings (Columns).
// Returns true if successful.
bool DatabaseManager::select(const char* query, vector<Task>& result)
{
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(dbConnection, query, -1, &stmt, nullptr);

    if(rc != SQLITE_OK)
    {
        cerr << "SQL Error: " << sqlite3_errmsg(dbConnection) << '\n';
        return false;
    }

    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        /*
        // NOTE: THIS HOW THE TABLE WILL LOOK IN THE DATEBASE!!
        // id PK, title, description, dueDate, priority, status, assigneeId FK
        */
        int id = sqlite3_column_int(stmt, 0);
        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        string tempDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        Date dueDate;
        
        string holder = "";
        int cnt = 0;
        for(int i = 0; i < tempDate.size(); i++)
        {
            if(tempDate[i] == '-')
            {
                if(cnt == 0)
                    dueDate.year = stoi(holder);
                else if(cnt == 1)
                    dueDate.month = stoi(holder);
                else
                    dueDate.day = stoi(holder);
                cnt++;
                holder = "";
            }
            else
                holder += tempDate[i];
                
        }

        Priority priority = (Priority)sqlite3_column_int(stmt, 4);
        TaskStatus taskStatus = (TaskStatus)sqlite3_column_int(stmt, 5);
        int assigneeId = sqlite3_column_int(stmt, 6);

        Task t(id, title, description, dueDate, priority, taskStatus, assigneeId);

        result.push_back(t);
    }

    sqlite3_finalize(stmt);
    return true;
}

bool DatabaseManager::select(const char* query, vector<User>& result)
{
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(dbConnection, query, -1, &stmt, nullptr);

    if(rc != SQLITE_OK)
    {
        cerr << "SQL Error: " << sqlite3_errmsg(dbConnection) << '\n';
        return false;
    }

    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        /*
        // NOTE: THIS HOW THE TABLE WILL LOOK IN THE DATEBASE!!
        // id PK, userName, hashedPassword
        */
        int id = sqlite3_column_int(stmt, 0);
        string userName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string hashedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        User u(id, userName, hashedPassword);

        result.push_back(u);
    }

    sqlite3_finalize(stmt);
    return true;
}

// 5. Utility Functions
// Returns the ID of the last row inserted (useful after creating a Task)
int DatabaseManager::getLastInsertId() {
    return sqlite3_last_insert_rowid(dbConnection);
}

// Returns the last error message from SQLite
string DatabaseManager::getLastError() {
    return sqlite3_errmsg(dbConnection);
}
