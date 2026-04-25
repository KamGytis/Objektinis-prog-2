#ifndef DEQUE_OPS_H
#define DEQUE_OPS_H

#include "studentas.h"
#include <deque>
#include <string>

void skaitymas_is_failo_d(const std::string& filename, std::deque<Studentas>& studentai);
void isvedimas_i_faila_d(const std::deque<Studentas>& studentai,
    const std::string& filename,
    const std::string& kategorija);
void pasirinkimo_metodas_d(int tipas, std::deque<Studentas>& studentai);
void rusiavimas_d(std::deque<Studentas>& studentai);

// Originali strategija
double skirstymas_i_grupes_d(const std::deque<Studentas>& visi,
    std::deque<Studentas>& kieti,
    std::deque<Studentas>& vargsai);

// STRATEGIJA 1 du nauji konteineriai, originalas lieka nepakeistas
double skirstymas_s1_d(const std::deque<Studentas>& visi,
    std::deque<Studentas>& kieti,
    std::deque<Studentas>& vargsai);

// STRATEGIJA 2 vienas naujas konteineris + erase/remove if
double skirstymas_s2_d(std::deque<Studentas>& studentai,
    std::deque<Studentas>& vargsai);

// STRATEGIJA 3 std::partition
double skirstymas_s3_d(std::deque<Studentas>& studentai,
    std::deque<Studentas>& vargsai);

#endif
