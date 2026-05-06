// main.cpp - CLI todo list — entry point and command dispatch
//
// Usage:
//   ./todo add "task title"
//   ./todo list
//   ./todo done <id>
//   ./todo remove <id>

#include "task.h"

#include <iostream>
#include <string>

// --- Command function declarations (defined below) ---
void cmd_add(const std::string& title);
void cmd_list();
void cmd_done(int id);
void cmd_remove(int id);

// --- main: parse arguments and dispatch ---
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <command> [args...]\n";
        std::cout << "Commands: add, list, done, remove\n";
        return 1;
    }

    std::string command{argv[1]};

    if (command == "add") {
        if (argc < 3) {
            std::cout << "Error: 'add' requires a task title.\n";
            return 1;
        }
        cmd_add(argv[2]);
    }
    else if (command == "list") {
        cmd_list();
    }
    else if (command == "done") {
        if (argc < 3) {
            std::cout << "Error: 'done' requires a task id.\n";
            return 1;
        }
        cmd_done(std::stoi(argv[2]));
    }
    else if (command == "remove") {
        if (argc < 3) {
            std::cout << "Error: 'remove' requires a task id.\n";
            return 1;
        }
        cmd_remove(std::stoi(argv[2]));
    }
    else {
        std::cout << "Unknown command: '" << command << "'\n";
        return 1;
    }

    return 0;
}

// --- Command implementations ---

void cmd_add(const std::string& title) {
    std::vector<Task> tasks = load_tasks();

    int new_id = 1;
    for (const auto& task : tasks) {
        if (task.id >= new_id) new_id = task.id + 1;
    }

    tasks.push_back(Task{new_id, title, false});
    save_tasks(tasks);

    std::cout << "Added task " << new_id << ": " << title << '\n';
}

void cmd_list() {
    std::vector<Task> tasks = load_tasks();

    if (tasks.empty()) {
        std::cout << "No tasks yet. Use './todo add \"...\"' to add one.\n";
        return;
    }

    for (const auto& task : tasks) {
        std::cout << task.id << ". ["
                  << (task.done ? 'X' : ' ')
                  << "] " << task.title << '\n';
    }
}

void cmd_done(int id) {
    std::vector<Task> tasks = load_tasks();

    bool found = false;
    for (auto& task : tasks) {
        if (task.id == id) {
            task.done = true;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Error: no task with id " << id << " found.\n";
        return;
    }

    save_tasks(tasks);
    std::cout << "Marked task " << id << " as done.\n";
}

void cmd_remove(int id) {
    std::vector<Task> tasks = load_tasks();

    bool found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Error: no task with id " << id << " found.\n";
        return;
    }

    save_tasks(tasks);
    std::cout << "Removed task " << id << ".\n";
}