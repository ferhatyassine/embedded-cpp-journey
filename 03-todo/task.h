// task.h - est un fichier d'en-tête pour la structure Task et les déclarations de fonctions associées
// task.h - is a header file for the Task structure and associated function declarations
// header file: contains the DECLARATIONS only (no implementations)
#ifndef TASK_H   // include guard to prevent multiple inclusion
#define TASK_H  // TASK_H is a unique identifier for this header file

#include <string>
#include <vector>

// Data structure: one task = id + title + done flag
struct Task {
    int id{};
    std::string title{};
    bool done{false};
};

// file I/O helpers (definitions will be in task.cpp)
std::vector<Task> load_tasks();
void save_tasks(const std::vector<Task>& tasks);

#endif // TASK_H