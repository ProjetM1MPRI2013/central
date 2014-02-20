#include "main.h"
#include "test.h"
#define DEBUG false
#include "debug.h"

#include <iostream>
using namespace std;
#include "Note.h"
#include "Accord.h"
#include "Accompagnement.h"
#include "Basse.h"
#include "Melodie.h"
#include "Musique.h"
#include <vector>
#include "GrilleHarmonique.h"

#include "ToMIDI.h"
#include <fluidsynth.h>
#include <sys/types.h>
#include <unistd.h>

//#define FONTFILE "/home/polimegalo/workspace/central/code/example.sf2"
#define FONTFILE "/home/polimegalo/workspace/central/Musique/FluidR3\ GM2-2.SF2"
// "/usr/share/sounds/sf2/FluidR3_GS.sf2"

#if defined(WIN32)
#include <windows.h>
#define sleep(_t) Sleep(_t * 1000)
#else
#include <stdlib.h>
#endif


namespace test {
  int music() {
    srand( time(NULL)); // obligatoire pour initialisation de l'aleatoire
    
    Musique musique;
    vector<string> mesures;
    musique.nextMesures(mesures);
    for (unsigned int k = 0; k < mesures.size(); k++) {
      cout << endl << mesures[k] << endl;
      cout << "try to parse next input";
      std::vector<MIDIEvent> parsed = parse_notes(mesures[k].substr(16),120);
    }


    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    int sfont_id;
    int i, key;

    /* Create the settings. */
    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "alsa");

    /* Change the settings if necessary*/

    /* Create the synthesizer. */
    synth = new_fluid_synth(settings);

    /* Create the audio driver. The synthesizer starts playing as soon
       as the driver is created. */
    adriver = new_fluid_audio_driver(settings, synth);

    /* Load a SoundFont and reset presets (so that new instruments
     * get used from the SoundFont) */
    sfont_id = fluid_synth_sfload(synth, FONTFILE, 1);

    /* Initialize the random number generator */
    srand(getpid());

    for (i = 0; i < 12; i++) {

      /* Generate a random key */
      key = 60 + (int) (12.0f * rand() / (float) RAND_MAX);

      /* Play a note */
      fluid_synth_noteon(synth, 0, key, 80);

      /* Sleep for 1 second */
      sleep(1);
      
      /* Stop the note */
      fluid_synth_noteoff(synth, 0, key);
    }
    
    /* Clean up */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
    return 0;
  }
}



