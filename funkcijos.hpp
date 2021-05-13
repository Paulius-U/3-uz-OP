#pragma once

class duomenys
{
    private:
        std::string Vardas;
        std::string Pavarde;
        double Vidurkio_Balas;
    public:
        duomenys() : Vidurkio_Balas(0) { };
        void set_Vardas(std::string);
        void set_Pavarde(std::string);
        void set_Vidurkio_Balas(double);
        inline std::string get_Vardas() const { return Vardas; }
        inline std::string get_Pavarde() const { return Pavarde; }
        inline double get_Vidurkio_Balas() const { return Vidurkio_Balas; }
        ~duomenys() {};
        duomenys (const duomenys& v)
        {
            v.get_Vardas() == Vardas; 
            v.get_Pavarde() == Pavarde;
            v.get_Vidurkio_Balas() == Vidurkio_Balas;
        }
        duomenys& operator = (const duomenys& v)
        {
            if(&v ==this) return* this;

            Vardas = get_Vardas();
            Pavarde = get_Pavarde();
            Vidurkio_Balas = get_Vidurkio_Balas();
        }
};
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
void Dalinimas_Vector (std::vector<duomenys> &, std::vector<duomenys> &);
void Spauzdinimas_Vector (std::vector<duomenys> &, char, std::string);
