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

    std::cout << "Pasirinkite rezima:\n";
    std::cout << "1 - Atlikti programos spartos analize (laiko matavimas)\n";
    std::cout << "2 - Skaiciuoti studentu rezultatus (iprastas rezimas)\n";
    int rezimas = ivestiSkaiciu("Pasirinkimas (1-2): ");


    if (rezimas == 1) {
        string failo_pavadinimas = "";
        vector<studentas> sarasas;
        studentas A;

        std::cout << "Pasirinkite veiksma:\n";
        std::cout << "1 - Sugeneruoti nauja duomenu faila\n";
        std::cout << "2 - Naudoti jau egzistuojanti faila\n";
        int veiksmas = ivestiSkaiciu("Pasirinkimas (1-2): ");

        if (veiksmas == 1) {
            std::cout << "\nPasirinkite failo dydi:\n";
            std::cout << "1 - 1 000 irasu\n";
            std::cout << "2 - 10 000 irasu\n";
            std::cout << "3 - 100 000 irasu\n";
            std::cout << "4 - 1 000 000 irasu\n";
            std::cout << "5 - 10 000 000 irasu\n";

            int dydis = ivestiSkaiciu("Pasirinkimas (1-5): ");

            if (dydis == 1) { failo_pavadinimas = "studentai1000.txt"; generuotiFaila(failo_pavadinimas, 1000); }
            else if (dydis == 2) { failo_pavadinimas = "studentai10000.txt"; generuotiFaila(failo_pavadinimas, 10000); }
            else if (dydis == 3) { failo_pavadinimas = "studentai100000.txt"; generuotiFaila(failo_pavadinimas, 100000); }
            else if (dydis == 4) { failo_pavadinimas = "studentai1000000.txt"; generuotiFaila(failo_pavadinimas, 1000000); }
            else if (dydis == 5) { failo_pavadinimas = "studentai10000000.txt"; generuotiFaila(failo_pavadinimas, 10000000); }
        } else {
            std::cout << "Iveskite analizuojamo failo pavadinima: ";
            std::cin >> failo_pavadinimas;
        }

        std::ifstream fd(failo_pavadinimas);
        if (!fd.is_open()) {
            std::cout << "Klaida: Nepavyko atidaryti failo '" << failo_pavadinimas << "'!\n";
            return 1;
        }

        std::cout << "\n--- REZULTATAI (" << failo_pavadinimas << ") ---\n";

        clock_t pradzia_nusk = clock();

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

            sarasas.push_back(A);
            A.paz.clear();
        }
        fd.close();

        clock_t pabaiga_nusk = clock();
        double laikas_nusk = double(pabaiga_nusk - pradzia_nusk) / CLOCKS_PER_SEC;
        std::cout << "1. Duomenu nuskaitymas is failo uztruko: " << laikas_nusk << " s.\n";

        clock_t pradzia_rus = clock();

        vector<studentas> vargsiukai;
        vector<studentas> kietiakiai;

        for (const auto &s : sarasas) {
            if (s.galutinis_vid < 5.0) {
                vargsiukai.push_back(s);
            } else {
                kietiakiai.push_back(s);
            }
        }

        clock_t pabaiga_rus = clock();
        double laikas_rus = double(pabaiga_rus - pradzia_rus) / CLOCKS_PER_SEC;
        std::cout << "2. Studentu rusiavimas i 2 grupes uztruko: " << laikas_rus << " s.\n";

        clock_t pradzia_isv = clock();

        isvestiIFaila("vargsiukai.txt", vargsiukai, 1);
        isvestiIFaila("kietiakiai.txt", kietiakiai, 1);

        clock_t pabaiga_isv = clock();
        double laikas_isv = double(pabaiga_isv - pradzia_isv) / CLOCKS_PER_SEC;
        std::cout << "3. Isvedimas i du naujus failus uztruko: " << laikas_isv << " s.\n";

        double bendras_laikas = laikas_nusk + laikas_rus + laikas_isv;
        std::cout << "-------------------------------------------\n";
        std::cout << "Bendras viso proceso laikas: " << bendras_laikas << " s.\n\n";

    }

    else {
        vector<studentas> sarasas;
        studentas A;
        string failo_pavadinimas = "";

        std::cout << "Pasirinkite duomenu saltini:\n";
        std::cout << "1 - Skaityti is esamo failo\n";
        std::cout << "2 - Ivesti ranka / generuoti atsitiktinai\n";
        std::cout << "3 - Sugeneruoti nauja studentu faila\n";
        int saltinis = ivestiSkaiciu("Pasirinkimas (1-3): ");

        if (saltinis == 3) {
            std::cout << "\nPasirinkite failo dydi:\n";
            std::cout << "1 - 1 000 irasu\n";
            std::cout << "2 - 10 000 irasu\n";
            std::cout << "3 - 100 000 irasu\n";
            std::cout << "4 - 1 000 000 irasu\n";
            std::cout << "5 - 10 000 000 irasu\n";

            int dydis = ivestiSkaiciu("Pasirinkimas (1-5): ");

            if (dydis == 1) { failo_pavadinimas = "studentai1000.txt"; generuotiFaila(failo_pavadinimas, 1000); }
            else if (dydis == 2) { failo_pavadinimas = "studentai10000.txt"; generuotiFaila(failo_pavadinimas, 10000); }
            else if (dydis == 3) { failo_pavadinimas = "studentai100000.txt"; generuotiFaila(failo_pavadinimas, 100000); }
            else if (dydis == 4) { failo_pavadinimas = "studentai1000000.txt"; generuotiFaila(failo_pavadinimas, 1000000); }
            else if (dydis == 5) { failo_pavadinimas = "studentai10000000.txt"; generuotiFaila(failo_pavadinimas, 10000000); }

            saltinis = 1;
        }

        if (saltinis == 1) {
            if (failo_pavadinimas == "") {
                std::cout << "Iveskite failo pavadinima: ";
                std::cin >> failo_pavadinimas;
            }

            std::ifstream fd(failo_pavadinimas);
            if (!fd.is_open()) {
                std::cout << "Klaida: Nepavyko atidaryti failo!\n";
                return 1;
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

                sarasas.push_back(A);
                A.paz.clear();
            }
            fd.close();
        } else {
            int n = ivestiSkaiciu("Kiek yra studentu sarase: ");

            for (int j = 0; j < n; j++) {
                A.paz.clear();
                std::cout << "\nIveskite studento vardas ir pavarde: ";
                std::cin >> A.vardas >> A.pavarde;

                std::cout << "Pasirinkite pazymiu ivedimo buda:\n";
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

                    A.exam = ivestiSkaiciu("Iveskite semestro Egzamino paz: ");
                }

                float sum = 0;
                for (int p : A.paz) sum += p;
                float vid = !A.paz.empty() ? sum / A.paz.size() : 0.0;
                float med = Mediana(A.paz);

                A.galutinis_vid = 0.4 * vid + 0.6 * A.exam;
                A.galutinis_med = 0.4 * med + 0.6 * A.exam;

                sarasas.push_back(A);
                A.paz.clear();
            }
        }

        std::cout << "\nPasirinkite skaiciavimo buda isvedimui:\n";
        std::cout << "1 - Skaiciuoti pagal Vidurki\n";
        std::cout << "2 - Skaiciuoti pagal Mediana\n";
        int pasirinkimas = ivestiSkaiciu("Pasirinkimas (1-2): ");
;
        std::cout << std::left << std::setw(15) << "Vardas"
                  << std::setw(15) << "Pavarde";
        if (pasirinkimas == 1) {
            std::cout << std::setw(20) << "Galutinis (Vid.)" << "\n";
        } else {
            std::cout << std::setw(20) << "Galutinis (Med.)" << "\n";
        }
        std::cout << string(50, '-') << "\n";

        for (const auto &s : sarasas) {
            std::cout << std::left << std::setw(15) << s.vardas
                      << std::setw(15) << s.pavarde;
            if (pasirinkimas == 1) {
                std::cout << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinis_vid << "\n";
            } else {
                std::cout << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinis_med << "\n";
            }
        }

        vector<studentas> vargsiukai;
        vector<studentas> kietiakiai;

        for (const auto &s : sarasas) {
            float balas = (pasirinkimas == 2) ? s.galutinis_med : s.galutinis_vid;
            if (balas < 5.0) {
                vargsiukai.push_back(s);
            } else {
                kietiakiai.push_back(s);
            }
        }

        isvestiIFaila("vargsiukai.txt", vargsiukai, pasirinkimas);
        isvestiIFaila("kietiakiai.txt", kietiakiai, pasirinkimas);

        std::cout << "\nRezultatai sekmingai israsyti i failus 'vargsiukai.txt' ir 'kietiakiai.txt'!\n";
    }

    return 0;
}
