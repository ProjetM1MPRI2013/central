/*
 * Gamme.h
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#ifndef GAMME_H_
#define GAMME_H_
#include <vector>
#include <string>
#include "Note.h"


class Gamme {
public:


	std::string m_noteDominante ; // exemple C(do)
	std::string m_typeGamme ; // exemple min7
	Note m_note;
	Gamme();
	Gamme(std::string const& i_gamme);
	void setGamme(std::string const& i_gamme);

	void nomNotes(
			std::vector<std::string> &o_list); // methode qui modifie la liste des notes de la gamme.

	virtual ~Gamme();
};

#endif /* GAMME_H_ */
