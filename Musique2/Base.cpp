/*
 * Base.cpp
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#include "Base.h"
#include <vector>
#include <string>
#include <math.h>

using namespace std;

Base::Base(
		std::string const& i_dominante,
		std::vector<Accord> const& i_tabAccord) {

	m_dominante = i_dominante;
	m_tabAccord = i_tabAccord;
	m_nbMesures = i_tabAccord.size();
	m_nbTemps   = 8;
}

float Base::getFrequence(
		const std::string &i_note,
		const unsigned int i_octave) {

	float frequence;
	if (i_note == "C") {
		frequence = 32.70f;
	}
	else if (i_note == "D") {
		frequence = 36.71f;
	}
	else if (i_note == "E") {
		frequence = 41.20f;
	}
	else if (i_note == "F") {
		frequence = 43.65f;
	}
	else if (i_note == "G") {
		frequence = 49.00f;
	}
	else if (i_note == "A") {
		frequence = 55.00f;
	}
	else {
		frequence = 61.74f;
	}

	return frequence * pow(2.f, (float) i_octave);
}


Base::~Base() {
	// TODO Auto-generated destructor stub
}

// void Base::generePiste(
		//std::string &o_piste,
		//int tempo ) {

//}

