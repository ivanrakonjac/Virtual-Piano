#pragma once

#include <vector>
#include "Nota.h"
#include "MuzickiZnak.h"

using namespace std;


class Akord :
	public MuzickiZnak
{
private:
	bool part;
	vector<Nota*> nizNota;
public:
	Akord(Razlomak trajanje, bool prt=false) :MuzickiZnak(trajanje), part(prt) {};
	~Akord() {
		auto it2=nizNota.begin();
		for (auto it = nizNota.begin();it != nizNota.end();it=it2) {
			 it2= ++it;
			 delete (*it);
		}
		delete (*nizNota.end());
	}

	void dodaj(Nota* n) {
		nizNota.push_back(n);
	}

	bool getPart() const {
		return part;
	}

	void ispisi();

	int getBrMuzickihSimbola() const {
		return nizNota.size();
	}

	vector<Nota*> getNizNota() {
		return nizNota;
	}
};


