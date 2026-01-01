#define rpcndr_is_fortran
#include <Windows.h>
#include "Auth.h"
#include <iostream>
#include <conio.h>
#include <functional>

using namespace std;

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void gotoxy(int x, int y)
{
    COORD coord = { 0,0 };
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char** text;
int* l, * r, c = 0, cl = 0;
bool* outOfLimitFlag, * invalidCharacterFlag;

void printOutOfLimitError(int xCord, int yCord)
{
    gotoxy(xCord, yCord - 1);
    cout << "You have reached your text limit !!";
}

void printContent(int limit, int xCord, int yCord, int lineNumber)
{
    gotoxy(xCord + 1, yCord + 1);
    for (int i = l[lineNumber]; i <= r[lineNumber] - 1; i++)
        cout << text[lineNumber][i];
}

void printCursor(int xCord, int yCord)
{
    gotoxy(xCord + c, yCord + 2);
    cout << '_';
}

void printBox(int row, int col, int xCord, int yCord)
{

    gotoxy(xCord, yCord);
    for (int i = 0; i < col + 1; i++)
        cout << '-';

    for (int i = 0; i < row; i++)
    {
        gotoxy(xCord - 1, yCord + 1 + i);
        cout << '|';
    }

    for (int i = 0; i < row; i++)
    {
        gotoxy(xCord + col + 1, yCord + 1 + i);
        cout << '|';
    }

    gotoxy(xCord, yCord + row + 1);
    for (int i = 0; i < col + 1; i++)
        cout << '-';
}

void rightShift(int left, int right)
{
    for (int i = right; i >= left; i--)
        text[cl][i + 1] = text[cl][i];
}

void leftShift(int left, int right)
{
    for (int i = left; i <= right; i++)
        text[cl][i - 1] = text[cl][i];
}

void clearText(int* limit, int totalLines)
{
    for(int i = 0; i < totalLines; i++) 
    {
        memset(text[i], 0, limit[i]);
    }
}

// I need t use the line editor task 6.2

// it will take two strings by refrence so it will give us what the user will input, this is needed to return the current user
// it will return true or false indcating if this user exists or not 
bool Auth::login(string& userName, string& password)
{
    myUser = _DAO->selectUser(userName, password);
    if(myUser == nullptr)
        return false;

    return true;
}

// it will take two strings by refrence so it will give us what the user will input, this is needed to return the current user
// it will return true or false indcating id this user name is taken or not
bool Auth::signup(string& userName, string& password)
{

    myUser = _DAO->selectUser(userName, password);
    if(myUser == nullptr)
    {
        myUser = new User(0, userName, password);
        return _DAO->createUser(*myUser);
    }
    
    return false;
} 

// this will be function that is used to hash the password when a user signup
// it will take a string by refrence which is the password and it is going to hash it 
void Auth::hashing(string& password)
{
    char key = 'A'; 
    for (size_t i = 0; i < password.length(); ++i) 
    {
        password[i] = password[i] ^ key;
    }
}

Auth::Auth() 
{
    _DAO = new TaskDAO();
}
Auth::~Auth() {}

// This function will use the login and signup based on the user case 
//
// it will create a pointer to user and returns it which will be the current logged in user 
User* Auth::start()
{
    char ch;
    // modeFlag will be 0 if it is login and 1 if it is signup
    int* limit, * xCord, * yCord, numberOfLines = 2, modeFlag = 0, totalLines = 3, invalidePassWordMatching = 0;
    bool terminationFlag = false;

    text = new char* [totalLines];
    l = new int[totalLines] {};
    r = new int[totalLines] {};
    limit = new int[totalLines];
    xCord = new int[totalLines];
    yCord = new int[totalLines];
    outOfLimitFlag = new bool[totalLines] {};
    invalidCharacterFlag = new bool[totalLines] {};

    
    limit[0] = 35; limit[1] = 35; limit[2] = 35;
    text[0] = new char[limit[0]]; text[1] = new char[limit[1]]; text[2] = new char[limit[2]];
    do {
        system("cls");

        if(invalidePassWordMatching == 3)
        {
            gotoxy(3, 3);
            cout << "YOU HAVE TRIED TOO MANY TIMES YOU ARE BLOCKED NOW!";
            break;
        }

        xCord[0] = 2; yCord[0] = 7;
        xCord[1] = 2; yCord[1] = 13;
        xCord[2] = 2; yCord[2] = 19;

        gotoxy(3, 3);
        if(!invalidePassWordMatching)
            cout << "WELCOME TO OUR CLI-AGILE PROJECT";
        else 
            cout << "INVALID PASSWORD MATCHING PLEASE TRY AGAIN!";

        gotoxy(15, 6);
        cout << "USERNAME";

        gotoxy(15, 12);
        cout << "PASSWORD";
        
        if(!modeFlag)
        {
            printBox(11, 37, 1, 5);
    
            gotoxy(3, 19);
            if(cl == numberOfLines)
                cout << "ARE YOU NEW HERE? \033[42mSIGNUP\033[0m";
            else
                cout << "ARE YOU NEW HERE? SIGNUP";
        }
        else
        {
            printBox(17, 37, 1, 5);

            gotoxy(13, 18);
            cout << "CONFIRM PASSWORD";
        }

        int activeFields = numberOfLines + modeFlag;

        for (int i = 0; i < activeFields; i++)
        {
            printBox(2, limit[i], xCord[i], yCord[i]);
            printContent(limit[i], xCord[i], yCord[i], i);

            if (i == cl) printCursor(xCord[i], yCord[i]);

            if (outOfLimitFlag[i])
            {
                outOfLimitFlag[i] = false;
                printOutOfLimitError(xCord[i], yCord[i]);
            }
        }

        for(int i = 0; i < 20; i++)
            cout << '\n';

        ch = _getch();

        switch (ch)
        {
        case -32:
            ch = _getch();

            switch (ch)
            {
            case 'K': // left
                if (c > 1)
                    c--;
                break;
            case 'M': // right
                if (c < r[cl])
                    c++;
                break;
            case 'G': //home
                c = 0;
                break;
            case 'O': // end
                c = r[cl];
                break;
            case 72: //up
                if (cl != 0) cl--;
                c = r[cl];
                break;
            case 80: //down
                if (cl != activeFields - modeFlag) cl++;
                c = r[cl];
                break;
            case 83: // delete
                if (c == r[cl])
                    break;
                leftShift(c + 1, r[cl]);
                r[cl]--;
                break;
            }
            break;

        case 13: // enter
            if(cl == activeFields - 1)
            {
                string userName = "", passWord = "", confirmPassWord = "";

                for (int i = 0; i < activeFields; i++)
                {
                    for (int j = 0; j < r[i]; j++)
                        if(i == 0)
                            userName += text[i][j];
                        else if(i == 1) 
                            passWord += text[i][j];
                        else 
                            confirmPassWord += text[i][j];
                }

                if(modeFlag)
                {
                    if(passWord == confirmPassWord)
                    {
                        hashing(passWord);
                        if(signup(userName, passWord))
                        {
                            cout << "a new user\n";
                            return myUser;
                        }
                        else
                        {
                            system("cls");
                            gotoxy(3, 3);
                            cout << "THIS USERNAME ALREADY TAKEN";
                            
                            return nullptr;
                        }
                        invalidePassWordMatching = 0;
                    }
                    else
                    {
                        clearText(limit, totalLines);
                        invalidePassWordMatching++;
                        for(int i = 0; i < totalLines; i++) r[i] = 0; 
                        c = 0; cl = 0;
                        terminationFlag = !terminationFlag;
                    }
                }
                else
                {
                    hashing(passWord);
                    if(login(userName, passWord))
                        return myUser;
                    else
                    {
                        system("cls");
                        gotoxy(3, 3);
                        cout << "THIS USER DOES NOT EXISTS";
                        
                        return nullptr;
                    }
                }
                terminationFlag = !terminationFlag;
            }
            else if (cl == numberOfLines)
            {
                modeFlag = (modeFlag + 1) % 2;
            }
            

            if (cl != activeFields - 1) cl++;
            c = r[cl];

            break;

        case 27: //exit
            terminationFlag = !terminationFlag;
            break;


        case 8: // backspace
            if (c == 0)
                break;
            leftShift(c, r[cl]);

            c--;
            r[cl]--;
            break;

        default:
            if (r[cl] == limit[cl])
            {
                outOfLimitFlag[cl] = true;
                break;
            }

            if (c != r[cl])
            {
                rightShift(c, r[cl]);
            }

            text[cl][c] = ch;
            c++;
            r[cl]++;

            break;
        }
    } while (!terminationFlag);

    for(int i = 0; i < totalLines; i++) 
    {
        delete[] text[i]; 
    }
    delete[] text; 
    delete[] l;
    delete[] r;
    delete[] limit;
    delete[] xCord;
    delete[] yCord;
    delete[] outOfLimitFlag;
    delete[] invalidCharacterFlag;
    return nullptr;
}
