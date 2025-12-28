#include <iostream>
#include "DatabaseSeeder.h"

using namespace std;

int main()
{
    cout << "CLI Agile Task Board" << endl;
    cout << "====================" << endl;

    DatabaseSeeder seeder;

    if (seeder.initializeDatabase())
    {
        cout << endl << "✅ Database setup complete!" << endl;
    }
    else
    {
        cout << endl << "❌ Database setup failed!" << endl;
        return 1;
    }

    return 0;
}