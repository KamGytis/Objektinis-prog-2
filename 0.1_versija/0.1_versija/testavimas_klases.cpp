#include "studentas.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iomanip>

//Pagalbines funkcijos testavimui

static int testai_is_viso = 0;
static int testai_pavyke = 0;

static void tikrinti(bool salyga, const std::string& pavadinimas) {
	++testai_is_viso;
	if (salyga) {
		++testai_pavyke;
		std::cout << "Testas pavykes: " << pavadinimas << "\n";
	}
	else {
		std::cout << "Testas nepavykes: " << pavadinimas << "\n";
	}
}

static void sekcija (const std::string& pavadinimas) {
	std::cout << "\n======= " << pavadinimas << " =======\n";
}

// Testavimas

static void testuoti_konstruktorius() {
	sekcija("Konstruktoriai (Rules of five)");

	//Numatyti konstruktoriai

	Studentas a;
	tikrinti(a.getVardas() == "", "Numatytasis vardas tuscias");
	tikrinti(a.getPavarde() == "", "Numatytasis pavarde tuscias");
	tikrinti(a.getEgz() == 0, "Numatytasis egzaminas 0");
	tikrinti(a.getRez() == 0.0, "Numatytasis rezultatas 0.0");
	tikrinti(a.getPaz() == 0, "Numatytasis paz saras tuscias");

	//Parametriniai konstruktoriai

	Studentas b("Jonas", "Jonaitis", { 8, 9, 7 }, 10);
	tikrinti(b.getVardas() == "Jonas", "Parametrinis vardas");
	tikrinti(b.getPavarde() == "Jonaitis", "Parametrinis pavarde");
	tikrinti(b.getEgz() == 10, "Parametrinis egzaminas");
	tikrinti(b.getRez() == 0.0, "Parametrinis rezultatas (prieš skaiciavima)");
	tikrinti(b.getPazSkaicius() == 3, "Parametrinis paz skaicius");
	tikrinti(b.getPaz()[0] ==8, "Parametrinis pazymiai paz[0] = 8");

	//Kopijavimo konstruktorius

	Studentas c(b);

	tikrinti(c.getVardas() == b.getVardas, "Kopijavimo vardas sutampa");
	tikrinti(c.getPavarde() == b.getPavarde(), "Kopijavimo pavarde sutampa");
	tikrinti(c.getEgz() == b.getEgz(), "Kopijavimo egzaminas sutampa");
	tikrinti(c.getPazSkaicius() == b.getPazSkaicius(), "Kopijavimo paz skaicius sutampa");
	tikrinti(c.getPaz() == b.getPaz(), "Kopijavimo pazymiai sutampa");
	c.setVardas("Petras");
	tikrinti(b.getVardas() == "Jonas", "Kopijavimo gili kopija (b) nepakito");