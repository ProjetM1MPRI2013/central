/*
 * Melodie.h
 *
 *  Created on: 14 févr. 2014
 *      Author: riesner
 */

#ifndef MELODIE_H_
#define MELODIE_H_

#include "Base.h"

class Melodie : public Base {
public:

	std::vector<std::string> m_tabNotes;
	std::string m_instrument;

	Melodie(
		std::string const& i_dominante,
		std::vector<Accord> const& i_tabAccord);

	virtual ~Melodie();

	virtual void generePiste(
		std::string &o_piste);
};

#endif /* MELODIE_H_ */
