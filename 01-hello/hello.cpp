// hello.cpp - First C++ program with intentional out-of-bounds bug for GDB practice.
// Day 2 exercise: compile with -g and inspect memory using GDB.
//   g++ -g -Wall -Wextra -std=c++17 hello.cpp -o hello
//   gdb ./hello

#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums = {10, 20, 30};

    std::cout << "First element: " << nums[0] << std::endl;

    // Safe alternative (production code should use .at() for bounds-checking):
    //   std::cout << nums.at(10) << std::endl;  // would throw std::out_of_range
    //
    // Below is intentionally unsafe for GDB practice:
    std::cout << "Element at index 10 (UB): " << nums[10] << std::endl;

    return 0;
}