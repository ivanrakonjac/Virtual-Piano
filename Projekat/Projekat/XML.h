#pragma once

#include "Kompozicija.h"
#include "Akord.h"
#include "Pauza.h"

#include <iostream>
#include <fstream>

class XML
{
private:
	Kompozicija komp;
public:
	XML(Kompozicija k) :komp(k) {};

	void formatirajXML();
};

