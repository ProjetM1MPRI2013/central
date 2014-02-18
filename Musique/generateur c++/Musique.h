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

class Musique {

public:

	Musique();

	virtual ~Musique();

	void setStress(
		const bool i_stress);

	/*void getTempo(
		std::string &o_tempo);*/

	void nextMesures(
		std::vector<std::string> &o_mesure);

private:
	Accompagnement *m_accompagnementNormal, *m_accompagnementSpeed;
	Basse *m_basseNormal, *m_basseSpeed;
	Melodie *m_melodieNormal, *m_melodieSpeed;
	bool m_stress;
};

#endif /* MUSIQUE_H_ */
