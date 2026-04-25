# Studentų programa v1.1

Programa skirta studentų duomenų valdymui naudojant C++ klases ir STL konteinerius.

---

## Turinys
1. [Reikalavimai](#reikalavimai)
2. [Įdiegimo instrukcija](#įdiegimo-instrukcija)
3. [Naudojimo instrukcija](#naudojimo-instrukcija)
4. [Repozitorijos klonavimas](#repozitorijos-klonavimas)
5. [Pakeitimai v1.0 → v1.1](#pakeitimai-v10--v11)
6. [Spartos palyginimas: struct vs class](#spartos-palyginimas-struct-vs-class)
7. [Optimizavimo vėliavėlių analizė](#optimizavimo-vėliavėlių-analizė)
8. [Relizų aprašas](#relizų-aprašas)

---

## Reikalavimai

- C++17 kompiliatorius (`g++` arba MSVC 2019+)
- Windows / Linux / macOS
- `make` (Linux/macOS kompiliavimui)

---

## Įdiegimo instrukcija

### Linux / macOS

```bash
git clone https://github.com/USERNAME/studentai_v11.git
cd studentai_v11
make
./studentai
```

### Makefile komandos

```bash
make        # Kompiliuoti be optimizavimo
make O1     # Kompiliuoti su -O1
make O2     # Kompiliuoti su -O2
make O3     # Kompiliuoti su -O3
make clean  # Ištrinti sukompiliuotus failus
```

### Windows (Visual Studio)

Atidaryti `.sln` failą ir spausti **Build → Build Solution**, tada paleisti `studentai.exe`.

---

## Naudojimo instrukcija

```
======= STUDENTU PROGRAMA v1.1 (class) =======
1 - Rankinis ivedimas
2 - Skaityti is failo (vector)
3 - Skaityti is failo (list)
4 - Skaityti is failo (deque)
5 - Testavimas (visi konteineriai)
6 - Generuoti studentu failus
7 - Baigti
```

- **1 parinktis** – rankinis duomenų įvedimas: vardas, pavardė, pažymiai, egzaminas, rezultato išvedimas.
- **2–4 parinktis** – skaitymas iš pasirinkto `.txt` failo su pasirinktu konteineriu, rūšiavimas ir skirstymas į grupes.
- **5 parinktis** – automatinis testavimas visais konteineriais ir strategijomis, rezultatai išvedami į terminalą.
- **6 parinktis** – studentų failų generavimas (1k, 10k, 100k, 1M, 10M įrašų).
- **7 parinktis** – programos nutraukimas.

**Rekomenduojama tvarka:**
1. Pasirinkti **6 → 1** – sugeneruoti testų failus.
2. Pasirinkti **5** – atlikti lyginamąjį testavimą.

---

## Repozitorijos klonavimas

v1.1 sukurta remiantis v1.0 repozitorija – išsaugota visa ankstesnė git istorija.

```bash
# 1. Nukopijuoti lokaliai seną repozitoriją
cp -r studentai_v10/ studentai_v11/
cd studentai_v11/

# 2. Pakeisti nuotolinį adresą į naują repozitoriją
git remote set-url origin https://github.com/USERNAME/studentai_v11.git

# 3. Nupushinti su visa istorija
git push -u origin master

# 4. Sukurti v1.1 release
git tag v1.1
git push origin v1.1
```

---

## Pakeitimai v1.0 → v1.1

### Struktūros → Klasės perėjimas

`v1.0` naudojo atskiras struktūras kiekvienam konteineriui: `StudentasV`, `StudentasL`, `StudentasD`.  
`v1.1` naudoja **vieną universalią klasę `Studentas`**, tinkančią visiems STL konteineriams.

### Klasės `Studentas` realizacija

```cpp
class Studentas {
private:
    std::string      vardas_;
    std::string      pavarde_;
    std::vector<int> paz_;
    int              egz_;
    double           rez_;
public:
    Studentas();                                          // numatytasis konstruktorius
    Studentas(string, string, vector<int>, int);          // parametrinis konstruktorius
    Studentas(const Studentas&);                          // kopijavimo konstruktorius
    Studentas(Studentas&&) noexcept;                      // perkėlimo konstruktorius
    ~Studentas();                                         // destruktorius
    Studentas& operator=(const Studentas&);               // kopijavimo priskyrimas
    Studentas& operator=(Studentas&&) noexcept;           // perkėlimo priskyrimas
    bool operator<(const Studentas&) const;
    bool operator>(const Studentas&) const;
    bool operator==(const Studentas&) const;
    friend std::ostream& operator<<(std::ostream&, const Studentas&);
    friend std::istream& operator>>(std::istream&, Studentas&);
    // getteriai, setteriai, vidurkis(), mediana(), skaiciuotiRez()
};
```

### Failų struktūra

| v1.0 (pašalinti)                  | v1.1 (naudoti)                    |
|-----------------------------------|-----------------------------------|
| `vector.h` + `vector_funkc.cpp`   | `studentas.h` + `studentas.cpp`   |
| `list.h` + `list_funkc.cpp`       | `vector_ops.h` + `vector_ops.cpp` |
| `deque.h` + `deque_funkc.cpp`     | `list_ops.h` + `list_ops.cpp`     |
|                                   | `deque_ops.h` + `deque_ops.cpp`   |

---

## Spartos palyginimas: struct vs class

### Testavimo aplinka

| Komponentas    | Parametrai                                    |
|----------------|-----------------------------------------------|
| OS             | Linux x86-64                                  |
| Kompiliatorius | g++ 13, `-std=c++17`                          |
| Konteineris    | `std::vector`                                 |
| Strategija     | S3 (`std::partition`) – greičiausia strategija|
| Failai         | `studentai100000.txt`, `studentai1000000.txt` |

---

### 100 000 studentų

| Tipas   | Vėliavėlė | Skaitymas (s) | Rūšiavimas (s) | Skirstymas (s) | **Bendras (s)** | Failo dydis |
|---------|:---------:|:-------------:|:--------------:|:--------------:|:---------------:|:-----------:|
| struct  | -O0       |   0.215042    |   0.117661     |   0.023081     |   **0.355784**  |   323 KB    |
| class   | -O0       |   0.221276    |   0.168335     |   0.019804     |   **0.409415**  |   369 KB    |
| struct  | -O1       |   0.122160    |   0.015939     |   0.008229     |   **0.146328**  |   199 KB    |
| class   | -O1       |   0.125432    |   0.040418     |   0.010156     |   **0.176006**  |   173 KB    |
| struct  | -O2       |   0.117129    |   0.018532     |   0.009067     |   **0.144728**  |   203 KB    |
| class   | -O2       |   0.132843    |   0.060403     |   0.009287     |   **0.202533**  |   174 KB    |
| struct  | -O3       |   0.154266    |   0.019151     |   0.009373     |   **0.182790**  |   254 KB    |
| class   | -O3       |   0.128392    |   0.038806     |   0.008507     |   **0.175704**  |   187 KB    |

---

### 1 000 000 studentų

| Tipas   | Vėliavėlė | Skaitymas (s) | Rūšiavimas (s) | Skirstymas (s) | **Bendras (s)** | Failo dydis |
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

## Optimizavimo vėliavėlių analizė

### Pastebėjimai

**struct vs class:**
- **-O0:** `class` versija lėtesnė ~15–19%. Rūšiavimas lėtesnis, nes getter'iai (`getRez()`) nėra inline'inti ir kiekvienas palyginimas `std::sort` viduje reikalauja funkcijos iškvietimo.
- **-O1/O2/O3:** Skirtumas išlieka ~17–22% dėl to, kad `class` versija turi daugiau abstrakcijos sluoksnių, tačiau skirstymo fazėje abu praktiškai vienodi.
- `class` versijos **exe failas mažesnis** su -O1/O2/O3 – kompiliatorius efektyviau inline'ina metodus ir pašalina perteklinį kodą.

**Optimizavimo lygiai:**
- **-O0 → -O1** didžiausias pagreitėjimas: ~2–2.5× abiem versijoms. Pagrindinis inlining, dead-code elimination.
- **-O1 → -O2** minimalus pokytis – I/O (`std::getline`, `std::stringstream`) dominuoja ir mažai reaguoja į optimizavimą.
- **-O2 → -O3** taip pat nereikšmingas – kodas nėra SIMD/vektorizacijos kandidatas.

**Exe failo dydis:**
- Mažiausias failas su `class` + `-O1` (173 KB) – kompiliatorius agresyviai inline'ina ir pašalina nereikalingą kodą.
- Didžiausias failas su `struct` + `-O3` (254 KB) – agresyvios optimizacijos padidina kodo dydį dėl loop unrolling.

**Rekomendacija:** naudoti **`-O1`** arba **`-O2`** – geriausias greičio ir kompiliavimo laiko bei failo dydžio balansas.

---

## Relizų aprašas

### v1.1
- Studento struktūra (`struct`) pakeista į klasę (`class`).
- Realizuoti visi konstruktoriai ir destruktorius (Rule of Five).
- Realizuoti palyginimo operatoriai (`<`, `>`, `==`) ir srautų operatoriai (`<<`, `>>`).
- Vietoj trijų atskirų struktūrų – viena universali `Studentas` klasė visiems konteineriams.
- Atliktas spartos palyginimas: `struct` vs `class` su visais optimizavimo lygiais.
- Atnaujintas `README.md` su matavimų lentelėmis.

### v1.0
- Realizuotos 3 skirstymo strategijos (S1/S2/S3) visiems trims konteineriams.
- Naudojami STL algoritmai: `std::copy_if`, `std::remove_if`, `std::partition`, `list::splice`.
- Lyginamasis tyrimas: 3 konteineriai × 3 strategijos × 5 failų dydžiai.
- Pridėtas `Makefile`.
