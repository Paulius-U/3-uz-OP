#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>

using namespace std;

struct duomenys
{
    string Vardas;
    string Pavarde;
    int n;
    int *Balai;
    int Egzaminas;
    double Vidurkis = 0;
    double Mediana = 0;
    double Vidurkio_Balas;
};

void Skaitymas (int k, duomenys A[]);
void Skaiciavimas (int k, duomenys A[]);
void ATS (int k, duomenys A[]);
void Klaida (int &ats);

int main()
{
    int k;
    label0:
    cout << "Kiek  studentu yra: " << endl;
    cin >> k;
    Klaida(k);
    if (k <= 0)
        goto label0;
    duomenys *A = new duomenys[k];
    Skaitymas(k, A);
    Skaiciavimas(k, A);
    ATS(k, A);
    return 0;
}

void Skaitymas (int k, duomenys A[])
{
    srand (time (NULL));
    int random;

    for (int i = 0; i < k; i++)
    {
        cout << "Iveskite studento varda: ";
        cin >> A[i].Vardas;
        cout << "Iveskite studento Pavarde: ";
        cin >> A[i].Pavarde;
        label10:
        cout << "Ar zinome ND skaiciu (1/0): ";
        cin >> random;
        Klaida(random);
        if (random < 0 || random > 1)
            goto label10;
        if (random == 1)
        {
            label:
            cout << "Iveskite ND kieki: ";
            cin >> A[i].n;
            Klaida(A[i].n);
            if (A[i].n < 0)
            {
                cout << "Iveskite bent viena ND: "; 
                goto label;
            }
            A[i].Balai = new (nothrow) int [A[i].n];
        }
        else 
        {
            int a = 0;
            int Masyvas[100];
            cout << "Iveskite ND ivertinimus: ";
            while (cin >> Masyvas[a] && Masyvas[a] > 0 && Masyvas[a] <= 10)
            {
                Klaida(Masyvas[a]);
                a++;
            }
            A[i].Balai = new (nothrow) int[a];
            for( int j = 0; j < a; j++ )
            {
                A[i].Balai[j] = Masyvas[j];
            }
            A[i].n = a;
            goto label4;
        }
        label2:
        cout << "Ar norite ivesti pats balus (1/0): ";
        cin >> random;
        Klaida(random);
        if (random < 0 || random > 1)
            goto label2;
        if (random == 1)
        {
            cout << "Iveskite ND ivertinimus: " << endl;
            for (int j = 0; j < A[i].n; j++)
            {
                label3:
                cin >> A[i].Balai[j];
                Klaida(A[i].Balai[j]);
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
                A[i].Balai[j] = 1 + rand() / (double) (RAND_MAX + 1) * 9;
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
}

void Skaiciavimas (int k, duomenys A[])
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < A[i].n; j++)
            A[i].Vidurkis += A[i].Balai[j];
        A[i].Vidurkis = A[i].Vidurkis / A[i].n;
    }
    for (int i = 0; i < k; i++)
        sort (A[i].Balai, A[i].Balai + A[i].n);
    
    for (int i = 0; i < k; i++)
    {
        if(A[i].n % 2 == 0)
            A[i].Mediana =(A[i].Balai[A[i].n / 2 - 1] + A[i].Balai[A[i].n / 2]) / 2.0;
        else 
            A[i].Mediana = A[i].Balai[A[i].n / 2];
    }

    for (int i = 0; i < k; i++)
        A[i].Vidurkio_Balas = 0.4 * A[i].Vidurkis + 0.6 * A[i].Egzaminas;
}

void ATS (int k, duomenys A[])
{
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
