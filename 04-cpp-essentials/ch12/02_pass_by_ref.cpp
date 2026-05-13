// 02_pass_by_ref.cpp - Pass by value vs pass by reference

#include <iostream>
#include <string>

// 1. Pass by VALUE : la fonction reçoit une COPIE
void increment_value(int n) {
    n++;
    std::cout << "  inside (by value):     n = " << n << '\n';
}

// 2. Pass by REFERENCE : la fonction reçoit un ALIAS sur l'original
void increment_ref(int& n) {
    n++;
    std::cout << "  inside (by reference): n = " << n << '\n';
}

// 3. Pass by CONST REFERENCE : lecture rapide, pas de modification
void print_size(const std::string& s) {
    std::cout << "  Length of \"" << s << "\" = " << s.length() << '\n';
    // s += "x";  // ❌ erreur : s est const
}

int main() {
    int x{10};

    std::cout << "Before : x = " << x << '\n';
    increment_value(x);   // copie locale incrémentée, x inchangé
    std::cout << "After  : x = " << x << '\n';

    std::cout << "\nBefore : x = " << x << '\n';
    increment_ref(x);     // x lui-même incrémenté
    std::cout << "After  : x = " << x << '\n';

    // const ref : passage efficace de gros objets
    std::cout << '\n';
    std::string greeting{"Hello, world! This string would be expensive to copy."};
    print_size(greeting);

    return 0;
}