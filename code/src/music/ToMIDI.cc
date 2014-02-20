#include "ToMIDI.h"
#define DEBUG true
#include "debug.h"
#include <stdio.h>
#include <iostream>

void set_instrument (fluid_synth_t * synth, int channel, int instrument){
  fluid_synth_program_change (synth, channel, instrument);
}


MIDIEvent::MIDIEvent()  : time(0), MIDInumber(0) {}; 

MIDIEvent::MIDIEvent(float f, int n) : time(f), MIDInumber(n) {};

void MIDIEvent::print (){
  std::cout << "MIDI : " << time << " " << MIDInumber << std::endl;
}

/**
 * Give the offset for converting the note to a MIDI code
 */
int note_offset (char c){
  if ('A'== c){
    return 9;
  } else if ('B'== c){
    return 11;
  } else if ('C'== c){
    return 0;
  } else if ('D'== c){
    return 2;
  } else if ('E'== c){
    return 4;
  } else if ('F'== c){
    return 5;
  } else if ('G'== c){
    return 7;
  } else {
    DBG << "Music note unknown " << c;
  }
  return 0;
}

/**
 * Return the MIDI code of the corresponding note
 */
int note_to_midi (char s, int octave){
  return note_offset(s) + 12 * octave;
}



/**
 * Return the time value of c (times 8)
 */
int time_value (char c){
  if (c=='i'){
    return 1;
  } else if (c=='q'){
    return 2;
  } else if (c=='h'){
    return 4;
  } else if (c=='w'){
    return 8;
  } else {
    DBG << "time_value error";
  }
  return 0;
}


/**
 * Return the time in seconds corresponding to the string s
 */
float parse_time (std::string s, int tempo){
  float acc = 0;
  for (char it : s){
    acc += (time_value(it) / 8) / (tempo / 120);
  }
  return acc;
}


/**
 * Turn an accord into a vector of 3 notes
 */
std::vector<int> accord_to_vect(std::string s){
  std::vector<int> temp;
  if (s.compare("Cmaj")){
    temp.push_back(note_to_midi('A',5));
    temp.push_back(note_to_midi('E',5));
    temp.push_back(note_to_midi('G',5));
  } else if (s.compare("Dmin")){
    temp.push_back(note_to_midi('D',5));
    temp.push_back(note_to_midi('F',5));
    temp.push_back(note_to_midi('A',5));
  } else if (s.compare("Emin")){
    temp.push_back(note_to_midi('E',5));
    temp.push_back(note_to_midi('G',5));
    temp.push_back(note_to_midi('B',5));
  } else if (s.compare("Fmaj")){
    temp.push_back(note_to_midi('F',5));
    temp.push_back(note_to_midi('A',5));
    temp.push_back(note_to_midi('C',5));
  } else if (s.compare("Gmaj")){
    temp.push_back(note_to_midi('G',5));
    temp.push_back(note_to_midi('B',5));
    temp.push_back(note_to_midi('D',5));
  } else if (s.compare("Amin")){
    temp.push_back(note_to_midi('A',5));
    temp.push_back(note_to_midi('C',5));
    temp.push_back(note_to_midi('E',5));
  } else {
    DBG << "Accord inconnu " << s;
  }
  return std::vector<int>(temp);
}



std::vector<MIDIEvent> parse_notes (std::string s, int tempo){
  unsigned long next = 0;
  unsigned long next2 = s.find(" ",1);
  unsigned long looptest = 0;
  std::vector<MIDIEvent> out;
  DBG << "parse_notes " << s;
  while (looptest != std::string::npos){
    DBG << "values : " << next << " " << next2;
    int octave = 5;
    std::string tempostring;
    if ((s[next+1] == '0') || (s[next+1] == '1') || (s[next+1] == '2') || (s[next+1] == '3') || (s[next+1] == '4') || (s[next+1] == '5')){
      octave = s[next+2];
      tempostring = s.substr(next + 2, next2 - next - 2);
    } else{
      tempostring = s.substr(next + 1, next2 - next - 1);
    }
    DBG << "tempostring " << tempostring;
    getchar();
    MIDIEvent temp = MIDIEvent(parse_time(tempostring,tempo),note_to_midi(s[next],octave));
    temp.print();
    out.push_back(temp);
    next = next2 + 1;
    looptest = next2;
    next2 = s.find(" ",next);
    DBG << "lololol " << std::string::npos << " " <<next;
  }
  return std::vector<MIDIEvent>(out);
}
