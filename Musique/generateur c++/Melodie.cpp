/*
 * Melodie.cpp
 *
 *  Created on: 14 févr. 2014
 *      Author: riesner
 */

#include "Melodie.h"
#include "Gamme.h"
#include <stdlib.h>

using namespace std;

Melodie::Melodie(
	std::string const& i_dominante,
	std::vector<Accord> const& i_tabAccord) :
	Base(i_dominante, i_tabAccord) {

	m_tabNotes.assign(m_nbTemps * m_nbMesures * 2, "");
	m_instrument = "[10]";
}

Melodie::~Melodie() {
	// TODO Auto-generated destructor stub
}

void Melodie::generePiste(
	std::string &o_piste) {

	// Pour convenience
	const string octave4 = "4";
	const string octave5 = "5";
	const string octave6 = "6";
	const int indiceNote = 7;

	// Initialisation
	vector<string> gamme;
	(new Gamme(m_dominante + "maj"))->nomNotes(gamme);
	vector<string> listeGamme;

	for (unsigned int i = 0; i < gamme.size(); i++) {
		listeGamme.push_back(gamme[i] + octave4);
	}

	for (unsigned int i = 0; i < gamme.size(); i++) {
		listeGamme.push_back(gamme[i] + octave5);
	}

	listeGamme.push_back(m_dominante + octave6);

	o_piste = " I" + m_instrument;
	for (unsigned int temps = 0; temps < m_tabNotes.size(); temps++) {
		const unsigned int a = rand() % 5;
		if (a == 0) {
			unsigned int k = 0;
			for (int i = indiceNote - 2; i <= indiceNote + 2; i++) {
				if (i >= 0 && i < (int) listeGamme.size()) {
					k++;
					const unsigned int b = rand() % k;
					o_piste += " " + listeGamme[b] + "i";
				}
			}
		}
		else if (a == 1) {
			const int b = rand() % listeGamme.size();
			o_piste += " " + listeGamme[b] + "i";
		}
		else {
			o_piste += " Ri";
		}
	}
}
