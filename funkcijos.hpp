#pragma once

template <typename T>
void Klaida(T&);
void Pasirinkimas (char&, char, char);
void Pasirinkimas (char&, char, char, char);
void Pazymiai (int&, int, int);

void Vectorius (char, char);
void Pazymiu_generavimas_Vector (duomenys*, char);
double Galutinis_Vector (std::vector <int>&, int, char);
double Vidurkis_Vector (std::vector <int>&, int);
double Mediana_Vector (std::vector <int>&, int);
void Data_Vector (std::vector<duomenys>&, char, char);
void Failo_Skaitymas_Vector (std::vector<duomenys> &, std::string, char);
void Dalinimas_Vector (std::vector<duomenys> &, std::vector<duomenys> &, std::vector<duomenys> &);
void Spauzdinimas_Vector (std::vector<duomenys> &, char, std::string);
void Listas (char, char);
void Pazymiu_generavimas_List (duomenys*, char );
double Galutinis_List (std::list <int> &, int, char);
double Vidurkis_List (std::list <int> &, int);
double Mediana_List (std::list <int> &, int );
void Data_List (std::list<duomenys> &, char , char);
void Failo_Skaitymas_List (std::list<duomenys> &, std::string, char);
void Dalinimas_List (std::list<duomenys> &, std::list<duomenys> &, std::list<duomenys> &);
void Spauzdinimas_List (std::list<duomenys> &, char, std::string);
void Dequelas (char, char);
void Pazymiu_generavimas_Deque (duomenys*, char);
double Galutinis_Deque (std::deque <int> &, int, char );
double Vidurkis_Deque (std::deque <int> &, int);
double Mediana_Deque (std::deque <int> &, int);
void Data_Deque (std::deque<duomenys> &, char, char);
void Failo_Skaitymas_Deque (std::deque<duomenys> &, std::string, char);
void Dalinimas_Deque (std::deque<duomenys> &, std::deque<duomenys> &, std::deque<duomenys> &);
void Spauzdinimas_Deque (std::deque<duomenys> &, char, std::string);
