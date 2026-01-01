#include <vector>
#include "Task.h"
#include "User.h"

using namespace std;

class Board
{
public:
    User* CURRENTUSER;
    Board(User*);
    void displayBoard(vector <Task>);
    void showTaskDetails(Task ts);
    void showMessage(string mesg, bool flag);
    void handleNavigation(vector<Task> tasks, int selectedButton = 0);
};
