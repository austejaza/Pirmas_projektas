#include "funkcijos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

int ivestiSkaiciu(const std::string &zinute) {
    int x;
    std::cout << zinute;
    while (!(std::cin >> x)) {
        std::cout << "Klaida! Iveskite skaiciu: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

void generuotiFaila(std::string failoPavadinimas, int kiekis, int nd_kiekis) {
    std::ofstream f(failoPavadinimas);

    f << "Vardas          Pavarde         ";
    for (int j = 1; j <= nd_kiekis; j++) {
        f << "ND" << j << " ";
    }
    f << "Egzaminas\n";

    for (int i = 1; i <= kiekis; i++) {
        f << "Vardas" << i << "         "
          << "Pavarde" << i << "        ";

        for (int j = 0; j < nd_kiekis; j++) {
            f << (rand() % 10 + 1) << " ";
        }
        f << (rand() % 10 + 1) << "\n";
    }

    f.close();
    std::cout << "Failas " << failoPavadinimas << " sekmingai sugeneruotas!\n";
}

void isvestiIFaila(const std::string &failoPavadinimas, const std::vector<studentas> &sarasas, int pasirinkimas) {
    std::ofstream out(failoPavadinimas);
    if (!out.is_open()) return;

    out << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(15) << "Pavarde";
    if (pasirinkimas == 1) {
        out << std::right << std::setw(18) << "Galutinis (Vid.)" << "\n";
        out << std::string(48, '-') << "\n";
    } else if (pasirinkimas == 2) {
        out << std::right << std::setw(18) << "Galutinis (Med.)" << "\n";
        out << std::string(48, '-') << "\n";
    } else {
        out << std::right << std::setw(18) << "Galutinis (Vid.)"
            << std::right << std::setw(18) << "Galutinis (Med.)" << "\n";
        out << std::string(66, '-') << "\n";
    }

    for (const auto &s : sarasas) {
        out << std::left << std::setw(15) << s.vardas
            << std::left << std::setw(15) << s.pavarde;
        if (pasirinkimas == 1) {
            out << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_vid;
        } else if (pasirinkimas == 2) {
            out << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_med;
        } else {
            out << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_vid
                << std::right << std::setw(18) << std::fixed << std::setprecision(2) << s.galutinis_med;
        }
        out << "\n";
    }
    out.close();
}

void printas(studentas &A, int pasirinkimas) {
    std::cout << std::left << std::setw(15) << A.vardas
              << std::left << std::setw(15) << A.pavarde;
    if (pasirinkimas == 1) {
        std::cout << std::right << std::setw(18) << std::fixed << std::setprecision(2) << A.galutinis_vid;
    } else if (pasirinkimas == 2) {
        std::cout << std::right << std::setw(18) << std::fixed << std::setprecision(2) << A.galutinis_med;
    } else {
        std::cout << std::right << std::setw(18) << std::fixed << std::setprecision(2) << A.galutinis_vid
                  << std::right << std::setw(18) << std::fixed << std::setprecision(2) << A.galutinis_med;
    }
    std::cout << "\n";
}
