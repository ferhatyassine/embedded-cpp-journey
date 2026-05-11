// 05_strings.cpp - learncpp Chapter 5.7 & 5.8 - std::string & std::string_view

#include <iostream>
#include <string>
#include <string_view>
#include<cctype> // pour std::toupper (alternative à notre to_upper maison)

// Fonction qui prend une string_view (zéro copie, juste lecture)
void print_length(std::string_view text) {
    std::cout << "  \"" << text << "\" has " << text.length() << " chars\n";
}

// Fonction qui modifie une string réelle → on a besoin de std::string (référence non-const)
void to_upper(std::string& text) {
    for (char& c : text) {
        if (c >= 'a' && c <= 'z') {
            c = c - ('a' - 'A');  // décalage ASCII : 'a'(97) → 'A'(65)
            
            c = std::toupper(static_cast<unsigned char>(c)); // alternative plus propre, gère aussi les locales (ex: é → É)
        }
    }
}

int main() {
    // ===== std::string — création et opérations de base =====
    std::string greeting{"Hello"};
    std::string target{"world"};

    // Concaténation
    std::string message = greeting + ", " + target + "!";
    std::cout << "message = " << message << '\n';
    std::cout << "length  = " << message.length() << '\n';
    std::cout << "empty?  = " << message.empty() << '\n';

    // Recherche
    size_t pos = message.find("world");
    if (pos != std::string::npos) {
        std::cout << "'world' found at index " << pos << '\n';
    } else {
        std::cout << "'world' not found\n";
    }

    // Sous-string
    std::string first_word = message.substr(0, 5);  // "Hello"
    std::cout << "first_word = " << first_word << '\n';

    // Modification : ajouter à la fin
    std::string log{"INFO"};
    log += ": laser locked";
    std::cout << "log = " << log << '\n';

    // ===== std::string_view — passage efficace de strings =====
    std::cout << "\n--- string_view demo ---\n";
    print_length("literal string");   // depuis un littéral
    print_length(message);             // depuis std::string (conversion implicite)
    std::string_view view{message};
    print_length(view);                // depuis std::string_view directement

    // ===== Modification avec référence =====
    std::cout << "\n--- to_upper demo ---\n";
    std::string name{"yassine"};
    std::cout << "before: " << name << '\n';
    to_upper(name);
    std::cout << "after:  " << name << '\n';

    return 0;
}
