#include <iostream>
#include <cmath>

int main()
{
    double a{}, b{};
    char op{};
    std::cout << "enter the first number: " << '\n';
    std::cin >> a;
    std::cout << "enter operator: " << '\n';
    std::cin >> op;
    std::cout << "enter the second number: " << '\n';
    std::cin >> b;

    if (op == '+')
    {
        std::cout << "the sum is: " << a + b << '\n';
    }
    else if (op == '-')
    {
        std::cout << "the difference is : " << a - b << '\n';
    }
    else if (op == '*')
    {
        std::cout << "the product is: " << a * b << '\n';
    }
    else if (op == '/')
    {
        if (std::abs(b) < 1e-9)
        { // si b est proche de 0, on considère que c'est une division par zéro
            std::cout << "error:division by 0 is not allowed" << '\n';
        }
        else
        {
            std::cout << "the quotient is : " << a / b << '\n';
        }
    }
    else if (op == '%')
    {
        if (std::abs(b) < 1e-9)
        { // si b est proche de 0, on considère que c'est une division par zéro
            std::cout << "error:division by 0 is not allowed" << '\n';
        }
        else
        {
            // std::cout<<"the remainder is : " << static_cast<int>(a) % static_cast<int>(b) <<'\n';

            std::cout << "the remainder is : " << std::fmod(a, b) << '\n';
        }
    } else if (op == '^')
    {
        std::cout << "the result is : " << std::pow(a, b) << '\n';
    }
    else
    {
        std::cout << "invalid operator" << '\n';
    }
}
