/*
 * Base.cpp
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#include "Base.h"
#include <vector>
#include <string>

using namespace std;

Base::Base(
	std::string const& i_dominante,
	std::vector<Accord> const& i_tabAccord) {

	m_dominante = i_dominante;
	m_tabAccord = i_tabAccord;
	m_nbMesures = i_tabAccord.size();
	m_nbTemps   = 8;
}

Base::~Base() {
	// TODO Auto-generated destructor stub
}

void Base::generePiste(
	std::string &o_piste) {

}

