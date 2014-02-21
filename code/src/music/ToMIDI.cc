#include "ToMIDI.h"
#include "debug.h"
#define DEBUG false
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

void set_instrument (fluid_synth_t * synth, int channel, int instrument){
  cout << "result : " << fluid_synth_program_change (synth, channel, instrument) << " " << FLUID_OK <<endl;
}


MIDIEvent::MIDIEvent()  : begintime(0), duration(0), MIDInumber(0) {isplayed = false;}; 

MIDIEvent::MIDIEvent(float f, float d, int n) : begintime(f), duration(d), MIDInumber(n) {isplayed = false;};

void MIDIEvent::print (){
  std::cout << "MIDI : " << begintime << " " << duration << " " << MIDInumber << std::endl;
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
  assert (octave < 6);
  return note_offset(s) + 12 * octave;
}



/**
 * Return the time value of c (times 8)
 */
float time_value (char c){
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
    acc += (time_value(it) / 8.) / (tempo / 120.);
  }
  return acc;
}


/**
 * Turn an accord into a vector of 3 notes
 */
std::vector<int> accord_to_vect(std::string s){
  std::vector<int> temp;
  if (s.compare("Cmaj") == 0){
    DBG << "comp " << s <<"Cmaj"; 
    temp.push_back(note_to_midi('A',5));
    temp.push_back(note_to_midi('E',5));
    temp.push_back(note_to_midi('G',5));
  } else if (s.compare("Dmin") == 0){
    DBG << "comp " << s << "Dmin"; 
    temp.push_back(note_to_midi('D',5));
    temp.push_back(note_to_midi('F',5));
    temp.push_back(note_to_midi('A',5));
  } else if (s.compare("Emin") == 0){
    DBG << "comp " << s << "Emin"; 
    temp.push_back(note_to_midi('E',5));
    temp.push_back(note_to_midi('G',5));
    temp.push_back(note_to_midi('B',5));
  } else if (s.compare("Fmaj") == 0){
    DBG << "comp " << s << "Fmaj"; 
    temp.push_back(note_to_midi('F',5));
    temp.push_back(note_to_midi('A',5));
    temp.push_back(note_to_midi('C',5));
  } else if (s.compare("Gmaj") == 0){
    DBG << "comp " << s << "Gmaj"; 
    temp.push_back(note_to_midi('G',5));
    temp.push_back(note_to_midi('B',5));
    temp.push_back(note_to_midi('D',5));
  } else if (s.compare("Amin") == 0){
    DBG << "comp " << s << "Amin"; 
    temp.push_back(note_to_midi('A',5));
    temp.push_back(note_to_midi('C',5));
    temp.push_back(note_to_midi('E',5));
  } else {
    DBG << "Accord inconnu " << s;
  }
  return std::vector<int>(temp);
}



std::list<MIDIEvent> parse_notes (std::string s, int tempo){
  unsigned long next = 0;
  unsigned long next2 = s.find(" ",1);
  unsigned long looptest = 0;
  float cumulatetime = 0;
  std::list<MIDIEvent> out;
  DBG << "parse_notes " << s;
  while (looptest != std::string::npos){
    DBG << "values : " << next << " " << next2;
    int octave = 5;
    std::string tempostring;

    if (s[next+1] == 'm'){
      // An accord
      std::vector<int> accord_notes = accord_to_vect(s.substr(next,4));
      DBG << "accord " << s.substr(next,4);
      tempostring = s.substr(next + 4, next2 - next - 4);
      DBG << "tempostring " << tempostring;
      float duration = parse_time(tempostring,tempo);
      cumulatetime += duration;
      DBG << "temps " << cumulatetime;
      for (int i : accord_notes){
	//getchar();
	MIDIEvent temp = MIDIEvent(cumulatetime,duration,i);
	//temp.print();
	out.push_back(temp);
      }
    } else {
      // Not an accord
      if ((s[next+1] == '0') || (s[next+1] == '1') || (s[next+1] == '2') || (s[next+1] == '3') || (s[next+1] == '4') || (s[next+1] == '5')){
	octave = stoi(s.substr(next+1,1));
	tempostring = s.substr(next + 2, next2 - next - 2);
      } else{
	tempostring = s.substr(next + 1, next2 - next - 1);
      }
      DBG << "tempostring " << tempostring;
      //getchar();
      float duration = parse_time(tempostring,tempo);
      cumulatetime += duration;
      if (s[next] != 'R'){
	MIDIEvent temp = MIDIEvent(cumulatetime,duration,note_to_midi(s[next],octave));
	//temp.print();
	out.push_back(temp);
      }
    }
    next = next2 + 1;
    looptest = next2;
    next2 = s.find(" ",next);
    DBG << "variables de la boucle " << std::string::npos << " " <<next;
  }
  std::cout << "Just calculate new musics " << cumulatetime << std::endl;
  return std::list<MIDIEvent>(out);
}


void setNextMesures(Musique& musique, std::vector<std::list<MIDIEvent>>& MIDImusic,fluid_synth_t * synth, bool resetInstrument){
  std::vector<string> mesures;
  musique.nextMesures(mesures);
  MIDImusic.clear();
  MIDImusic = std::vector<std::list<MIDIEvent>>(16);
    for (unsigned int k = 0; k < mesures.size(); k++) {
      cout << "loop " << stoi(mesures[k].substr(1,1)) << " " << MIDImusic.size();
      if (stoi(mesures[k].substr(1,1)) - 1 < (int)MIDImusic.size()){
	cout << "in loop\n";
	cout << mesures[k];
	if (resetInstrument){
	  cout << "set instrument " <<stoi(mesures[k].substr(12,2)) << " to channel " << stoi(mesures[k].substr(1,1)) - 1 << endl;
	  set_instrument(synth,stoi(mesures[k].substr(1,1)) - 1,stoi(mesures[k].substr(12,2)));
	}
	std::list<MIDIEvent> parsed = parse_notes(mesures[k].substr(16),stoi(mesures[k].substr(5,2)));
	MIDImusic[stoi(mesures[k].substr(1,1)) - 1] = parsed;
      }
    }
}
