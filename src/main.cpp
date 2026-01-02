#include <iostream>
#include "DatabaseSeeder.h"
#include "DatabaseManager.h"
#include "TaskForm.h"
#include "Board.h"
#include "Auth.h"
#include "User.h"
#include "TaskDetails.h"
#include <conio.h>

using namespace std;

User* CURRENTUSER;

/*
    Hard coded user:
    UserName: Hamada
    Password: 123
    His role to be the team lead
*/

int main()
{
    Auth auth;

    CURRENTUSER = auth.start();

    while(CURRENTUSER == nullptr)
    {
        cout << "\nILEAGAL BEHAIVOR!!\nPLEASE TRY AGAIN\n";
        _getch();
        CURRENTUSER = auth.start();
    }

    cout << CURRENTUSER->getId() << '\n';

    Board board(CURRENTUSER);

    TaskDAO dao;
    
    board.displayBoard(dao.selectAllTasks());

    return 0;
}