# Programos veikimo spartos tyrimas (v1.0)

Šiame tyrime lyginamas `std::vector` ir `std::list` konteinerių bei 3 skirtingų dalijimo į dvi kategorijas („vargšiukai“ ir „kietiakai“) strategijų efektyvumas.

## Spartos analizės rezultatai (sekundėmis)

| Įrašų kiekis | Konteineris ir Strategija | Nuskaitymas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s)|
|--------------|---------------------------|-----------------|----------------|---------------|-------------------|
| **1 000**    | `std::vector` (1 strat.)  | 0.006           | 0.003          | 0.005         | 0.014             |
|              | `std::list` (1 strat.)    | 0.006           | 0.001          | 0.004         | 0.011             |
|              | `std::vector` (2 strat.)  | 0.006           | 0.046          | 0.005         | 0.057             |
|              | `std::list` (2 strat.)    | 0.006           | 0.001          | 0.004         | 0.011             |
|              | `std::vector` (3 strat. `partition`) | 0.006 | 0.003         | 0.005         | 0.014             |
| **10 000**   | `std::vector` (1 strat.)  | 0.053           | 0.029          | 0.029         | 0.111             |
|              | `std::list` (1 strat.)    | 0.050           | 0.015          | 0.034         | 0.099             |
|              | `std::vector` (2 strat.)  | 0.053           | 4.254          | 0.029         | 4.336             |
|              | `std::list` (2 strat.)    | 0.050           | 0.010          | 0.034         | 0.094             |
|              | `std::vector` (3 strat. `partition`) | 0.053 | 0.026         | 0.029         | 0.108             |
| **100 000**  | `std::vector` (1 strat.)  | 0.543           | 0.303          | 0.247         | 1.093             |
|              | `std::list` (1 strat.)    | 0.521           | 0.235          | 0.245         | 1.001             |
|              | `std::list` (2 strat.)    | 0.521           | 0.131          | 0.245         | 0.897             |
|              | `std::vector` (3 strat. `partition`) | 0.543 | 0.280         | 0.247         | 1.070             |
| **1 000 000**| `std::vector` (1 strat.)  | 5.195           | 3.736          | 2.251         | 11.182            |
|              | `std::list` (1 strat.)    | 5.115           | 2.264          | 2.503         | 9.882             |
|              | `std::list` (2 strat.)    | 5.115           | 1.958          | 2.503         | 9.576             |
|              | `std::vector` (3 strat. `partition`) | 5.195 | 3.656         | 2.251         | 11.102            |
| **10 000 000**| `std::vector` (1 strat.) | 28.033          | 17.261         | 9.041         | 54.335            |
|              | `std::list` (1 strat.)    | 20.202          | 15.667         | 10.259        | 46.128            |
|              | `std::list` (2 strat.)    | 20.202          | 14.524         | 10.259        | 44.985            |
|              | `std::vector` (3 strat. `partition`) | 28.033 | 18.321       | 9.041         | 55.395            |

## Išvados

1. **`std::list` efektyvumas:** `std::list` konteineris atlieka rūšiavimą ir trynimą (2 strategija) greičiau nei `std::vector`, nes elementų trynimas iš sąrašo vidurio neturi papildomų atminties perstūmimo sąnaudų.
2. **2 strategija su `std::vector`:** Prie 10 000 įrašų trynimas užtruko 4.254s, o neįtraukta į didesnių duomenų lentelę (100k+), nes dėl elementų perstūmimo atmintyje trynimo metu ($O(N^2)$ sudėtingumas) veikia ekstremaliai lėtai.
3. **3 strategija (`std::partition`):** Vektoriui leidžia greitai ir saugiai pertvarkyti duomenis vietoje be brangaus elementų trynimo.


# Studentų rezultatų skaičiavimo ir spartos analizės sistema (v1.0)

Ši programa skirtas studentų namų darbų ir egzamino rezultatų apdorojimui, galutinio balo (pagal vidurkį arba medianą) skaičiavimui bei studentų rūšiavimui į dvi kategorijas („vargšiukai“ ir „kietiakai“). Taip pat programoje atliktas išsamus skirtingų C++ konteinerių (`std::vector` ir `std::list`) bei duomenų rūšiavimo strategijų veikimo spartos tyrimas.

---

## Programos režimai

Paleidus programą, vartotojui pateikiamas pasirinkimas tarp dviejų pagrindinių režimų:

1. **Spartos analizės režimas (1 režimas):**
   - Leidžia automatiškai sugeneruoti arba nuskityti didelės apimties duomenų failus.
   - Atlieka ir išmatuoja tris pagrindinius etapus: failo nuskaitymą, studentų rūšiavimą į grupes ir galutinių rezultatų išvedimą į failus.
   - Lyginamas `std::vector` ir `std::list` konteinerių efektyvumas bei skirtingos duomenų skaidymo strategijos.

2. **Įprastas skaičiavimo režimas (2 režimas):**
   - Leidžia įvesti studentų duomenis ranka, generuoti atsitiktinius pažymius arba nuskaityti duomenis iš egzistuojančio failo.
   - Suteikia galimybę pasirinkti: ar galutinis balas bus skaičiuojamas pagal vidurkį, ar pagal medianą.