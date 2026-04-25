#include "vector.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>

void ivesti_pazymius(StudentasV& s, int paz)
{
    s.paz.push_back(paz);
}

double vidurkis(const std::vector<int>& paz)
{
    if (paz.empty()) return 0.00;

    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    return suma / paz.size();
}

double mediana(const std::vector<int>& paz)
{
    if (paz.empty()) return 0.00;

    std::vector<int> temp = paz;
    std::sort(temp.begin(), temp.end());

    size_t n = temp.size();
    if (n % 2 == 0)
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    else
        return temp[n / 2];
}

void pasirinkimo_metodas(int tipas, std::vector<StudentasV>& studentai)
{
    for (auto& studentas : studentai) {
        double x;
        if (tipas == 1) {
            x = vidurkis(studentas.paz);
        }
        else {
            x = mediana(studentas.paz);
        }
        studentas.rez = galutinis_vid(x, studentas.egz);
    }
}

void isvedimas(const std::vector<StudentasV>& studentai, int metodas)
{
    std::string rez = (metodas == 1) ? "Galutinis (vidurkis)" : "Galutinis (mediana)";
    std::cout << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(15) << "Pavarde"
        << std::right << std::setw(20) << rez << std::endl;

    for (const auto& studentas : studentai) {
        std::cout << std::left << std::setw(15) << studentas.vardas
            << std::setw(15) << studentas.pavarde
            << std::right << std::setw(20) << std::fixed
            << std::setprecision(2) << studentas.rez << std::endl;
    }
}

void skaitymas_is_failo(const std::string& filename, std::vector<StudentasV>& studentai) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << filename << "\n";
        return;
    }
    studentai.clear();

    std::string header;
    std::getline(file, header);

    std::string line;
    int line_number = 0;

    try {
        while (std::getline(file, line)) {
            line_number++;
            std::stringstream ss(line);
            StudentasV s;
            ss >> s.vardas >> s.pavarde;
            int value;
            while (ss >> value) {
                s.paz.push_back(value);
            }

            if (!s.paz.empty()) {
                s.egz = s.paz.back();
                s.paz.pop_back();
            }
            else {
                std::cerr << "Klaida eiluteje " << line_number << ": nera pazymiu\n";
                continue;
            }

            studentai.push_back(std::move(s));
            if (line_number % 1000000 == 0) {
                std::cout << "Nuskaityta: " << line_number << " studentu...\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida nuskaitymo metu: " << e.what() << "\n";
    }

    std::cout << "Is viso nuskaityta: " << studentai.size() << " studentu\n";
}

bool pagal_varda(const StudentasV& a, const StudentasV& b) {
    return a.vardas < b.vardas;
}
bool paga_pavarde(const StudentasV& a, const StudentasV& b) {
    return a.pavarde < b.pavarde;
}
bool pagal_rez(const StudentasV& a, const StudentasV& b) {
    return a.rez < b.rez;
}
bool pagal_varda_maz(const StudentasV& a, const StudentasV& b) {
    return a.vardas > b.vardas;
}
bool paga_pavarde_maz(const StudentasV& a, const StudentasV& b) {
    return a.pavarde > b.pavarde;
}
bool pagal_rez_maz(const StudentasV& a, const StudentasV& b) {
    return a.rez > b.rez;
}

void rusiavimas(std::vector<StudentasV>& studentai, int rusiavimo_budas) {
    switch (rusiavimo_budas) {
    case 1: std::sort(studentai.begin(), studentai.end(), pagal_varda);      break;
    case 2: std::sort(studentai.begin(), studentai.end(), pagal_varda_maz);  break;
    case 3: std::sort(studentai.begin(), studentai.end(), paga_pavarde);     break;
    case 4: std::sort(studentai.begin(), studentai.end(), paga_pavarde_maz); break;
    case 5: std::sort(studentai.begin(), studentai.end(), pagal_rez);        break;
    case 6: std::sort(studentai.begin(), studentai.end(), pagal_rez_maz);    break;
    default: std::cerr << "Neteisingas rusiavimo budas. Nenaudojamas rusiavimas.\n"; break;
    }
}

int pasirinkimas_rusiavimo_budo() {
    int pasirinkimas;
    std::cout << "Pasirinkite rusiavimo buda:\n";
    std::cout << "1 - pagal varda didejanciai\n";
    std::cout << "2 - pagal varda mazejanciai\n";
    std::cout << "3 - pagal pavarde didejanciai\n";
    std::cout << "4 - pagal pavarde mazejanciai\n";
    std::cout << "5 - pagal galutini rezultata didejanciai\n";
    std::cout << "6 - pagal galutini rezultata mazejanciai\n";
    std::cin >> pasirinkimas;
    if (std::cin.fail() || pasirinkimas < 1 || pasirinkimas > 6) {
        std::cerr << "Neteisingas pasirinkimas. Nenaudojamas rusiavimas.\n";
        return 0;
    }
    return pasirinkimas;
}

int isvedimo_budas() {
    int pasirinkimas;
    std::cout << "Pasirinkite isvedimo buda:\n";
    std::cout << "1 - i ekrana\n";
    std::cout << "2 - i faila\n";
    std::cin >> pasirinkimas;
    if (std::cin.fail() || pasirinkimas < 1 || pasirinkimas > 2) {
        std::cerr << "Neteisingas pasirinkimas. Naudojamas isvedimas i ekrana.\n";
        return 1;
    }
    return pasirinkimas;
}

void spausdinimas_i_faila(const std::vector<StudentasV>& studentai, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Nepavyko atidaryti failo rezultatai.txt\n";
        return;
    }
    try {
        out << std::left << std::setw(15) << "Vardas"
            << std::left << std::setw(15) << "Pavarde"
            << std::right << std::setw(20) << "Galutinis (rezultatas)" << "\n";
        for (const auto& studentas : studentai) {
            out << std::left << std::setw(15) << studentas.vardas
                << std::left << std::setw(15) << studentas.pavarde
                << std::right << std::setw(20) << std::fixed
                << std::setprecision(2) << studentas.rez << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida spausdinant i faila: " << e.what() << "\n";
    }
}

void skirstymas_i_grupes(
    const std::vector<StudentasV>& visi,
    std::vector<StudentasV>& kieti,
    std::vector<StudentasV>& vargsai
) {
    for (const auto& s : visi) {
        if (s.rez >= 5.0) kieti.push_back(s);
        else               vargsai.push_back(s);
    }
}

void isvedimas_i_faila(
    const std::vector<StudentasV>& studentai,
    const std::string& filename,
    const std::string& kategorija
) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);
    }

    out << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::right << std::setw(20) << "Galutinis" << "\n"
        << std::string(60, '-') << "\n";

    for (const auto& s : studentai) {
        out << std::left << std::setw(20) << s.vardas
            << std::setw(20) << s.pavarde
            << std::right << std::setw(20) << std::fixed
            << std::setprecision(2) << s.rez << "\n";
    }

    out.close();
    std::cout << "Kategorija '" << kategorija << "': "
        << studentai.size() << " studentu issaugota i "
        << filename << "\n";
}

// ============================================================
// STRATEGIJA 1 - du nauji konteineriai su kopijomis (std::copy_if)
// orginalas lieka nepakeistas
// ============================================================

double skirstymas_s1(const std::vector<StudentasV>& studentai,
    std::vector<StudentasV>& kieti,
    std::vector<StudentasV>& vargsai) {
    auto t0 = std::chrono::high_resolution_clock::now();
    kieti.clear();
    vargsai.clear();
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(kieti),
        [](const StudentasV& s) { return s.rez >= 5.0; });
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(vargsai),
        [](const StudentasV& s) { return s.rez < 5.0; });
    return std::chrono::duration<double>(
        std::chrono::high_resolution_clock::now() - t0).count();
}

// ============================================================
// STRATEGIJA 2 - vienas naujas konteineris + erase/remove_if
// po operacijos originalas lieka tik kietiakai
// ============================================================

double skirstymas_s2(std::vector<StudentasV>& studentai,
    std::vector<StudentasV>& vargsai) {
    auto t0 = std::chrono::high_resolution_clock::now();
    vargsai.clear();
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(vargsai),
        [](const StudentasV& s) { return s.rez < 5.0; });
    studentai.erase(
        std::remove_if(studentai.begin(), studentai.end(),
            [](const StudentasV& s) { return s.rez < 5.0; }),
        studentai.end());
    return std::chrono::duration<double>(
        std::chrono::high_resolution_clock::now() - t0).count();
}

// ============================================================
// STRATEGIJA 3 - std::partition (greiciausia vector atveju)
// po operacijos originalas lieka tik kietiakai
// ============================================================

double skirstymas_s3(std::vector<StudentasV>& studentai,
    std::vector<StudentasV>& vargsai) {
    auto t0 = std::chrono::high_resolution_clock::now();
    vargsai.clear();
    auto pivot = std::partition(studentai.begin(), studentai.end(),
        [](const StudentasV& s) { return s.rez >= 5.0; });
    vargsai.assign(pivot, studentai.end());
    studentai.erase(pivot, studentai.end());
    return std::chrono::duration<double>(
        std::chrono::high_resolution_clock::now() - t0).count();
}