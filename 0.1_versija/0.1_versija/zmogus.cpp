#include "zmogus.h"

// --- Numatytasis konstruktorius ---
Zmogus::Zmogus()
    : vardas_(""), pavarde_("") {
}

// --- Parametrinis konstruktorius ---
Zmogus::Zmogus(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {
}

// --- Kopijavimo konstruktorius ---
Zmogus::Zmogus(const Zmogus& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_) {
}

// --- Perkelimo konstruktorius ---
Zmogus::Zmogus(Zmogus&& other) noexcept
    : vardas_(std::move(other.vardas_)),
    pavarde_(std::move(other.pavarde_)) {
}

// --- Grynas virtualus destruktorius – turi tureti realizacija ---
// Net ir grynas virtualus destruktorius privalo buti realizuotas,
// nes isvestines klases destruktorius ji isskviecia grandinine tvarka.
Zmogus::~Zmogus() {}

// --- Kopijavimo priskyrimo operatorius ---
Zmogus& Zmogus::operator=(const Zmogus& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
    }
    return *this;
}

// --- Perkelimo priskyrimo operatorius ---
Zmogus& Zmogus::operator=(Zmogus&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
    }
    return *this;
}