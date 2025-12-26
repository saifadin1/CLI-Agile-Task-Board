#include <string>

using namespace std;

class User
{
private:
    string _userName, _hashedPassword;
    int _id;
public:
    User(int id, string userName, string hashedPassword);
    ~User();
};

// NOTE: THIS HOW THE TABLE WILL LOOK IN THE DATEBASE!!
// id int PK, userName varchar, hashedPassword varchar
