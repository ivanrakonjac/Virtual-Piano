#include "XML.h"

void XML::formatirajXML()
{
	ofstream xml;
	int x;
	bool part = false;

	string naziv;
	cout << "Upisite naziv izlaznog fajla: ";
	cin >> naziv;
	naziv += ".musicxml";

	vector<Takt> desna = komp.getDesna();
	vector<Takt> leva = komp.getLeva();

	xml.open(naziv);
	if (xml.is_open()) {
		xml << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
		xml << "<!DOCTYPE score-partwise PUBLIC\n";
		xml << "    \"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"\n";
		xml << "    \"http://www.musicxml.org/dtds/partwise.dtd\">\n";
		xml << "<score-partwise version=\"3.1\">\n";
		xml << "  <part-list>\n";
		xml << "    <score-part id=\"Right\"></score-part>\n";
		xml << "    <score-part id=\"Left\"></score-part>\n";
		xml << "  </part-list>\n";

		xml << "  <part id=\"Right\">\n";
		xml << "    <measure>\n";
		xml << "      <attributes>\n";
		xml << "        <divisions>2</divisions>\n";
		xml << "        <time>\n";
		xml << "          <beats>" << komp.getDuzinaTakta().getBrojilac() << "</beats>\n";
		xml << "          <beat-type>" << komp.getDuzinaTakta().getImenilac() << "</beat-type>\n";
		xml << "        </time>\n";
		xml << "        <clef>\n";
		xml << "          <sign>G</sign>\n";
		xml << "          <line>2</line>\n";
		xml << "        </clef>\n";
		xml << "      </attributes>\n";
		xml << "\n";

		for (auto iter = desna.begin(); iter != desna.end(); iter++)
		{
			if (iter != desna.begin()) xml << "    <measure>\n";
			vector<MuzickiZnak*> takt = (*iter).getTakt();
			for (auto it = takt.begin(); it != takt.end(); it++)
			{
				if (dynamic_cast<Nota*>(*it) != nullptr) {
					xml << "      <note>\n";
					xml << "        <pitch>\n";
					xml << "          <step>" << dynamic_cast<Nota*>(*it)->getVisinaXML() << "</step>\n";
					xml << "          <octave>" << dynamic_cast<Nota*>(*it)->getOktava() << "</octave>\n";
					if (dynamic_cast<Nota*>(*it)->getPovisena()) {
						xml << "          <alter>1</alter>\n";
					}
					xml << "        </pitch>\n";
					if ((*it)->getTrajanje() == Razlomak(1, 8)) {
						x = 1;
					}
					else {
						x = 2;
					}
					xml << "        <duration>" << x << "</duration>\n";
					if (dynamic_cast<Nota*>(*it)->getPart() && !part) {
						xml << "        <tie type=\"start\"/>\n";
						part = true;
					}
					else
						if (dynamic_cast<Nota*>(*it)->getPart() && part) {
							xml << "        <tie type=\"end\"/>\n";
							part = false;
						}
					xml << "      </note>\n";
				}
				if (dynamic_cast<Akord*>(*it) != nullptr) {
					vector<Nota*> akord = dynamic_cast<Akord*>(*it)->getNizNota();
					for (int i = 0; i < akord.size(); i++) {
						xml << "      <note>\n";
						if (i != 0) xml << "        <chord/>\n";
						xml << "        <pitch>\n";
						xml << "          <step>" << akord[i]->getVisinaXML() << "</step>\n";
						xml << "          <octave>" << akord[i]->getOktava() << "</octave>\n";
						xml << "        </pitch>\n";
						if (akord[i]->getTrajanje() == Razlomak(1, 8)) x = 1; else x = 2;
						xml << "        <duration>" << x << "</duration>\n";
						xml << "      </note>\n";
					}
				}
				if (dynamic_cast<Pauza*>(*it) != nullptr) {
					xml << "      <note>\n";
					xml << "        <rest/>\n";
					if ((*it)->getTrajanje() == Razlomak(1, 8)) x = 1; else x = 2;
					xml << "        <duration>" << x << "</duration>\n";
					xml << "      </note>\n";
				}
			}
			xml << "    </measure>\n";
		}

		xml << "  </part>\n";
		xml << "\n";

		xml << "  <part id=\"Left\">\n";
		xml << "    <measure>\n";
		xml << "      <attributes>\n";
		xml << "        <divisions>2</divisions>\n";
		xml << "        <time>\n";
		xml << "          <beats>" << komp.getDuzinaTakta().getBrojilac() << "</beats>\n";
		xml << "          <beat-type>" << komp.getDuzinaTakta().getImenilac() << "</beat-type>\n";
		xml << "        </time>\n";
		xml << "        <clef>\n";
		xml << "          <sign>F</sign>\n";
		xml << "          <line>4</line>\n";
		xml << "        </clef>\n";
		xml << "      </attributes>\n";
		xml << "\n";

		for (auto iter = leva.begin(); iter != leva.end(); iter++)
		{
			if (iter != leva.begin()) xml << "    <measure>\n";
			vector<MuzickiZnak*> takt = (*iter).getTakt();
			for (auto it = takt.begin(); it != takt.end(); it++)
			{
				if (dynamic_cast<Nota*>(*it) != nullptr) {
					xml << "      <note>\n";
					xml << "        <pitch>\n";
					xml << "          <step>" << dynamic_cast<Nota*>(*it)->getVisinaXML() << "</step>\n";
					xml << "          <octave>" << dynamic_cast<Nota*>(*it)->getOktava() << "</octave>\n";
					if (dynamic_cast<Nota*>(*it)->getPovisena()) {
						xml << "          <alter>1</alter>\n";
					}
					xml << "        </pitch>\n";
					if ((*it)->getTrajanje() == Razlomak(1, 8)) x = 1; else x = 2;
					xml << "        <duration>" << x << "</duration>\n";
					if (dynamic_cast<Nota*>(*it)->getPart() && !part) {
						xml << "        <tie type=\"start\"/>\n";
						part = true;
					}
					else
						if (dynamic_cast<Nota*>(*it)->getPart() && part) {
							xml << "        <tie type=\"end\"/>\n";
							part = false;
						}
					xml << "      </note>\n";
				}
				if (dynamic_cast<Akord*>(*it) != nullptr) {
					vector<Nota*> akord = dynamic_cast<Akord*>(*it)->getNizNota();
					for (int i = 0; i < akord.size(); i++) {
						xml << "      <note>\n";
						if (i != 0) xml << "        <chord/>\n";
						xml << "        <pitch>\n";
						xml << "          <step>" << akord[i]->getVisinaXML() << "</step>\n";
						xml << "          <octave>" << akord[i]->getOktava() << "</octave>\n";
						//if (dynamic_cast<Nota*>(*it)->jePovisena()) xmlfile << "          <alter>1</alter>\n";
						xml << "        </pitch>\n";
						if (akord[i]->getTrajanje() == Razlomak(1, 8)) x = 1; else x = 2;
						xml << "        <duration>" << x << "</duration>\n";
						xml << "      </note>\n";
					}
				}
				if (dynamic_cast<Pauza*>(*it) != nullptr) {
					xml << "      <note>\n";
					xml << "        <rest/>\n";
					if ((*it)->getTrajanje() == Razlomak(1, 8)) x = 1; else x = 2;
					xml << "        <duration>" << x << "</duration>\n";
					xml << "      </note>\n";
				}
			}
			xml << "    </measure>\n";
		}
		xml << "  </part>\n";
		xml << "</score-partwise>";

		xml.close();
	}
	else {
		cout << endl << "File is not open" << endl;
	}

}
