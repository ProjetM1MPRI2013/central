/**
 * @author Adrien K.
 */

#ifndef TO_MIDI_H
#define TO_MIDI_H

#include <fluidsynth.h>
#include <vector>
#include <string>
#include <list>
#include "Musique.h"

/**
 * @brief Set an instrument on a given MIDI channel
 * @param channel: the MIDI channel number
 * @param instrument: between 0 and 127. See the General MIDI norm for more information.
 */
void set_instrument (fluid_synth_t * synth, int channel, int instrument);

class MIDIEvent {
 public:
  bool isplayed;
  float begintime;
  float duration;
  int MIDInumber;
  MIDIEvent (float begin, float duration, int instrument);
  MIDIEvent ();
  void print();
};

/**
 * @brief parsed the string returned by the music generator and set the result in the input vector
 * @param resetInstrument: if set at true then set the instrument on the MIDI channel to those given by the music generator
 */
void setNextMesures(Musique& musique, std::vector<std::list<MIDIEvent>>& MIDImusic,fluid_synth_t * synth, bool resetInstrument);



#endif
