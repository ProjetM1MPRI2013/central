/*
 * Accord.cpp
 *
 *  Created on: 2 janv. 2014
 *      Author: riesner
 */
#include "Note.h"
#include "Accord.h"
#include <iostream>
#include <string>
#include<list>
#include<map>

using namespace std;

string m_noteDominante ; // exemple C(do)
string m_typeAccord ; // exemple Maj

//methode qui remplit la note dominante et le type d'accord, a parti d'une string "Cmaj7" :
Accord::Accord(string accord) {
	if (accord.substr(1,1)=="#") {
		m_noteDominante= accord.substr(0,2);
		m_typeAccord = accord.substr(2);
	}
	else {
		m_noteDominante= accord.substr(0,1);
		m_typeAccord = accord.substr(1);
	}

}


// methode qui retourne la liste des notes de l'accord :
list<string> Accord::nomNotes() {
	list<string> liste ;
	if (m_typeAccord == "min") {

		liste.push_back(m_noteDominante);
		liste.push_back(Note::decalage(m_noteDominante,3));
		liste.push_back(Note::decalage (m_noteDominante,7));
	}
	else {
		liste.push_back(m_noteDominante);
		liste.push_back(Note::decalage(m_noteDominante,4));
		liste.push_back(Note::decalage (m_noteDominante,7));
	}
	// ici il faut completer avec le reste des types d'accords possibles
	return liste;

}
// TODO La hashmap eventuellement

Accord::~Accord() {
	// TODO Auto-generated destructor stub
}

namespace std {
// definit l'operateur de comparaison entre deux accords
template<> struct less<Accord>
{
	bool operator() (const Accord& a, const Accord& b){
		return 	(a.m_noteDominante+a.m_typeAccord) < (b.m_noteDominante+b.m_typeAccord);
	}

};
}
