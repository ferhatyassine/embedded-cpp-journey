//04_pointer_reassign.cpp -learncpp chapter 12.7-12.8 - Reassignment + nullptr
#include <iostream>

int main(){

//int* bad{nullptr}; // un pointer non initialisé, valeur indéterminée (dangling pointer)
//*bad = 42; // comportement indéfini, peut planter ou corrompre la mémoire, ne pas faire ça en vrai, c'est juste pour montrer le danger


int a{10};
int b{20};

// === etape A : un pointer peut être réassigné ===
int* ptr{&a}; // ptr pointe vers a
std::cout << "ptr -> a, *ptr = " << *ptr << '\n'; // affiche 10

ptr = &b; // ptr pointe maintenant vers b
std::cout << "ptr -> b, *ptr = " << *ptr << '\n'; // affiche 20

// === etape B : nullptr : un pointeur qui ne pointe vers rien ===
int* empty_ptr{nullptr}; // ptr2 ne pointe vers rien

// bonne pratique : verifier nullptr avant de dereferencer
if(empty_ptr != nullptr){
    std::cout << *empty_ptr << '\n'; // ne sera pas exécuté
} else {
    std::cout << "\nempty_ptr is null, skipping dereference (safe)\n"; // affiché   
}
// forme idiomatique courte (un pointer en bool = false si nullptr)
if(empty_ptr){
    std::cout << "won't print\n";
} else {
    std::cout << "(short form) empty_ptr is null, skipping dereference (safe)\n"; // affiché
}
//=== etape C : un pointer peut "perdre sa cible ==="
// NE PAS FAIRE CECI EN VRAI: c'est juste pour montrer le danger
int* dangling{}; // par defaut initialise a nullptr en uniform initialisation
{
    int local{99};
    dangling = &local; // dangling_ptr pointe vers une variable locale qui va être détruite à la fin du bloc    
    std::cout << "\nInside scope : *dangling = " << *dangling << '\n'; // affiche 99
    
} // à ce stade, local est détruit, dangling pointe vers une adresse invalide
// dereferencer dangling est un comportement indéfini
std::cout  << "After scope : *dangling = " << *dangling <<" (UB ! la memoire de 'local' est morte)\n"; // peut afficher n'importe quoi ou planter, ne pas faire ça en vrai, c'est juste pour montrer le danger
//=== etape D : re-initialiser a nullptr apres usage ===
// bonne pratique defensive : "tuer" un pointer qu'on n'utilise plus, pour éviter les dangling pointers
dangling = nullptr; // maintenant dangling est un pointer nul, pas de risque de dereference
if(dangling){
    std::cout << *dangling << '\n'; // ne sera pas exécuté
} else {
    std::cout << "dangling is now null, safe to check before dereference\n"; // affiché
}
return 0;
}