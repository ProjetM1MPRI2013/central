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
//#define FONTFILE "../../../Musique/FluidR3\ GM2-2.SF2"
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
    std::vector<std::list<MIDIEvent>> MIDImusic(16);  
      fluid_settings_t* settings;
      fluid_synth_t* synth;
      fluid_audio_driver_t* adriver;
      int sfont_id;
      
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
      cout << "Chargement de SoundFont " 
	   << (sfont_id = fluid_synth_sfload(synth, "../../../Musique/FluidR3_GM2-2.SF2", 1)) 
	   << " "
	   << FLUID_WARN <<"\n";
      setNextMesures(musique,MIDImusic,synth,true);
      for (auto MIDIchannel : MIDImusic){
	cout << "\nNew channel\n";
	for (MIDIEvent event : MIDIchannel){
	  cout << event.MIDInumber << " " << event.duration << " " << event.begintime << "  |  ";
	}
      }
      getchar();
      cout << "loaded\n";
      while(true){
	float time = 0.;
	sleep(0.05);
	sf::Clock clock;
	while(time < MIDImusic[0].back().begintime + MIDImusic[0].back().duration){
	  time += clock.restart().asSeconds();
	  int cpt = 0;
	  cout << "time " << time;
	  for (auto MIDIchannel : MIDImusic){
	    for (MIDIEvent event : MIDIchannel){
	      if ((event.begintime > time)&&(event.isplayed == false)){
		fluid_synth_noteon(synth, cpt, event.MIDInumber, 80);
		event.isplayed = true;
	      }
	      if((event.begintime + event.duration > time)&&(event.isplayed == true)){
		fluid_synth_noteoff(synth, cpt, event.MIDInumber);
	      }
	    }
	    cpt++;
	  }
	}
      }
      /* Clean up */
      delete_fluid_audio_driver(adriver);
      delete_fluid_synth(synth);
      delete_fluid_settings(settings);
      return 0;
  }
}
  
  

