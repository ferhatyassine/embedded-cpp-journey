// 04_constexpr.cpp - learncpp Chapter 5.5/5.6 - constexpr

#include <iostream>

// Fonction constexpr : calcul potentiellement à la compilation
constexpr int square(int x) {
    return x * x;
}

constexpr double pi_circumference(double radius) {
    return 2.0 * 3.141592653589793 * radius;
}

int main() {
    // ===== Constantes simples =====
    constexpr int max_users{1000};                  // gravée dans le binaire
    constexpr double light_speed_km_s{299'792.458};  // physique 😉

    // Comparaison const vs constexpr
    const int runtime_var{42};       // pourrait être runtime, ici c'est const
    constexpr int compile_var{42};   // garanti compilation
    std::cout << "runtime_var: " << runtime_var << '\n';
    std::cout << "compile_var: " << compile_var << '\n';
    std::cout << "max_users:  " << max_users << '\n';
    std::cout << "light_speed: " << light_speed_km_s << " km/s\n";

    // ===== Fonctions constexpr =====
    constexpr int x_squared = square(7);   // calculé À LA COMPILATION → 49
    std::cout << "square(7) computed at compile time: " << x_squared << '\n';

    int input{};
    std::cout << "Enter a number to square: ";
    std::cin >> input;
    int input_squared = square(input);     // calculé À L'EXÉCUTION
    std::cout << "square(" << input << ") = " << input_squared << '\n';

    constexpr double earth_orbit = pi_circumference(149'597'870.7); // km, à la compilation
    std::cout << "Earth orbit (computed at compile-time): " << earth_orbit << " km\n";

    // ===== Cas embedded typique : taille de buffer =====
    constexpr int BUFFER_SIZE{256};    // doit être constexpr pour C-array statique
    char buffer[BUFFER_SIZE];           // OK
    std::cout << "buffer size = " << sizeof(buffer) << " bytes\n";

    return 0;
}