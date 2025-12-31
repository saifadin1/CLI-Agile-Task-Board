#pragma once

using namespace std;


class TaskDetails {
    public:
        TaskDetails();
        ~TaskDetails();

        void displayTaskInfo(int taskId) const;
        void backButton() const;
        void clearScreen() const;
};