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

	static const int m_GAMME_MAJEURE=0; //choisit si on est en gamme majeure ou mineur. Pour l'insant par défaut majeure
	int m_nbMesure; // nb de mesures qu'on génère
	std::string m_dominante; // Les accords qu'on tire au sort soeront dans la gamme de cette note dominante.
	Parametres m_parametres ; //harmonie
	std::map<std::string,int> m_accords; // la string c'est l'acccord, l'entier c'es sa probabilité d'être tiré au sort.
	// la map associe à chaque accord sa probabailité d'être tiré.



	GrilleHarmonique(Parametres p,std::string dom );
	Accord randomAccord(); // tire au sort les accords avec leur probabilité d'être tirés
	Accord* tabGrille();

	virtual ~GrilleHarmonique();
};

#endif /* GRILLEHARMONIQUE_H_ */
