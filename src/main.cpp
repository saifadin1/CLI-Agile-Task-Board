#include <iostream>
#include "DatabaseSeeder.h"
#include "DatabaseManager.h"
#include "TaskForm.h"
#include "Board.h"
#include "TaskDetails.h"

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
    TaskDetails taskDetails;
    taskDetails.displayTaskInfo(1);
    


    cout << "\n";
    cout << "  ==========================================================\n";
    cout << "  |          CLI AGILE TASK BOARD                           |\n";
    cout << "  ==========================================================\n";
    cout << "\n";

    TaskForm taskForm;
    taskForm.run();

    // if (seeder.initializeDatabase())
    // {
    //     cout << endl << "✅ Database setup complete!" << endl;
    // }
    // else
    // {
    //     cout << endl << "❌ Database setup failed!" << endl;
    //     return 1;
    // }
    Board b;
    TaskDAO dao;
    auto tasks = dao.selectAllTasks();
    b.displayBoard(tasks);
    return 0;
}