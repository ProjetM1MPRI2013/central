/*
 * Melodie.cpp
 *
 *  Created on: 14 févr. 2014
 *      Author: riesner
 */

#include "Melodie.h"
#include "Gamme.h"
#include <stdlib.h>
#include <iostream>

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
	std::vector<CelluleNote> &o_piste,
	std::string &o_instrument,
	const unsigned int i_tempo) {

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

	o_instrument = m_instrument;
	o_piste.resize(m_tabNotes.size());
	for (unsigned int temps = 0; temps < m_tabNotes.size(); temps++) {
		const unsigned int a = rand() % 5;
		CelluleNote cellule;
		if (a == 0) {
			unsigned int k = 0;
			for (int i = indiceNote - 2; i <= indiceNote + 2; i++) {
				if (i >= 0 && i < (int) listeGamme.size()) {
					k++;
					const unsigned int b = rand() % k;
					const unsigned int size = listeGamme[b].length();
					cellule.note      = listeGamme[b].substr(0, size - 1);
					cellule.octave    = atoi(listeGamme[b].substr(size - 1, 1).c_str());
					cellule.frequence = getFrequence(cellule.note, cellule.octave);
					cellule.duree     = 6000.f / (8.f * (float) i_tempo);
				}
			}
		}
		else if (a == 1) {
			const unsigned int b = rand() % listeGamme.size();
			const unsigned int size = listeGamme[b].length();
			cellule.note      = listeGamme[b].substr(0, size - 1);
			cellule.octave    = atoi(listeGamme[b].substr(size - 1, 1).c_str());
			cellule.frequence = getFrequence(cellule.note, cellule.octave);
			cellule.duree     = 6000.f / (8.f * (float) i_tempo);
		}
		else {
			cellule.note      = "R" ;
			cellule.frequence = 0.f ;
			cellule.octave    = 0.f;
			cellule.duree     = 6000.f / (8.f * (float) i_tempo);
		}
		o_piste[temps] = cellule;
	}
}
