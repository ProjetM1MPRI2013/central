#ifndef TO_MIDI_H
#define TO_MIDI_H

#include <fluidsynth.h>
#include "debug.h"

/**
 * @brief Set an instrument on a given MIDI channel
 * @param channel: the MIDI channel number
 * @param instrument: between 0 and 127. See the General MIDI norm for more information.
 */
void set_instrument (fluid_synth_t * synth, int channel, int instrument);

class MIDIEvent {
 public:
  float time;
  int MIDInumber;
  MIDIEvent (float,int);
  MIDIEvent ();
  void print();
};

std::vector<MIDIEvent> parse_notes (std::string s, int tempo);

#endif
