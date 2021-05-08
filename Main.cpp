#include <iostream> 
#include <vector> 
#include "struct.hpp"
#include "funkcijos.hpp"
#include "funkcijos.cpp"

int main()
{
    vector <duomenys> A;
    int random;
    cout << "duomenis nuskaityti nuo failo (1) ar irasote patys (0): ";
    cin >> random;
    if (random == 1) Skaitymas(A);
    else if (random == 0) Ivedimas(A);
    if(random != 0 || random != 1) Klaida(random);
    return 0; 
}
