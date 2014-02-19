/*
 * Basse.cpp
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#include "Basse.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

Basse::Basse(
		std::string const& i_dominante,
		std::vector<Accord> const& i_tabAccord,
		const unsigned int i_nbNotesAjoutees) :
		Base(i_dominante, i_tabAccord)
{
	m_tabNotes.assign(m_nbTemps * m_nbMesures, "");
	m_instrument = "[33]";
	m_nbNotesAjoutees = std::min(i_nbNotesAjoutees, (unsigned int) 7);

}

Basse::~Basse() {
	// TODO Auto-generated destructor stub
}


void Basse::generePiste(
	std::string &o_piste){

	// Pour convenience
	const string octave2 = "2";
	const string octave3 = "3";

	// au debut de chaque accord on joue la tonique de l'accord

	for (unsigned int i = 0; i < m_nbMesures; i++) {
		m_tabNotes[m_nbTemps * i] = m_tabAccord[i].m_noteDominante + octave2;
		//cout << "===" << m_tabNotes[m_nbTemps * i] << "===" << m_tabAccord[i].m_noteDominante << endl;
	}

	// puis on rajoute peu de notes (k) au pif
	// on tire au sort k entre 2 et 8.
	// k = le nombre de notes qu'on rajoute en tout
	// on tire au sort une case du tableau k fois, si la case
	// n'est pas remplie, on met une note de l'accord dedans

	const unsigned int N = (m_nbNotesAjoutees + 1) / 2;
	const unsigned int nbNotes = (rand() % N) + N;
	for (unsigned int i = 0; i < nbNotes; i++) {
		const unsigned int cases = rand() % (m_nbTemps * m_nbMesures);

		if (m_tabNotes[cases] == "") {
			vector<string> notesAccord;
			m_tabAccord[cases / m_nbTemps].nomNotes(notesAccord);
			m_tabNotes[cases] = notesAccord[rand() % notesAccord.size()] + octave3;
		}
	}

	// le choix des octaves : c'est octave2 si la case est congru à 0 modulo 8, octave3 sinon.

	// si j'ai do vide vide vide mi, do dois durer quatre croches
	o_piste = " I" + m_instrument;
	for (unsigned int i = 0; i < m_tabNotes.size(); i++) {
		if (m_tabNotes[i] == "") {
			o_piste += "q";
		}
		else {
			o_piste += " " + m_tabNotes[i] + "q";
		}
	}
}
