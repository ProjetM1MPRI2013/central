/*
 * Accompagnement.h
 *
 *  Created on: 14 févr. 2014
 *      Author: riesner
 */

#ifndef ACCOMPAGNEMENT_H_
#define ACCOMPAGNEMENT_H_

#include "Base.h"

class Accompagnement : public Base {
public:

	int m_nbNotesAjoutees;
	std::vector<std::string> m_tabNotes;
	std::string m_instrument;

	Accompagnement(
		std::string const& i_dominante,
		std::vector<Accord> const& i_tabAccord,
		const unsigned int i_nbNotesAjoutees);

	virtual ~Accompagnement();

	void generePiste(
		std::vector<CelluleAccord> &o_piste,
		std::string &o_instrument,
		const unsigned int i_tempo);

};

#endif /* ACCOMPAGNEMENT_H_ */
