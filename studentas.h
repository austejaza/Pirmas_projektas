#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include <string>
#include <vector>

struct studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int exam;
    float galutinis_vid;
    float galutinis_med;
};

float Mediana(std::vector<int> paz);

#endif
