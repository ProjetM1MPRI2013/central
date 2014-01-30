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


string Note::m_notes[] = { "C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};


int Note::indNote(string note){
	for (int i = 0; i < 12; i++) {
		if (m_notes[i]==note) {
			return i;
		}
	}

	return -1;
}

string Note::decalage(string note,int decalage){
	return m_notes[(indNote(note)+decalage)%12];
}

Note::Note() {

}


Note::~Note() {
}

