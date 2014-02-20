/*
 * Musique.cpp
 *
 *  Created on: 17 févr. 2014
 *      Author: riesner
 */

#include "Musique.h"
#include "GrilleHarmonique.h"

#include <math.h>

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

void Musique::nextMesures(
	std::vector<CelluleAccord> &o_mesureAccompagnement,
	std::vector<CelluleNote> &o_mesureBasse,
	std::vector<CelluleNote> &o_mesureMelodie,
	std::string &o_instrumentAccompagnement,
	std::string &o_instrumentBasse,
	std::string &o_instrumentMelodie,
	unsigned int &o_tempo) {

	o_tempo = (m_stress ? 180 : 90);

	if (m_stress) {
		m_accompagnementSpeed ->generePiste(o_mesureAccompagnement, o_instrumentAccompagnement, o_tempo);
		m_basseSpeed          ->generePiste(o_mesureBasse         , o_instrumentBasse         , o_tempo);
		m_melodieSpeed        ->generePiste(o_mesureMelodie       , o_instrumentMelodie       , o_tempo);
	}
	else {
		m_accompagnementNormal->generePiste(o_mesureAccompagnement, o_instrumentAccompagnement, o_tempo);
		m_basseNormal         ->generePiste(o_mesureBasse         , o_instrumentBasse         , o_tempo);
		m_melodieNormal       ->generePiste(o_mesureMelodie       , o_instrumentMelodie       , o_tempo);
	}
}



