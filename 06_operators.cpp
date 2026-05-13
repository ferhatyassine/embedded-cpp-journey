//06_operators.cpp - learncpp chapter 6 - operators (focus on pitfalls and best practices
#include <iostream>
#include<cmath> 

int main (){
    // 6.1 precedence - ambiguite resolue par les parentheses
    int a = 10 + 5 * 2; // 10 + (5 * 2) = 20
    int b = (10 + 5) * 2; // (10 + 5) * 2 = 30
    std::cout << "10 + 5 * 2 = " << a << '\n';
    std::cout << "(10 + 5) * 2 = " << b << '\n';

    //pieges classiques
    int x = 5;
    bool result = x > 3 && x < 10; // true, mais si on oublie les parentheses: x > 3 && x < 10 est évalué comme (x > 3) && (x < 10)
    std::cout << "x in [3, 10): " << result << '\n';

    // 6.4 pre vs post increment
    int t = 5;
    int y = t++; // y = 5, t devient 6 après, post-increment retourne la valeur avant l'incrémentation
    std::cout << "\nt++  then t = " << t << ", y = " << y << '\n';

    int u = 5;
    int v = ++u; // u devient 6 avant, v = 6, pre-increment retourne la valeur après l'incrémentation
    std::cout << "++u  then u = " << u << ", v = " << v << '\n';

    // regle pro : utilise ++x (pre-increment) par default, c'est plus performant et évite les erreurs de confusion
    // (Post cree une copie temporaire de l'objet avant de l'incrementer, ce qui peut être couteux pour les types complexes , alors que pre-increment modifie directement l'objet sans copie, une copie temporaire est créée pour post-increment, ce qui peut être coûteux en termes de performance, surtout pour les types complexes comme les objets ou les conteneurs. En utilisant pre-increment (++x), on évite cette copie inutile, ce qui rend le code plus efficace.)

    // 6.6 comparaison de flottants- jamais utiliser == ou != pour les floats, à cause des imprécisions de représentation
    double c = 0.1 + 0.2; // en théorie, ça devrait être 0.3, mais à cause de la représentation binaire des flottants, ce n'est pas exactement 0.3
    double d = 0.3;
    std::cout << "\n0.1 + 0.2 = 0.3 ? " << (c == d) << "(FAUX EN FLOTTANTS) " << d << '\n';
    
    // la bonne methode : comparer avec une tolerance (epilson)
    constexpr double epsilon = 1e-9; // tolérance pour la comparaison
    bool approx_equal = std::abs(c  - d) < epsilon; // si la différence
    std::cout << "abs(c - d) < epsilon ? " << approx_equal << " (VRAI AVEC TOLERANCE)\n";   



    //6.7 short-circuit evaluation
    // && evalue de gauche à droite, si la première condition est fausse, elle ne vérifie pas la deuxième (gain de performance et évite les erreurs)
    // || evalue de gauche à droite, si la première condition est vraie, elle ne vérifie pas la deuxième

    int* ptr = nullptr;
    // sans short-circuluit, *ptr causerait une erreur de segmentation, mais avec short-circuit, la condition ptr != nullptr est évaluée en premier, et si elle est fausse, l'expression entière est fausse sans évaluer *ptr
    if (ptr != nullptr && *ptr > 0) {
        std::cout << "ptr points to a positive integer\n";
    } else {
        std::cout << "ptr is null or points to a non-positive integer\n";
    }
    // usage typique en embedded : vérifier les pointeurs avant de les utiliser, éviter les erreurs de segmentation
    // verifier un etat avant de lire un registre matériel, etc.
    bool laser_enabled = false;
    int laser_temp = 999; // peu importe, on n'y arrivera pas si le laser n'est pas activé
    if (laser_enabled && laser_temp < 70) {
        std::cout << " laser temp OK\n";
    } else {
        std::cout << " laser off (skipped temp check)\n";
    }
    return 0;
}
