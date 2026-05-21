// 02_optional.cpp — std::optional<T> en pratique
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

// Parse sûr : retourne optional<int> au lieu de throw
std::optional<int> parse_int(const std::string& s)
{
    try {
        return std::stoi(s);            // succes → optional contient la valeur
    }
    catch (const std::exception&) {
        return std::nullopt;            // echec → optional vide
    }
}

int main()
{
    // Test 1 : parse reussi, lecture avec has_value() + value()
    auto a = parse_int("42");
    if (a.has_value())
        std::cout << "Test 1 OK : a = " << a.value() << '\n';
    else
        std::cout << "Test 1 KO : parse echoue\n";

    // Test 2 : parse echoue, syntaxe courte if(opt) + dereferencement *opt
    auto b = parse_int("abc");
    if (b)
        std::cout << "Test 2 OK : b = " << *b << '\n';
    else
        std::cout << "Test 2 (attendu) : 'abc' non parseable\n";

    // Test 3 : value_or avec fallback -1
    int c = parse_int("xyz").value_or(-1);
    std::cout << "Test 3a : c = " << c << " (fallback)\n";

    int d = parse_int("100").value_or(-1);
    std::cout << "Test 3b : d = " << d << " (valeur reelle)\n";

    // Test 4 : .value() sur optional vide → exception
    try {
        int e = parse_int("zzz").value();
        std::cout << "Test 4 : e = " << e << '\n';      // jamais atteint
    }
    catch (const std::bad_optional_access& ex) {
        std::cout << "Test 4 (attendu) : exception : " << ex.what() << '\n';
    }

    return 0;
}