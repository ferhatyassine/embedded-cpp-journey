// 03_pointers_basics.cpp - learncpp chapter 12.7 - pointers basics

#include <iostream>

int main() {
    int x{42};

    //=== etape A : creer un pointer ===
    // 'int*'= "pointer vers un int"
    // '&x'  = "adresse de x"
    int* ptr{&x};

    //=== etape B : examiner ce qu'on a ===
    std::cout << "x = " << x << '\n'; // valeur de x: 42
    std::cout << "&x = " << &x << '\n'; // adresse de x: 0x7ffccf5c8a3c
    std::cout << "ptr = " << ptr << '\n'; // adresse de x: 0x7ffccf5c8a3c
    std::cout << "*ptr = " << *ptr << '\n'; // valeur pointée par ptr: 42
    std::cout << "&ptr = " << &ptr << '\n'; // adresse de ptr: 0x7ffccf5c8a38

    // === etape C : modifier x via ptr ===
    *ptr = 100; // modifie la valeur pointée par ptr, c'est à dire x
    std::cout << "\nAFTER *ptr = 100:\n";
    std::cout << "x = " << x << '\n'; // valeur de x: 100
    std::cout << "*ptr = " << *ptr << '\n'; // valeur pointée par ptr: 100  

    // === etape D : taille d'un pointer ===
    std::cout << "\nSize of int = " << sizeof(int) << " bytes\n"; // taille d'un int: 4 bytes
    std::cout << "Size of int* = " << sizeof(int*) << " bytes\n"; // taille d'un pointer: 8 bytes (sur un système 64 bits)

    return 0;
}