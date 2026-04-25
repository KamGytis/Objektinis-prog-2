#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <iomanip>

//  Numatytasis konstruktorius 
Studentas::Studentas()
    : vardas_(""), pavarde_(""), paz_(), egz_(0), rez_(0.0) {
}

//  Parametrinis konstruktorius 
Studentas::Studentas(const std::string& vardas,
    const std::string& pavarde,
    const std::vector<int>& paz,
    int egz)
    : vardas_(vardas), pavarde_(pavarde), paz_(paz), egz_(egz), rez_(0.0) {
}

//  Kopijavimo konstruktorius 
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_),
    pavarde_(other.pavarde_),
    paz_(other.paz_),
    egz_(other.egz_),
    rez_(other.rez_) {
}

// Perkelimo konstruktorius 
Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
    pavarde_(std::move(other.pavarde_)),
    paz_(std::move(other.paz_)),
    egz_(other.egz_),
    rez_(other.rez_) {
    other.egz_ = 0;
    other.rez_ = 0.0;
}

//  Destruktorius 
Studentas::~Studentas() {
    paz_.clear();
}

//  Kopijavimo priskyrimo operatorius 
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        paz_ = other.paz_;
        egz_ = other.egz_;
        rez_ = other.rez_;
    }
    return *this;
}

//  Perkelimo priskyrimo operatorius
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        paz_ = std::move(other.paz_);
        egz_ = other.egz_;
        rez_ = other.rez_;
        other.egz_ = 0;
        other.rez_ = 0.0;
    }
    return *this;
}

// Palyginimo operatoriai (pagal rezultata) 
bool Studentas::operator<(const Studentas& other) const {
    return rez_ < other.rez_;
}
bool Studentas::operator>(const Studentas& other) const {
    return rez_ > other.rez_;
}
bool Studentas::operator==(const Studentas& other) const {
    return vardas_ == other.vardas_ && pavarde_ == other.pavarde_;
}

//  Isvedimo operatorius 
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(20) << s.vardas_
        << std::setw(20) << s.pavarde_
        << std::right << std::setw(20) << std::fixed
        << std::setprecision(2) << s.rez_;
    return os;
}

//  Ivedimo operatorius 
std::istream& operator>>(std::istream& is, Studentas& s) {
    is >> s.vardas_ >> s.pavarde_;
    int v;
    std::string line;
    std::getline(is, line);
    std::istringstream ss(line);
    s.paz_.clear();
    while (ss >> v) s.paz_.push_back(v);
    if (!s.paz_.empty()) {
        s.egz_ = s.paz_.back();
        s.paz_.pop_back();
    }
    return is;
}

// Metodai 
void Studentas::addPazymys(int p) {
    paz_.push_back(p);
}

void Studentas::clearPazymiai() {
    paz_.clear();
}

double Studentas::vidurkis() const {
    if (paz_.empty()) return 0.0;
    return std::accumulate(paz_.begin(), paz_.end(), 0.0) / paz_.size();
}

double Studentas::mediana() const {
    if (paz_.empty()) return 0.0;
    std::vector<int> tmp = paz_;
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    return (n % 2 == 0) ? (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0 : tmp[n / 2];
}

void Studentas::skaiciuotiRez(int tipas) {
    double x = (tipas == 1) ? vidurkis() : mediana();
    rez_ = x * 0.4 + egz_ * 0.6;
}