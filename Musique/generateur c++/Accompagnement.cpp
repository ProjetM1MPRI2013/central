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
	m_tabNotes.assign(m_nbTemps * m_nbMesures / 2, "");
	m_instrument = "[53]";
	m_nbNotesAjoutees = std::min(i_nbNotesAjoutees, (unsigned int) 7);
}

Accompagnement::~Accompagnement() {
	// TODO Auto-generated destructor stub
}


void Accompagnement::generePiste(
	std::string &o_piste) {

	// au debut de chaque accord on joue l'accord
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

	o_piste = " I" + m_instrument;
	for (unsigned int i = 0; i < m_tabNotes.size(); i++) {
		if (m_tabNotes[i] == "") {
			o_piste += "h";
		}
		else {
			o_piste += " " + m_tabNotes[i] + "h";
		}
	}
}
