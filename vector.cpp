#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::vector;
using std::fixed;
using std::right;
using std::setprecision;

struct duomenys
{
    string Vardas;
    string Pavarde;
    int n;
    vector <int> Balai;
    int Egzaminas;
    double Vidurkis = 0;
    double Mediana = 0;
    double Vidurkio_Balas;
};

void Klaida (int &ats);

int main()
{
    srand ( time ( NULL ) );
    int k;
    label1:
    cout << "Iveskite studentu skaiciu: "; cin >> k;
    Klaida(k);
    if(k <= 0)
        goto label1;
    
    vector <duomenys> A;

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
            cin >> A[i].n;
            Klaida(A[i].n);
            if (A[i].n < 0)
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
            A[i].n = c;
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
            for (int j = 0; j < A[i].n; j++)
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
            for (int j = 0; j < A[i].n; j++)
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
            cin >> A[i].Egzaminas;
            Klaida(A[i].Egzaminas);
            if (A[i].Egzaminas < 1 || A[i].Egzaminas > 10)
            {
                cout << "Riba yra nuo 1 iki 10";
                goto label5;
            }
        }
        else
        {
         cout << "Egzamino rezultatas yra: " << endl;
        A[i].Egzaminas = 1 + rand() / (double) (RAND_MAX + 1) * 9;
        cout << A[i].Egzaminas << endl;
        }
    }
    // Skaiciavimai
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < A[i].n; j++)
            A[i].Vidurkis += A[i].Balai[j];
        A[i].Vidurkis = A[i].Vidurkis / A[i].n;
    }
    for (int i = 0; i < k; i++)
        sort(A[i].Balai.begin(), A[i].Balai.end());
    
    for (int i = 0; i < k; i++)
    {
        if(A[i].n % 2 == 0)
            A[i].Mediana =(A[i].Balai[A[i].n / 2 - 1] + A[i].Balai[A[i].n / 2]) / 2.0;
        else 
            A[i].Mediana = A[i].Balai[A[i].n / 2];
    }

    for (int i = 0; i < k; i++)
        A[i].Vidurkio_Balas = 0.4 * A[i].Vidurkis + 0.6 * A[i].Egzaminas;

        int random0;
    cout << "Ar norite Vidurkio (1) ar Medianos (0): ";
    cin >> random0;
    if (random0 == 1)
    {
        cout << "Pavarde" << right << setw(20) << "Vardas" << right << setw(35) 
            << "Galutinis Vidurkis" << endl;
        cout << "----------------------------------------------------------"
             << "--------------" << endl;
        for(int i = 0; i < k; i++)
            cout << A[i].Pavarde << right << setw(20) << A[i].Vardas << right << setw(20)
                << fixed << setprecision(2) << right << A[i].Vidurkio_Balas << endl;
    }
    else 
    {
        cout << "Pavarde" << right << setw(20) << "Vardas" << right << setw(30) 
            << "Mediana" << endl;
        cout << "------------------------------------------------------------"
             << "------------" << endl;
        for(int i = 0; i < k; i++)
        {
            cout << A[i].Pavarde << right << setw(20) << A[i].Vardas 
                << setw(20) << right << A[i].Mediana << endl;
        }
    }   
    cout << "----------------------------------------------------------------"
        << "-------" << endl;

    return 0; 
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
