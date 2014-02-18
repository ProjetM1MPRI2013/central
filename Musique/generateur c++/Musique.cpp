/*
 * Musique.cpp
 *
 *  Created on: 17 févr. 2014
 *      Author: riesner
 */

#include "Musique.h"
#include "GrilleHarmonique.h"

using namespace std;

Musique::Musique() {

	// Initialisation
	Parametres param(0);
	const string dominante = "C";
	const int gamme        = 0; // GAMME_MAJEURE
	const int nbMesures    = 4;
	m_stress               = false;

	// Grille harmonique
	GrilleHarmonique ghNormal(param, dominante, gamme, nbMesures);
	GrilleHarmonique ghSpeed (param, dominante, gamme, nbMesures);

	// Grille
	vector<Accord> grilleNormal, grilleSpeed;
	ghNormal.tabGrille(grilleNormal);
	ghSpeed .tabGrille(grilleSpeed );

	// Accompagnement
	m_accompagnementNormal = new Accompagnement(ghNormal.m_dominante, grilleNormal, 10);
	m_accompagnementSpeed  = new Accompagnement(ghSpeed .m_dominante, grilleSpeed , 20);

	// Basse
	m_basseNormal = new Basse(ghNormal.m_dominante, grilleNormal, 20);
	m_basseSpeed  = new Basse(ghSpeed .m_dominante, grilleSpeed , 40);

	// Melodie
	m_melodieNormal = new Melodie(ghNormal.m_dominante, grilleNormal);
	m_melodieSpeed  = new Melodie(ghSpeed .m_dominante, grilleSpeed );
}

Musique::~Musique() {
	// TODO Auto-generated destructor stub
}

void Musique::setStress(
	const bool i_stress){

	m_stress = i_stress;
}

/*void Musique::getTempo(
	std::string &o_tempo){

	o_tempo = "[" + (m_stress ? "180" : "90") + "]";
}*/

void Musique::nextMesures(
	std::vector<std::string> &o_mesure){

	o_mesure.resize(3);
	if (m_stress) {
		m_basseSpeed          ->generePiste(o_mesure[0]);
		m_accompagnementSpeed ->generePiste(o_mesure[1]);
		m_melodieSpeed        ->generePiste(o_mesure[2]);
	}
	else {
		m_basseNormal         ->generePiste(o_mesure[0]);
		m_accompagnementNormal->generePiste(o_mesure[1]);
		m_melodieNormal       ->generePiste(o_mesure[2]);
	}

	const string tempo = (string) "T" + (m_stress ? "[180]" : "[90]") + (string) " ";

	o_mesure[0] = "V1 " + tempo + o_mesure[0];
	o_mesure[1] = "V2 " + tempo + o_mesure[1];
	o_mesure[2] = "V3 " + tempo + o_mesure[2];
}






