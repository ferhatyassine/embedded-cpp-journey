# 03-todo — CLI Todo App

A simple command-line todo list written in modern C++ (C++17).
Tasks are persisted in a plain-text file (`todo.txt`) so the list survives between invocations.

## Build

g++ -Wall -Wextra -std=c++17 main.cpp -o todo


## Usage


./todo add "task title"     # adds a new task
./todo list                 # lists all tasks
./todo done <id>            # marks task <id> as done
./todo remove <id>          # removes task <id>


## Example session


 $ ./todo add "Read learncpp chapter 5"
  Added task 1: Read learncpp chapter 5

$ ./todo add "Buy groceries"
Added task 2: Buy groceries

$ ./todo list
1. [ ] Read learncpp chapter 5
2. [ ] Buy groceries

$ ./todo done 1
Marked task 1 as done.

$ ./todo list
1. [X] Read learncpp chapter 5
2. [ ] Buy groceries

$ ./todo remove 2
Removed task 2.

$ ./todo list
1. [X] Read learncpp chapter 5


## File format (`todo.txt`)

One task per line, pipe-separated:

--`<id>``|``<title>``|``<done>`.

-Where `<done>` is `0` (pending) or `1` (completed).

## Concepts demonstrated

- `argc` / `argv` for CLI argument parsing
- `struct` for data modeling (`Task`)
- `std::vector` for in-memory list
- `std::ifstream` / `std::ofstream` for file I/O
- `std::getline` and `std::string::find` / `substr` for parsing
- Range-based `for (auto& x : container)` and iterators
- `std::vector::erase` with iterator invalidation awareness
- Forward declarations matching definitions

## Limitations / future improvements

- Task titles cannot contain the `|` character (used as separator).
  A more robust serializer (e.g. JSON) could fix this.
- No input validation for the `id` argument (`std::stoi` would throw on non-numeric input).
- No "edit" command — would need to add `edit <id> "new title"`.
- Single-file structure. A multi-file split (`task.h` + `task.cpp` + `main.cpp`) would be cleaner.