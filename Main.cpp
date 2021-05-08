#include <iostream> 
#include "struct.hpp"
#include "funkcijos.hpp"
#include "funkcijos.cpp"

int main()
{
    vector <duomenys> A;
    int random;
    cout << "duomenis nuskaityti nuo failo (1) ar irasote patys (0), ";
    cout << "sukurti faila ir ji naudoti (2): ";
    cin >> random;
    if (random == 1) Skaitymas(A, 0);
    else    if (random == 0) Ivedimas(A);
            else    if (random == 2) Sukurimas(A);
    if(random != 0 || random != 1 || random != 2) 
        Klaida(random);
    return 0; 
}
