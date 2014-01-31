/*
 * Accord.h
 *
 *  Created on: 24 janv. 2014
 *      Author: riesner
 */

#ifndef ACCORD_H_
#define ACCORD_H_
#include <list>
#include <string>

class Accord {
public:


	std::string m_noteDominante ; // exemple C(do)
	std::string m_typeAccord ; // exemple maj

	Accord(std::string accord); // exemple Accord("Cmin7")
	virtual ~Accord();

	std::list<std::string> nomNotes(); // methode qui renvoie la liste des notes de l'accord.
};

#endif /* ACCORD_H_ */
