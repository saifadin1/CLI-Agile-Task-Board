#include <iostream>
#include "DatabaseSeeder.h"
#include "Auth.h"
#include "User.h"

using namespace std;

User* CURRENTUSER;

int main()
{

    Auth auth;

    CURRENTUSER = auth.start();

    cout << "The Current user is: " << CURRENTUSER->getUserName();

    return 0;
}