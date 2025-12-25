#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class DatabaseManager {
private:
    // Singleton instance pointer
    static DatabaseManager* instance;
    
    // The actual SQLite connection object
    sqlite3* dbConnection;
    
    // Private Constructor (so no one can create a second instance)
    DatabaseManager();

public:
    // 1. Singleton Access
    static DatabaseManager* getInstance();

    // 2. Lifecycle Management
    // Opens the database file. Returns true if successful.
    bool connect(const string& dbPath = "data/agile_board.db");
    
    // Closes the connection.
    void disconnect();

    // 3. Write Operations (INSERT, UPDATE, DELETE, CREATE)
    // Executes a query that changes data. Returns true if successful.
    bool exec(const string& sql);

    // 4. Read Operations (SELECT)
    // Executes a query and stores the result in the 'result' vector.
    // Result format: Vector of Rows, where each Row is a Vector of Strings (Columns).
    // Returns true if successful.
    bool select(const string& sql, vector<vector<string>>& result);

    // 5. Utility Functions
    // Returns the ID of the last row inserted (useful after creating a Task)
    int getLastInsertId();
    
    // Returns the last error message from SQLite
    string getLastError();
};

#endif