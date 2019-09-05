#pragma once

#include "MuzickiZnak.h"
#include "Razlomak.h"
#include "Izuzetak.h"
#include "Nota.h"

#include <vector>
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

class Takt
{
private:
	Razlomak trajanjeTakta;
	vector<MuzickiZnak*> niz;
public:
	Takt(Razlomak r) :trajanjeTakta(r) {};

	void dodaj(MuzickiZnak* mz);

	void stampaj();

	int getBrMuzickihSimbola() const {
		return niz.size();
	}

	MuzickiZnak* getMuzickiSimbol(int i) {
		if (i < 0 || i == niz.size()) throw Izuzetak("index ne sme biti manji od 0 ni veci ili jednak od " + niz.size());
		else return niz[i];
	}

	vector<MuzickiZnak*> getTakt() {
		return niz;
	}

	Razlomak getTrajanjeTakta() const {
		return trajanjeTakta;
	}

	void umanjiTakt(MuzickiZnak* mz) {
		trajanjeTakta = trajanjeTakta - mz->getTrajanje();
	}

	void iterirajKrozTakt();

	void smanjiOktavuSvihNotaPuta(int i);
	void povecajOktavuSvihNotaPuta(int i);

};

