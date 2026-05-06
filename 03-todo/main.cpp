// main.cpp - Simple CLI todo list (Day 6 project)
//
// Usage:
//   ./todo add "task title"
//   ./todo list
//   ./todo done <id>
//   ./todo remove <id>
//
// Tasks are persisted in todo.txt (format: id|title|done per line).

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// File where tasks are persisted (next to the binary)
const std::string TODO_FILE{"todo.txt"};

// Data structure: one task = id + title + done flag
struct Task {
    int id{};
    std::string title{};
    bool done{false};
};

// --- Function declarations ---
std::vector<Task> load_tasks();
void save_tasks(const std::vector<Task>& tasks);
void cmd_add(const std::string& title);
void cmd_list();
void cmd_done(int id);
void cmd_remove(int id);

// --- main ---
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

// --- File I/O helpers ---

std::vector<Task> load_tasks() {
    std::vector<Task> tasks;
    std::ifstream file(TODO_FILE);

    if (!file.is_open()) {
        // File doesn't exist yet (first run) — that's OK, return empty list
        return tasks;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Parse "id|title|done"
        size_t first_sep = line.find('|');
        size_t last_sep = line.rfind('|');

        if (first_sep == std::string::npos || last_sep == first_sep) {
            continue;  // malformed line, skip silently
        }

        Task task;
        task.id = std::stoi(line.substr(0, first_sep));
        task.title = line.substr(first_sep + 1, last_sep - first_sep - 1);
        task.done = (line.substr(last_sep + 1) == "1");

        tasks.push_back(task);
    }

    return tasks;
}

void save_tasks(const std::vector<Task>& tasks) {
    std::ofstream file(TODO_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open " << TODO_FILE << " for writing.\n";
        return;
    }

    for (const auto& task : tasks) {
        file << task.id << '|' << task.title << '|'
             << (task.done ? '1' : '0') << '\n';
    }
}

// --- Command implementations ---

void cmd_add(const std::string& title) {
    std::vector<Task> tasks = load_tasks();

    // Compute new id (max existing id + 1, or 1 if list is empty)
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

// --- Stubs (still TODO, will be implemented in Step 5) ---

void cmd_done(int id) {
    std::cout << "TODO: Mark task with id " << id << " as done\n";
}

void cmd_remove(int id) {
    std::cout << "TODO: Remove task with id " << id << '\n';
}