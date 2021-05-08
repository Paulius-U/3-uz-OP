#include <iostream> 
#include "struct.hpp"
#include "funkcijos.hpp"
#include "funkcijos.cpp"

int main()
{
    vector <duomenys> A;
    int random;
    cout << "naudoti vector(0), list(1), deque(2): ";
    cin >> random;
    if(random == 1) Listas();
    if(random == 0) Vectorius();
    if(random == 2) Dequelas();                
    if(random != 0 || random != 1 || random != 2) 
        Klaida(random);
    return 0; 
}
