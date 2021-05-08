#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "funkcijos.hpp"

double Vidurkis (vector <int> Balai, int n)
{
    double Suma = 0;
    for (int i = 0; i < n; i++)
        Suma += Balai[i];
    return 1.0 * Suma / n;
}

double Mediana (vector <int> Balai, int n)
{
    for (int i = 0; i < n; i++)
        sort(Balai.begin(), Balai.end());
    for (int i = 0; i < n; i++)
    {
        if(n % 2 == 0)
            return (Balai[n / 2 - 1] + Balai[n / 2]) / 2.0;
        else 
            return Balai[n / 2];
    }
}

bool Digits (const string & str)   
{
    return all_of (str.begin(), str.end(), ::isdigit);
}

void Spauzdinimas (int n, vector <duomenys> A, int var)
{
    int var_il = 7,  
        pav_il = 9; 

    for (int i = 0; i <= n; i++)
    {
        if (var_il < A[i].Vardas.length()+1)  
            var_il = A[i].Vardas.length()+1;
        if (pav_il < A[i].Pavarde.length()+1)
            pav_il = A[i].Pavarde.length()+1;
    }

    cout << endl;
    printf("%*s", -var_il, "Vardas");
    printf("%*s", -var_il, "Pavarde");

    int ilgis = 20;
    if (var == 1)
        cout << " Vidurkis" << endl;
    else if (var == 0)
        cout << " Mediana" << endl;
    else
    {
        cout << "  Vidurkis        Mediana" << endl;
        ilgis = 25;
    }

    for (int i = 0; i < var_il + pav_il + ilgis; i++)
        printf("-");

    if (var == 1 || var == 0)
        for (int i = 0; i <= n; i++)
        {
            printf("\n%*s", -var_il, A[i].Vardas.c_str());
            printf("%*s", -pav_il, A[i].Pavarde.c_str());
            printf("%4.2f", A[i].Vidurkio_Balas);
        }

    else
    {
        int kiekis = 0;

        while (kiekis != n + 1)
        {
            printf("\n%*s", -var_il, A[kiekis].Vardas.c_str());
            printf("%*s", -pav_il, A[kiekis].Pavarde.c_str());
            printf("%-17.2f", A[kiekis].Vidurkio_Balas);
            printf("%-17.2f", A[kiekis].Mediana);
            kiekis++;
        }
    }
}

void Sortas (vector <duomenys> A, int n)
{
    sort (A.begin(), A.end(), [](const duomenys &i, const duomenys &j)
    {
       if (i.Vardas != j.Vardas) return i.Vardas < j.Vardas;
       else return i.Pavarde < j.Pavarde;
    });

    Spauzdinimas (n, A, 2);
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



void Skaitymas (vector <duomenys> &A)
{
    int Nr = -1;
    std::ifstream D("kursiokai.txt");
    std::string line, b;
    try
    {
        if (!D.good()) cout << "Tokio failo nera: " << endl;
    }
    catch(const char *Message)
    {
        cout << Message << endl;
    }
    while (getline (D, line))
    {
        A.push_back (duomenys());
        istringstream iss(line);
        Nr++;
        iss >> A[Nr].Vardas >> A[Nr].Pavarde;
        int kiek = 0;
        while (iss >> b)
        {
            if (Digits (b))
            {
                int balas = stoi (b);
                if (balas > 0 && balas <= 10)
                {
                    A[Nr].Balai.push_back (int ());
                    A[Nr].Balai[kiek] = balas;
                    kiek++;
                }
            }
        }
        iss.end;
        int Egzaminas = 0;
        if (kiek > 0)
        {
            Egzaminas = A[Nr].Balai[kiek - 1];
            A[Nr].Vidurkio_Balas = 1.0 * (0.4 * Vidurkis (A[Nr].Balai, kiek - 1) + 0.6 * Egzaminas);
            A[Nr].Mediana = Mediana (A[Nr].Balai, kiek - 1);
        }
        else cout << "Klaida " << endl;
    }
    if (Nr > -1)
    {
        Sortas (A, Nr);
    }
    else cout << "Failas tuscias" << endl;
    D.close();
}

void Ivedimas (vector <duomenys> &A)
{
    srand (time (NULL));
    int k, Egzaminas, n;
    label1:
    cout << "Iveskite studentu skaiciu: "; cin >> k;
    Klaida(k);
    if(k <= 0)
        goto label1;
    int random;

    for (int i = 0; i < k; i++)
    {
        A.push_back (duomenys());
        cout << "Iveskite savo varda ir pavarde: ";
        A.push_back (duomenys());
        cin >> A[i].Vardas >> A[i].Pavarde;
        label10:
        cout << "Ar zinome ND skaiciu (1/0): ";
        cin >> random;
        Klaida(random);
        if (random < 0 || random > 1)
            goto label10;
        if (random == 1)
        {
            label11:
            cout << "Iveskite ND kieki: ";
            cin >> n;
            Klaida(n);
            if (n < 0)
            {
                cout << "Iveskite bent vieneta: "; 
                goto label11;
            }
        }
        else 
        {
            cout << "Iveskite ND ivertinimus: ";
            int a, c = 0;
            while(cin >> a && a > 0 && a <= 10)
            {
                A[i].Balai.push_back(a);
                c++;
            }
            n = c;
            goto label4;
        }

        label2:
        cout << "Ar norite ivesti pats balus (1/0): ";
        cin >> random;
        Klaida(random);
        if (random < 0 || random > 1)
            goto label2;
        int b;
        if (random == 1)
        {
            cout << "Iveskite ND ivertinimus: ";
            for (int j = 0; j < n; j++)
            {
                label3:
                cin >> b;
                A[i].Balai.push_back(b);
                while(cin.fail())
                {
                    cout << "Klaida, Iveskite ko praso: ";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> b;
                    A[i].Balai.push_back(b);
                }
                if (A[i].Balai[j] < 1 || A[i].Balai[j] > 10)
                {
                    cout << "Riba nuo 1 iki 10: ";
                    goto label3;
                }
            } 
        } 
        else
        {
            cout << "ND ivertinimai yra: " << endl;
            for (int j = 0; j < n; j++)
            {
                b = 1 + rand() / (double) (RAND_MAX + 1) * 9;
                A[i].Balai.push_back(b);
                cout << A[i].Balai[j] << endl;
            }
        }
        label4:
        cout << "Ar pats norite irasyti egzamino ivertinima (1/0): ";
        cin >> random;
        Klaida(random);
        if(random > 1 or random < 0)
            goto label4;
        if(random == 1)
        {
            cout << "Iveskite egzamino rezultata: ";
            label5:
            cin >> Egzaminas;
            Klaida(Egzaminas);
            if (Egzaminas < 1 || Egzaminas > 10)
            {
                cout << "Riba yra nuo 1 iki 10";
                goto label5;
            }
        }
        else
        {
            cout << "Egzamino rezultatas yra: " << endl;
            Egzaminas = 1 + rand() / (double) (RAND_MAX + 1) * 9;
            cout << Egzaminas << endl;
        }
        A[i].Vidurkio_Balas = 1.0 * (0.4 * Vidurkis (A[i].Balai, n) + 0.6 * Egzaminas);
        A[i].Mediana = Mediana (A[i].Balai, n);
    }
    int r;
    cout << "Norite Vidurkio (1), Medianos (0) ar abieju (2): ";
    cin >> r;
    Spauzdinimas(k, A, r);
}
