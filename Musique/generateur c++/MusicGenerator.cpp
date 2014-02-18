//============================================================================
// Name        : MusicGenerator.cpp
// Author      : melissa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Note.h"
#include "Accord.h"
#include "Accompagnement.h"
#include "Basse.h"
#include "Melodie.h"
#include "Musique.h"
#include <vector>
#include "GrilleHarmonique.h"


int main() {
	srand( time(NULL)); // obligatoire pour initialisation de l'aleatoire

	Musique musique;
	vector<string> mesures;
	musique.nextMesures(mesures);
	for (unsigned int k = 0; k < mesures.size(); k++) {
		cout << endl << mesures[k] << endl;
	}

	/*vector<Accord> tabAccord(4);
	Accord accord("Amaj");
	tabAccord[0] = accord;
	accord.setAccord("C#min");
	tabAccord[1] = accord;
	accord.setAccord("Bmin");
	tabAccord[2] = accord;
	accord.setAccord("Emaj");
	tabAccord[3] = accord;*/
	/*Basse basse("A", tabAccord, 3);
	string piste;
	basse.generePiste(piste);
	cout << piste << endl;*/
	/*Accompagnement accompagnement("A", tabAccord, 3);
	string piste;
	accompagnement.generePiste(piste);
	cout << piste << endl;*/
	/*Melodie melodie("A", tabAccord);
	string piste;
	melodie.generePiste(piste);
	cout << piste << endl;*/

	/*Note note;
	int i = note.indNote("E");
	cout << i << endl;
	string name;
	note.decalage("A#", 3, name);
	cout << name << endl;*/

	/*Accord accord = Accord("C#min");
	vector<string> listNote;
	accord.nomNotes(listNote);
	for (unsigned int i = 0; i < listNote.size(); i++) {
		cout << listNote[i] << endl;
	}
	cout << "note dominante = " << accord.m_noteDominante << endl;
	cout << "type d'accord  = " << accord.m_typeAccord << endl;*/

	/*Parametres param;
	GrilleHarmonique grille = GrilleHarmonique(param,"C", 0, 4);
	vector<string> partition;
	grille.tabGrille(partition);
	for(unsigned int i = 0; i < partition.size(); i++){
		cout << partition[i] << endl;
	}*/


	return 0;
}
