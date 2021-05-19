#pragma once

class asmuo
{
    protected:
        std::string Vardas;
        std::string Pavarde;

    public:
        asmuo(std::string, std::string);
        asmuo() {};
        ~asmuo() {};
        virtual void set_Vardas(std::string) = 0;
        virtual void set_Pavarde(std::string) = 0;
        std::string get_Vardas() const;
        std::string get_Pavarde() const;
};

class duomenys: public asmuo
{
    public:
        duomenys() : Vidurkio_Balas(0) {};
        ~duomenys() {};        
        void set_Vardas(std::string);
        void set_Pavarde(std::string);
        void set_Vidurkio_Balas(double);
        std::string get_Vardas() const { return Vardas; }
        std::string get_Pavarde() const { return Pavarde; }
        double get_Vidurkio_Balas() const { return Vidurkio_Balas; }
        duomenys (const duomenys&);
        duomenys& operator = (const duomenys& v) 
        {
            Vardas = v.get_Vardas();
            Pavarde = v.get_Pavarde();
            Vidurkio_Balas = v.get_Vidurkio_Balas();
            return *this;
        }
    private:
        double Vidurkio_Balas;
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
