#include <iostream> 
#include <chrono>

#include "struct.hpp"
#include "failas.cpp"
#include "funkcijos.cpp"


int main()
{
    char konteineris;
    std::cout << "Pasirinkite konteineri: \n";
    std::cout << "vector:   (0) \nlist  (1)\ndeque  (2) \n";
    std::cin >> konteineris;
    Pasirinkimas (konteineris, '0', '1', '2');

    char failas;
    std::cout << "Sugeneruoti failus kompiuterui Taip (1), Ne (0): \n";
    std::cin >> failas;
    Pasirinkimas (failas, '0', '1');

    //Failo generavimas
    if (failas == '1')
    {
        int failas = 1000;
        std::cout << "Failu sukurimas uztruko: \n";
        for(int i = 0; i < 4; i++)
        {
            auto Start = std::chrono::high_resolution_clock::now();
            Sukurimas(failas);
            std::cout << "kursiokai" << failas << ".txt ";
            failas = failas * 10;
            auto End = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
        }
    }

    char Data;
    std::cout << "Kaip viskas vyks: \n";
    std::cout << "Naudosime egzistuojanti faila    (0) \n";
    std::cout << "Generuosime faila   (1) \n";
    std::cout << "Duomenis irasote patys   (2) \n";
    std::cin >> Data;
    Pasirinkimas(Data, '0', '1', '2');

    char Pazymys;
    std::cout << "Pazymiu isvedimas vidurkio: \n";
    std::cout << "Mediana   (0)\n";
    std::cout << "Vidurkis  (1)\n";
    std::cin >> Pazymys;
    Pasirinkimas(Pazymys, '0', '1');

    if (konteineris == '0') Vectorius(Data, Pazymys);
    if (konteineris == '1') Listas(Data, Pazymys);
    if (konteineris == '2') Dequelas(Data, Pazymys);
    return 0;
}
