/*
 * GrilleHarmonique.h
 *
 *  Created on: 2 janv. 2014
 *      Author: riesner
 */

#ifndef GRILLEHARMONIQUE_H_
#define GRILLEHARMONIQUE_H_
#include "Note.h"
#include "Accord.h"
#include <iostream>
#include <string>
#include <map>
#include "Parametres.h"
#include <stdlib.h>
#include "Accord.h"

class GrilleHarmonique {
public:

	int m_GAMME_MAJEURE; //choisit si on est en gamme majeure ou mineur. Pour l'insant par défaut majeure
	int m_nbMesure; // nb de mesures qu'on génère
	std::string m_dominante; // Les accords qu'on tire au sort soeront dans la gamme de cette note dominante.
	Parametres m_parametres; //harmonie
	std::map<std::string, int> m_accords; // la string c'est l'acccord, l'entier c'est sa probabilité d'être tiré au sort.
	// la map associe à chaque accord sa probabilité d'être tiré.
	Note m_note;


	GrilleHarmonique(
		Parametres const& i_param,
		std::string const& i_dom,
		const int i_gamme,
		const int i_nbMesure); //constructeur

	void randomAccord(
		Accord& o_accord); // tire au sort les accords avec leur probabilité d'être tirés
	//Accord* tabGrille(); // a rajouter

	void tabGrille(
		std::vector<Accord> &o_partition);

	virtual ~GrilleHarmonique();
};

#endif /* GRILLEHARMONIQUE_H_ */
