#pragma once
#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

// 
// Abstrakti bazine klase Zmogus
//
// Negalima sukurti Zmogus tipo objektu tiesiogiai –
// klase abstrakti del grynai virtualaus destruktoriaus.
// Is jos galima kurti tik isvesdines klases (pvz. Studentas).
// 

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    // --- Konstruktoriai (Rule of Five) ---

    Zmogus();
    Zmogus(const std::string& vardas, const std::string& pavarde);
    Zmogus(const Zmogus& other);
    Zmogus(Zmogus&& other) noexcept;

    // Grynas virtualus destruktorius – daro klase abstrakcia
    // Isvestines klases privalo override'inti
    virtual ~Zmogus() = 0;

    // --- Priskyrimo operatoriai (Rule of Five) ---

    Zmogus& operator=(const Zmogus& other);
    Zmogus& operator=(Zmogus&& other) noexcept;

    // --- Getteriai ---

    const std::string& getVardas()  const { return vardas_; }
    const std::string& getPavarde() const { return pavarde_; }

    // --- Setteriai ---

    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }

    // --- Grynas virtualus metodas – isvestines klases privalo realizuoti ---

    // Isveda informacija apie objekta i srautua
    virtual void print(std::ostream& os) const = 0;
};

// Globalus isvedimo operatorius naudoja virtual print()
inline std::ostream& operator<<(std::ostream& os, const Zmogus& z) {
    z.print(os);
    return os;
}

#endif // ZMOGUS_H
