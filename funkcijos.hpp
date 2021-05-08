#define pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <random>
#include <numeric>
#include <stdexcept>
#include <list>
#include <deque>

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

double Vidurkis (vector <int> Balai);
double Mediana (vector <int> Balai);
double Balas (double Exam, double Score);
double Balas (const duomenys& A, double (*Criteria)(vector <int>));
bool Digits (const string & str);
void Klaida (int &ats);
void Listas();
void Vectorius();
void Dequelas();
