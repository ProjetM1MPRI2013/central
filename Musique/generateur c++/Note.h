/*
 * Notes.h
 *
 *  Created on: 24 janv. 2014
 *      Author: riesner
 */

#ifndef NOTE_H_
#define NOTE_H_

#include <string>

class Note {
public:
	static std::string  m_notes[] ; // tableau des notes
	static int indNote(std::string note); // donne l'indice de la note dans le tableau
	static std::string decalage(std::string note, int decalage); // calcule l'indice(note) + int modulo nb de notes
	Note();
	virtual ~Note();
};

#endif /* NOTE_H_ */
