#include <vector>
#include "task.h"

using namespace std;

class Board
{
public:
    void displayBoard(vector <Task>);
    void showTaskDetails(Task ts);
    void showError(string mesg);

};
