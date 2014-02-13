/*
 * Gamme.cpp
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#include "Gamme.h"
#include <iostream>
#include <string>
//#include<list>

using namespace std;

Gamme::Gamme() {

	m_noteDominante = "C";
	m_typeGamme  = "maj";
	// valeur par défaut de la gamme

}

Gamme::Gamme(
		std::string const& i_gamme) {

	if (i_gamme.substr(1,1)=="#") {
		m_noteDominante = i_gamme.substr(0,2);
		m_typeGamme   = i_gamme.substr(2);
	}
	else {
		m_noteDominante = i_gamme.substr(0,1);
		m_typeGamme    = i_gamme.substr(1);
	}

}


void Gamme::setGamme(
		std::string const& i_gamme) {
	if (i_gamme.substr(1,1)=="#") {
		m_noteDominante = i_gamme.substr(0,2);
		m_typeGamme   = i_gamme.substr(2);
	}
	else {
		m_noteDominante = i_gamme.substr(0,1);
		m_typeGamme    = i_gamme.substr(1);
	}

}


void Gamme::nomNotes(
		std::vector<std::string> &o_list) {

	o_list.clear();
	if (m_typeGamme == "maj") {
		o_list.resize(7);
		o_list[0] = m_noteDominante;
		m_note.decalage(m_noteDominante, 2, o_list[1]);
		m_note.decalage(m_noteDominante, 4, o_list[2]);
		m_note.decalage(m_noteDominante, 5, o_list[3]);
		m_note.decalage(m_noteDominante, 7, o_list[4]);
		m_note.decalage(m_noteDominante, 9, o_list[5]);
		m_note.decalage(m_noteDominante, 11, o_list[6]);
	}
	else {
		if (m_typeGamme == "min") { // ici il faut remplacer avec les vraiess valeurs pour une gamme mineure
			o_list.resize(7);
			o_list[0] = m_noteDominante;
			m_note.decalage(m_noteDominante, 2, o_list[1]);
			m_note.decalage(m_noteDominante, 4, o_list[2]);
			m_note.decalage(m_noteDominante, 5, o_list[3]);
			m_note.decalage(m_noteDominante, 7, o_list[4]);
			m_note.decalage(m_noteDominante, 9, o_list[5]);
			m_note.decalage(m_noteDominante, 11, o_list[6]);

		}
		// ici il faut completer avec le reste des types de gamme possibles

	}

}

	Gamme::~Gamme() {
		// TODO Auto-generated destructor stub
	}

