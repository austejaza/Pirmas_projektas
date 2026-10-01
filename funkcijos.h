#ifndef FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include <string>
#include <vector>
#include "studentas.h"

int ivestiSkaiciu(const std::string &zinute);
void generuotiFaila(std::string failoPavadinimas, int kiekis, int nd_kiekis = 5);
void isvestiIFaila(const std::string &failoPavadinimas, const std::vector<studentas> &sarasas, int pasirinkimas);
void printas(studentas &A, int pasirinkimas);

#endif



