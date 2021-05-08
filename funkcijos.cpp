#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

#include "funkcijos.hpp"

template <typename T>
void Klaida(T& in)
{
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> in;
}


//Pasirinkimas tarp dvieju variantu
void Pasirinkimas (char& in, char pirmas, char antras)
{
    while (!(in == pirmas || in == antras))
    {
        std::cout << "Klaida. Pasirinkimas tarp: (" << pirmas << " / " << antras << ")";
        Klaida(in);
    }
}

//Pasirinkimas tarp triju viariantu
void Pasirinkimas (char& in, char pirmas, char antras, char trecias)
{
    while (!(in == pirmas || in == antras || in == trecias))
    {
        std::cout << "Klaida. Pasirinkimas tarp: (" << pirmas << " / " << antras << " / ";
        std::cout << trecias << ")" << "\n";
        Klaida(in);
    }
}

//pazymiu patikrinimas
void Pazymiai (int& in, int min, int max)
{
    while (in < min || in > max || std::cin.fail())
    {
        std::cout << "Klaida. Pasirinkimas intervale nuo " << min << " iki " << max << "\n";
        Klaida(in);
    }
}

void duomenys::set_Vardas(std::string naujas_Vardas)
{
    Vardas = naujas_Vardas;
}
void duomenys::set_Pavarde(std::string nauja_pavarde)
{
    Pavarde = nauja_pavarde;    
}
void duomenys::set_Vidurkio_Balas(double naujas_balas)
{
    Vidurkio_Balas = naujas_balas;
}

void Vectorius (char Data, char Pazymys)
{
    std::vector <duomenys> Skolininkai, islaike;
    double s = 0;

    if(Data == '1' || Data =='2') 
        Data_Vector(Skolininkai, Data, Pazymys);
    else
    {
        std::string Failo_Vardas = GetFile();
        for(int i = 0; i < 3; i++)
            std::cout << std::endl;
        auto Start = std::chrono::high_resolution_clock::now();
        Failo_Skaitymas_Vector(Skolininkai, Failo_Vardas, Pazymys);
        auto End = std::chrono::high_resolution_clock::now();
        std::cout << "Failo nuskaitymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
        s += std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    }
    Skolininkai.shrink_to_fit();

    auto Start0 = std::chrono::high_resolution_clock::now();
    Dalinimas_Vector(Skolininkai, islaike);
    auto End0 = std::chrono::high_resolution_clock::now();
    std::cout << "Failo suskirstymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.<< " s."<< std::endl;
    s += std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.;
    std::cout << "Is viso uztruko: " << s << " s.";
    for(int i = 0; i < 3; i++)
        std::cout << std::endl;

    Spauzdinimas_Vector(islaike, Pazymys, "Islaike.txt");
    Spauzdinimas_Vector(Skolininkai, Pazymys, "Skolininkai.txt");
} 

void Pazymiu_generavimas_Vector (duomenys* A, char Pazymys)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char random;
    std::vector<int> ND;
    std::cout << "Pazymiu generavimas: \n";
    do
    {
        ND.push_back(random10(mt));
        std::cout << "Balas: " << ND.back() << "\nDar viena (1/0): ";
        std::cin >> random;
        Pasirinkimas(random, '0', '1');
    } while (random == '1');

    int Egzas = random10(mt);
    std::cout << "Egzamino rezultatas: " << Egzas << std::endl;

    A ->set_Vidurkio_Balas (Galutinis_Vector(ND, Egzas, Pazymys));
}

double Galutinis_Vector (std::vector <int> &A, int Egzas, char tipas)
{
    double nd;
    if (!A.empty()) 
        tipas == '0' ? nd = Mediana_Vector(A, A.size()) : nd = Vidurkis_Vector(A, A.size());
    else nd = 0;
    return 0.4 * nd + 0.6 * Egzas;
}
double Vidurkis_Vector (std::vector <int> &Balai, int n)
{
    double Suma = 0;
    for (int i = 0; i < n; i++)
        Suma += Balai[i];
    return 1.0 * Suma / n;
}
double Mediana_Vector (std::vector <int> &Balai, int n)
{
    double m;
    std::sort(Balai.begin(), Balai.end());
    n % 2 == 0 ? (m = 1.00 * (Balai[n / 2 - 1] + Balai[n / 2]) / 2) : m = Balai[n / 2];
    return m;
}
void Data_Vector (std::vector<duomenys> &A, char Data, char Pazymys)
{
    char random;
    bool IF;
    int nd;
    duomenys Laikinas;
    std::vector <int> ND;
    int Egzas;
    std::string Vardas_0, Pavarde_0;
    do
    {
        IF = true;
        ND.clear();

        std::cout << "Vardas ir Pavarde" << std::endl;
        std::cin >> Vardas_0 >> Pavarde_0;
        Laikinas.set_Vardas(Vardas_0);
        Laikinas.set_Pavarde(Pavarde_0);

        if(Data == '1')  Pazymiu_generavimas_Vector (&Laikinas, Pazymys);
        else
        {
            std::cout << "Veskite pazymius: " << std::endl;
            do
            {
                std::cin >> nd;
                Pazymiai(nd, 0, 10);
                if (nd == 0) IF = false;
                else ND.push_back(nd);
            } while (IF);
            ND.shrink_to_fit();

            std::cout << "Egzo balas: \n";
            std::cin >> Egzas;
            Pazymiai(Egzas, 0, 10);
            Laikinas.set_Vidurkio_Balas (Galutinis_Vector(ND, Egzas, Pazymys));
        }
        A.push_back(Laikinas);

        std::cout << "Prideti studenta: (1/0) ";
        std::cin >> random;
        Pasirinkimas(random, '0', '1');
    } while (random == '1');
}
void Failo_Skaitymas_Vector (std::vector<duomenys> &A, std::string FileName, char Pazymys) 
{
    std::ifstream D (FileName);

    int n = 0;
    std::string header;
    std::getline(D, header);           
    std::istringstream firstRow (header);
    std::string str;
    while (firstRow >> str)             
        n ++;
    n -= 3;                        

    duomenys B;
    int tempMark, Egzaminas;
    std::string row, Vardas_0, Pavarde_0;
    std::istringstream dataRow;
    std::vector<int> ND;
    ND.reserve(n);
    while (std::getline(D, row)) 
    {      
        dataRow.clear();
        dataRow.str(row);
        dataRow >> Vardas_0 >> Pavarde_0;
        B.set_Vardas(Vardas_0);
        B.set_Pavarde(Pavarde_0);
        ND.clear();                      
        for (int i = 0; i < n; i ++)
        {
            dataRow >> tempMark;
            ND.push_back(tempMark);
        }
        dataRow >> Egzaminas;
        B.set_Vidurkio_Balas (Galutinis_Vector(ND, Egzaminas, Pazymys));
        A.push_back(B);               
    } 
    D.close();
}

void Dalinimas_Vector (std::vector<duomenys> &A, std::vector<duomenys> &B)
{
    std::sort(A.begin(), A.end(), [](duomenys &s1, duomenys &s2) {return s1.get_Vidurkio_Balas() < s2.get_Vidurkio_Balas();});
    //auto random = std::partition (A.begin(), A.end(), [](duomenys &i) {return (i.get_Vidurkio_Balas() < 5);});
    int random = 0;
    for (int i = 0; i < A.size(); i++)
        if(A[i].get_Vidurkio_Balas() < 5.0)
            random++;
    B.reserve(A.size() - random);
    std::copy(A.begin() + random, A.end(), std::back_inserter(B));
    A.resize(random);
    A.shrink_to_fit();
}

void Spauzdinimas_Vector (std::vector<duomenys> &A, char Pazymys, std::string Failas)
{
    std::ofstream R(Failas);
    std::ostringstream RR("");

    RR << std::setw(20) << std::left << "Vardas" << std::setw(20) << std::left << "Pavarde";
    RR << "Vidurkis";
    R << RR.str();

    Pazymys == '0' ? R <<"(Med.)\n" : R << "(Vid.)\n";
    R << "--------------------------------------------------------\n";

    for (int i = 0; i < A.size(); i++)
    {
        RR.str("");
        RR << std::setw(20) << std::left << A[i].get_Vardas() << std::setw(20) << A[i].get_Pavarde();
        RR << std::fixed << std::setprecision(2) << A[i].get_Vidurkio_Balas() << std::endl;
        R << RR.str();
    }
    R.close();
}
