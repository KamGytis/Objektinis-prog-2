#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
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

	// prideti pazymi prie esamu
    Studentas& operator+=(int pazymys);

	//indeksavimo operatorius - grazina pazymi pagal indeksa
    int  operator[](size_t i) const;
    int& operator[](size_t i);


    //  Srautu operatoriai 
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);

    //  Getteriai 
    const std::string& getVardas()  const { return vardas_; }
    const std::string& getPavarde() const { return pavarde_; }
    const std::vector<int>& getPaz() const { return paz_; }
    int    getEgz() const { return egz_; }
    double getRez() const { return rez_; }
    size_t getPazSkaicius() const { return paz_.size(); }

    // Setteriai 
    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }
    void setEgz(int e) { egz_ = e; }
    void setRez(double r) { rez_ = r; }

    //  Metodai 
    void addPazymys(int p);
    void clearPazymiai();

    double vidurkis() const;
    double mediana()  const;
    void   skaiciuotiRez(int tipas);  // 1 = vidurkis, 2 = mediana
    bool   islaike() const { return rez_ >= 5.0; }
};

#endif 