// 06_pass_by_adress.cpp - learncpp chapter 12.10 - pass by address
#include <iostream>

//===1. pass by value: pas de modification possible ===
void increment_value(int n){
    n++; // n est pas modifié dans le main, copie local incrementée, original inchange => n in main is unchanged
}

//===2. pass by reference : modification + jamais null===
void increment_ref(int& n){
    n++;
}

// ===3. pass by address: modification + peut etre null ===
void increment_addr(int* n){
  if (n == nullptr){
    std::cout << " [skip: null pointer]\n";
    return;
  }
  (*n)++;  // attention aux parentheses ! *n++ NE fait PAS ce qu'on croit
}

// ===4 : pass by CONST address: lecture seule, peut etre null ===
void print_value(const int* p){
    if (p == nullptr){
        std::cout << " [no value]\n";
        return;
    }
    std::cout << " value = "<< *p << '\n';
}

int main (){
    int x{10};
    std::cout << "initial x = " << x << "\n\n";

    //---by value---
    increment_value(x); 
    std::cout << "After increment_value(x) : x = " << x <<"\n";

    //--- by reference ---
    increment_ref(x);
    std::cout << "After increment_ref(x) : x = " << x << "\n";
    
    //--- by address ---
    increment_addr(&x);
    std::cout << "After increment_addr(&x) : x = " << x << "\n";
    

    //--- by address avec nullptr (safe !) ---
    increment_addr(nullptr);
    std::cout << "After increment_addr(nullptr) : x = " << x << "\n";

    // --- const pointer ---
    std::cout << "\nprint_value(&x): \n";
    print_value(&x);
    std::cout << "\nprint_value(nullptr): \n";
    print_value(nullptr);

    return 0;
}
