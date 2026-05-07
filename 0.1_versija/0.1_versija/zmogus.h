#pragma once
#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

/**
 * @class Zmogus
 * @brief Abstrakti bazine klase, atstovaujanti zmogu
 *
 * Negalima sukurti Zmogus tipo objektu tiesiogiai -
 * klase abstrakti del grynai virtualaus destruktoriaus.
 * Is jos galima kurti tik isvestines klases (pvz. Studentas).
 *
 * @author Studentu Valdymo Sistema
 * @version 2.0
 */
class Zmogus {
protected:
	std::string vardas_; // Vardas
	std::string pavarde_; // Pavarde

public:
    // --- Konstruktoriai (Rule of Five) ---

    /**
     * @brief Numatytasis konstruktorius
     * Sukuria tuscia zmogu su tusciais vardu ir pavarde
     */
    Zmogus();

    /**
     * @brief Parametrinis konstruktorius
     * @param vardas Asmens vardas
     * @param pavarde Asmens pavarde
     */
    Zmogus(const std::string& vardas, const std::string& pavarde);

    /**
     * @brief Kopijavimo konstruktorius
     * @param other Zmogus objektas, is kurio kopijuojama
     */
    Zmogus(const Zmogus& other);

    /**
     * @brief Perkelimo konstruktorius
     * @param other Zmogus objektas, is kurio perkeliama
     */

    Zmogus(Zmogus&& other) noexcept;

    /**
     * @brief Virtualus destruktorius
     *
     * Grynas virtualus destruktorius - daro klase abstrakcia.
     * Isvestines klases privalo ji realizuoti.
     */
    virtual ~Zmogus() = 0;

    // --- Priskyrimo operatoriai (Rule of Five) ---

    /**
     * @brief Kopijavimo priskyrimo operatorius
     * @param other Zmogus objektas, is kurio kopijuojama
     * @return Nuoroda i si objekta
     */
    Zmogus& operator=(const Zmogus& other);

    /**
     * @brief Perkelimo priskyrimo operatorius
     * @param other Zmogus objektas, is kurio perkeliama
     * @return Nuoroda i si objekta
     */
    Zmogus& operator=(Zmogus&& other) noexcept;

    // --- Getteriai ---

    /** @return Asmens vardas */
    const std::string& getVardas()  const { return vardas_; }

    /** @return Asmens pavarde */
    const std::string& getPavarde() const { return pavarde_; }

    // --- Setteriai ---

     /** @param v Naujas vardas */
    void setVardas(const std::string& v) { vardas_ = v; }

    /** @param p Nauja pavarde */
    void setPavarde(const std::string& p) { pavarde_ = p; }

    // --- Grynas virtualus metodas – isvestines klases privalo realizuoti ---

    /**
     * @brief Grynas virtualus metodas spausdinimui
     * @param os Isvesties srautas
     *
     * Isvestines klases privalo realizuoti si metoda.
     * Naudojamas operator<< globaliame operatoriuje.
     */
    virtual void print(std::ostream& os) const = 0;
};

/**
 * @brief Globalus isvedimo operatorius
 * @param os Isvesties srautas
 * @param z Nuoroda i Zmogus objekta
 * @return Nuoroda i isvesties srauta
 *
 * @details Naudoja virtualu print() metoda polimorfizmui uztikrinti
 */
inline std::ostream& operator<<(std::ostream& os, const Zmogus& z) {
    z.print(os);
    return os;
}

#endif // ZMOGUS_H
