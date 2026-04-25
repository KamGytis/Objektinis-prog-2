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