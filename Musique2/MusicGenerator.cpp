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
#include "Base.h"
#include "Basse.h"
#include "Melodie.h"
#include "Musique.h"
#include <vector>
#include "GrilleHarmonique.h"


int main() {

	srand( time(NULL)); // obligatoire pour initialisation de l'aleatoire

	Musique musique;
	vector<CelluleAccord> mesureAccompagnement;
	vector<CelluleNote  > mesureBasse;
	vector<CelluleNote  > mesureMelodie;
	string instrumentAccompagnement;
	string instrumentBasse;
	string instrumentMelodie;
	unsigned int tempo;
	bool stress = false;
	musique.setStress(stress);
	musique.nextMesures(mesureAccompagnement, mesureBasse,mesureMelodie,
						instrumentAccompagnement, instrumentBasse, instrumentMelodie, tempo);
	cout << "Tempo = " << tempo << endl;
	cout << endl;
	float dureeAccompagnement = 0.f;
	float dureeBasse          = 0.f;
	float dureeMelodie        = 0.f;
	cout << "sizeAccompagnement = " << mesureAccompagnement.size() << endl;
	cout << "sizeBasse          = " << mesureBasse.size() << endl;
	cout << "sizeMelodie        = " << mesureMelodie.size() << endl;
	for (unsigned int k = 0; k < mesureAccompagnement.size(); k++) {
		dureeAccompagnement += mesureAccompagnement[k].duree;
	}
	for (unsigned int k = 0; k < mesureBasse.size(); k++) {
		dureeBasse += mesureBasse[k].duree;
	}
	for (unsigned int k = 0; k < mesureMelodie.size(); k++) {
		dureeMelodie += mesureMelodie[k].duree;
	}
	cout << "duree Accompagnement = " << dureeAccompagnement << endl;
	cout << "duree Basse          = " << dureeBasse          << endl;
	cout << "duree Melodie        = " << dureeMelodie        << endl;
	/*cout << "InstrumentAccompagnement = " << instrumentAccompagnement << endl;
	for (unsigned int i = 0; i < mesureAccompagnement.size(); i++) {
		cout << "note1      = " << mesureAccompagnement[i].note1 << endl;
		cout << "note2      = " << mesureAccompagnement[i].note2 << endl;
		cout << "note3      = " << mesureAccompagnement[i].note3 << endl;
		cout << "octave     = " << mesureAccompagnement[i].octave << endl;
		cout << "frequence1 = " << mesureAccompagnement[i].frequence1 << endl;
		cout << "frequence2 = " << mesureAccompagnement[i].frequence2 << endl;
		cout << "frequence3 = " << mesureAccompagnement[i].frequence3 << endl;
		cout << "duree      = " << mesureAccompagnement[i].duree << endl;
	}
	cout << endl;
	cout << endl;
	cout << "InstrumentBasse = " << instrumentBasse<< endl;
	for (unsigned int i = 0; i < mesureBasse.size(); i++) {
		cout << "note      = " << mesureBasse[i].note << endl;
		cout << "octave    = " << mesureBasse[i].octave << endl;
		cout << "frequence = " << mesureBasse[i].frequence << endl;
		cout << "duree     = " << mesureBasse[i].duree << endl;
	}
	cout << endl;
	cout << endl;
	cout << "InstrumentMelodie = " << instrumentMelodie << endl;
	for (unsigned int i = 0; i < mesureMelodie.size(); i++) {
		cout << "note      = " << mesureMelodie[i].note << endl;
		cout << "octave    = " << mesureMelodie[i].octave << endl;
		cout << "frequence = " << mesureMelodie[i].frequence << endl;
		cout << "duree     = " << mesureMelodie[i].duree << endl;
	}
	cout << endl;*/
	cout << "done" << endl;

	/*vector<Accord> tabAccord(4);
	Accord accord("Bmin");
	tabAccord[0] = accord;
	accord.setAccord("Cmaj");
	tabAccord[1] = accord;
	accord.setAccord("Fmaj");
	tabAccord[2] = accord;
	accord.setAccord("Emin");
	tabAccord[3] = accord;
//emin fmaj gmaj amin
	Base b("A", tabAccord);
	float f = b.getFrequence("A",3);
	Basse basse("C", tabAccord, 3);
	vector<CelluleNote> celvect;
	string s = "[33]";

	basse.generePiste(celvect,s,190);
*/


	//string piste;
	//basse.generePiste(piste);
	//cout << piste << endl;*/
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
