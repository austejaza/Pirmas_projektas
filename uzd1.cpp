#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using std::string;
using std::vector;


struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam;
    float galutinis_vid;
    float galutinis_med;
};

int ivestiSkaiciu(const string &zinute) {
    int x;
    std::cout << zinute;
    while (!(std::cin >> x)) {
        std::cout << "Klaida! Iveskite skaiciu: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

float Mediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    
    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();
    
    if (n % 2 == 0) {
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    } else {
        return paz[n / 2];
    }
}

void printas(studentas &A, int pasirinkimas);

int main()
{
    srand(time(0));
    vector<studentas> grupe;
    studentas A;

    int saltinis;
    std::cout << "Pasirinkite duomenu saltini:\n";
    std::cout << "1 - Skaityti is failo (kursiokai.txt)\n";
    std::cout << "2 - Ivesti ranka / generuoti atsitiktinai\n";
    saltinis = ivestiSkaiciu("Pasirinkimas (1-2): ");

    if (saltinis == 1) {
        std::ifstream fd("kursiokai.txt");
        if (!fd.is_open()) {
            std::cout << "Klaida: Nepavyko atidaryti failo kursiokai.txt!\n";
            return 1;
        }

        string eilute;
        std::getline(fd, eilute);
        while (std::getline(fd, eilute)) {
            if (eilute.empty()) continue;

            std::stringstream ss(eilute);
            ss >> A.pavarde >> A.vardas;

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
    }
    else {

    int n = ivestiSkaiciu("kiek yra studentu sarase: ");

    for (int j = 0; j < n; j++)
    {
        std::cout << "iveskite per tarpa studento varda ir pav: ";
        std::cin >> A.vardas >> A.pavarde;

        std::cout << "\nPasirinkite pazymiu ivedimo buda:\n";
        std::cout << "1 - Ivesti pazymius rankiniu budu\n";
        std::cout << "2 - Generuoti pazymius atsitiktinai\n";
        std::cout << "Pasirinkimas (1-2): ";

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
        } 
        else {
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

    std::cout << "\nKaip skaiciuoti galutini bala?\n";
    std::cout << "1 - Pagal vidurki\n";
    std::cout << "2 - Pagal mediana\n";
    std::cout << "3 - Abu variantus\n";
    int pasirinkimas = ivestiSkaiciu("Pasirinkimas (1-3): ");

    std::sort(grupe.begin(), grupe.end(), [](const studentas &a, const studentas &b) {
        if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
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

    for (studentas &B : grupe)
    {
        printas(B, pasirinkimas);
    }

    return 0;
}

void printas(studentas &A, int pasirinkimas)
{
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
