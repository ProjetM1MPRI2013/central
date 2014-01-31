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

const int m_GAMME_MAJEURE=0;
// ici il faut completer avec les autres gammes
int m_nbMesures =4;// Pour l'exemple.
string m_dominante;
Parametres m_parametres = Parametres(0) ;
map<string,int> m_accords;
//Random generateur ;



GrilleHarmonique::GrilleHarmonique(Parametres p, string dom) {
	m_dominante=dom;
	m_parametres=p;



	if(p.m_harmonie == GrilleHarmonique::m_GAMME_MAJEURE){

		// attention il faut créer un accord à partir du contenu de la map
		m_accords[ m_dominante + "maj"]  =   3;
		m_accords[ Note::decalage(m_dominante,2) + "min"]  =   1;
		m_accords[ Note::decalage(m_dominante,4) + "min" ]  =   1;
		m_accords[ Note::decalage(m_dominante,5) + "maj" ]  =   2;
		m_accords[ Note::decalage(m_dominante,7) + "maj" ]  =   2;
		m_accords[ Note::decalage(m_dominante,9) + "min" ]  =   1;
		// Ici on a remplit la hashmap avec des strings qui correspondent aux accords+ proba
		// reste à compléer avec les autres types de gamme
	}



}
// tire un accord au hasard avec les probabilités de la hashmap
Accord GrilleHarmonique::randomAccord(){
	int somme=0;
	for( map<string,int>::iterator itMap=m_accords.begin() ; itMap!= m_accords.end(); ++itMap){
		somme += itMap->second;
	}
	int alea;
	alea = rand()%somme;
	cout<<alea<<endl;
	for ( map<string,int>::iterator itMap=m_accords.begin() ; itMap!= m_accords.end(); ++itMap){
		if ( alea < (itMap->second)){
			return Accord(itMap->first);
		}

		alea = (alea -(itMap->second));
		cout << alea<< endl;
	}

	Accord a("C#maj");  // pas reussi a ne rien retourner
	return a;
}

// retourne le tableau de la grille harmonique de taille nb_mesure remplit avec nb_mesures accords tirés au sort.


 /*Accord* tabGrille(){

	string tab[m_nbMesures];
	for (int i =0  ; i<m_nbMesures; i++){
		Accord a =  GrilleHarmonique::randomAccord();

	}
	return tab;
}
a debuger
*/
GrilleHarmonique::~GrilleHarmonique() {

}

