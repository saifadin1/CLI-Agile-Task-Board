#include <iostream>
#include "DatabaseSeeder.h"
#include "Board.h"
using namespace std;

int main()
{
    cout << "CLI Agile Task Board" << endl;
    cout << "====================" << endl;

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
    Board b;
    TaskDAO dao;
    auto tasks =dao.selectAllTasks(); 
    b.displayBoard(tasks);
    return 0;
}