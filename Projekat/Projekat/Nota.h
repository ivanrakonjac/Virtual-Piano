#pragma once

#include "MuzickiZnak.h"
#include "Izuzetak.h"
#include <iostream>
#include <string>

using namespace std;

class Nota :
	public MuzickiZnak
{
public:enum  Visina { C, D, E, F, G, A, B };

private:
	Visina visina;
	int oktava,broj;
	bool povisena;
	bool part;
	bool spojena;
public:
	Nota(Razlomak r, Visina v, int o,int br, bool p, bool prt=false, bool spoj=false) :MuzickiZnak(r), visina(v),broj(br), povisena(p),part(prt),spojena(spoj) {
		if (o > 6 || o < 2) throw Izuzetak("Greska u oktavi! Oktava moze imati vrednosti od 2 do 6!"); 
		else oktava = o;
	};

	Visina getVisina() const {
		return visina;
	}

	bool getSpojena() const {
		return spojena;
	}

	bool getPovisena() const {
		return povisena;
	}

	bool getPart() const {
		return part;
	}

	int getBroj() const {
		return broj;
	}

	int getOktava() const {
		return oktava;
	}

	friend ostream& operator<<(ostream &ot, const Nota &n);

	void povecajOktavu() {
		if (oktava < 6) oktava++;
	}
	void smanjiOktavu() {
		if (oktava > 2) oktava--;
	}

	void povecajVisinu();
	void smanjiVisinu();

	void povisiTon() {
		if (povisena == false) povisena = true;
	}
	void sniziTon() {
		if (povisena == true) povisena = false;
	}

	void ispisi();

	char getVisinaXML() const;
};

