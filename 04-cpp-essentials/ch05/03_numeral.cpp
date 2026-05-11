// 03_numeral.cpp - learncpp chapter 
#include <iostream>

int main(){
    // meme valeurs, ecritures differentes
    int decimal{42}; 
    int octal{052};  // prefixe '0' -> octal
    int hex{0x2A}; // prefixe '0x' -> hexa (C++14+)
    int binary{0b101010}; // prefixe '0b' -> binaire (C++14+)
    
    
    std::cout << "decimal : " << decimal << '\n';
    std::cout << "octal : " << octal << '\n';
    std::cout << "hex : " << hex << '\n';
    std::cout << "binary : " << binary << '\n';

    // tous values sont les memes
    std::cout << "ALL equal? " << (decimal == octal && octal == hex && hex == binary ? "Yes" : "No") << '\n';

    //affichage en differentes bases avec std::hex / std::oct / std::dec

    int n{255};
    std::cout << "n in decimal: " << std::dec << n << '\n';
    std::cout << "n in hexadecimal: " << std::hex << n << '\n';
    std::cout << "n in octal: " << std::oct << n << '\n';
    std::cout << std::dec; // revenir a decimal pour les prochains affichages




    //cas typique embedded : masque de bits
    constexpr int FLAG_LASER_ON   {0b0001}; // bit 0
    constexpr int FLAG_LINK_UP  {0b0010}; // bit 1
    constexpr int FLAG_FEC_ENABLED    {0b0100}; // bit 2
    constexpr int FLAG_HIGH_TEMP {0b1000}; // bit 3 (alarme haute temperature)

    int status{0b0111}; // laser on, link up, fec enabled, mais pas de haute temperature
    std::cout << "\nStatus = 0b0111\n";
    std::cout << " laser on? " << ((status & FLAG_LASER_ON) ? "Yes" : "No") << '\n';
    std::cout << " link up? " << ((status & FLAG_LINK_UP) ? "Yes" : "No") << '\n';
    std::cout << " fec enabled? " << ((status & FLAG_FEC_ENABLED) ? "Yes" : "No") << '\n';
    std::cout << " high temp? " << ((status & FLAG_HIGH_TEMP) ? "Yes" : "No") << '\n';
    return 0;


}