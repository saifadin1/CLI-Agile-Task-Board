#include <iostream>
#include "DatabaseSeeder.h"
#include "DatabaseManager.h"
#include "TaskDAO.h"
#include "User.h"
#include "Task.h"
#include "Date.h"
#include "Priority.h"
#include "TaskStatus.h"

using namespace std;

DatabaseSeeder::DatabaseSeeder()
{
    db = DatabaseManager::getInstance();
    dao = new TaskDAO();
}

DatabaseSeeder::~DatabaseSeeder()
{
    delete dao;
}

bool DatabaseSeeder::initializeDatabase()
{
    // Connect to database
    if (!db->connect("data/agile_board.db"))
    {
        cout << "Failed to connect to database!" << endl;
        return false;
    }

    // Create tables
    createTables();

    // Seed data
    if (!seedData())
    {
        cout << "Failed to seed data!" << endl;
        return false;
    }

    cout << "Database initialized and seeded successfully!" << endl;
    return true;
}

void DatabaseSeeder::createTables()
{
    // Create user table
    string createUserTable = R"(
        CREATE TABLE IF NOT EXISTS user (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            userName TEXT NOT NULL UNIQUE,
            hashedPassword TEXT NOT NULL
        );
    )";

    // Create task table
    string createTaskTable = R"(
        CREATE TABLE IF NOT EXISTS task (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            description TEXT,
            dueDate TEXT,
            priority INTEGER DEFAULT 1,
            status INTEGER DEFAULT 0,
            assigneeId INTEGER,
            FOREIGN KEY (assigneeId) REFERENCES user (id)
        );
    )";

    if (!db->exec(createUserTable.c_str()))
    {
        cout << "Failed to create user table!" << endl;
    }

    if (!db->exec(createTaskTable.c_str()))
    {
        cout << "Failed to create task table!" << endl;
    }
}

bool DatabaseSeeder::seedData()
{
    createSampleUsers();
    createSampleTasks();
    return true;
}

void DatabaseSeeder::createSampleUsers()
{
    cout << "Creating sample users..." << endl;

    vector<User> users = {
        User(0, "alice_dev", "pass123"),
        User(0, "bob_qa", "pass123"),
        User(0, "charlie_pm", "pass123"),
        User(0, "diana_design", "pass123")
    };

    for (auto& user : users)
    {
        if (dao->createUser(user))
        {
            cout << "Created user: " << user.getUserName() << endl;
        }
        else
        {
            cout << "Failed to create user: " << user.getUserName() << endl;
        }
    }
}

void DatabaseSeeder::createSampleTasks()
{
    cout << "Creating sample tasks..." << endl;

    // Note: assigneeId will be set based on created users
    // For simplicity, assuming IDs 1,2,3,4 for the users created above
    vector<Task> tasks = {
        // High priority tasks
        Task(0, "Fix critical login bug", "Users cannot login after password reset", Date{2025, 12, 20}, Priority::High, TaskStatus::ToDo, 1),
        Task(0, "Implement payment gateway", "Integrate Stripe payment processing", Date{2025, 12, 25}, Priority::High, TaskStatus::ToDo, 1),
        Task(0, "Deploy to production", "Successfully deployed v2.1 to prod", Date{2025, 12, 15}, Priority::High, TaskStatus::Done, 3),
        Task(0, "Security audit", "Completed security review and fixes", Date{2025, 12, 10}, Priority::High, TaskStatus::Done, 2),

        // Mid priority tasks
        Task(0, "Add user profile page", "Create user dashboard with profile editing", Date{2025, 12, 30}, Priority::Mid, TaskStatus::InProgress, 1),
        Task(0, "Write API documentation", "Document all REST endpoints", Date{2026, 1, 5}, Priority::Mid, TaskStatus::InProgress, 4),
        Task(0, "Setup automated testing", "Configure CI/CD pipeline with tests", Date{2026, 1, 10}, Priority::Mid, TaskStatus::InProgress, 2),
        Task(0, "User registration flow", "Implemented complete signup process", Date{2025, 12, 18}, Priority::Mid, TaskStatus::Done, 1),
        Task(0, "Email notifications", "Setup automated email system", Date{2025, 12, 22}, Priority::Mid, TaskStatus::Done, 4),

        // Low priority tasks
        Task(0, "Add dark mode theme", "Implement dark/light theme toggle", Date{2026, 2, 15}, Priority::Low, TaskStatus::ToDo, 4),
        Task(0, "Optimize database queries", "Improve performance of slow queries", Date{2026, 3, 1}, Priority::Low, TaskStatus::ToDo, 1),
        Task(0, "Add export feature", "Allow users to export their data", Date{2026, 1, 20}, Priority::Low, TaskStatus::InProgress, 2),

        // Unassigned tasks
        Task(0, "Research new tech stack", "Evaluate React vs Vue for frontend", Date{2026, 2, 1}, Priority::Mid, TaskStatus::ToDo, 0),
        Task(0, "Plan Q1 roadmap", "Define goals and priorities for next quarter", Date{2026, 1, 15}, Priority::High, TaskStatus::ToDo, 0)
    };

    for (auto& task : tasks)
    {
        if (dao->createTask(task))
        {
            cout << "Created task: " << task.getTitle() << endl;
        }
        else
        {
            cout << "Failed to create task: " << task.getTitle() << endl;
        }
    }
}