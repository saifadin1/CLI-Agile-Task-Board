#include <iostream>
#include "DatabaseSeeder.h"
#include "Auth.h"
#include "User.h"

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

    if(CURRENTUSER != nullptr)
        cout << "The Current user is: " << CURRENTUSER->getUserName();
    else
        cout << "ay 7aga\n";

    return 0;
}