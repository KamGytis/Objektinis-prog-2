#include "utils.h"
#include <iostream>
#include <limits>

std::string ivesti_varda_ar_pavarde(const std::string& zinute)
{
    std::string tekstas;
    while (true) {
        std::cout << zinute;
        std::cin >> tekstas;
        if (!tekstas.empty()) {
            return tekstas;
        }
        std::cout << "Ivestis negali buti tuscia\n";
    }
}

int ivesties_tikrinimas(const std::string& zinute)
{
    int value;
    while (true)
    {
        std::cout << zinute;
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cout << "Ivestis turi buti skaicius, bandykite dar karta\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (value == -1 || (value >= 0 && value <= 10))
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Ivestis turi buti tarp 0 ir 10 (arba -1 baigti)\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int ivesties_skaicius(const std::string& zinute)
{
    int value;
    while (true)
    {
        std::cout << zinute;
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cout << "Ivestis turi buti skaicius, bandykite dar karta\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (value >= 1)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Ivestis turi buti teigiamas skaicius\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int skaiciavimo_metodas()
{
    int metodas;
    while (true) {
        std::cout << "Pasirinkite skaiciavimo metoda (1 - vidurkis, 2 - mediana): ";
        if (!(std::cin >> metodas)) {
            std::cout << "Ivestis turi buti skaicius 1 arba 2, bandykite dar karta\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (metodas == 1 || metodas == 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return metodas;
        }
        std::cout << "Neteisingas pasirinkimas. Pasirinkite 1 arba 2.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double galutinis_vid(double x, int egz)
{
    return x * 0.4 + egz * 0.6;
}