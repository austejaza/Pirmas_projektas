# Pirmas_projektas
Programos veikimo spartos analizė:
Atliekant programos testavimą buvo matuojamas trijų pagrindinių etapų laikas: duomenų nuskaitymas iš failo(1), studentų rūšiavimas į dvi grupes(2) bei rezultatų išvedimas į atskirus failus(3). Testavimas atliktas su 5 skirtingo dydžio sugeneruotais duomenų failais.
Testavimo rezultatai:

1000 įrašų: 1. 0.006s, 2. 0.001s, 3. 0.004s, bendras: 0.011s

10000 įrašų: 1. 0.054s, 2. 0.007s, 3. 0.025s, bendras: 0.086s

100000 įrašų: 1. 0.53s, 2. 0.058s, 3. 0.231s, bendras: 0.819s

1000000 įrašų: 1. 7.487s, 2. 0.657s, 3. 2.316s, bendras: 10.46s

10000000 įrašų: 1. 56.614s, 2. 5.468s, 3. 22.572s, bendras: 84.654s

Išvados: Didžiausią laiko dalį užima duomenų nuskaitymo ir išvedimo į failus operacijos.
