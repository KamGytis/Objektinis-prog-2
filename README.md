# Studentu programa v1.5

Programa skirta studentu duomenu valdymui naudojant C++ klases ir STL konteinerius.

---

## Turinys
1. [Reikalavimai](#reikalavimai)
2. [Idiegimo instrukcija](#idiegimo-instrukcija)
3. [Naudojimo instrukcija](#naudojimo-instrukcija)
4. [Klasiu hierarchija](#klasiu-hierarchija)
5. [Zmogus abstrakti klase](#zmogus-abstrakti-klase)
6. [Studentas isvestine klase](#studentas-isvestine-klase)
7. [Rule of Five](#rule-of-five)
8. [Perdengti ivesties ir isvesties operatoriai](#perdengti-ivesties-ir-isvesties-operatoriai)
9. [Klases testavimas](#klases-testavimas)
10. [Spartos palyginimas struct vs class](#spartos-palyginimas-struct-vs-class)
11. [Optimizavimo veliaveliuanalize](#optimizavimo-veliaveliuanalize)
12. [Reliazu aprasas](#reliazu-aprasas)

---

## Reikalavimai

- C++17 kompiliatorius (`g++` arba MSVC 2019+)
- Windows / Linux / macOS
- `make` (Linux/macOS kompiliavimui)

---

## Idiegimo instrukcija

### Linux / macOS

```bash
git clone https://github.com/USERNAME/studentai.git
cd studentai
make
./studentai
```

### Makefile komandos

```bash
make        # Kompiliuoti be optimizavimo
make O1     # Kompiliuoti su -O1
make O2     # Kompiliuoti su -O2
make O3     # Kompiliuoti su -O3
make clean  # Istrinti sukompiliuotus failus
```

### Windows (Visual Studio)

Atidaryti `.sln` faila ir spausti **Build -> Build Solution**, tada paleisti `studentai.exe`.

### Versiju kurimas (git)

```bash
# Nukopijuoti sena repozitorija
cp -r studentai_v12/ studentai_v15/
cd studentai_v15/
 
# Pakeisti nuotolini adresa
git remote set-url origin https://github.com/USERNAME/studentai_v15.git
git push -u origin master
 
# Sukurti v1.5 saka ir release
git checkout -b v1.5
git push origin v1.5
git tag v1.5
git push origin v1.5
```

---

## Naudojimo instrukcija

```
======= STUDENTU PROGRAMA v1.2 (class) =======
1 - Rankinis ivedimas
2 - Skaityti is failo (vector)
3 - Skaityti is failo (list)
4 - Skaityti is failo (deque)
5 - Testavimas (visi konteineriai)
6 - Generuoti studentu failus
7 - Studentas klases testavimas
8 - Baigti
```

- **1 parinktis** – rankinis duomenu ivedimas: vardas, pavarde, pazymiai, egzaminas, rezultato isvedimas.
- **2-4 parinktis** – skaitymas is pasirinkto `.txt` failo su pasirinktu konteineriu, rusiavimas ir skirstymas i grupes.
- **5 parinktis** – automatinis testavimas visais konteineriais ir strategijomis.
- **6 parinktis** – studentu failu generavimas (1k, 10k, 100k, 1M, 10M irasu).
- **7 parinktis** – `Studentas` klases visu metodu testavimas.
- **8 parinktis** – programos nutraukimas.

**Rekomenduojama tvarka:**
1. Pasirinkti **6 -> 1** – sugeneruoti testu failus.
2. Pasirinkti **5** – atlikti lyginamaji testavima.

---

## Klasiu hierarchija
 
```
Zmogus          <- abstrakti bazine klase (objektu kurti NEGALIMA)
    |
    +-- Studentas   <- isvestine klase (objektus kurti GALIMA)
```
 
### Failu struktura
 
| Failas                  | Aprasymas                                        |
|-------------------------|--------------------------------------------------|
| `zmogus.h / .cpp`       | Abstrakti bazine klase                           |
| `studentas.h / .cpp`    | Isvestine klase is Zmogus                        |
| `vector_ops.h / .cpp`   | Operacijos su `std::vector<Studentas>`           |
| `list_ops.h / .cpp`     | Operacijos su `std::list<Studentas>`             |
| `deque_ops.h / .cpp`    | Operacijos su `std::deque<Studentas>`            |
| `testavimas_klases.cpp` | Visu klases metodu testavimas                    |
| `generator.cpp`         | Testu failu generavimas                          |
| `testavimas.cpp`        | Spartos testavimas visiems konteineriams         |
 
---
 
## Zmogus abstrakti klase
 
### Kas ji daro abstrakcia?
 
Klase abstrakti del **grynai virtualaus destruktoriaus**:
 
```cpp
virtual ~Zmogus() = 0;
```
 
Del sio del to bandant sukurti `Zmogus` tipo objekta kompiliatorius meta klaida:
 
```cpp
Zmogus z;              // KLAIDA: cannot instantiate abstract class
Zmogus z("A", "B");   // KLAIDA: cannot instantiate abstract class
```
 
Galima kurti tik isvestines klases objektus:
 
```cpp
Studentas s;                              // OK
Zmogus* ptr = new Studentas("A", "B", {}, 0);  // OK – polimorfizmas
```
 
### Zmogus laukai ir metodai
 
| Laukas / Metodas     | Tipas / Grazinama | Aprasymas                          |
|----------------------|-------------------|------------------------------------|
| `vardas_`            | `std::string`     | Zmogaus vardas (protected)         |
| `pavarde_`           | `std::string`     | Zmogaus pavarde (protected)        |
| `getVardas()`        | `const string&`   | Grazina varda                      |
| `getPavarde()`       | `const string&`   | Grazina pavarde                    |
| `setVardas(v)`       | `void`            | Nustato varda                      |
| `setPavarde(p)`      | `void`            | Nustato pavarde                    |
| `print(os)`          | `virtual void`    | Grynas virtualus – realizuoja isvestine klase |
| `~Zmogus()`          | `virtual = 0`     | Grynas virtualus destruktorius     |
 
### Polimorfizmas per Zmogus*
 
```cpp
Zmogus* ptr = new Studentas("Jonas", "Jonaitis", {8, 9}, 10);
 
// Getter'iai veikia per bazine klase
ptr->getVardas();   // "Jonas"
ptr->getPavarde();  // "Jonaitis"
 
// operator<< naudoja virtual print() – iskvieciama Studentas versija
std::cout << *ptr;
// Jonas          Jonaitis       [8 9] Egz: 10  Rez: 0.00
 
// Virtualus destruktorius – teisingai iskvieciamas Studentas destruktorius
delete ptr;
```
 
### Rule of Five Zmogus klaseje
 
```cpp
Zmogus();                                    // numatytasis konstruktorius
Zmogus(const string& vardas, const string& pavarde); // parametrinis
Zmogus(const Zmogus& other);                 // kopijavimo konstruktorius
Zmogus(Zmogus&& other) noexcept;             // perkelimo konstruktorius
virtual ~Zmogus() = 0;                       // grynas virtualus destruktorius
Zmogus& operator=(const Zmogus& other);      // kopijavimo priskyrimas
Zmogus& operator=(Zmogus&& other) noexcept;  // perkelimo priskyrimas
```
 
---
 
## Studentas isvestine klase
 
### Paveldejimas
 
`Studentas` paveldi is `Zmogus` naudodama `public` paveldejima:
 
```cpp
class Studentas : public Zmogus { ... };
```
 
Tai reiskia:
- `Studentas` paveldi `vardas_`, `pavarde_` laukus
- `Studentas` paveldi `getVardas()`, `getPavarde()`, `setVardas()`, `setPavarde()`
- `Studentas` **privalo** realizuoti gryną virtualu `print()` metoda
### Studentas papildomi laukai
 
| Laukas   | Tipas              | Aprasymas                  |
|----------|--------------------|----------------------------|
| `paz_`   | `std::vector<int>` | Namu darbu pazymiai (1-10) |
| `egz_`   | `int`              | Egzamino pazymys           |
| `rez_`   | `double`           | Galutinis rezultatas       |
 
### Visi Studentas metodai
 
| Metodas                 | Aprasymas                                         |
|-------------------------|---------------------------------------------------|
| `getPaz()`              | Grazina pazymiu sarasa                            |
| `getEgz()`              | Grazina egzamino pazymi                           |
| `getRez()`              | Grazina galutini rezultata                        |
| `getPazSkaicius()`      | Grazina pazymiu skaiciu                           |
| `setEgz(e)`             | Nustato egzamino pazymi                           |
| `setRez(r)`             | Nustato galutini rezultata                        |
| `addPazymys(p)`         | Prideda pazymi i sarasa                           |
| `clearPazymiai()`       | Isvalo pazymiu sarasa                             |
| `vidurkis()`            | Skaiciuoja namu darbu vidurkis                    |
| `mediana()`             | Skaiciuoja namu darbu mediana                     |
| `skaiciuotiRez(tipas)`  | Skaiciuoja galutini rezultata (1=vidurkis, 2=mediana) |
| `islaike()`             | `true` jei `rez_ >= 5.0`                          |
| `print(os)`             | Realizuoja Zmogus gryna virtualu metoda           |

## Rule of Five

Pagal **Rule of Five** realizuoti visi penki specialieji metodai:

```cpp
// 1. Numatytasis konstruktorius
Studentas();

// 2. Kopijavimo konstruktorius – gili kopija visu lauku
Studentas(const Studentas& other);

// 3. Perkelimo konstruktorius – perima resursus, original palieka tuscia
Studentas(Studentas&& other) noexcept;

// 4. Destruktorius – isvalo paz_ vektoriu
~Studentas();

// 5. Kopijavimo priskyrimo operatorius – apsaugotas nuo saves priskyrimo
Studentas& operator=(const Studentas& other);

// 6. Perkelimo priskyrimo operatorius – apsaugotas nuo saves priskyrimo
Studentas& operator=(Studentas&& other) noexcept;
```

### Kodel svarbus Rule of Five?

`Studentas` klase valdo dinaminius resursus (`std::vector<int> paz_`). Be aiškiai apibrėžtu specialiuju metodu kompiliatorius generuotu pavirsutines kopijas – du objektai rodytų į ta pati atminties sriti, kas sukeltų klaidas trinant objektus. Rule of Five garantuoja:

- **Kopijavimo konstruktorius** – sukuria nepriklausoma kopija (gili kopija).
- **Perkelimo konstruktorius** – efektyviai perkelia resursus be kopijavimo (O(1) vietoj O(n)).
- **Destruktorius** – teisingai atlaisvina atminti.
- **Kopijavimo priskyrimas** – apsaugotas nuo `a = a` situacijos.
- **Perkelimo priskyrimas** – efektyvus priskyrimas su `std::move`.

### Kopijavimo vs Perkelimo konstruktorius

```cpp
Studentas a("Jonas", "Jonaitis", {8, 9, 7}, 10);

// Kopijavimo konstruktorius – a lieka nepakites
Studentas b(a);
// b ir a yra nepriklausomi objektai

// Perkelimo konstruktorius – a tampa tuscias
Studentas c(std::move(a));
// c turi visus a duomenis, a.getVardas() == ""
```

---

## Perdengti ivesties ir isvesties operatoriai

`Studentas` klaseje perdengti `operator>>` ir `operator<<` leidzia naudoti standartine C++ srauto sintakse duomenu ivedimui ir isvedimui. Svarbu tai, kad **abu operatoriai veikia su bet kokiu srautu** – nesvarbu ar tai ekranas, failas ar eilute atmintyje.

---

### operator>> (ivestis)

```cpp
friend std::istream& operator>>(std::istream& is, Studentas& s);
```

**Kaip veikia:** nuskaito viena eilute is srauto. Pirmas zodis – vardas, antras – pavarde, visi sekantys skaiciai – namu darbu pazymiai, **paskutinis skaicius – egzaminas**.

**Ivesties formatas:**
```
Vardas Pavarde nd1 nd2 nd3 ... ndN egzaminas
Jonas  Jonaitis  8   9   7        10
```

#### 1. Rankinis ivedimas (std::cin)

Vartotojas pats iraso duomenis i terminala:

```cpp
Studentas s;
std::cout << "Iveskite studenta (Vardas Pavarde paz1 paz2 ... egz): ";
std::cin >> s;

// Vartotojas iveda:  Jonas Jonaitis 8 9 7 10
// s.getVardas()   -> "Jonas"
// s.getPavarde()  -> "Jonaitis"
// s.getPaz()      -> {8, 9, 7}
// s.getEgz()      -> 10
```

#### 2. Automatinis ivedimas (std::istringstream)

Duomenys generuojami programos viduje arba suformuojami is eilutes:

```cpp
Studentas s;
std::istringstream iss("Jonas Jonaitis 8 9 7 10");
iss >> s;

// Rezultatas identiskas rankiniam ivedimui
// s.getVardas()  -> "Jonas"
// s.getEgz()     -> 10
// s.getPaz()     -> {8, 9, 7}
```

#### 3. Ivedimas is failo (std::ifstream)

Studentu failas turi antraste ir po jos po viena eilute kiekvienas studentas:

```
Vardas               Pavarde              ND1  ND2  ND3  ND4  ND5  Egz.
Jonas20              Jonaitis20           3    5    7    2    4    6
Petras21             Petraitis21          8    9    6    7    5    8
```

```cpp
std::ifstream failas("studentai.txt");
std::string antraste;
std::getline(failas, antraste);   // praleisti antraste

std::vector<Studentas> studentai;
Studentas s;
while (failas >> s)               // kol yra duomenu
    studentai.push_back(s);

// studentai[0].getVardas()  -> "Jonas20"
// studentai[0].getEgz()     -> 6
// studentai[0].getPaz()     -> {3, 5, 7, 2, 4}
```

---

### operator<< (isvestis)

```cpp
friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
```

**Kaip veikia:** isveda studenta suformatuota eilute. Pirma – vardas ir pavarde (plotis 15 simboliu), tada – pazymiu sarasas lauztuose skliaustuose, egzaminas ir galutinis rezultatas.

**Isvesties formatas:**
```
Jonas          Jonaitis       [8 9 7] Egz: 10  Rez: 9.20
```

#### 1. Isvestis i ekrana (std::cout)

```cpp
Studentas s("Jonas", "Jonaitis", {8, 9, 7}, 10);
s.skaiciuotiRez(1);
std::cout << s << "\n";

// Ekrane:
// Jonas          Jonaitis       [8 9 7] Egz: 10  Rez: 9.20
```

#### 2. Isvestis i faila (std::ofstream)

```cpp
std::vector<Studentas> studentai = { ... };
std::ofstream failas("rezultatai.txt");

for (const auto& s : studentai)
    failas << s << "\n";

// rezultatai.txt turinys:
// Jonas          Jonaitis       [8 9 7] Egz: 10  Rez: 9.20
// Petras         Petraitis      [4 3 5] Egz: 4   Rez: 4.00
```

#### 3. Isvestis i string (std::ostringstream)

Naudinga kai reikia studento duomenis suformatuoti kaip eilute, pvz. logavimui:

```cpp
Studentas s("Jonas", "Jonaitis", {8, 9, 7}, 10);
s.skaiciuotiRez(1);

std::ostringstream oss;
oss << s;
std::string tekstas = oss.str();
// tekstas = "Jonas          Jonaitis       [8 9 7] Egz: 10  Rez: 9.20"
```

### Palyginimo operatoriai

| Operatorius | Palyginimo pagrindas     | Aprasymas                  |
|:-----------:|--------------------------|----------------------------|
| `==`        | vardas + pavarde         | Tie patys duomenys?        |
| `!=`        | vardas + pavarde         | Skirtingi duomenys?        |
| `<`         | galutinis rezultatas     | Mazesnis rezultatas?       |
| `>`         | galutinis rezultatas     | Didesnis rezultatas?       |
| `<=`        | galutinis rezultatas     | Mazesnis arba lygus?       |
| `>=`        | galutinis rezultatas     | Didesnis arba lygus?       |

```cpp
Studentas a("Jonas", "Jonaitis", {9,9}, 9);
Studentas b("Petras", "Petraitis", {4,4}, 4);
a.skaiciuotiRez(1); // rez_ = 9.0
b.skaiciuotiRez(1); // rez_ = 4.0

std::sort(studentai.begin(), studentai.end()); // naudoja operator<
bool islaike = a >= b;                          // true
bool skirtingi = a != b;                        // true (skirtingi vardai)
```

---

## Klases testavimas

Programa turi atskirą testavimo modulį `testavimas_klases.cpp` (parinktis **7** meniu).  
Tikrinamos **7 sekcijos**:

| Sekcija                          | Tikrinamų testu sk. | Aprasymas                                    |
|----------------------------------|:-------------------:|----------------------------------------------|
| Konstruktoriai (Rule of Five)    |         20          | Visi 5 konstruktoriai ir destruktorius        |
| Priskyrimo operatoriai           |         10          | Kopijavimo, perkelimo, grandininis, save=save |
| Palyginimo operatoriai           |         10          | ==, !=, <, >, <=, >=                          |
| Srautu operatoriai               |         13          | >> is istringstream, << i ostringstream       |
| Metodai                          |         14          | vidurkis, mediana, skaiciuotiRez, islaike     |
| Naudojimas su STL                |          3          | std::sort, std::find_if, std::partition       |
| **Viso**                         |       **70+**       |                                               |

### Testo pavyzdys

```
=======================================================
   STUDENTAS KLASES TESTAVIMAS  (v1.2)
=======================================================

--- Konstruktoriai (Rule of Five) ---
  [OK] Numatytasis: vardas tuscias
  [OK] Numatytasis: pavarde tuscia
  [OK] Parametrinis: vardas
  [OK] Kopijavimo: gili kopija (b nepakito)
  [OK] Perkelimo: originalas istusejo
  [OK] Destruktorius: objektas sunaikintas be klaudu

--- Srautu operatoriai ---
  [OK] operator>>: vardas
  [OK] operator>>: egzaminas (paskutinis)
  [OK] operator<<: yra vardas
  [OK] operator<<: yra Rez.

=======================================================
  Rezultatas: 70 / 70 testu pavyko
  Visi testai pavyko!
=======================================================
```

---
### Testas 
<img width="771" height="1262" alt="image" src="https://github.com/user-attachments/assets/c7c1a928-004c-4448-aae7-9cd2d7360dad" />
<img width="809" height="1303" alt="image" src="https://github.com/user-attachments/assets/f9ea4c16-960f-4be9-b7b5-b315e471b0d1" />


## Spartos palyginimas struct vs class

### Testavimo aplinka

| Komponentas    | Parametrai                                    |
|----------------|-----------------------------------------------|
| OS             | Linux x86-64                                  |
| Kompiliatorius | g++ 13, `-std=c++17`                          |
| Konteineris    | `std::vector`                                 |
| Strategija     | S3 (`std::partition`) – greiciausia           |
| Failai         | `studentai100000.txt`, `studentai1000000.txt` |

### 100 000 studentu

| Tipas   | Veliavele | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | **Bendras (s)** | Failo dydis |
|---------|:---------:|:-------------:|:--------------:|:--------------:|:---------------:|:-----------:|
| struct  | -O0       |   0.215042    |   0.117661     |   0.023081     |   **0.355784**  |   323 KB    |
| class   | -O0       |   0.221276    |   0.168335     |   0.019804     |   **0.409415**  |   369 KB    |
| struct  | -O1       |   0.122160    |   0.015939     |   0.008229     |   **0.146328**  |   199 KB    |
| class   | -O1       |   0.125432    |   0.040418     |   0.010156     |   **0.176006**  |   173 KB    |
| struct  | -O2       |   0.117129    |   0.018532     |   0.009067     |   **0.144728**  |   203 KB    |
| class   | -O2       |   0.132843    |   0.060403     |   0.009287     |   **0.202533**  |   174 KB    |
| struct  | -O3       |   0.154266    |   0.019151     |   0.009373     |   **0.182790**  |   254 KB    |
| class   | -O3       |   0.128392    |   0.038806     |   0.008507     |   **0.175704**  |   187 KB    |

### 1 000 000 studentu

| Tipas   | Veliavele | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | **Bendras (s)** | Failo dydis |
|---------|:---------:|:-------------:|:--------------:|:--------------:|:---------------:|:-----------:|
| struct  | -O0       |   2.028479    |   1.432467     |   0.282285     |   **3.743231**  |   323 KB    |
| class   | -O0       |   2.102207    |   2.087393     |   0.277633     |   **4.467233**  |   369 KB    |
| struct  | -O1       |   1.278890    |   0.240549     |   0.130847     |   **1.650287**  |   199 KB    |
| class   | -O1       |   1.337855    |   0.571944     |   0.117793     |   **2.027592**  |   173 KB    |
| struct  | -O2       |   1.300151    |   0.296427     |   0.124121     |   **1.720699**  |   203 KB    |
| class   | -O2       |   1.406447    |   0.601851     |   0.096913     |   **2.105210**  |   174 KB    |
| struct  | -O3       |   1.297984    |   0.242435     |   0.132090     |   **1.672509**  |   254 KB    |
| class   | -O3       |   1.326707    |   0.547100     |   0.087980     |   **1.961786**  |   187 KB    |

---

## Optimizavimo veliaveliuanalize

### Pastebejmai

**struct vs class:**
- **-O0:** `class` versija letesne ~15-19%. Rusiavimas letesnis, nes getter'iai (`getRez()`) nera inline'inti – kiekvienas palyginimas `std::sort` viduje reikalauja funkcijos iskvietimo.
- **-O1/O2/O3:** Skirtumas islieka ~17-22%. Skirstymo fazeje abu praktiskai vienodi.
- `class` versijos **exe failas mazesnis** su -O1/O2/O3 – kompiliatorius efektyviau inline'ina metodus.

**Optimizavimo lygiai:**
- **-O0 -> -O1** didziausias pagreitejimas: ~2-2.5x abiem versijoms.
- **-O1 -> -O2** minimalus pokytis – I/O dominuoja ir mazai reaguoja i optimizavima.
- **-O2 -> -O3** taip pat nereiksminggas – kodas nera SIMD/vektorizacijos kandidatas.

**Exe failo dydis:**
- Maziausia failas: `class` + `-O1` (173 KB).
- Didziausia failas: `struct` + `-O3` (254 KB) – del loop unrolling.

**Rekomendacija:** naudoti **`-O2`** – geriausias greicio ir failo dydzio balansas.

---

## Reliazu aprasas

### v1.5
- Sukurta abstrakti bazine klase `Zmogus` su grynai virtualiu destruktoriumi.
- `Studentas` isvestine is `Zmogus` – paveldi `vardas_`, `pavarde_` ir ju metodus.
- Rule of Five realizuotas abiejose klasese – `Studentas` konstruktoriai kviecia `Zmogus` konstruktorius.
- Priskyrimo operatoriai kviecia `Zmogus::operator=`.
- Polimorfizmas – `Zmogus*` rodykle gali rodyti i `Studentas` objekta.
- Virtualus `print()` metodas – `operator<<(Zmogus&)` veikia per virtual dispatch.
- Pridetas naujas testas `testuoti_zmogus_abstrakti()` – 8 papildomi patikrinimai.
- Visi v1.2 testai islaikyti – 91/91 pavyko.
  
### v1.2
- Papildyti visi palyginimo operatoriai: `!=`, `<=`, `>=`.
- Sukurtas issamaus klases testavimo modulis `testavimas_klases.cpp`.
- Testuojami visi Rule of Five metodai, srautu operatoriai, metodai ir STL integracija.
- Atnaujintas `README.md` su operatoriu aprasymu ir naudojimo pavyzdziais.
- Prideta 7 meniu parinktis – klases testavimas.

### v1.1
- Studento struktura (`struct`) pakeista i klase (`class`).
- Realizuoti visi Rule of Five konstruktoriai ir destruktorius.
- Realizuoti srautu operatoriai `<<` ir `>>`.
- Viena universali `Studentas` klase visiems STL konteineriams.
- Atliktas spartos palyginimas: `struct` vs `class`.

### v1.0
- Realizuotos 3 skirstymo strategijos (S1/S2/S3) visiems trims konteineriams.
- Naudojami STL algoritmai: `std::copy_if`, `std::remove_if`, `std::partition`, `list::splice`.
- Lyginamasis tyrimas: 3 konteineriai x 3 strategijos x 5 failu dydziai.
- Pridetas `Makefile`.
