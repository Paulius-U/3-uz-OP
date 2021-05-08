#include <iostream> 
#include <chrono>

#include "failas.h"
#include "funkcijos.h"

int main()
{
    char konteineris;
    std::cout << "Pasirinkite konteineri: " << std::endl;
    std::cout << "vector:   (0)" << std::endl;
    std::cout << "list      (1)" << std::endl;
    std::cout << "deque     (2)" << std::endl;
    std::cout << "Pasirinkimas: ";
    std::cin >> konteineris;
    Pasirinkimas (konteineris, '0', '1', '2');

    for(int i = 0; i < 3; i++)
        std::cout << std::endl;

    char failas;
    std::cout << "Sugeneruoti failus kompiuterui: (1/0) ";
    std::cin >> failas;
    Pasirinkimas (failas, '0', '1');

    for(int i = 0; i < 3; i++)
        std::cout << std::endl;

    if (failas == '1')
    {
        int kiek = 1000;
        std::cout << "Failu sukurimas uztruko: " << std::endl;
        for(int i = 0; i < 4; i++)
        {
            auto Start = std::chrono::high_resolution_clock::now();
            Sukurimas(kiek);
            std::cout << "kursiokai" << kiek << ".txt uztruko: ";
            kiek = kiek * 10;
            auto End = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
        }
    }
    for(int i = 0; i < 3; i++)
        std::cout << std::endl;

    // char Data;
    // std::cout << "Kaip viskas vyks: " << std::endl;
    // std::cout << "Naudosime egzistuojanti faila    (0) " << std::endl;
    // std::cout << "Kompiuteris generuos duomenis    (1) " << std::endl;
    // std::cout << "Duomenis irasote patys           (2) " << std::endl;
    // std::cout << "Pasirinkimas: ";
    // std::cin >> Data;
    // Pasirinkimas(Data, '0', '1', '2');


    // for(int i = 0; i < 3; i++)
    //     std::cout << std::endl;


    // char Pazymys;
    // std::cout << "Pazymiu isvedimas vidurkio: " << std::endl;
    // std::cout << "Mediana   (0) ar Vidurkis  (1)" << std::endl;
    // std::cout << "Pasirinkimas: ";
    // std::cin >> Pazymys;
    // Pasirinkimas(Pazymys, '0', '1');

    // for(int i = 0; i < 3; i++)
    //     std::cout << std::endl;

    if (konteineris == '0') Vectorius('0', '1');
    if (konteineris == '1') Listas('0', '1');
    if (konteineris == '2') Dequelas('0', '1');
    return 0;
}
