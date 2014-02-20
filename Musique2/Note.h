/*
 * Notes.h
 *
 *  Created on: 24 janv. 2014
 *      Author: riesner
 */

#ifndef NOTE_H_
#define NOTE_H_

#include <string>
#include <vector>

class Note {
public:
	std::vector<std::string>  m_notes ; // tableau des notes

	int indNote(std::string const& i_note); // donne l'indice de la note dans le tableau
	void decalage(
		std::string const& i_note,
		const int i_decalage,
		std::string &o_note); // calcule l'indice(note) + int modulo nb de notes
	Note();
	virtual ~Note();;
};

#endif /* NOTE_H_ */
