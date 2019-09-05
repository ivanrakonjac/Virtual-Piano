#pragma once

#include <iostream>
#include "Razlomak.h"

using namespace std;

class MuzickiZnak
{
public:
protected:
	Razlomak trajanje;
public:

	MuzickiZnak(Razlomak r) :trajanje(r) {};

	Razlomak getTrajanje() const {
		return trajanje;
	}

	void setTrajanje(Razlomak r) {
		trajanje = r;
	}

	friend ostream& operator<<(ostream &ot, const MuzickiZnak &mz) {
		ot << mz.trajanje;
		return ot;
	};

	virtual void ispisi() {
		cout << trajanje;
	}
};

