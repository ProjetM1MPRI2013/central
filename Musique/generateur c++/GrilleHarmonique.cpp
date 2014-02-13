/*
 * GrilleHarmonique.cpp
 *
 *  Created on: 2 janv. 2014
 *      Author: riesner
 */

#include "GrilleHarmonique.h"
#include "Note.h"
#include "Accord.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "Parametres.h"
#include <stdlib.h>
#include "Accord.h"

using namespace std;

/*const int m_GAMME_MAJEURE=0;
// ici il faut completer avec les autres gammes
int m_nbMesures =4;// Pour l'exemple.
string m_dominante;
Parametres m_parametres = Parametres(0) ;
map<string,int> m_accords;
//Random generateur ;
*/


GrilleHarmonique::GrilleHarmonique(
	Parametres const& i_param,
	std::string const& i_dom,
	const int i_gamme,
	const int i_nbMesure) {

	//! Initialisation
	m_GAMME_MAJEURE = i_gamme;
	m_dominante     = i_dom;
	m_parametres    = i_param;
	m_nbMesure      = i_nbMesure;


	if(i_param.m_harmonie == m_GAMME_MAJEURE){
		// attention il faut créer un accord à partir du contenu de la map
		m_accords[m_dominante + "maj"] = 3;
		string note;
		m_note.decalage(m_dominante, 2, note);
		m_accords[note + "min"] = 1;
		m_note.decalage(m_dominante, 4, note);
		m_accords[note + "min"] = 1;
		m_note.decalage(m_dominante, 5, note);
		m_accords[note + "maj"] = 2;
		m_note.decalage(m_dominante, 7, note);
		m_accords[note + "maj"] = 2;
		m_note.decalage(m_dominante, 9, note);
		m_accords[note + "min"] = 1;
		// Ici on a remplit la hashmap avec des strings qui correspondent aux accords+ proba
		// reste à compléer avec les autres types de gamme
	}
}


// tire un accord au hasard avec les probabilités de la hashmap
void GrilleHarmonique::randomAccord(
	Accord& o_accord){

	int somme = 0;
	for (map<string,int>::iterator itMap = m_accords.begin(); itMap != m_accords.end(); ++itMap){
		somme += itMap->second;
	}
	int alea;
	alea = rand()%somme;
	//cout<<alea<<endl;
	for (map<string,int>::iterator itMap = m_accords.begin(); itMap != m_accords.end(); ++itMap){
		if ( alea < (itMap->second)){
			o_accord.setAccord(itMap->first);
			return;
		}

		alea = (alea -(itMap->second));
		//cout << alea<< endl;
	}

	o_accord.setAccord("C#maj");  // pas reussi a ne rien retourner
}

// retourne le tableau de la grille harmonique de taille nb_mesure remplit avec nb_mesures accords tirés au sort.


void GrilleHarmonique::tabGrille(
	std::vector<std::string> &o_partition){

	//! Initialisastion
	o_partition.resize(m_nbMesure);
	Accord accord;

	for (int i = 0 ; i < m_nbMesure; i++){
		randomAccord(accord);
		o_partition[i] = accord.m_noteDominante + accord.m_typeAccord;
	}
}


GrilleHarmonique::~GrilleHarmonique() {

}

