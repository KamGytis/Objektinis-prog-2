#ifndef LIST_OPS_H
#define LIST_OPS_H

#include "studentas.h"
#include <list>
#include <string>

void skaitymas_is_failo_l(const std::string& filename, std::list<Studentas>& studentai);
void isvedimas_i_faila_l(const std::list<Studentas>& studentai,
    const std::string& filename,
    const std::string& kategorija);
void pasirinkimo_metodas_l(int tipas, std::list<Studentas>& studentai);
void rusiavimas_l(std::list<Studentas>& studentai);

// Originali strategija
double skirstymas_i_grupes_l(const std::list<Studentas>& visi,
    std::list<Studentas>& kieti,
    std::list<Studentas>& vargsai);

// STRATEGIJA 1 du nauji konteineriai, originalas lieka nepakeistas
double skirstymas_s1_l(const std::list<Studentas>& visi,
    std::list<Studentas>& kieti,
    std::list<Studentas>& vargsai);

// STRATEGIJA 2 vienas naujas konteineris + erase/remove if
double skirstymas_s2_l(std::list<Studentas>& studentai,
    std::list<Studentas>& vargsai);

// STRATEGIJA 3 splice - nulines kopijos
double skirstymas_s3_l(std::list<Studentas>& studentai,
    std::list<Studentas>& vargsai);

#endif
