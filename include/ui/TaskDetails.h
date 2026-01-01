#pragma once

using namespace std;


class TaskDetails {
    public:
        TaskDetails();
        ~TaskDetails();

        static void displayTaskInfo(int taskId);
        static void clearScreen();
};