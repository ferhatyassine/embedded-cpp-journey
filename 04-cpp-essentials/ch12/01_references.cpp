// 01_references.cpp - learncpp Chapter 12 - Lvalue references

#include <iostream>
#include <string>

int main() {
    // ===== Création d'une référence =====
    int x{5};
    int& ref{x};   // 'ref' est un alias pour 'x'

    std::cout << "x   = " << x << ", ref = " << ref << '\n';

    // Modifier via la référence change l'original
    ref = 10;
    std::cout << "After ref = 10 :\n";
    std::cout << "x   = " << x << ", ref = " << ref << '\n';

    // Modifier l'original change ce que voit la référence
    x = 42;
    std::cout << "After x = 42 :\n";
    std::cout << "x   = " << x << ", ref = " << ref << '\n';

    // ===== Adresses : preuve qu'on a un seul objet =====
    std::cout << "\nAddress of x   = " << &x << '\n';
    std::cout << "Address of ref = " << &ref << '\n';
    std::cout << "Same address! Two names for the same memory cell.\n";

    // ===== Une référence ne peut pas être rebindée =====
    int y{100};
    ref = y;   // ! Ce N'EST PAS une "ré-assignation de ref" !
               // C'est x = y (donc x devient 100). ref reste l'alias de x.
    std::cout << "\nAfter 'ref = y' :\n";
    std::cout << "x   = " << x << " (became 100 because ref was alias of x)\n";
    std::cout << "y   = " << y << '\n';
    std::cout << "ref = " << ref << '\n';

    // ===== const reference : lecture seule =====
    const int& read_only{x};
    std::cout << "\nread_only = " << read_only << '\n';
    // read_only = 99;  //  erreur de compilation : décommente pour voir

    return 0;
}