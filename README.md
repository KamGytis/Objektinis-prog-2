# Studentu programa v2.0

## Apie programa

Programa skirta studentu duomenims apdoroti. Gali nuskaityti vardus, pavardes, namu darbu pazymius ir egzamino rezultata. Galutinis balas skaiciuojamas pagal vidurkis arba mediana.

## Programos funkcijos

- Rankinis studentu duomenu ivedimas
- Nuskaitymas is failo
- Studentu failu generavimas
- Galutinio balo skaiciavimas (vidurkis arba mediana)
- Rusiavimas pagal varda, pavarde arba rezultata
- Skirstymas i dvi grupes (kietiakai / vargsiukai)
- Spartos tyrimas su trimis konteineriais ir strategijomis
- Studentas klases testavimas
- Unit testai (Rule of Five, operatoriai)
- Doxygen dokumentacija

## Reikalavimai

- C++17 kompiliatorius (`g++` arba MSVC 2019+)
- Windows / Linux / macOS
- `make`, Doxygen (dokumentacijai)

## Programos atsisiuntimas

```bash
git clone https://github.com/USERNAME/studentai.git
cd studentai
```

## Kompiliavimas

```bash
make        # programa
make test   # unit testai
make docs   # Doxygen dokumentacija
make clean  # valymas
```

**Windows:** atidaryti `.sln`, spausti **Build -> Build Solution**.

## Programos meniu

```
1 - Rankinis ivedimas
2 - Skaityti is failo (vector)
3 - Skaityti is failo (list)
4 - Skaityti is failo (deque)
5 - Testavimas (visi konteineriai)
6 - Generuoti studentu failus
7 - Klases testavimas
8 - Baigti
```

## Unit testai

v2.0 versijoje prideti unit testai naudojant **Google Test (gtest)** biblioteka. Testai tikrina ar pagrindiniai `Studentas` klases metodai veikia teisingai.

| Testas                              | Ka tikrina                              |
|-------------------------------------|-----------------------------------------|
| `RuleOfFive.DefaultConstructor`     | Tusciu lauku tikrinimas                 |
| `RuleOfFive.ParameterConstructor`   | Lauku inicializacija                    |
| `RuleOfFive.CopyConstructor`        | Gili kopija, originalas nepakito        |
| `RuleOfFive.MoveConstructor`        | Perkelimas, originalas istusejo         |
| `RuleOfFive.CopyAssignment`         | Kopija, originalas nepakito             |
| `RuleOfFive.MoveAssignment`         | Perkelimas, originalas tuscias          |
| `RuleOfFive.SelfAssignment`         | `a = a` nesugriauna objekto             |
| `Functional.AverageAndMedian`       | vidurkis() ir mediana()                 |
| `Functional.CalculateResultMean`    | skaiciuotiRez(1) su vidurkiu            |
| `Functional.CalculateResultMedian`  | skaiciuotiRez(2) su mediana             |
| `Functional.IsPassed`               | islaike() riba 5.0                      |
| `AbstractZmogus.Polymorphism`       | `Zmogus*` rodykle, virtualus destr.     |
| `AbstractZmogus.OutputOperator`     | `operator<<` per virtual print()        |

Unit testai paleidžiami:

```bash
make test
./tests/run_tests
```

## Doxygen dokumentacija

v2.0 versijoje sugeneruota dokumentacija naudojant Doxygen. Aprašyta `Zmogus` ir `Studentas` klase, ju konstruktoriai, Rule of Five metodai, ivesties ir isvesties operatoriai.

| Dokumentacijos tipas | Vieta projekte        |
|----------------------|-----------------------|
| HTML                 | `docs/html/index.html`|
| LaTeX                | `docs/latex/`         |
| PDF                  | `docs/refman.pdf`     |

```bash
doxygen Doxyfile       # generuoti HTML ir LaTeX
cd docs/latex && make  # kompiliuoti PDF
```

PDF taip pat galima sugeneruoti per [Overleaf](https://www.overleaf.com) – uzarchyvuoti `docs/latex/` i `.zip` ir ikelti.

## Spartos palyginimas

Testuota: `std::vector`, S3 strategija, g++ 13, Linux x86-64.

### 100 000 studentu

| Tipas  | Veliavele | Bendras (s) | Failo dydis |
|--------|:---------:|:-----------:|:-----------:|
| struct | -O0       | 0.356       | 323 KB      |
| class  | -O0       | 0.409       | 369 KB      |
| struct | -O1       | 0.146       | 199 KB      |
| class  | -O1       | 0.176       | 173 KB      |
| struct | -O2       | 0.145       | 203 KB      |
| class  | -O2       | 0.203       | 174 KB      |
| struct | -O3       | 0.183       | 254 KB      |
| class  | -O3       | 0.176       | 187 KB      |

### 1 000 000 studentu

| Tipas  | Veliavele | Bendras (s) | Failo dydis |
|--------|:---------:|:-----------:|:-----------:|
| struct | -O0       | 3.743       | 323 KB      |
| class  | -O0       | 4.467       | 369 KB      |
| struct | -O1       | 1.650       | 199 KB      |
| class  | -O1       | 2.028       | 173 KB      |
| struct | -O2       | 1.721       | 203 KB      |
| class  | -O2       | 2.105       | 174 KB      |
| struct | -O3       | 1.673       | 254 KB      |
| class  | -O3       | 1.962       | 187 KB      |

`-O0 → -O1` duoda ~2.5x pagreitejima. `class` letesne ~15-22% del getter'iu iskvietimu. Rekomenduojama `-O2`.

## Reliazu aprasas

### v2.0
- Prideti unit testai `Studentas` klasei (Rule of Five, operatoriai).
- Sugeneruota Doxygen HTML ir LaTeX/PDF dokumentacija.
- Isvaloyta repozitorija nuo IDE silkeliu.
- Atnaujintas `README.md`.

### v1.5
- Sukurta abstrakti bazine klase `Zmogus`, `Studentas` isvestine.
- Polimorfizmas per `Zmogus*`, virtualus `print()`.
- Visi v1.2 testai islaikyti.

### v1.2
- Realizuoti visi Rule of Five metodai.
- Realizuoti `operator>>` ir `operator<<`.
- Sukurtas klases testavimo modulis.

### v1.1
- `struct` pakeistas i `class`, privatūs laukai.
- Getteriai, setteriai, konstruktoriai.
- Atliktas struct vs class spartos palyginimas su O1/O2/O3.

### v1.0
- Trys STL konteineriai: `vector`, `list`, `deque`.
- Trys skirstymo strategijos (S1/S2/S3).
- Lyginamasis tyrimas, `Makefile`.
