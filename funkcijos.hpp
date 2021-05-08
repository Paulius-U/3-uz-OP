#pragma once

#include "struct.hpp"
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::vector;
using std::fixed;
using std::right;
using std::setprecision;
using std::istringstream;
using std::getline;

double Vidurkis (vector <int> Balai, int n);
double Mediana (vector <int> Balai, int n);
bool Digits (const string & str);
void Sukurimas(vector <duomenys> &A);
void Spauzdinimas (int n, vector <duomenys> A, int var, double s);
void Sortas (vector <duomenys> A, int n, double s);
void Klaida (int &ats);
void Skaitymas (vector <duomenys> &A, double s);
void Ivedimas (vector <duomenys> &A);
