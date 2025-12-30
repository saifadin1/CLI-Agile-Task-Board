#include <iostream>
#include "DatabaseSeeder.h"
#include "DatabaseManager.h"
#include "TaskForm.h"

using namespace std;

int main()
{

    // DatabaseSeeder seeder;

    // if (seeder.initializeDatabase())
    // {
    //     cout << endl << "✅ Database setup complete!" << endl;
    // }
    // else
    // {
    //     cout << endl << "❌ Database setup failed!" << endl;
    //     return 1;
    // }
    
    cout << "\n";
    cout << "  ==========================================================\n";
    cout << "  |          CLI AGILE TASK BOARD                           |\n";
    cout << "  ==========================================================\n";
    cout << "\n";

    TaskForm taskForm;
    taskForm.run();

    return 0;
}