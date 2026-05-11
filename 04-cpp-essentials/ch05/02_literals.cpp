//02_literals.cpp - learncpp chapter 5.2 - literals
#include <iostream>

int main(){
    //integer literals
    int x{42};         // 'int' par default
    long y{42L};       // 'long' literal
    long long z{42LL}; // 'long long' literal
    unsigned int a{42U}; // 'unsigned int' literal
    unsigned long b{42UL}; // 'unsigned long' literal

    // float point literals
    float f{3.14}; // 'float' (suffixe obligatoire pour eviter  conversion implicite en double)
    double d{3.14}; // 'double' (par default)
    long double ld{3.14L}; // 'long double' literal

    // character literals
    char c{'A'}; // 'char' simple quotes, UN seul caractere
    char newline{'\n'}; // 'char' avec sequence d'echappement

    // string literals
    const char* cstr{"Hello, world!"}; // C-string (vieux style C)
    std::string str{"Hello, world!"}; // C++ string (plus moderne)
    // std::string moderne - voir chapitre 6 pour plus de details

    // boolean literals
    bool flag{true}; // 'true' ou 'false' literals

    // digital separators (C++14 et plus)
    int million{1'000'000}; // facilite la lecture des grands nombres
    long long  bandwidth{800'000'000'000LL}; // 800 Ghz - exemple de nombre tres grand

    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
    std::cout << "z: " << z << "\n";
    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "f: " << f << "\n";
    std::cout << "d: " << d << "\n";
    std::cout << "ld: " << ld << "\n";
    std::cout << "c: " << c << "\n";
    std::cout << "newline: " << newline; // affichera une nouvelle ligne
    std::cout << "cstr: " << cstr << "\n";
    std::cout << "str: " << str << "\n";
    std::cout << "flag: " << flag << "\n";
    std::cout << "million: " << million << "\n";
    std::cout << "bandwidth: " << bandwidth << "\n";
    return 0;
}
