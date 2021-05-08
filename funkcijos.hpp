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
        friend std::ostream& operator << (std::ostream& out, duomenys& s)
        {
            out << s.Vardas << " " << s.Pavarde << " " << s.Vidurkio_Balas << "\n";
            return out;
        }
        friend std::istream& operator >> (std::istream& in, duomenys & s)
        {
            in >> s.Vardas >> s.Pavarde >> s.Vidurkio_Balas;
            return in;
        }
        bool operator == (const duomenys & s)
        {
            return (Vardas == s.get_Vardas() && Pavarde == s.get_Pavarde());
        }
        bool operator != (const duomenys & s)
        {
            return !(*this == s);
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
