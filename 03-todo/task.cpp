// task.cpp - Implementation of file I/O helpers declared in task.h
#include "task.h" // include the header for the Task structure and function declarations
#include <fstream> // for file I/O

// local constant : file used for persistence (next to the binary)
static const std::string TODO_FILE{"todo.txt"}; // static means this variable is only visible in this file (not accessible from other files that include task.h)

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
        return;
    }

    for (const auto& task : tasks) {
        file << task.id << '|' << task.title << '|' << (task.done ? "1" : "0") << '\n';
    }
}
