/*
 * Basse.h
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#ifndef BASSE_H_
#define BASSE_H_

#include "Base.h"


class Basse : public Base {
public:

	int m_nbNotesAjoutees;
	std::vector<std::string> m_tabNotes;
	std::string m_instrument;

	Basse(
	std::string const& i_dominante,
	std::vector<Accord> const& i_tabAccord,
	const unsigned int i_nbNotesAjoutees);

	virtual ~Basse();

	void generePiste(
		std::vector<CelluleNote> &o_piste,
		std::string &o_instrument,
		const unsigned int i_tempo);
};

#endif /* BASSE_H_ */
