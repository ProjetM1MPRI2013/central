/*
 * Accord.cpp
 *
 *  Created on: 2 janv. 2014
 *      Author: riesner
 */
#include "Accord.h"
#include <iostream>
#include <string>
#include<list>
#include<map>

using namespace std;

//string m_noteDominante ; // exemple C(do)
//string m_typeAccord ; // exemple Maj

Accord::Accord() {
	m_noteDominante = "C";
	m_typeAccord    = "maj";
}  // valeur par défaut = Cmaj


//methode qui remplit la note dominante et le type d'accord, a parti d'une string "Cmaj7" :
Accord::Accord(
	std::string const& i_accord) {

	if (i_accord.substr(1,1)=="#") {
		m_noteDominante = i_accord.substr(0,2);
		m_typeAccord    = i_accord.substr(2);
	}
	else {
		m_noteDominante = i_accord.substr(0,1);
		m_typeAccord    = i_accord.substr(1);
	}

}

void Accord::setAccord(
	std::string const& i_accord) {

	if (i_accord.substr(1,1)=="#") {
		m_noteDominante = i_accord.substr(0,2);
		m_typeAccord    = i_accord.substr(2);
	}
	else {
		m_noteDominante = i_accord.substr(0,1);
		m_typeAccord    = i_accord.substr(1);
	}
}


/* list<string> list;
nomNotes(list);
*/

// methode qui retourne la liste des notes de l'accord :
void Accord::nomNotes(
	std::vector<std::string> &o_list) {

	o_list.clear();
	if (m_typeAccord == "min") {
		o_list.resize(3);
		o_list[0] = m_noteDominante;
		m_note.decalage(m_noteDominante, 3, o_list[1]);
		m_note.decalage(m_noteDominante, 7, o_list[2]);
	}
	else {
		o_list.resize(3);
		o_list[0] = m_noteDominante;
		m_note.decalage(m_noteDominante, 4, o_list[1]);
		m_note.decalage(m_noteDominante, 7, o_list[2]);
	}
	// ici il faut completer avec le reste des types d'accords possibles

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
