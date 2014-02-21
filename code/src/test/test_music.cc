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
      fluid_settings_setnum(settings,"synth.gain",0.4);

      /* Change the settings if necessary*/

      /* Create the synthesizer. */
      synth = new_fluid_synth(settings);

      /* Create the audio driver. The synthesizer starts playing as soon
	 as the driver is created. */
      adriver = new_fluid_audio_driver(settings, synth);

      /* Load a SoundFont and reset presets (so that new instruments
       * get used from the SoundFont) */
      /* "../../../Musique/FluidR3_GM2-2.SF2" */
      cout << "Chargement de SoundFont " 
	   << (sfont_id = fluid_synth_sfload(synth, "../../../Musique/GS_MuseScore v1.442.sf2", 1)) 
	   << " "
	   << FLUID_WARN <<"\n";
      setNextMesures(musique,MIDImusic,synth,false);
      for (auto MIDIchannel : MIDImusic){
	cout << "\nNew channel\n";
	for (MIDIEvent event : MIDIchannel){
	  cout << event.MIDInumber << " " << event.duration << " " << event.begintime << "  |  ";
	}
      }
      bool switchbool = true;
      if (switchbool){
      fluid_synth_program_change (synth, 0, 33);//Acoustic Bass
      fluid_synth_program_change (synth, 1, 36);//Fretless Bass
      fluid_synth_program_change (synth, 2, 65);//Soprano Sax 65
      }
      else{      
	fluid_synth_program_change (synth, 0, 17);//Drawbar Organ
	fluid_synth_program_change (synth, 1, 113);//Tinkle Bell
	fluid_synth_program_change (synth, 2, 80);//Ocarina
      }
      cout << "loaded\n";
      while(true){
	setNextMesures(musique,MIDImusic,synth,false);
	cout << "play again\n";
	float time = 0.;
	sleep(0.1);
	sf::Clock clock;
	while(time < MIDImusic[0].back().begintime + MIDImusic[0].back().duration){
	  time += clock.restart().asSeconds();
	  int cpt = 0;
	  for (auto MIDIchannel = MIDImusic.begin(); MIDIchannel != MIDImusic.end(); MIDIchannel++){
	    for (auto event = MIDIchannel->begin(); event != MIDIchannel->end(); event++){
	      //cout << event->begintime + event->duration << " " << time << " " << event->begintime << " " << event->isplayed << "\n";
	      if ((event->begintime + event->duration > time)&&(event->begintime < time)&&(event->isplayed == false)){
		fluid_synth_noteon(synth, cpt, event->MIDInumber, 80);
		event->isplayed = true;
		cout << "play a note " << event->MIDInumber << " channel " << cpt << " time " << time << "\n";
	      }
	      if((event->begintime + event->duration < time)&&(event->isplayed == true)){
		fluid_synth_noteoff(synth, cpt, event->MIDInumber);
		event->isplayed = false;
		cout << "stop playing a note " << event->MIDInumber << " channel " << cpt << " time " << time << "\n";
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
  
  

