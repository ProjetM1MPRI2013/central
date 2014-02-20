/*
 * Musique.h
 *
 *  Created on: 17 févr. 2014
 *      Author: riesner
 */

#ifndef MUSIQUE_H_
#define MUSIQUE_H_

#include "Accompagnement.h"
#include "Basse.h"
#include "Melodie.h"
#include "Base.h"

class Musique {

public:

	Musique();

	virtual ~Musique();

	void setStress(
		const bool i_stress);

	void nextMesures(
		std::vector<CelluleAccord> &o_mesureAccompagnement,
		std::vector<CelluleNote> &o_mesureBasse,
		std::vector<CelluleNote> &o_mesureMelodie,
		std::string &o_instrumentAccompagnement,
		std::string &o_instrumentBasse,
		std::string &o_instrumentMelodie,
		unsigned int &o_tempo);

private:

	Accompagnement *m_accompagnementNormal, *m_accompagnementSpeed;
	Basse *m_basseNormal, *m_basseSpeed;
	Melodie *m_melodieNormal, *m_melodieSpeed;
	bool m_stress;
};

#endif /* MUSIQUE_H_ */
