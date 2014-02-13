/*
 * Accord.h
 *
 *  Created on: 24 janv. 2014
 *      Author: riesner
 */

#ifndef ACCORD_H_
#define ACCORD_H_
#include <vector>
#include <string>
#include "Note.h"

class Accord {
public:


	std::string m_noteDominante ; // exemple C(do)
	std::string m_typeAccord ; // exemple maj
	Note m_note;

	Accord();
	Accord(std::string const& i_accord); // exemple Accord("Cmin7")
	void setAccord(std::string const& i_accord);
	virtual ~Accord();

	void nomNotes(
		std::vector<std::string> &o_list); // methode qui modifie la liste des notes de l'accord.
};

#endif /* ACCORD_H_ */
