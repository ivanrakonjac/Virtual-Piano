#pragma once

#include "MuzickiZnak.h"
#include "Razlomak.h"

class Pauza :
	public MuzickiZnak
{
private:
	bool akord;
	bool part;
public:
	Pauza(Razlomak r,bool a=false,bool prt=false) :MuzickiZnak(r),akord(a),part(prt) {};

	friend ostream& operator<<(ostream &ot, const Pauza &p) {
		ot << p.trajanje;
		return ot;
	};

	bool getPart() const {
		return part;
	}

	virtual void ispisi() {
		cout << trajanje;
		if (akord == true) cout << "   ";
	}
};

