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

struct CelluleNote
{
	std::string note;
	unsigned int octave;
	float frequence;
	float duree;
};

struct CelluleAccord
{
	std::string note1;
	float frequence1;
	std::string note2;
	float frequence2;
	std::string note3;
	float frequence3;
	unsigned int octave;
	float duree;
};

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

	float getFrequence(
		const std::string &i_note,
		const unsigned int i_octave);
};

#endif /* BASE_H_ */
