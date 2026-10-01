#include "funkcijos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>

int ivestiSkaiciu(const std::string& pranesimas) {
    int skaicius;
    while (true) {
        std::cout << pranesimas;
        if (std::cin >> skaicius) {
            return skaicius;
        } else {
            std::cout << "Neteisinga ivestis! Iveskite skaiciu.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void printas(const studentas& s, int pasirinkimas) {
    std::cout << std::left << std::setw(15) << s.vardas
              << std::left << std::setw(15) << s.pavarde;
    if (pasirinkimas == 1) {
        std::cout << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_vid << "\n";
    } else if (pasirinkimas == 2) {
        std::cout << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_med << "\n";
    } else {
        std::cout << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_vid
                  << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_med << "\n";
    }
}

void isvestiIFaila(const std::string& failo_pavadinimas, const std::vector<studentas>& sarasas, int pasirinkimas) {
    std::ofstream fr(failo_pavadinimas);
    if (!fr.is_open()) return;

    fr << std::left << std::setw(15) << "Vardas"
       << std::left << std::setw(15) << "Pavarde";
    if (pasirinkimas == 1) {
        fr << std::right << std::setw(18) << "Galutinis (Vid.)" << "\n";
        fr << std::string(48, '-') << "\n";
    } else if (pasirinkimas == 2) {
        fr << std::right << std::setw(18) << "Galutinis (Med.)" << "\n";
        fr << std::string(48, '-') << "\n";
    } else {
        fr << std::right << std::setw(18) << "Galutinis (Vid.)"
           << std::right << std::setw(18) << "Galutinis (Med.)" << "\n";
        fr << std::string(66, '-') << "\n";
    }

    for (const auto& s : sarasas) {
        fr << std::left << std::setw(15) << s.vardas
           << std::left << std::setw(15) << s.pavarde;
        if (pasirinkimas == 1) {
            fr << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_vid << "\n";
        } else if (pasirinkimas == 2) {
            fr << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_med << "\n";
        } else {
            fr << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_vid
               << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_med << "\n";
        }
    }
    fr.close();
}

void generuotiFaila(const std::string& failoPavadinimas, int kiekis, int nd_kiekis) {
    clock_t pradzia = clock();

    std::ofstream f(failoPavadinimas);
    if (!f.is_open()) return;

    f << std::left << std::setw(15) << "Vardas"
      << std::left << std::setw(15) << "Pavarde";
    for (int j = 1; j <= nd_kiekis; j++) {
        f << std::right << std::setw(8) << ("ND" + std::to_string(j));
    }
    f << std::right << std::setw(10) << "Egzaminas" << "\n";

    for (int i = 1; i <= kiekis; i++) {
        f << std::left << std::setw(15) << ("Vardas" + std::to_string(i))
          << std::left << std::setw(15) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < nd_kiekis; j++) {
            f << std::right << std::setw(8) << (rand() % 10 + 1);
        }
        f << std::right << std::setw(10) << (rand() % 10 + 1) << "\n";
    }

    f.close();

    clock_t pabaiga = clock();
    double laikas = double(pabaiga - pradzia) / CLOCKS_PER_SEC;

    std::cout << "Failas " << failoPavadinimas << " sugeneruotas per " << laikas << " s.\n";
}
