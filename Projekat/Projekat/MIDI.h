#pragma once

#include "MidiFile.h"
#include "Kompozicija.h"
#include "Takt.h"
#include "Pauza.h"
#include "Akord.h"

#include <vector>
#include <string>

using namespace std;
using namespace smf;

class MIDI
{
private:
	MidiFile outputfile;
	Kompozicija komp;
public:
	MIDI(Kompozicija k):komp(k) {};

	void formatiraj();

	void eksportuj();
};

