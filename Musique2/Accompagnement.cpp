/*
 * Accompagnement.cpp
 *
 *  Created on: 14 févr. 2014
 *      Author: riesner
 */

#include <stdlib.h>

#include "Accompagnement.h"

Accompagnement::Accompagnement(
		std::string const& i_dominante,
		std::vector<Accord> const& i_tabAccord,
		const unsigned int i_nbNotesAjoutees) :
		Base(i_dominante, i_tabAccord)
{
	m_tabNotes.assign(m_nbTemps * m_nbMesures / 2,"");    //Accord());
	m_instrument = "[53]";
	m_nbNotesAjoutees = std::min(i_nbNotesAjoutees, (unsigned int) 7);
}

Accompagnement::~Accompagnement() {
	// TODO Auto-generated destructor stub
}


void Accompagnement::generePiste(
	std::vector<CelluleAccord> &o_piste,
	std::string &o_instrument,
	const unsigned int i_tempo){

	// au debut de chaque mesure on joue l'accord
	const unsigned int octave5 = 5;
	const unsigned int doubleTemps = m_nbTemps / 2;

	for (unsigned int i = 0; i < m_nbMesures; i++) {
		m_tabNotes[doubleTemps * i] = m_tabAccord[i].m_noteDominante + m_tabAccord[i].m_typeAccord;
	}

	const unsigned int N = (m_nbNotesAjoutees + 1) / 2;
	const unsigned int nbNotes = (rand() % N) + N;
	for (unsigned int i = 0; i < nbNotes; i++) {
		const unsigned int cases = rand() % (doubleTemps * m_nbMesures);

		if (m_tabNotes[cases] == "") {
			m_tabNotes[cases] = m_tabAccord[cases / doubleTemps].m_noteDominante +
					m_tabAccord[cases / doubleTemps].m_typeAccord;
		}
	}

	o_instrument = m_instrument;
	o_piste.resize(m_tabNotes.size());
	for (unsigned int i = 0; i < m_tabNotes.size(); i++) {
		CelluleAccord cellule;
		if (m_tabNotes[i] == "") {
			cellule.note1      = "";
			cellule.note2      = "";
			cellule.note2      = "";
			cellule.frequence1 = 0.f;
			cellule.frequence2 = 0.f;
			cellule.frequence3 = 0.f;
			cellule.octave     = 0;
			cellule.duree      = 0.f;
		}
		else {
			Accord accord(m_tabNotes[i]);
			std::vector<std::string> notesAccord;
			accord.nomNotes(notesAccord);
			cellule.note1      = notesAccord[0];
			cellule.note2      = notesAccord[1];
			cellule.note3      = notesAccord[2];
			cellule.frequence1 = getFrequence(notesAccord[0], octave5);
			cellule.frequence2 = getFrequence(notesAccord[1], octave5);
			cellule.frequence3 = getFrequence(notesAccord[2], octave5);
			cellule.octave     = octave5;
			cellule.duree      = 6000.f  /(2.f * (float) i_tempo);
			unsigned int j = 1;
			bool test = (i + j < m_tabNotes.size() ? m_tabNotes[i + j] == "" : false);
			while (test){
				cellule.duree += 6000.f / (2.f * (float) i_tempo);
				j++;
				if (i + j < m_tabNotes.size()) {
					test = (m_tabNotes[i + j] == "");
				}
				else {
					test = false;
				}
			}
		}
		o_piste[i] = cellule;
	}
}
