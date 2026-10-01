#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "studentas.h"
#include "funkcijos.h"

using std::string;
using std::vector;

int main() {
    srand(time(0));
    vector<studentas> grupe;
    studentas A;

    string failo_pavadinimas = "";

    std::cout << "Pasirinkite duomenu saltini:\n";
    std::cout << "1 - Skaityti is failo\n";
    std::cout << "2 - Ivesti ranka / generuoti atsitiktinai\n";
    std::cout << "3 - Sugeneruoti nauja studentu faila\n";
    int saltinis = ivestiSkaiciu("Pasirinkimas (1-3): ");

    if (saltinis == 3) {
        std::cout << "\nPasirinkite failo dydi:\n";
        std::cout << "1 - 1 000 irasu (studentai1000.txt)\n";
        std::cout << "2 - 10 000 irasu (studentai10000.txt)\n";
        std::cout << "3 - 100 000 irasu (studentai100000.txt)\n";
        std::cout << "4 - 1 000 000 irasu (studentai1000000.txt)\n";
        std::cout << "5 - 10 000 000 irasu (studentai10000000.txt)\n";

        int dydis = ivestiSkaiciu("Pasirinkimas (1-5): ");

        if (dydis == 1) generuotiFaila("studentai1000.txt", 1000);
        else if (dydis == 2) generuotiFaila("studentai10000.txt", 10000);
        else if (dydis == 3) generuotiFaila("studentai100000.txt", 100000);
        else if (dydis == 4) generuotiFaila("studentai1000000.txt", 1000000);
        else if (dydis == 5) generuotiFaila("studentai10000000.txt", 10000000);
        else std::cout << "Neteisingas pasirinkimas!\n";

        saltinis = 1;
    }

    if (saltinis == 1) {
        if (failo_pavadinimas == "") {
            std::cout << "Iveskite failo pavadinima (pvz., kursiokai.txt arba studentai1000.txt): ";
            std::cin >> failo_pavadinimas;
        }

        std::ifstream fd(failo_pavadinimas);
        if (!fd.is_open()) {
            std::cout << "Klaida: Nepavyko atidaryti failo \n";
            std::cout << "Iveskite teisinga failo pavadinima: ";
            std::cin >> failo_pavadinimas;
            fd.open(failo_pavadinimas);
        }

        string eilute;
        std::getline(fd, eilute);
        while (std::getline(fd, eilute)) {
            if (eilute.empty()) continue;

            std::stringstream ss(eilute);
            ss >> A.vardas >> A.pavarde;

            int skaicius;
            vector<int> visi_skaiciai;
            while (ss >> skaicius) {
                visi_skaiciai.push_back(skaicius);
            }

            if (!visi_skaiciai.empty()) {
                A.exam = visi_skaiciai.back();
                visi_skaiciai.pop_back();
                A.paz = visi_skaiciai;
            }
            float sum = 0;
            for (int p : A.paz) sum += p;
            float vid = !A.paz.empty() ? sum / A.paz.size() : 0.0;
            float med = Mediana(A.paz);

            A.galutinis_vid = 0.4 * vid + 0.6 * A.exam;
            A.galutinis_med = 0.4 * med + 0.6 * A.exam;

            grupe.push_back(A);
            A.paz.clear();
        }
        fd.close();
    } else {
        int n = ivestiSkaiciu("kiek yra studentu sarase: ");

        for (int j = 0; j < n; j++) {
            A.paz.clear();
            std::cout << "iveskite per tarpa studento varda ir pav: ";
            std::cin >> A.vardas >> A.pavarde;

            std::cout << "\nPasirinkite pazymiu ivedimo buda:\n";
            std::cout << "1 - Ivesti pazymius rankiniu budu\n";
            std::cout << "2 - Generuoti pazymius atsitiktinai\n";

            int ivesties_budas = ivestiSkaiciu("Pasirinkimas (1-2): ");

            if (ivesties_budas == 2) {
                int nd_kiekis;
                std::cout << "Kiek atsitiktiniu ND pazymiu sugeneruoti? ";
                std::cin >> nd_kiekis;

                for (int i = 0; i < nd_kiekis; i++) {
                    A.paz.push_back(rand() % 10 + 1);
                }
                A.exam = rand() % 10 + 1;

                std::cout << "Sugeneruoti ND pazymiai: ";
                for (int p : A.paz) std::cout << p << " ";
                std::cout << "\nSugeneruotas egzamino pazymys: " << A.exam << "\n";
            } else {
                std::cin.ignore(1000, '\n');
                std::cout << "Iveskite ND pazymius (spauskite du kartus ENTER, kad baigtumete):\n";
                string eilute;
                while (true) {
                    std::getline(std::cin, eilute);
                    if (eilute.empty()) break;

                    std::stringstream ss(eilute);
                    int pazymys;
                    while (ss >> pazymys) {
                        A.paz.push_back(pazymys);
                    }
                }

                A.exam = ivestiSkaiciu("iveskite semestro Egzamino paz: ");
            }

            float sum = 0;
            for (int p : A.paz) {
                sum += p;
            }
            float vid = !A.paz.empty() ? sum / A.paz.size() : 0.0;
            float med = Mediana(A.paz);

            A.galutinis_vid = 0.4 * vid + 0.6 * A.exam;
            A.galutinis_med = 0.4 * med + 0.6 * A.exam;

            grupe.push_back(A);
            A.paz.clear();
        }
    }

    std::cout << "\nKaip skaiciuoti galutini bala?\n";
    std::cout << "1 - Pagal vidurki\n";
    std::cout << "2 - Pagal mediana\n";
    std::cout << "3 - Abu variantus\n";
    int pasirinkimas = ivestiSkaiciu("Pasirinkimas (1-3): ");

    std::sort(grupe.begin(), grupe.end(), [](const studentas &a, const studentas &b) {
        if (a.vardas.substr(0, 6) == "Vardas" && b.vardas.substr(0, 6) == "Vardas") {
            try {
                return std::stoi(a.vardas.substr(6)) < std::stoi(b.vardas.substr(6));
            } catch (...) {}
        }
        return a.vardas < b.vardas;
    });

    std::cout << "\n"
              << std::left << std::setw(15) << "Vardas"
              << std::left << std::setw(15) << "Pavarde";
    if (pasirinkimas == 1) {
        std::cout << std::right << std::setw(18) << "Galutinis (Vid.)" << "\n";
        std::cout << string(48, '-') << "\n";
    } else if (pasirinkimas == 2) {
        std::cout << std::right << std::setw(18) << "Galutinis (Med.)" << "\n";
        std::cout << string(48, '-') << "\n";
    } else {
        std::cout << std::right << std::setw(18) << "Galutinis (Vid.)"
                  << std::right << std::setw(18) << "Galutinis (Med.)" << "\n";
        std::cout << string(66, '-') << "\n";
    }

    for (studentas &B : grupe) {
        printas(B, pasirinkimas);
    }

    vector<studentas> vargsiukai;
    vector<studentas> kietiakiai;

    for (const auto &s : grupe) {
        float balas = (pasirinkimas == 2) ? s.galutinis_med : s.galutinis_vid;
        if (balas < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }

    isvestiIFaila("vargsiukai.txt", vargsiukai, pasirinkimas);
    isvestiIFaila("kietiakiai.txt", kietiakiai, pasirinkimas);

    std::cout << "\nStudentai sekmingai isrusiuoti i 'vargsiukai.txt' ir 'kietiakiai.txt'!\n";

    return 0;
}
