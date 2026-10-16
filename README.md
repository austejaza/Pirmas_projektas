# Testavimo rezultatai
Programos versija "v0.3" skirta ištirti ir palyginti programos spartą naudojant skirtingus konteinerius: "std::vector" ir "std::list".

Testavimo sistemos parametrai:
* **CPU:** AMD Ryzen 7 7730U
* **RAM:** 16 GB
* **Diskas:** SSD

## Spartos analizės rezultatai(sekundėmis):

Palyginimas atliktas tarp `std::list` ir `std::vector` konteinerių naudojant skirtingą įrašų kiekį. Pateikti vidutiniai duomenų nuskaitymo, rūšiavimo ir išvedimo laikai bei bendras laikas.

| Įrašų kiekis | Konteineris | Nuskaitymas | Rūšiavimas  | Išvedimas  | Bendras laikas  |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1 000** | `std::list` | 0.006 | 0.001 | 0.006 | 0.013 |
| | `std::vector` | 0.005 | 0.003 | 0.088 | 0.096 |
| **10 000** | `std::list` | 0.053 | 0.013 | 0.024 | 0.089 |
| | `std::vector` | 0.050 | 0.0285 | 0.027 | 0.105 |
| **100 000** | `std::list` | 0.522 | 0.185 | 0.272 | 0.981 |
| | `std::vector` | 0.510 | 0.362 | 0.216 | 1.055 |
| **1 000 000** | `std::list` | 5.315 | 2.007 | 2.261 | 9.583 |
| | `std::vector` | 5.022 | 4.417 | 2.118 | 11.558 |
| **10 000 000** | `std::list` | 51.317 | 24.186 | 22.874 | 98.877 |
| | `std::vector` | 52.103 | 52.929 | 21.046 | 126.069 |
