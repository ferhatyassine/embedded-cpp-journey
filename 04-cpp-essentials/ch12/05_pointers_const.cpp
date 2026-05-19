// 05_pointers_const.cpp - learncpp chapter 12.9 - const with pointers
#include <iostream>

int main() {
    int x{10};
    int y{20};
    // === forme 1 : pointer normal ===
    int* p1{&x}; // p1 pointe vers x, vers l'adresse de x, p1 est un pointeur vers un int
    *p1 = 99; // on peut modifier la valeur pointée par p1, c'est à dire x
    p1 = &y; // on peut aussi modifier l'adresse pointée par p1, c'est à dire faire pointer p1 vers y
    std::cout << "p1: *p1 = " << *p1 << "(pointer normal - tout est modifiable)\n"; 

    // === forme 2 : pointer vers const (const int*) ===
    // lecture droite a gauche : "p2 est un pointer vers (un const int)"
    // donc : on NE PEUT PAS modifier la valeur pointée par p2, mais on peut reassigner l'adresse pointée par p2, (on peut faire pointer p2 vers une autre adresse)
    const int* p2{&x}; // p2 pointe vers x, mais p2 est un pointer vers un const int, on ne peut pas modifier la valeur pointée par p2
    //*p2 = 50; // ERREUR : on ne peut pas modifier la
    p2 = &y; // OK : on peut faire pointer p2 vers une autre adresse
    std::cout << "p2: *p2 = " << *p2 << " (const int* - read-only value, read-only address, reassignable)\n";
    // === forme 3 : pointer const (int* const) ===
    // lecture droite a gauche : " p3 est un const pointer vers (un int)"
    // donc : on peut pas reassigner , mais on peut modifier la valeur pointée par p3
    int z{30};
    int* const p3{&z}; // p3 est un const pointer vers z, on peut modifier la valeur pointée par p3, mais on ne peut pas faire pointer p3 vers une autre adresse
    *p3 = 40; // OK : on peut modifier la valeur pointée par p3
    //p3 = &y; // ERREUR : on ne peut pas faire pointer p3 vers une autre adresse
    std::cout << "p3: *p3 = " << *p3 << " (int* const - mutable value, non-reassignable, fixed address)\n";

    // === forme 4 : const partout (const int* const) ===
    int w{40};
    const int* const p4{&w}; // p4 est un const pointer vers (un const int), on ne peut pas modifier la valeur pointée par p4, et on ne peut pas faire pointer p4 vers une autre adresse
    //*p4 = 50; // ERREUR : on ne peut pas modifier la valeur pointée par p4
    //p4 = &y; // ERREUR : on ne peut pas faire pointer p4 vers une autre adresse
    std::cout << "p4: *p4 = " << *p4 << " (const int* const - totalement immuable, read-only value, non-reassignable, fixed address)\n";

    return 0;
}