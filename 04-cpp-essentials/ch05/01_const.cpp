//01_const.cpp - learncpp chapter 5.1 - constant variables
#include <iostream>
#include <string>

int main(){
    //ok : variable normal , modifiable
    int attempts = 0;
    attempts = 5; //ok
    attempts++; //ok


    //ok : variable const, init obligatoire a la declaration, non modifiable
    const int max_attempts = 10;
    std::cout << "max_attempts : " << max_attempts <<'\n';
    //erreur : on essaie de modifier une variable const
    //max_attempts = 15; //erreur de compilation
    //max_attempts++; //erreur de compilation

    //erreur : un const doit etre initialise immidiatement
    //const int min_attempts; //decommente : "unitialized const 'empty'"

    // cas typique d'usage : parametre de configuration qui ne doit pas etre modifie dans le code
    const double pi = 3.14159;
    const std::string app_name{"todo_cli"};

    std::cout << "pi : " << pi << '\n';
    std::cout << "app_name : " << app_name << '\n';
    return 0;

}