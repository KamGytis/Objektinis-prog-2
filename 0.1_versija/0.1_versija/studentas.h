#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

// 
// Isvestine klase Studentas : public Zmogus
//
// Paveldi is abstrakcios klases Zmogus:
//   - vardas_, pavarde_ laukus
//   - getVardas(), getPavarde(), setVardas(), setPavarde()
//   - Rule of Five is bazines klases
//
// Papildo savo laukais: paz_, egz_, rez_
// Realizuoja gryna virtualu metoda: print()
// 

class Studentas : public Zmogus {
private:
    std::vector<int> paz_;
    int egz_;
    double rez_;

public:
    // Konstruktoriai 

    // Numatytasis konstruktorius
    Studentas();

    // Parametrinis konstruktorius
    Studentas(const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& paz,
        int egz);

    // Kopijavimo konstruktorius
    Studentas(const Studentas& other);

    // Perkelimo konstruktorius
    Studentas(Studentas&& other) noexcept;

    // Destruktorius
    ~Studentas();

    //  Priskyrimo operatoriai 
    Studentas& operator=(const Studentas& other);
    Studentas& operator=(Studentas&& other) noexcept;

    //  Palyginimo operatoriai 
    bool operator<(const Studentas& other) const;
    bool operator>(const Studentas& other) const;
    bool operator==(const Studentas& other) const;
    bool operator<=(const Studentas& other) const;
    bool operator>=(const Studentas& other) const;
    bool operator!=(const Studentas& other) const;

    // Prideti pazymi: s += 8
    Studentas& operator+=(int pazymys);

    // Prieiga prie paz_[i]
    int  operator[](size_t i) const;
    int& operator[](size_t i);

    // SRAUTU OPERATORIAI

    // Isveda: Vardas  Pavarde  [paz1 ... pazN]  Egz: E  Rez: R
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);

    // Nuskaito eilute: Vardas Pavarde paz1 paz2 ... pazN egz
    friend std::istream& operator>>(std::istream& is, Studentas& s);

    // 
    // Virtualus metodas – realizuoja bazines klases gryna virtualu metoda
    // 

    void print(std::ostream& os) const override;

    // 
    // GETTERIAI
    // 

    const std::vector<int>& getPaz()         const { return paz_; }
    int                     getEgz()         const { return egz_; }
    double                  getRez()         const { return rez_; }
    size_t                  getPazSkaicius() const { return paz_.size(); }

    // 
    // SETTERIAI
    // 

    void setEgz(int e) { egz_ = e; }
    void setRez(double r) { rez_ = r; }

    // 
    // METODAI
    // 

    void   addPazymys(int p);
    void   clearPazymiai();
    double vidurkis() const;
    double mediana()  const;
    void   skaiciuotiRez(int tipas); // 1=vidurkis, 2=mediana
    bool   islaike() const { return rez_ >= 5.0; }
};

#endif 