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
	tikrinti(a.getPazSkaicius() == 0, "Numatytasis paz saras tuscias");

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

	tikrinti(c.getVardas() == b.getVardas(), "Kopijavimo vardas sutampa");
	tikrinti(c.getPavarde() == b.getPavarde(), "Kopijavimo pavarde sutampa");
	tikrinti(c.getEgz() == b.getEgz(), "Kopijavimo egzaminas sutampa");
	tikrinti(c.getPazSkaicius() == b.getPazSkaicius(), "Kopijavimo paz skaicius sutampa");
	tikrinti(c.getPaz() == b.getPaz(), "Kopijavimo pazymiai sutampa");
	c.setVardas("Petras");
	tikrinti(b.getVardas() == "Jonas", "Kopijavimo gili kopija (b) nepakito");

	//Perkelimo konstruktorius

	Studentas d_orig("Ona", "Onaite", {5, 6}, 7);
	Studentas d(std::move(d_orig));
	tikrinti(d.getVardas() == "Ona", "Perkelimo vardas");
	tikrinti(d.getPavarde() == "Onaite", "Perkelimo pavarde");
	tikrinti(d.getEgz() == 7, "Perkelimo egzaminas");
	tikrinti(d.getPazSkaicius() == 2, "Perkelimo paz skaicius");
	tikrinti(d_orig.getPazSkaicius() == 0, "Perkelimo orginalas tuscias");
	tikrinti(d_orig.getVardas() == "", "Perkelimo orginalo vardas tuscias");


	//Destruktorius.

	{
		Studentas laikinas("Laikinas", "Laikinaitis", { 1, 2 }, 3);
		(void)laikinas; // Kad destruktorius nebutu pazymetas kaip nenaudojamas
		}
	tikrinti(true, "Destruktorius iskvieciamas (neuzstringa)");
	}


static void testuoti_priskyrima() {
	sekcija("Priskyrimo operatoriai (Rule of Five)");

	Studentas a("Jonas", "Jonaitis", { 8, 9}, 10);
	Studentas b;

	//kopijavimo priskyrimo operatorius
	b = a;
	tikrinti(b.getVardas() == "Jonas", "Kopijavimo priskyrimo vardas");
	tikrinti(b.getPavarde() == "Jonaitis", "Kopijavimo priskyrimo pavarde");
	tikrinti(b.getEgz() == 10, "Kopijavimas priskyrimas egz");
	tikrinti(b.getPaz() == a.getPaz(), "Kopijavimo priskyrimo pazymiai sutampa");
	//Gilios kopijos tikrinimas
	b.setVardas("kitas");
	tikrinti(a.getVardas() == "Jonas", "Kopijavimo priskyrimo gili kopija (a) nepakito");

	//saves priskyrimo operatorius
	a = a;
	tikrinti(a.getVardas() == "Jonas", "Saves priskyrimo vardas nepakito");

	//perkelimo priskyrimo operatorius

	Studentas c("Ona", "Onaite", { 5, 6 }, 7);
	Studentas d;
	d = std::move(c);
	tikrinti(d.getVardas() == "Ona", "Perkelimo priskyrimo vardas");
	tikrinti(d.getPazSkaicius() == 2, "Perkelimo priskyrimo paz skaicius");
	tikrinti(c.getVardas() == "", "Perkelimo priskyrimo originalo vardas tuscias");

	//Grandininis priskyrimas
	Studentas x("A", "B", { 1 }, 2);
	Studentas y, z;
	z = y = x;
	tikrinti(y.getVardas() == "A" && z.getVardas() == "A", "Grandininis priskyrimas y = z = x");
}
