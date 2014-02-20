/*
 * Base.h
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#ifndef BASE_H_
#define BASE_H_
#include <vector>
#include <string>

#include "Accord.h"

class Base {
public:
	std::string m_dominante;
	std::vector<Accord> m_tabAccord;
	unsigned int m_nbMesures;
	unsigned int m_nbTemps; // Nombre de temps dans une mesure (8)

	Base(
		std::string const& i_dominante,
		std::vector<Accord> const& i_tabAccord);

	virtual ~Base();

	virtual void generePiste(
		std::string &o_piste);
};

#endif /* BASE_H_ */
