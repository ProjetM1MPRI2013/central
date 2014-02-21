/*
 * Note.cpp
 *
 *  Created on: 24 janv. 2014
 *      Author: riesner
 */

#include "Note.h"
#include <iostream>
#include <string>

using namespace std;

int Note::indNote(
	std::string const& i_note){

	for (unsigned int i = 0; i < m_notes.size(); i++) {
		if (m_notes[i] == i_note) {
			return i;
		}
	}

	return -1;
}

void Note::decalage(
	std::string const& i_note,
	const int i_decalage,
	std::string &o_note){

	o_note = m_notes[(indNote(i_note) + i_decalage) % m_notes.size()];
}

Note::Note() {
	m_notes.resize(12);
	m_notes[ 0] = "C";
	m_notes[ 1] = "C#";
	m_notes[ 2] = "D";
	m_notes[ 3] = "D#";
	m_notes[ 4] = "E";
	m_notes[ 5] = "F";
	m_notes[ 6] = "F#";
	m_notes[ 7] = "G";
	m_notes[ 8] = "G#";
	m_notes[ 9] = "A";
	m_notes[10] = "A#";
	m_notes[11] = "B";
}


Note::~Note() {
}

