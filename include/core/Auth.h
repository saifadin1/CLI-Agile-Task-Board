#include <string>
#include "User.h"
#include "TaskDAO.h"

class Auth
{
private:
    // it will take two strings by refrence so it will give us what the user will input, this is needed to return the current user
    // it will return true or false indcating if this user exists or not 
    bool login(string& userName, string& password); 

    // it will take two strings by refrence so it will give us what the user will input, this is needed to return the current user
    // it will return true or false indcating id this user name is taken or not
    bool signup(string& userName, string& password); 

    // this will be function that is used to hash the password when a user signup
    // it will take a string by refrence which is the password and it is going to hash it 
    void hashing(string& password);

    // this object will only be used in the start function to query from database
    TaskDAO* _DAO;

    // this will be the current user logged in
    User* myUser;

public:
    Auth();
    ~Auth();

    // This function will use the login and signup based on the user case 
    //
    // it will create a pointer to user and returns it which will be the current logged in user 
    User* start();

};

