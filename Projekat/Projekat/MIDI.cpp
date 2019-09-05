#include "MIDI.h"

void MIDI::formatiraj()
{
	outputfile.absoluteTicks();
	vector<uchar> midievent;
	midievent.resize(3);
	int tpq = 48;
	outputfile.setTicksPerQuarterNote(tpq);
	outputfile.addTrack(1);

	vector<Takt> desna = komp.getDesna();
	vector<MuzickiZnak*> melody;
	vector<int> mrhythm;

	bool cekiraj1 = false, cekiraj2 = false;

	//iteriram kroz desnu
	for (auto iter = desna.begin();iter != desna.end();iter++) {
		vector<MuzickiZnak*> takt = iter->getTakt();
		//iteriram kroz takt
		for (auto taktIter = takt.begin();taktIter != takt.end();taktIter++) {
			if (dynamic_cast<Nota*>(*taktIter) != nullptr) {
				if (dynamic_cast<Nota*>(*taktIter)->getPart()) {
					if (cekiraj1) { cekiraj1 = false; continue; }
					Nota* n = dynamic_cast<Nota*>(*taktIter);
					MuzickiZnak* mz = new Nota(n->getTrajanje(), n->getVisina(), n->getOktava(), n->getBroj(), n->getPovisena());
					mz->setTrajanje(n->getTrajanje() + n->getTrajanje());
					melody.push_back(mz);
					if (mz->getTrajanje() == Razlomak(1, 8))
						mrhythm.push_back(1);
					else
						mrhythm.push_back(2);

					cekiraj1 = true;
				}
			}
			if (dynamic_cast<Pauza*>(*taktIter) != nullptr) {
				if (dynamic_cast<Pauza*>(*taktIter)->getPart()) {
					Pauza* p = dynamic_cast<Pauza*>(*taktIter);
					MuzickiZnak* mz = new Pauza(p->getTrajanje() + p->getTrajanje());
					melody.push_back(mz);
					if (mz->getTrajanje() == Razlomak(1, 8))
						mrhythm.push_back(1);
					else
						mrhythm.push_back(2);

					cekiraj1 = true;
				}
			}
			if (dynamic_cast<Akord*>(*taktIter) != nullptr) {
				if (dynamic_cast<Akord*>(*taktIter)->getPart()) {
					Akord* a = dynamic_cast<Akord*>(*taktIter);
					MuzickiZnak* mz = new Akord(a->getTrajanje() + a->getTrajanje());
					melody.push_back(mz);
					if (mz->getTrajanje() == Razlomak(1, 8))
						mrhythm.push_back(1);
					else
						mrhythm.push_back(2);

					cekiraj1 = true;
				}
			}
			if ((dynamic_cast<Nota*>(*taktIter) != nullptr && dynamic_cast<Nota*>(*taktIter)->getPart() == false) || (dynamic_cast<Pauza*>(*taktIter) != nullptr && dynamic_cast<Pauza*>(*taktIter)->getPart() == false) ||
				(dynamic_cast<Akord*>(*taktIter) != nullptr && dynamic_cast<Akord*>(*taktIter)->getPart() == false)) {
				melody.push_back((*taktIter));
				if ((*taktIter)->getTrajanje() == Razlomak(1, 8))
					mrhythm.push_back(1);
				else
					mrhythm.push_back(2);
			}
		}

	}

	vector<Takt> leva = komp.getLeva();
	vector<MuzickiZnak*> bass;
	vector<int> brhythm;
	//iteriram kroz levu
	for (auto iter = leva.begin();iter != leva.end();iter++) {
		vector<MuzickiZnak*> takt = iter->getTakt();
		//iteriram kroz takt
		for (auto taktIter = takt.begin();taktIter != takt.end();taktIter++) {
			if (dynamic_cast<Nota*>(*taktIter) != nullptr) {
				if (dynamic_cast<Nota*>(*taktIter)->getPart()) {
					if (cekiraj2) { cekiraj2 = false; continue; }
					Nota* n = dynamic_cast<Nota*>(*taktIter);
					MuzickiZnak *mz = new Nota(n->getTrajanje() + n->getTrajanje(), n->getVisina(), n->getOktava(), n->getBroj(), n->getPovisena());
					bass.push_back(mz);
					if (mz->getTrajanje() == Razlomak(1, 8))
						brhythm.push_back(1);
					else
						brhythm.push_back(2);

					cekiraj2 = true;
				}
			}
			if (dynamic_cast<Pauza*>(*taktIter) != nullptr) {
				if (dynamic_cast<Pauza*>(*taktIter)->getPart()) {
					Pauza* p = dynamic_cast<Pauza*>(*taktIter);
					MuzickiZnak* mz = new Pauza(p->getTrajanje() + p->getTrajanje());
					bass.push_back(mz);
					if (mz->getTrajanje() == Razlomak(1, 8))
						brhythm.push_back(1);
					else
						brhythm.push_back(2);

					cekiraj2 = true;
				}
			}
			if (dynamic_cast<Akord*>(*taktIter) != nullptr) {
				if (dynamic_cast<Akord*>(*taktIter)->getPart()) {
					Akord* a = dynamic_cast<Akord*>(*taktIter);
					MuzickiZnak* mz = new Akord(a->getTrajanje() + a->getTrajanje());
					melody.push_back(mz);
					bass.push_back(mz);
					if (mz->getTrajanje() == Razlomak(1, 8))
						brhythm.push_back(1);
					else
						brhythm.push_back(2);

					cekiraj2 = true;
				}
			}
			if ((dynamic_cast<Nota*>(*taktIter) != nullptr && dynamic_cast<Nota*>(*taktIter)->getPart() == false) || (dynamic_cast<Pauza*>(*taktIter) != nullptr && dynamic_cast<Pauza*>(*taktIter)->getPart() == false) ||
				(dynamic_cast<Akord*>(*taktIter) != nullptr && dynamic_cast<Akord*>(*taktIter)->getPart() == false)) {
				bass.push_back((*taktIter));
				if ((*taktIter)->getTrajanje() == Razlomak(1, 8))
					brhythm.push_back(1);
				else
					brhythm.push_back(2);
			}
		}

	}

	int actiontime = 0;
	midievent[2] = 64;
	for (int i = 0; i < melody.size(); i++)
	{
		midievent[0] = 0x90;
		if (dynamic_cast<Nota*>(melody[i]) != nullptr) {
			midievent[1] = dynamic_cast<Nota*>(melody[i])->getBroj();
			outputfile.addEvent(0, actiontime, midievent);
			actiontime += tpq / 2 * mrhythm[i];
			midievent[0] = 0x80;
			outputfile.addEvent(0, actiontime, midievent);
		}
		if (dynamic_cast<Pauza*>(melody[i]) != nullptr) {
			actiontime += tpq / 2 * mrhythm[i];
			continue;
		}
		if (dynamic_cast<Akord*>(melody[i]) != nullptr) {
			vector<Nota*> akord = dynamic_cast<Akord*>(melody[i])->getNizNota();
			for (auto iter = akord.begin(); iter != akord.end(); iter++) {
				midievent[1] = (*iter)->getBroj();
				outputfile.addEvent(0, actiontime, midievent);
			}
			actiontime += tpq / 2 * mrhythm[i];
			midievent[0] = 0x80;
			for (auto iter = akord.begin(); iter != akord.end(); iter++) {
				midievent[1] = (*iter)->getBroj();
				outputfile.addEvent(0, actiontime, midievent);
			}
		}
	}

	actiontime = 0;
	for (int i = 0; i < bass.size(); i++)
	{
		midievent[0] = 0x90;
		if (dynamic_cast<Nota*>(bass[i]) != nullptr) {
			midievent[1] = dynamic_cast<Nota*>(bass[i])->getBroj();
			outputfile.addEvent(1, actiontime, midievent);
			actiontime += tpq / 2 * brhythm[i];
			midievent[0] = 0x80;
			outputfile.addEvent(1, actiontime, midievent);
		}
		if (dynamic_cast<Pauza*>(bass[i]) != nullptr) {
			actiontime += tpq / 2 * brhythm[i];
			continue;
		}
		if (dynamic_cast<Akord*>(bass[i]) != nullptr) {
			vector<Nota*> akord = dynamic_cast<Akord*>(bass[i])->getNizNota();
			for (auto iter = akord.begin(); iter != akord.end(); iter++) {
				midievent[1] = (*iter)->getBroj();
				outputfile.addEvent(1, actiontime, midievent);
			}
			actiontime += tpq / 2 * brhythm[i];
			midievent[0] = 0x80;
			for (auto iter = akord.begin(); iter != akord.end(); iter++) {
				midievent[1] = (*iter)->getBroj();
				outputfile.addEvent(1, actiontime, midievent);
			}
		}
	}

	outputfile.sortTracks();

}

void MIDI::eksportuj()
{
	string ime;
	cout << endl << "Unesite ime eksportovanog MIDI fajla: ";
	cin >> ime;
	ime = ime + ".mid";
	outputfile.write(ime);
}
