#include "funkcijos.hpp"
#include "struct.hpp"

double Vidurkis (vector <int> Balai)
{
    return std::accumulate (Balai.begin(), Balai.end(), 0.0)/Balai.size();
}


double Mediana (vector <int> Balai)
{
    vector <int>::size_type VecSize;
    VecSize size = Balai.size();

    sort (Balai.begin(), Balai.end());

    VecSize Middle = size / 2;

    if (size % 2 == 0)
        return (Balai[Middle-1] + Balai[Middle])/2;
    else
        return Balai[Middle];
}
//---------------------------------------
double Balas (double Exam, double Score)
{
    return 0.4 * Score + 0.6 * Exam;
}
double Balas (const duomenys& A, double (*Criteria)(vector <int>))
{
    return Balas (A.Egzaminas, Criteria(A.Balai)); 
}
//----------------------------------------
bool Digits (const string & str)   
{
    return all_of (str.begin(), str.end(), ::isdigit);
}
void Klaida (int &ats)
{
    while(cin.fail())
    {
        cout << "Klaida, Iveskite ko praso: " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> ats;
    }
}
void Listas()
{
    std::list <duomenys> S;
    duomenys A;
    string::size_type LongestName = 0,
                      LongestSurname = 0;
    S.clear();
    int random;
    cout << "Iveskite mokiniu skaiciu: ";
    cin >> random;
    //Failo sukurimas
auto Start = std::chrono::high_resolution_clock::now();
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);
    std::uniform_int_distribution <int> Interval (1, 10), Amount(10, 20);

    int n = Amount(eng);
    std::ofstream R;
    R.open("kursiokai.txt");
    for  (size_t i = 1; i <= random; i++)
    {
        R << "Vardas" << i << " " << "Pavarde" << i << " " << Interval(eng);
        vector <int> Balai;
        vector <int>::iterator IT;
        for (size_t j = 0; j < n; j++)
            Balai.push_back(Interval(eng));
        for (IT = Balai.begin(); IT < Balai.end(); IT++)
            R << " " << *IT;
        R << endl;
    }
    R.close();
auto End = std::chrono::high_resolution_clock::now();
    cout << "Kursiokai.txt sukurimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< endl;
    double s = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    //nuskaitymas failo
    S.clear(); 
    std::ifstream D("kursiokai.txt");
    try
    {
        if (!D.good()) cout << "Tokio failo nera: " << endl;
    }
    catch(const char *Message)
    {
        cout << Message << endl;
    }    
auto Start2 = std::chrono::high_resolution_clock::now();
    std::string line, Name, Surname, Exam, b;
    while (getline (D, line))
    {
        std::stringstream iss(line);
        iss >> Name >> Surname >> Exam;

        A.Vardas = Name;
        LongestName = std::max(LongestName, A.Vardas.length());
        A.Pavarde = Surname;
        LongestSurname = std::max(LongestSurname, A.Pavarde.length());
        A.Egzaminas = stoi(Exam);
        A.Balai.clear();
        while (iss >> b)
        {
            if (Digits (b))
            {
                int balas = stoi (b);
                if (balas > 0 && balas <= 10)
                {
                    A.Balai.push_back (b);
                }
            }
        }
        S.push_back(A);
        iss.clear();
        iss.end;
    }
auto End2 = std::chrono::high_resolution_clock::now();
    cout << "Duomenu nuskaitymas is failo uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() / 1000. << " s."<< endl;
    s = s + std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() / 1000.;

auto Start3 = std::chrono::high_resolution_clock::now();
    std::list <duomenys> Failed;
    std::list <duomenys>::iterator IT = S.begin();
    while (IT != S.end())
    {
        if (Balas((*IT), Vidurkis)< 5.0, Balai((*IT), Mediana) < 5.0)
        {
            Failed.push_back(*IT);
            IT = S.erase(IT);
        }
        else IT++;
    }

    //skolininkai
    std::ofstream R;
    R.open("skola.txt");
    for(std::list <duomenys>::iterator IT = Failed.begin(); IT != Failed.end(); IT++)
    {
        R << (*IT).Vardas << string(LongestName + 1 - (*IT).Vardas.size(), ' ');
        R << (*IT).Pavarde << string(LongestSurname + 1 - (*IT).Pavarde.size());

        std::streamsize prec = cout.precision();
        R << std::fixed << setprecision(2) << Balas((*IT), Vidurkis) << Balas((*IT), Mediana);
        R << setprecision(prec) << endl;
    }
    for (auto i = 0; i != LongestName + LongestSurname + 10; i++)
        R << "-";
    R << endl;
    R.close();

    //iskaile
    std::ofstream R2;
    R2.open("skola.txt");
    for(std::list <duomenys>::iterator IT = Failed.begin(); IT != Failed.end(); IT++)
    {
        R2 << (*IT).Vardas << string(LongestName + 1 - (*IT).Vardas.size(), ' ');
        R2 << (*IT).Pavarde << string(LongestSurname + 1 - (*IT).Pavarde.size());

        std::streamsize prec = cout.precision();
        R2 << std::fixed << setprecision(2) << Balas((*IT), Vidurkis) << Balas((*IT), Mediana);
        R2 << setprecision(prec) << endl;
    }
    for (auto i = 0; i != LongestName + LongestSurname + 10; i++)
        R2 << "-";
    R2 << endl;
    R2.close();


auto End3 = std::chrono::high_resolution_clock::now();
    cout << "Duomenu isskaidymas i du failus: " << std::chrono::duration_cast<std::chrono::milliseconds>(End3 - Start3).count() / 1000. << " s."<< endl;
    s = s + std::chrono::duration_cast<std::chrono::milliseconds>(End3 - Start3).count() / 1000.;
    cout << "Is viso laiko uztruko: " << s << " s";
}

void Vectorius()
{
    std::vector <duomenys> S;
    duomenys A;
    string::size_type LongestName = 0,
                      LongestSurname = 0;
    S.clear();
    int random;
    cout << "Iveskite mokiniu skaiciu: ";
    cin >> random;
    //Failo sukurimas
auto Start = std::chrono::high_resolution_clock::now();
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);
    std::uniform_int_distribution <int> Interval (1, 10), Amount(10, 20);

    int n = Amount(eng);
    std::ofstream R;
    R.open("kursiokai.txt");
    for  (size_t i = 1; i <= random; i++)
    {
        R << "Vardas" << i << " " << "Pavarde" << i << " " << Interval(eng);
        vector <int> Balai;
        vector <int>::iterator IT;
        for (size_t j = 0; j < n; j++)
            Balai.push_back(Interval(eng));
        for (IT = Balai.begin(); IT < Balai.end(); IT++)
            R << " " << *IT;
        R << endl;
    }
    R.close();
auto End = std::chrono::high_resolution_clock::now();
    cout << "Kursiokai.txt sukurimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< endl;
    double s = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    //nuskaitymas failo
    S.clear(); 
    std::ifstream D("kursiokai.txt");
    try
    {
        if (!D.good()) cout << "Tokio failo nera: " << endl;
    }
    catch(const char *Message)
    {
        cout << Message << endl;
    }    
auto Start2 = std::chrono::high_resolution_clock::now();
    std::string line, Name, Surname, Exam, b;
    while (getline (D, line))
    {
        std::stringstream iss(line);
        iss >> Name >> Surname >> Exam;

        A.Vardas = Name;
        LongestName = std::max(LongestName, A.Vardas.length());
        A.Pavarde = Surname;
        LongestSurname = std::max(LongestSurname, A.Pavarde.length());
        A.Egzaminas = stoi(Exam);
        A.Balai.clear();
        while (iss >> b)
        {
            if (Digits (b))
            {
                int balas = stoi (b);
                if (balas > 0 && balas <= 10)
                {
                    A.Balai.push_back (b);
                }
            }
        }
        S.push_back(A);
        iss.clear();
        iss.end;
    }
auto End2 = std::chrono::high_resolution_clock::now();
    cout << "Duomenu nuskaitymas is failo uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() / 1000. << " s."<< endl;
    s = s + std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() / 1000.;

auto Start3 = std::chrono::high_resolution_clock::now();
    std::vector <duomenys> Failed;
    std::vector <duomenys>::iterator IT = S.begin();
    while (IT != S.end())
    {
        if (Balas((*IT), Vidurkis)< 5.0, Balai((*IT), Mediana) < 5.0)
        {
            Failed.push_back(*IT);
            IT = S.erase(IT);
        }
        else IT++;
    }

    //skolininkai
    std::ofstream R;
    R.open("skola.txt");
    for(std::vector <duomenys>::iterator IT = Failed.begin(); IT != Failed.end(); IT++)
    {
        R << (*IT).Vardas << string(LongestName + 1 - (*IT).Vardas.size(), ' ');
        R << (*IT).Pavarde << string(LongestSurname + 1 - (*IT).Pavarde.size());

        std::streamsize prec = cout.precision();
        R << std::fixed << setprecision(2) << Balas((*IT), Vidurkis) << Balas((*IT), Mediana);
        R << setprecision(prec) << endl;
    }
    for (auto i = 0; i != LongestName + LongestSurname + 10; i++)
        R << "-";
    R << endl;
    R.close();

    //iskaile
    std::ofstream R2;
    R2.open("skola.txt");
    for(std::vector <duomenys>::iterator IT = Failed.begin(); IT != Failed.end(); IT++)
    {
        R2 << (*IT).Vardas << string(LongestName + 1 - (*IT).Vardas.size(), ' ');
        R2 << (*IT).Pavarde << string(LongestSurname + 1 - (*IT).Pavarde.size());

        std::streamsize prec = cout.precision();
        R2 << std::fixed << setprecision(2) << Balas((*IT), Vidurkis) << Balas((*IT), Mediana);
        R2 << setprecision(prec) << endl;
    }
    for (auto i = 0; i != LongestName + LongestSurname + 10; i++)
        R2 << "-";
    R2 << endl;
    R2.close();


auto End3 = std::chrono::high_resolution_clock::now();
    cout << "Duomenu isskaidymas i du failus: " << std::chrono::duration_cast<std::chrono::milliseconds>(End3 - Start3).count() / 1000. << " s."<< endl;
    s = s + std::chrono::duration_cast<std::chrono::milliseconds>(End3 - Start3).count() / 1000.;
    cout << "Is viso laiko uztruko: " << s << " s";
}

Dequelas()
{
    std::deque <duomenys> S;
    duomenys A;
    string::size_type LongestName = 0,
                      LongestSurname = 0;
    S.clear();
    int random;
    cout << "Iveskite mokiniu skaiciu: ";
    cin >> random;
    //Failo sukurimas
auto Start = std::chrono::high_resolution_clock::now();
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);
    std::uniform_int_distribution <int> Interval (1, 10), Amount(10, 20);

    int n = Amount(eng);
    std::ofstream R;
    R.open("kursiokai.txt");
    for  (size_t i = 1; i <= random; i++)
    {
        R << "Vardas" << i << " " << "Pavarde" << i << " " << Interval(eng);
        vector <int> Balai;
        vector <int>::iterator IT;
        for (size_t j = 0; j < n; j++)
            Balai.push_back(Interval(eng));
        for (IT = Balai.begin(); IT < Balai.end(); IT++)
            R << " " << *IT;
        R << endl;
    }
    R.close();
auto End = std::chrono::high_resolution_clock::now();
    cout << "Kursiokai.txt sukurimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< endl;
    double s = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.;
    //nuskaitymas failo
    S.clear(); 
    std::ifstream D("kursiokai.txt");
    try
    {
        if (!D.good()) cout << "Tokio failo nera: " << endl;
    }
    catch(const char *Message)
    {
        cout << Message << endl;
    }    
auto Start2 = std::chrono::high_resolution_clock::now();
    std::string line, Name, Surname, Exam, b;
    while (getline (D, line))
    {
        std::stringstream iss(line);
        iss >> Name >> Surname >> Exam;

        A.Vardas = Name;
        LongestName = std::max(LongestName, A.Vardas.length());
        A.Pavarde = Surname;
        LongestSurname = std::max(LongestSurname, A.Pavarde.length());
        A.Egzaminas = stoi(Exam);
        A.Balai.clear();
        while (iss >> b)
        {
            if (Digits (b))
            {
                int balas = stoi (b);
                if (balas > 0 && balas <= 10)
                {
                    A.Balai.push_back (b);
                }
            }
        }
        S.push_back(A);
        iss.clear();
        iss.end;
    }
auto End2 = std::chrono::high_resolution_clock::now();
    cout << "Duomenu nuskaitymas is failo uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() / 1000. << " s."<< endl;
    s = s + std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() / 1000.;

auto Start3 = std::chrono::high_resolution_clock::now();
    std::deque <duomenys> Failed;
    std::deque <duomenys>::iterator IT = S.begin();
    while (IT != S.end())
    {
        if (Balas((*IT), Vidurkis)< 5.0, Balai((*IT), Mediana) < 5.0)
        {
            Failed.push_back(*IT);
            IT = S.erase(IT);
        }
        else IT++;
    }

    //skolininkai
    std::ofstream R;
    R.open("skola.txt");
    for(std::deque <duomenys>::iterator IT = Failed.begin(); IT != Failed.end(); IT++)
    {
        R << (*IT).Vardas << string(LongestName + 1 - (*IT).Vardas.size(), ' ');
        R << (*IT).Pavarde << string(LongestSurname + 1 - (*IT).Pavarde.size());

        std::streamsize prec = cout.precision();
        R << std::fixed << setprecision(2) << Balas((*IT), Vidurkis) << Balas((*IT), Mediana);
        R << setprecision(prec) << endl;
    }
    for (auto i = 0; i != LongestName + LongestSurname + 10; i++)
        R << "-";
    R << endl;
    R.close();

    //iskaile
    std::ofstream R2;
    R2.open("skola.txt");
    for(std::deque <duomenys>::iterator IT = Failed.begin(); IT != Failed.end(); IT++)
    {
        R2 << (*IT).Vardas << string(LongestName + 1 - (*IT).Vardas.size(), ' ');
        R2 << (*IT).Pavarde << string(LongestSurname + 1 - (*IT).Pavarde.size());

        std::streamsize prec = cout.precision();
        R2 << std::fixed << setprecision(2) << Balas((*IT), Vidurkis) << Balas((*IT), Mediana);
        R2 << setprecision(prec) << endl;
    }
    for (auto i = 0; i != LongestName + LongestSurname + 10; i++)
        R2 << "-";
    R2 << endl;
    R2.close();


auto End3 = std::chrono::high_resolution_clock::now();
    cout << "Duomenu isskaidymas i du failus: " << std::chrono::duration_cast<std::chrono::milliseconds>(End3 - Start3).count() / 1000. << " s."<< endl;
    s = s + std::chrono::duration_cast<std::chrono::milliseconds>(End3 - Start3).count() / 1000.;
    cout << "Is viso laiko uztruko: " << s << " s";
}
