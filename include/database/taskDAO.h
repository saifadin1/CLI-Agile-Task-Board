#include <vector>
#include <string>
#include <databaseManager.h>
#include "User.h"

using namespace std;

class taskDAO
{
private:
    DatabaseManager* db;
public:
    taskDAO();

    ~taskDAO();

    void updateUser(const User& _user);
};

