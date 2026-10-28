#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <list>
#include "studentas.h"
#include "funkcijos.h"

using std::string;
using std::vector;
using std::list;

int main() {
    srand(time(0));

    std::cout << "Pasirinkite rezima:\n";
    std::cout << "1 - Atlikti programos spartos analize (laiko matavimas)\n";
    std::cout << "2 - Skaiciuoti studentu rezultatus (iprastas rezimas)\n";
    int rezimas = ivestiSkaiciu("Pasirinkimas (1-2): ");


    if (rezimas == 1) {
        string failo_pavadinimas = "";
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

            if (dydis == 1) { failo_pavadinimas = "studentai1000.txt"; }
            else if (dydis == 2) { failo_pavadinimas = "studentai10000.txt"; }
            else if (dydis == 3) { failo_pavadinimas = "studentai100000.txt"; }
            else if (dydis == 4) { failo_pavadinimas = "studentai1000000.txt"; }
            else if (dydis == 5) { failo_pavadinimas = "studentai10000000.txt"; }

            std::ifstream tikrinimas(failo_pavadinimas);
            if (!tikrinimas.is_open()) {
               std::cout << "Failas nerastas. Generuojamas naujas failas...\n";
               if (dydis == 1) generuotiFaila(failo_pavadinimas, 1000);
               else if (dydis == 2) generuotiFaila(failo_pavadinimas, 10000);
               else if (dydis == 3) generuotiFaila(failo_pavadinimas, 100000);
               else if (dydis == 4) generuotiFaila(failo_pavadinimas, 1000000);
               else if (dydis == 5) generuotiFaila(failo_pavadinimas, 10000000);
           } else {
              std::cout << "Rastas jau egzistuojantis failas '" << failo_pavadinimas << "'. Jis bus naudojamas be pakartotinio generavimo.\n";
              tikrinimas.close();
           }
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


        vector<studentas> sarasas_v;
        clock_t pradzia_nusk_v = clock();
        std::ifstream fd1(failo_pavadinimas);

        string eilute;
        std::getline(fd1, eilute);
        while (std::getline(fd1, eilute)) {
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

            sarasas_v.push_back(A);
            A.paz.clear();
        }
        fd1.close();
        clock_t pabaiga_nusk_v = clock();
        double laikas_nusk_v = double(pabaiga_nusk_v - pradzia_nusk_v) / CLOCKS_PER_SEC;

        list<studentas> sarasas_l;
        clock_t pradzia_nusk_l = clock();

        std::ifstream fd2(failo_pavadinimas);
        std::getline(fd2, eilute);
        while (std::getline(fd2, eilute)) {
            if (eilute.empty()) continue;
            std::stringstream ss(eilute);
            ss >> A.vardas >> A.pavarde;
            int skaicius;
            vector<int> visi_skaiciai;
            while (ss >> skaicius) visi_skaiciai.push_back(skaicius);
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
            sarasas_l.push_back(A);
            A.paz.clear();
        }
        fd2.close();
        clock_t pabaiga_nusk_l = clock();
        double laikas_nusk_l = double(pabaiga_nusk_l - pradzia_nusk_l) / CLOCKS_PER_SEC;

        std::cout << "\n--- REZULTATAI (" << failo_pavadinimas << ") ---\n";
        std::cout << "1a. Nuskaitymas (std::vector) uztruko: " << laikas_nusk_v << " s.\n";
        std::cout << "1b. Nuskaitymas (std::list) uztruko:   " << laikas_nusk_l << " s.\n";

        clock_t pradzia_vec = clock();

        vector<studentas> vargsiukai_v;
        vector<studentas> kietiakiai_v;

        for (const auto &s : sarasas_v) {
            if (s.galutinis_vid < 5.0) {
                vargsiukai_v.push_back(s);
            } else {
                kietiakiai_v.push_back(s);
            }
        }

        std::sort(vargsiukai_v.begin(), vargsiukai_v.end(), [](const studentas& a, const studentas& b) {
            return a.galutinis_vid > b.galutinis_vid;
        });

        std::sort(kietiakiai_v.begin(), kietiakiai_v.end(), [](const studentas& a, const studentas& b) {
            return a.galutinis_vid > b.galutinis_vid;
        });

        clock_t pabaiga_vec = clock();
        double laikas_vec = double(pabaiga_vec - pradzia_vec) / CLOCKS_PER_SEC;
        std::cout << "2a. Studentu rusiavimas i 2 grupes (1 strategija su vector) uztruko: " << laikas_vec << " s.\n";

        clock_t pradzia_list = clock();

        list<studentas> vargsiukai_l;
        list<studentas> kietiakiai_l;

        for (const auto &s : sarasas_l) {
            if (s.galutinis_vid < 5.0) {
                vargsiukai_l.push_back(s);
            } else {
                kietiakiai_l.push_back(s);
            }
        }
        vargsiukai_l.sort([](const studentas& a, const studentas& b) {
            return a.galutinis_vid > b.galutinis_vid;
        });

        kietiakiai_l.sort([](const studentas& a, const studentas& b) {
            return a.galutinis_vid > b.galutinis_vid;
        });


        clock_t pabaiga_list = clock();
        double laikas_list = double(pabaiga_list - pradzia_list) / CLOCKS_PER_SEC;
        std::cout << "2b. Studentu rusiavimas i 2 grupes (1 strategija su list) uztruko: " << laikas_list << " s.\n";



        vector<studentas> sarasas_v2 = sarasas_v;
        clock_t pradzia_strat2_v = clock();

        vector<studentas> vargsiukai_v2;
        for (auto it = sarasas_v2.begin(); it != sarasas_v2.end(); ) {
            if (it->galutinis_vid < 5.0) {
                vargsiukai_v2.push_back(*it);
                it = sarasas_v2.erase(it);
            } else {
                ++it;
            }
        }

        std::sort(vargsiukai_v2.begin(), vargsiukai_v2.end(), [](const studentas& a, const studentas& b) { return a.galutinis_vid > b.galutinis_vid; });
        std::sort(sarasas_v2.begin(), sarasas_v2.end(), [](const studentas& a, const studentas& b) { return a.galutinis_vid > b.galutinis_vid; });

        clock_t pabaiga_strat2_v = clock();
        double laikas_strat2_v = double(pabaiga_strat2_v - pradzia_strat2_v) / CLOCKS_PER_SEC;
        std::cout << "2c. Studentu rusiavimas i 2 grupes (2 strategija su vector) uztruko: " << laikas_strat2_v << " s.\n";



        list<studentas> sarasas_l2 = sarasas_l;
        clock_t pradzia_strat2_l = clock();

        list<studentas> vargsiukai_l2;
        for (auto it = sarasas_l2.begin(); it != sarasas_l2.end(); ) {
            if (it->galutinis_vid < 5.0) {
                vargsiukai_l2.push_back(*it);
                it = sarasas_l2.erase(it);
            } else {
                ++it;
            }
        }

        vargsiukai_l2.sort([](const studentas& a, const studentas& b) { return a.galutinis_vid > b.galutinis_vid; });
        sarasas_l2.sort([](const studentas& a, const studentas& b) { return a.galutinis_vid > b.galutinis_vid; });

        clock_t pabaiga_strat2_l = clock();
        double laikas_strat2_l = double(pabaiga_strat2_l - pradzia_strat2_l) / CLOCKS_PER_SEC;
        std::cout << "2d. Studentu rusiavimas i 2 grupes (2 strategija su list) uztruko:   " << laikas_strat2_l << " s.\n";


        vector<studentas> sarasas_v3 = sarasas_v;
        clock_t pradzia_strat2_v3 = clock();
        auto ribos_it = std::partition(sarasas_v3.begin(), sarasas_v3.end(), [](const studentas& s) {
            return s.galutinis_vid < 5.0;
        });

        vector<studentas> vargsiukai_v3(sarasas_v3.begin(), ribos_it);
        vector<studentas> kietiakiai_v3(ribos_it, sarasas_v3.end());

        std::sort(vargsiukai_v3.begin(), vargsiukai_v3.end(), [](const studentas& a, const studentas& b) { return a.galutinis_vid > b.galutinis_vid; });
        std::sort(kietiakiai_v3.begin(), kietiakiai_v3.end(), [](const studentas& a, const studentas& b) { return a.galutinis_vid > b.galutinis_vid; });

        clock_t pabaiga_strat2_v3 = clock();
        double laikas_strat2_v3 = double(pabaiga_strat2_v3 - pradzia_strat2_v3) / CLOCKS_PER_SEC;
        std::cout << "2e. Studentu rusiavimas i 2 grupes (3 strategija su std::partition, vector) uztruko: " << laikas_strat2_v3 << " s.\n";



        clock_t pradzia_isv_v = clock();
        isvestiIFaila("vargsiukai_v.txt", vargsiukai_v, 1);
        isvestiIFaila("kietiakiai_v.txt", kietiakiai_v, 1);
        clock_t pabaiga_isv_v = clock();
        double laikas_isv_v = double(pabaiga_isv_v - pradzia_isv_v) / CLOCKS_PER_SEC;

        clock_t pradzia_isv_l = clock();
        isvestiIFaila("vargsiukai_l.txt", vargsiukai_l, 1);
        isvestiIFaila("kietiakiai_l.txt", kietiakiai_l, 1);
        clock_t pabaiga_isv_l = clock();
        double laikas_isv_l = double(pabaiga_isv_l - pradzia_isv_l) / CLOCKS_PER_SEC;

        std::cout << "3a. Isvedimas (std::vector) uztruko: " << laikas_isv_v << " s.\n";
        std::cout << "3b. Isvedimas (std::list) uztruko:   " << laikas_isv_l << " s.\n";

        double bendras_laikas_vector = laikas_nusk_v + laikas_vec + laikas_isv_v;
        double bendras_laikas_list = laikas_nusk_l + laikas_list + laikas_isv_l;
        double bendras_laikas_v_p = laikas_nusk_v + laikas_strat2_v3+ laikas_isv_v;
        std::cout << "-------------------------------------------\n";
        std::cout << "1. Bendras viso proceso laikas(su vector): " << bendras_laikas_vector << " s.\n\n";
        std::cout << "2. Bendras viso proceso laikas(su list): " << bendras_laikas_list << " s.\n\n";
        std::cout << "3. Bendras viso proceso laikas(su vector ir partition): " << bendras_laikas_v_p << " s.\n\n";

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

                std::cout << "Studento objekto atminties adresas atmintyje: " << &A << "\n";

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
        std::sort(vargsiukai.begin(), vargsiukai.end(), [](const studentas& a, const studentas& b) {
            return a.galutinis_vid > b.galutinis_vid;
        });

        std::sort(kietiakiai.begin(), kietiakiai.end(), [](const studentas& a, const studentas& b) {
            return a.galutinis_vid > b.galutinis_vid;
        });


        isvestiIFaila("vargsiukai.txt", vargsiukai, pasirinkimas);
        isvestiIFaila("kietiakiai.txt", kietiakiai, pasirinkimas);

        std::cout << "\nRezultatai sekmingai israsyti i failus 'vargsiukai.txt' ir 'kietiakiai.txt'!\n";
    }

    return 0;
}
