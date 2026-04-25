#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include "studentas.h"
#include <vector>
#include <string>

// Skaitymas ir isvedimas
void skaitymas_is_failo(const std::string& filename, std::vector<Studentas>& studentai);
void isvedimas(const std::vector<Studentas>& studentai, int metodas);
void isvedimas_i_faila(const std::vector<Studentas>& studentai,
    const std::string& filename,
    const std::string& kategorija);

// Skaiciavimai
void pasirinkimo_metodas(int tipas, std::vector<Studentas>& studentai);

// rusiavimas
void rusiavimas(std::vector<Studentas>& studentai, int budas);
int  pasirinkimas_rusiavimo_budo();

// skirtstymas i grupes
void   skirstymas_i_grupes(const std::vector<Studentas>& visi,
    std::vector<Studentas>& kieti,
    std::vector<Studentas>& vargsai);

double skirstymas_s1(const std::vector<Studentas>& studentai,
    std::vector<Studentas>& kieti,
    std::vector<Studentas>& vargsai);

double skirstymas_s2(std::vector<Studentas>& studentai,
    std::vector<Studentas>& vargsai);

double skirstymas_s3(std::vector<Studentas>& studentai,
    std::vector<Studentas>& vargsai);

#endif
