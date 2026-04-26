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

static void testuoti_palyginimo_operatorius() {

	sekcija("Palyginimo operatoriai");

	Studentas a("Jonas", "Jonaitis", { 8, 9, 7 }, 10);
	Studentas b("Petras", "Petraitis", { 4, 3, 5 }, 4);
	a.skaiciuotiRez(1); // rez_ = 8.0*0.4 + 10*0.6 = 3.2+6 = 9.2  (vidurkis=(8+9+7)/3=8)
	b.skaiciuotiRez(1); // rez_ = 4.0*0.4 + 4*0.6  = 1.6+2.4 = 4.0

	tikrinti(a > b, "operator>  : a.rez > b.rez");
	tikrinti(b < a, "operator<  : b.rez < a.rez");
	tikrinti(a >= b, "operator>= : a.rez >= b.rez");
	tikrinti(b <= a, "operator<= : b.rez <= a.rez");

	//Lygybe - pagal varda ir pavarde

	Studentas c("Jonas", "Jonaitis", { 1 }, 1);
	tikrinti(a == c, "operator== : tas pats vardas ir pavarde");
	tikrinti(a != b, "operator!= : skirtingas vardas ir pavarde");

	//lygus sau
	tikrinti(a == a, "operator== : lygus sau");
	tikrinti(!(a != a), "operator!= : nelygus sau");

	// <= ir >= su lygiais rezultatais

	Studentas d("Dalia", "Dalaite", { 8, 9 ,7 }, 10);
	d.skaiciuotiRez(1); //tas patas rezultatas kaip a, bet skirtingas vardas ir pavarde
	tikrinti(a <= d, "operator<= lygus rez (a <= d)");
	tikrinti(a >= d, "operator>= lygus rez (a >= d)");

}

static void testuoti_sudetinius_operatorius() {
	sekcija("Sudetiniai operatoriai");

	Studentas a("Jonas", "Jonaitis", {}, 0);
	tikrinti(a.getPazSkaicius() == 0, "operator+= pradzia paz skaicius");

	//operator+=
	a += 8;
	tikrinti(a.getPazSkaicius() == 1, "operator+= paz skaicius po 1 pazymio");
	tikrinti(a.getPaz()[0] == 8, "operator+= pazymys 8 pridetas");

	a += 6;
	a += 10;
	tikrinti(a.getPazSkaicius() == 3, "operator+= paz skaicius po 3 pazymiu");

	//Grandininis +=
	Studentas b("Ona", "Onaite", {}, 0);
	b += 5;
	b += 7;
	tikrinti(b.getPazSkaicius() == 2, "Grandininis operator+= paz skaicius po 2 pazymiu");

	//operator+= su neteisingu pazymiu - turi mesto isimti

	bool isimtis_meta = false;
	try { a += 11; }
	catch (const std::out_of_range&) { isimtis_meta = true; }
	tikrinti(isimtis_meta, "operator+=: meta isimti pazymiu > 10");

	isimtis_meta = false;
	try { a += 0; }
	catch (const std::out_of_range&) { isimtis_meta = true; }
	tikrinti(isimtis_meta, "operator+=: meta isimti pazymiu < 1");

	//operator[] skaitymas
	Studentas c("X", "Y", { 3, 7, 9 }, 5);
	tikrinti(c[0] == 3, "operator[] skaitymas paz[0] == 3");
	tikrinti(c[1] == 7, "operator[] skaitymas paz[1] == 7");
	tikrinti(c[2] == 9, "operator[] skaitymas paz[2] == 9");

	//operator[] rasymas
	c[0] = 10;
	tikrinti(c[0] == 10, "operator[] rasymas paz[0] == 10");

	//operator [] su per dideliu indeksu turi mesti isimti
	isimtis_meta = false;
	try { (void)c[99]; }
	catch (const std::out_of_range&) { isimtis_meta = true; }
	tikrinti(isimtis_meta, "operator[]: meta isimti del per didelio indekso");

}

static void testuoti_srautu_operatorius() {
	sekcija("Srautu operatoriai");

	//opperator>> su istringstream
	Studentas a;
	std::istringstream iss("Jonas Jonaitis 8 9 7 10");
	iss >> a;
	tikrinti(a.getVardas() == "Jonas", "operator>> vardas");
	tikrinti(a.getPavarde() == "Jonaitis", "operator>> pavarde");
	tikrinti(a.getPazSkaicius() == 3, "operator>> paz skaicius");
	tikrinti(a.getPaz()[0] == 8, "operator>> pazymiai paz[0] == 8");
	tikrinti(a.getPaz()[2] == 7, "operator>> pazymiai paz[2] == 7");

	//operator>> su vienu skaiciumi (tik egzaminas,0 namu darbu)
	Studentas b;
	std::istringstream iss2("Ona Onaite 5");
	iss2 >> b;
	tikrinti(b.getEgz() == 5, "operator>> egzaminas");
	tikrinti(b.getPazSkaicius() == 0, "operator>> paz skaicius 0");

	//operator<< su ostringstream
	Studentas c("Petras", "Petraitis", { 6,8 }, 9);
	c.skaiciuotiRez(1);
	std::ostringstream oss;
	oss << c;
	std::string isvestis = oss.str();

	tikrinti(isvestis.find("Petras") != std::string::npos, "operator<<: yra vardas");
	tikrinti(isvestis.find("Petraitis") != std::string::npos, "operator<<: yra pavarde");
	tikrinti(isvestis.find("Egz") != std::string::npos, "operator<<: yra Egz.");
	tikrinti(isvestis.find("Rez") != std::string::npos, "operator<<: yra Rez.");

	// Apvalus testas: >> tada <<
	Studentas d;
	std::istringstream iss3("Inga Ingaite 7 8 9 6");
	iss3 >> d;
	std::ostringstream oss2;
	oss2 << d;
	tikrinti(oss2.str().find("Inga") != std::string::npos,
		"operator<< po >>: vardas isvestyje");
}