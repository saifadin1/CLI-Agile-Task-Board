#pragma once

#include "taskDAO.h"

using namespace std;


class TaskDetails {
    private:
    static TaskDAO* _DAO;
    public:
        TaskDetails();
        ~TaskDetails();

        static void displayTaskInfo(int taskId);
        static void clearScreen();
};