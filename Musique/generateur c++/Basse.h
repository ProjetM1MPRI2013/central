/*
 * Basse.h
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#ifndef BASSE_H_
#define BASSE_H_

class Basse {
public:
	int nbNotesAjoutes;

	Basse(std::string i_m_dominante, std::vector<std::string> tabAccord, int i_nbNotesAjoutes);

	nbNotesAjoutes = nbNotesAjoutes;

	virtual ~Basse();
};

#endif /* BASSE_H_ */
