#pragma once

#include <vector>

#include "MuzickiZnak.h"
#include "Razlomak.h"
#include "Takt.h"

using namespace std;

class Kompozicija
{
private:
	vector<Takt> leva;
	vector<Takt> desna;
	Razlomak duzinaTakta;
public:
	Kompozicija(Razlomak dt) :duzinaTakta(dt) {};

	Razlomak getDuzinaTakta() const {
		return duzinaTakta;
	}

	void dodajLeva(Takt takt) {
		leva.push_back(takt);
	}

	void dodajDesna(Takt takt) {
		desna.push_back(takt);
	}

	void stampajLeva();

	void stampajDesna();

	int getBrMuzickihSimbola() const {
		return leva.size();
	}

	void stampaj();

	void iterirajKrozLevuRuku();

	void iterirajKrozDesnuRuku();

	void povecajOktavuSvihNota(int i);

	void smanjiOktavuSvihNota(int i);

	vector<Takt> getLeva() {
		return leva;
	}
	vector<Takt> getDesna() {
		return desna;
	}

};

