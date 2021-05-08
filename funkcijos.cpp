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

#include "funkcijos.h"
#include "failas.h"

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

void Vectorius (char Data, char Pazymys)
{
    std::vector <duomenys> Skolininkai, islaike, Bendras;
    double s = 0;

    if(Data == '1' || Data =='2')
        Data_Vector(Skolininkai, Data, Pazymys);
    else
    {
        std::string Failo_Vardas = GetFile();
        for(int i = 0; i < 3; i++)
            std::cout << std::endl;
        auto Start = std::chrono::high_resolution_clock::now();
        Failo_Skaitymas_Vector(Bendras, Failo_Vardas, Pazymys);
        auto End = std::chrono::high_resolution_clock::now();
        std::cout << "Failo nuskaitymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
        s += std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    }
    Bendras.shrink_to_fit();

    auto Start0 = std::chrono::high_resolution_clock::now();
    Dalinimas_Vector(Skolininkai, islaike, Bendras);
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

    A ->Vidurkio_Balas = Galutinis_Vector(ND, Egzas, Pazymys);
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
    do
    {
        IF = true;
        ND.clear();

        std::cout << "Vardas ir Pavarde" << std::endl;
        std::cin >> Laikinas.Vardas >> Laikinas.Pavarde;

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
            Laikinas.Vidurkio_Balas = Galutinis_Vector(ND, Egzas, Pazymys);
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
    std::string row;
    std::istringstream dataRow;
    std::vector<int> ND;
    ND.reserve(n);
    while (std::getline(D, row)) 
    {      
        dataRow.clear();
        dataRow.str(row);
        dataRow >> B.Vardas >> B.Pavarde;
        ND.clear();                      
        for (int i = 0; i < n; i ++)
        {
            dataRow >> tempMark;
            ND.push_back(tempMark);
        }
        dataRow >> Egzaminas;
        B.Vidurkio_Balas = Galutinis_Vector(ND, Egzaminas, Pazymys);
        A.push_back(B);               
    } 
    D.close();
}

void Dalinimas_Vector (std::vector<duomenys> &A, std::vector<duomenys> &B, std::vector<duomenys> &C)
{
    std::sort(C.begin(), C.end(), [](duomenys &s1, duomenys &s2) {return s1.Vidurkio_Balas < s2.Vidurkio_Balas;});

    int n;
    while (C[n].Vidurkio_Balas < 5.0 && n != C.size()) 
        n++;
    B.reserve(C.size() - n);
    A = C;
    std::copy(A.begin() + n, A.end(), std::back_inserter(B));
    A.resize(n);
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
        RR << std::setw(20) << std::left << A[i].Vardas << std::setw(20) << A[i].Pavarde;
        RR << std::fixed << std::setprecision(2) << A[i].Vidurkio_Balas << std::endl;
        R << RR.str();
    }
    R.close();
}

void Listas (char Data, char Pazymys)
{
    std::list <duomenys> Skolininkai, islaike, Bendras;
    double s = 0;

    if(Data == '1' || Data =='2')
        Data_List(Skolininkai, Data, Pazymys);
    else
    {
        std::string Failo_Vardas = GetFile();
        for(int i = 0; i < 3; i++)
            std::cout << std::endl;
        auto Start = std::chrono::high_resolution_clock::now();
        Failo_Skaitymas_List(Bendras, Failo_Vardas, Pazymys);
        auto End = std::chrono::high_resolution_clock::now();
        std::cout << "Failo nuskaitymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
        s += std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    }

    auto Start0 = std::chrono::high_resolution_clock::now();
    Dalinimas_List(Skolininkai, islaike, Bendras);
    auto End0 = std::chrono::high_resolution_clock::now();
    std::cout << "Failo suskirstymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.<< " s."<< std::endl;
    s += std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.;
    std::cout << "Is viso uztruko: " << s << " s.";
    for(int i = 0; i < 3; i++)
        std::cout << std::endl;

    Spauzdinimas_List(islaike, Pazymys, "Islaike.txt");
    Spauzdinimas_List(Skolininkai, Pazymys, "Skolininkai.txt");
} 

void Pazymiu_generavimas_List (duomenys* A, char Pazymys)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char random;
    std::list<int> ND;
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

    A ->Vidurkio_Balas = Galutinis_List(ND, Egzas, Pazymys);
}

double Galutinis_List (std::list <int> &A, int Egzas, char tipas)
{
    double nd;
    if (!A.empty()) 
        tipas == '0' ? nd = Mediana_List(A, A.size()) : nd = Vidurkis_List(A, A.size());
    else nd = 0;
    return 0.4 * nd + 0.6 * Egzas;
}
double Vidurkis_List (std::list <int> &Balai, int n)
{
    double Suma = 0;
    auto i = Balai.begin();
    for (auto i = Balai.begin(); i != Balai.end(); i++)
        Suma += *(i);
    return 1.0 * Suma / n;
}
double Mediana_List (std::list <int> &Balai, int n)
{
    double m;
    auto it1 = Balai.begin();         
    auto it2 = it1;
    std::advance(it1, n / 2 - 1);   
    std::advance(it2, n / 2);       

    n % 2 == 0 ? (m = 1.00 * (*it1 + *it2) / 2) : m = *it2;
    return m;
}
void Data_List (std::list<duomenys> &A, char Data, char Pazymys)
{
    char random;
    bool IF;
    int nd;
    duomenys Laikinas;
    std::list <int> ND;
    int Egzas;
    do
    {
        IF = true;
        ND.clear();

        std::cout << "Vardas ir Pavarde\n";
        std::cin >> Laikinas.Vardas >> Laikinas.Pavarde;

        if(Data == '1')  Pazymiu_generavimas_List (&Laikinas, Pazymys);
        else
        {
            std::cout << "Veskite pazymius: " << std::endl;
            do
            {
                std::cin >>nd;
                Pazymiai(nd, 0, 10);
                if (nd == 0) IF = false;
                else ND.push_back(nd);
            } while (IF);

            std::cout << "Egzo balas: \n";
            std::cin >> Egzas;
            Pazymiai(Egzas, 0, 10);
            Laikinas.Vidurkio_Balas = Galutinis_List(ND, Egzas, Pazymys);
        }
        A.push_back(Laikinas);

        std::cout << "Prideti studenta: (1/0) ";
        std::cin >> random;
        Pasirinkimas(random, '0', '1');
    } while (random == '1');
}
void Failo_Skaitymas_List (std::list<duomenys> &A, std::string FileName, char Pazymys) 
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
    std::string row;
    std::istringstream dataRow;
    std::list<int> ND;
    while (std::getline(D, row)) 
    {      
        dataRow.clear();
        dataRow.str(row);
        dataRow >> B.Vardas >> B.Pavarde;
        ND.clear();                      
        for (int i = 0; i < n; i ++)
        {
            dataRow >> tempMark;
            ND.push_back(tempMark);
        }
        dataRow >> Egzaminas;
        B.Vidurkio_Balas = Galutinis_List(ND, Egzaminas, Pazymys);
        A.push_back(B);               
    } 
    D.close();
}

void Dalinimas_List (std::list<duomenys> &A, std::list<duomenys> &B, std::list<duomenys> &C)
{
    C.sort([](duomenys &s1, duomenys &s2) {return s1.Vidurkio_Balas < s2.Vidurkio_Balas;});

    int n = 0;
    auto it = C.begin();
    while (it->Vidurkio_Balas < 5.0 && it != C.end()) 
    {
        n++;
        it++;
    }
    A = C;
    B.assign(it, C.end());
    A.resize(n);
}

void Spauzdinimas_List (std::list<duomenys> &A, char Pazymys, std::string Failas)
{
    std::ofstream R(Failas);
    std::ostringstream RR("");

    RR << std::setw(20) << std::left << "Vardas" << std::setw(20) << std::left << "Pavarde";
    RR << "Vidurkis";
    R << RR.str();

    Pazymys == '0' ? R <<"(Med.)\n" : R << "(Vid.)\n";
    R << "--------------------------------------------------------\n";

    auto i = A.begin();
    for (auto i = A.begin(); i != A.end(); i++)
    {
        RR.str("");
        RR << std::setw(20) << std::left << i->Vardas << std::setw(20) << i->Pavarde;
        RR << std::fixed << std::setprecision(2) << i->Vidurkio_Balas << std::endl;
        R << RR.str();
    }
    R.close();
}

void Dequelas (char Data, char Pazymys)
{
    std::deque <duomenys> Skolininkai, islaike, Bendras;
    double s = 0;

    if(Data == '1' || Data =='2')
        Data_Deque(Skolininkai, Data, Pazymys);
    else
    {
        std::string Failo_Vardas = GetFile();
        for(int i = 0; i < 3; i++)
            std::cout << std::endl;  
        auto Start = std::chrono::high_resolution_clock::now();
        Failo_Skaitymas_Deque(Bendras, Failo_Vardas, Pazymys);
        auto End = std::chrono::high_resolution_clock::now();
        std::cout << "Failo nuskaitymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
        s += std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    }

    auto Start0 = std::chrono::high_resolution_clock::now();
    Dalinimas_Deque(Skolininkai, islaike, Bendras);
    auto End0 = std::chrono::high_resolution_clock::now();
    std::cout << "Failo suskirstymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.<< " s."<< std::endl;
    s += std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.;
    std::cout << "Is viso uztruko: " << s << " s.";
    for(int i = 0; i < 3; i++)
        std::cout << std::endl;

    Spauzdinimas_Deque(islaike, Pazymys, "Islaike.txt");
    Spauzdinimas_Deque(Skolininkai, Pazymys, "Skolininkai.txt");
} 

void Pazymiu_generavimas_Deque (duomenys* A, char Pazymys)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char random;
    std::deque<int> ND;
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

    A ->Vidurkio_Balas = Galutinis_Deque(ND, Egzas, Pazymys);
}

double Galutinis_Deque (std::deque <int> &A, int Egzas, char tipas)
{
    double nd;
    if (!A.empty()) 
        tipas == '0' ? nd = Mediana_Deque(A, A.size()) : nd = Vidurkis_Deque(A, A.size());
    else nd = 0;
    return 0.4 * nd + 0.6 * Egzas;
}
double Vidurkis_Deque (std::deque <int> &Balai, int n)
{
    double Suma = 0;
    for (int i = 0; i < n; i++)
        Suma += Balai[i];
    return 1.0 * Suma / n;
}
double Mediana_Deque (std::deque <int> &Balai, int n)
{
    double m;
    std::sort(Balai.begin(), Balai.end());
    n % 2 == 0 ? (m = 1.00 * (Balai[n / 2 - 1] + Balai[n / 2]) / 2) : m = Balai[n / 2];
    return m;
}
void Data_Deque (std::deque<duomenys> &A, char Data, char Pazymys)
{
    char random;
    bool IF;
    int nd;
    duomenys Laikinas;
    std::deque <int> ND;
    int Egzas;
    do
    {
        IF = true;
        ND.clear();

        std::cout << "Vardas ir Pavarde\n";
        std::cin >> Laikinas.Vardas >> Laikinas.Pavarde;

        if(Data == '1')  Pazymiu_generavimas_Deque (&Laikinas, Pazymys);
        else
        {
            std::cout << "Veskite pazymius: " << std::endl;
            do
            {
                std::cin >>nd;
                Pazymiai(nd, 0, 10);
                if (nd == 0) IF = false;
                else ND.push_back(nd);
            } while (IF);
            ND.shrink_to_fit();

            std::cout << "Egzo balas: \n";
            std::cin >> Egzas;
            Pazymiai(Egzas, 0, 10);
            Laikinas.Vidurkio_Balas = Galutinis_Deque(ND, Egzas, Pazymys);
        }
        A.push_back(Laikinas);

        std::cout << "Prideti studenta: (1/0) ";
        std::cin >> random;
        Pasirinkimas(random, '0', '1');
    } while (random == '1');
}
void Failo_Skaitymas_Deque (std::deque<duomenys> &A, std::string FileName, char Pazymys) 
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
    std::string row;
    std::istringstream dataRow;
    std::deque<int> ND;
    while (std::getline(D, row)) 
    {      
        dataRow.clear();
        dataRow.str(row);
        dataRow >> B.Vardas >> B.Pavarde;
        ND.clear();                      
        for (int i = 0; i < n; i ++)
        {
            dataRow >> tempMark;
            ND.push_back(tempMark);
        }
        dataRow >> Egzaminas;
        B.Vidurkio_Balas = Galutinis_Deque(ND, Egzaminas, Pazymys);
        A.push_back(B);               
    } 
    D.close();
}

void Dalinimas_Deque (std::deque<duomenys> &A, std::deque<duomenys> &B, std::deque<duomenys> &C)
{
    std::sort(C.begin(), C.end(), [](duomenys &s1, duomenys &s2) {return s1.Vidurkio_Balas < s2.Vidurkio_Balas;});

    int n;
    while (C[n].Vidurkio_Balas < 5.0 && n != C.size()) 
        n++;
    A = C;
    std::copy(A.begin() + n, A.end(), std::back_inserter(B));
    A.resize(n);
}

void Spauzdinimas_Deque (std::deque<duomenys> &A, char Pazymys, std::string Failas)
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
        RR << std::setw(20) << std::left << A[i].Vardas << std::setw(20) << A[i].Pavarde;
        RR << std::fixed << std::setprecision(2) << A[i].Vidurkio_Balas << std::endl;
        R << RR.str();
    }
    R.close();
}
