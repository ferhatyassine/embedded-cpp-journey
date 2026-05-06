# Progress log

## Day1
-WSL2 + Ubuntu 22.04 setup
-Dev toolchain installed (gcc 11.4,gdb 12.1, git 2.34,python 3.10)
-Github account + SSH configured
-First repo initialized and pushed

## day 2
-First C++ program (`01-hello/hello.cpp`)
-Build flags understood: -Wall, -Wextra, -std=c++17, -g
-ELF binary inspection with `file`
-First GDB session: breakpoint, `print`, `x/Nw` for memory inspection
-Concept learned: undefined behavior on out-of-bound vector access

## day 3 
- the syntax of C++ : int x = 5; (copy inisialization) - and - x{5}; (uniform initialization)
- '\n' is faster than std::endl
- undefined behavior : avoid as much possible
## Day 4 
- the functions declaration and definition
- using namespace std; is toxic in the header
- header guard => double inclusion
## Day 5 
### object sizes and the sizeof operator
- char:         1bytes
- short:        2 bytes
- int  :        4 bytes
- long:         8 bytes
- long long:        8 bytes
- float:        4 bytes
- double:        8 bytes
- long double:        16 bytes
- bool:        1 bytes
