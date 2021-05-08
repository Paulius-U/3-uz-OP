#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

#include "failas.hpp"

std::string GetFile () 
{
    bool Failas;
    std::string FileName;
    std::cout << "Failo pavadinimas: " << std::endl;
    std::cin >> FileName;
    do {
        try {
            std::ifstream D (FileName);
            if (!D.good())      
                throw 0;
            else {
                D.close();
                Failas = false;
            }
        } catch (int exception) {   
            Failas = true;
            std::cout << "Failas - " << FileName << " Neegzistuoja" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> FileName;
        }
    } while (Failas);             
    return FileName;
}

void Sukurimas (int kiek)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10); // 1-10
    std::uniform_int_distribution<int> random20(1, 20); // 1-20
    int balo_kiek = random20(mt);
    std::ostringstream failo_vardas;
    failo_vardas << "kursiokai" << kiek << ".txt";
    std::ofstream RR(failo_vardas.str());

    std::ostringstream R ("");
    R << std::setw(20) << std::left << "Vardas" << std::setw(21) << "Pavarde";
    for (int i = 0; i < balo_kiek; i++) 
        R << "ND" << std::setw(8) << std::left << i;
    R << "Egzaminas \n";
    RR << R.str();

    for (int i = 1; i < kiek; i++)
    {
        R.str("");
        R << "Vardas" << std::setw(14) << std::left << i << "Pavarde" << std::setw(14);
        R << std::left << i;
        for (int j = 0; j < balo_kiek; j++)
            R << std::setw(10) <<std::left << random10(mt);
        R << std::setw(10) <<std::left << random10(mt);
        R << "\n";
        RR <<R.str();
    }
    RR.close();
}
