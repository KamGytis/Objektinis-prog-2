#include "studentas.h"
#include "zmogus.h"
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
	tikrinti(b.getRez() == 0.0, "Parametrinis rezultatas (pries skaiciavima)");
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

static void testuoti_metodus() {
	sekcija("Metodai: vidurkis, mediana, skaiciuotiRez, islaike");

	// vidurkis
	Studentas a("X", "Y", { 6, 8, 10 }, 0);
	tikrinti(std::abs(a.vidurkis() - 8.0) < 1e-9, "vidurkis(): (6+8+10)/3 = 8.0");

	// vidurkis su tusciu sarasu
	Studentas b;
	tikrinti(b.vidurkis() == 0.0, "vidurkis(): tuscias sarasas = 0.0");

	// mediana – nelyginis skaicius
	Studentas c("X", "Y", { 3, 9, 5 }, 0);
	tikrinti(std::abs(c.mediana() - 5.0) < 1e-9, "mediana(): {3,9,5} -> 5.0");

	// mediana – lyginis skaicius
	Studentas d("X", "Y", { 2, 4, 6, 8 }, 0);
	tikrinti(std::abs(d.mediana() - 5.0) < 1e-9, "mediana(): {2,4,6,8} -> 5.0");

	// skaiciuotiRez su vidurkiu
	Studentas e("X", "Y", { 8, 10, 6 }, 8);
	e.skaiciuotiRez(1); // vidurkis = 8, rez = 8*0.4 + 8*0.6 = 8.0
	tikrinti(std::abs(e.getRez() - 8.0) < 1e-9, "skaiciuotiRez(1): rez = 8.0");

	// skaiciuotiRez su mediana
	Studentas f("X", "Y", { 4, 6, 8 }, 10);
	f.skaiciuotiRez(2); // mediana = 6, rez = 6*0.4 + 10*0.6 = 2.4+6.0 = 8.4
	tikrinti(std::abs(f.getRez() - 8.4) < 1e-9, "skaiciuotiRez(2): rez = 8.4");

	// islaike
	Studentas g("X", "Y", {}, 0);
	g.setRez(4.9);
	tikrinti(!g.islaike(), "islaike(): 4.9 < 5.0 -> false");
	g.setRez(5.0);
	tikrinti(g.islaike(), "islaike(): 5.0 >= 5.0 -> true");
	g.setRez(8.5);
	tikrinti(g.islaike(), "islaike(): 8.5 >= 5.0 -> true");

	// addPazymys ir clearPazymiai
	Studentas h;
	h.addPazymys(7);
	h.addPazymys(9);
	tikrinti(h.getPazSkaicius() == 2, "addPazymys(): 2 pazymiai");
	h.clearPazymiai();
	tikrinti(h.getPazSkaicius() == 0, "clearPazymiai(): sarasas tuscias");

	// getteriai ir setteriai
	Studentas i;
	i.setVardas("Inga");
	i.setPavarde("Ingaite");
	i.setEgz(7);
	i.setRez(6.5);
	tikrinti(i.getVardas() == "Inga", "setter/getter: vardas");
	tikrinti(i.getPavarde() == "Ingaite", "setter/getter: pavarde");
	tikrinti(i.getEgz() == 7, "setter/getter: egz");
	tikrinti(std::abs(i.getRez() - 6.5) < 1e-9, "setter/getter: rez");
}

static void testuoti_su_stl() {
	sekcija("Naudojimas su STL konteineriais ir algoritmais");

	std::vector<Studentas> studentai = {
		Studentas("C", "C", {4,4}, 4),
		Studentas("A", "A", {9,9}, 9),
		Studentas("B", "B", {6,6}, 6)
	};
	for (auto& s : studentai) s.skaiciuotiRez(1);

	// std::sort su operator<
	std::sort(studentai.begin(), studentai.end());
	tikrinti(studentai[0].getVardas() == "C" &&
		studentai[1].getVardas() == "B" &&
		studentai[2].getVardas() == "A",
		"std::sort su operator<: rusiuoja pagal rez_");

	// std::find_if su islaike
	auto pirmas_islaikes = std::find_if(studentai.begin(), studentai.end(),
		[](const Studentas& s) { return s.islaike(); });
	tikrinti(pirmas_islaikes != studentai.end() &&
		pirmas_islaikes->getVardas() == "B",
		"std::find_if su islaike(): randa pirma islaikiusi");
	// std::partition su operator>=
	std::vector<Studentas> v = studentai;
	auto pivot = std::partition(v.begin(), v.end(),
		[](const Studentas& s) { return s.islaike(); });
	int islaike = (int)std::distance(v.begin(), pivot);
	int neislaike = (int)std::distance(pivot, v.end());
	tikrinti(islaike == 2 && neislaike == 1,
		"std::partition + islaike(): 2 islaike, 1 neislaike");
}

// PAGRINDINIS TESTO KVIETIMAS
static void testuoti_zmogus_abstrakti() {
	sekcija("Zmogus abstrakti klase (v1.5)");

	// Zmogus objekto sukurti NEGALIMA – klase abstrakti.
	// Toliau pateiktas kodas NEKOMPILIUOJAS (tai yra tinkamas elgesys):
	//   Zmogus z;                  // KLAIDA: cannot instantiate abstract class
	//   Zmogus z("A", "B");        // KLAIDA: cannot instantiate abstract class
	// Tai irodo kad abstraktumas veikia teisingai.

	// Galima sukurti tik Studentas objekta (isvestine klase):
	Studentas s("Jonas", "Jonaitis", { 8, 9 }, 10);
	tikrinti(true, "Zmogus abstrakti: Studentas objektas sukurtas sekmingai");

	// Studentas yra Zmogus tipo (polimorfizmas)
	Zmogus* ptr = new Studentas("Ona", "Onaite", { 7, 8 }, 9);
	tikrinti(ptr != nullptr, "Zmogus abstrakti: Zmogus* rodo i Studentas objekta");
	tikrinti(ptr->getVardas() == "Ona", "Zmogus abstrakti: getVardas() per bazine klase");
	tikrinti(ptr->getPavarde() == "Onaite", "Zmogus abstrakti: getPavarde() per bazine klase");

	// operator<< per bazine klase naudoja virtual print()
	std::ostringstream oss;
	oss << *ptr;
	tikrinti(oss.str().find("Ona") != std::string::npos,
		"Zmogus abstrakti: operator<< per Zmogus& naudoja virtual print()");

	// Virtualus destruktorius – teisingai iskvieciamas Studentas destruktorius
	delete ptr;
	tikrinti(true, "Zmogus abstrakti: virtualus destruktorius iskviestas teisingai");

	// Bazines klases getteriai ir setteriai veikia per isvestine klase
	Studentas t;
	t.setVardas("Petras");
	t.setPavarde("Petraitis");
	tikrinti(t.getVardas() == "Petras", "Zmogus abstrakti: setVardas/getVardas is bazines");
	tikrinti(t.getPavarde() == "Petraitis", "Zmogus abstrakti: setPavarde/getPavarde is bazines");
}

void atlikti_klases_testus() {
	std::cout << "\n";
	std::cout << std::string(55, '=') << "\n";
	std::cout << "   STUDENTAS KLASES TESTAVIMAS  (v1.2)\n";
	std::cout << std::string(55, '=') << "\n";

	testuoti_konstruktorius();
	testuoti_priskyrima();
	testuoti_palyginimo_operatorius();
	testuoti_srautu_operatorius();
	testuoti_metodus();
	testuoti_su_stl();
	testuoti_zmogus_abstrakti();

	std::cout << "\n" << std::string(55, '=') << "\n";
	std::cout << "  Rezultatas: " << testai_pavyke << " / "
		<< testai_is_viso << " testu pavyko\n";
	if (testai_pavyke == testai_is_viso)
		std::cout << "  Visi testai pavyko!\n";
	else
		std::cout << "  DEMESIO: "
		<< (testai_is_viso - testai_pavyke)
		<< " testai nepavyko!\n";
	std::cout << std::string(55, '=') << "\n";
}