#include <TGUI/TGUI.hpp>
#include <iostream>
// #include <string.hpp>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <SFML/Audio.hpp>

using namespace std;
int usl = chdir("./src/interfaceinit");
#define THEME_CONFIG_FILE "../widgets/Black.conf"
static const std::vector<sf::VideoMode> vect_fs_vm = sf::VideoMode::getFullscreenModes();
bool synchro_vert = false;

std::string getKeyName(const sf::Keyboard::Key key) {
  switch(key)
  {
  case sf::Keyboard::Unknown: return "Unknown";
  case sf::Keyboard::A: return "A";
  case sf::Keyboard::B: return "B";
    case sf::Keyboard::C: return "C";
    case sf::Keyboard::D: return "D";
    case sf::Keyboard::E: return "E";
    case sf::Keyboard::F: return "F";
    case sf::Keyboard::G: return "G";
    case sf::Keyboard::H: return "H";
    case sf::Keyboard::I: return "I";
    case sf::Keyboard::J: return "J";
    case sf::Keyboard::K: return "K";
    case sf::Keyboard::L: return "L";
    case sf::Keyboard::M: return "M";
    case sf::Keyboard::N: return "N";
    case sf::Keyboard::O: return "O";
    case sf::Keyboard::P: return "P";
    case sf::Keyboard::Q: return "Q";
    case sf::Keyboard::R: return "R";
    case sf::Keyboard::S: return "S";
    case sf::Keyboard::T: return "T";
    case sf::Keyboard::U: return "U";
    case sf::Keyboard::V: return "V";
    case sf::Keyboard::W: return "W";
    case sf::Keyboard::X: return "X";
    case sf::Keyboard::Y: return "Y";
    case sf::Keyboard::Z: return "Z";
    case sf::Keyboard::Num0: return "Num0";
    case sf::Keyboard::Num1: return "Num1";
    case sf::Keyboard::Num2: return "Num2";
    case sf::Keyboard::Num3: return "Num3";
    case sf::Keyboard::Num4: return "Num4";
    case sf::Keyboard::Num5: return "Num5";
    case sf::Keyboard::Num6: return "Num6";
    case sf::Keyboard::Num7: return "Num7";
    case sf::Keyboard::Num8: return "Num8";
    case sf::Keyboard::Num9: return "Num9";
    case sf::Keyboard::Escape: return "Escape";
    case sf::Keyboard::LControl: return "LControl";
    case sf::Keyboard::LShift: return "LShift";
    case sf::Keyboard::LAlt: return "LAlt";
    case sf::Keyboard::LSystem: return "LSystem";
    case sf::Keyboard::RControl: return "RControl";
    case sf::Keyboard::RShift: return "RShift";
    case sf::Keyboard::RAlt: return "RAlt";
    case sf::Keyboard::RSystem: return "RSystem";
    case sf::Keyboard::Menu: return "Menu";
    case sf::Keyboard::LBracket: return "LBracket";
    case sf::Keyboard::RBracket: return "RBracket";
    case sf::Keyboard::SemiColon: return "SemiColon";
    case sf::Keyboard::Comma: return "Comma";
    case sf::Keyboard::Period: return "Period";
    case sf::Keyboard::Quote: return "Quote";
    case sf::Keyboard::Slash: return "Slash";
    case sf::Keyboard::BackSlash: return "BackSlash";
    case sf::Keyboard::Tilde: return "Tilde";
    case sf::Keyboard::Equal: return "Equal";
    case sf::Keyboard::Dash: return "Dash";
    case sf::Keyboard::Space: return "Space";
    case sf::Keyboard::Return: return "Return";
    case sf::Keyboard::BackSpace: return "BackSpace";
    case sf::Keyboard::Tab: return "Tab";
    case sf::Keyboard::PageUp: return "PageUp";
    case sf::Keyboard::PageDown: return "PageDown";
    case sf::Keyboard::End: return "End";
    case sf::Keyboard::Home: return "Home";
    case sf::Keyboard::Insert: return "Insert";
    case sf::Keyboard::Delete: return "Delete";
    case sf::Keyboard::Add: return "Add";
    case sf::Keyboard::Subtract: return "Subtract";
    case sf::Keyboard::Multiply: return "Multiply";
    case sf::Keyboard::Divide: return "Divide";
    case sf::Keyboard::Left: return "Left";
    case sf::Keyboard::Right: return "Right";
    case sf::Keyboard::Up: return "Up";
    case sf::Keyboard::Down: return "Down";
    case sf::Keyboard::Numpad0: return "Numpad0";
    case sf::Keyboard::Numpad1: return "Numpad1";
    case sf::Keyboard::Numpad2: return "Numpad2";
    case sf::Keyboard::Numpad3: return "Numpad3";
    case sf::Keyboard::Numpad4: return "Numpad4";
    case sf::Keyboard::Numpad5: return "Numpad5";
    case sf::Keyboard::Numpad6: return "Numpad6";
    case sf::Keyboard::Numpad7: return "Numpad7";
    case sf::Keyboard::Numpad8: return "Numpad8";
    case sf::Keyboard::Numpad9: return "Numpad9";
    case sf::Keyboard::F1: return "F1";
    case sf::Keyboard::F2: return "F2";
    case sf::Keyboard::F3: return "F3";
    case sf::Keyboard::F4: return "F4";
    case sf::Keyboard::F5: return "F5";
    case sf::Keyboard::F6: return "F6";
    case sf::Keyboard::F7: return "F7";
    case sf::Keyboard::F8: return "F8";
    case sf::Keyboard::F9: return "F9";
    case sf::Keyboard::F10: return "F10";
    case sf::Keyboard::F11: return "F11";
    case sf::Keyboard::F12: return "F12";
    case sf::Keyboard::F13: return "F13";
    case sf::Keyboard::F14: return "F14";
    case sf::Keyboard::F15: return "F15";
    case sf::Keyboard::Pause: return "Pause";
      }
}

int copierFichier(char const * const source, char const * const destination)
{
    FILE* fSrc;
    FILE* fDest;
    char buffer[512];
    int NbLus;

    if ((fSrc = fopen(source, "rb")) == NULL)
    {
        return 1;
    }

    if ((fDest = fopen(destination, "wb")) == NULL)
    {
        fclose(fSrc);
        return 2;
    }

    while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
        fwrite(buffer, 1, NbLus, fDest);

    fclose(fDest);
    fclose(fSrc);

    return 0;
}

void modifyConfig (int index , std::string s) {
  FILE* temp = fopen("temp.txt","wt");
  string fichierConfName = "../../keymap.conf";
  ifstream fichierConf(fichierConfName.c_str(), ios::in);
  if(fichierConf)
  {
      std::string ligne;
      int i = 0 ;
      while(getline(fichierConf, ligne) && i < index)
        {
          i++;
          fprintf(temp,"%s\n",(const char *)ligne.c_str());
        }
      std::string delimiter = "_";
      std::string action = ligne.substr(0, ligne.find(delimiter));
      fprintf(temp, "%s",(action + (std::string)"_" + s + (std::string) + "\n").c_str());
      while(getline(fichierConf, ligne))
        {
          fprintf(temp,"%s\n",ligne.c_str());
        }
    }
  fclose(temp);
  fichierConf.close();
  rename("temp.txt","../../keymap2.conf");
  remove("../../keymap.conf");
  rename("../../keymap2.conf","../../keymap.conf");
}
void modifyConfigAudio (int music , int sound) {
  FILE* audioconf = fopen("../../audio.conf","wt");
  fprintf(audioconf,"Music_%d\n",music);
  fprintf(audioconf,"Sound_%d",sound);
  fclose(audioconf);
}

void reloadKeyMapping(tgui::ListBox::Ptr lc) {
  lc->removeAllItems();
  string fichierConfName = "../../keymap.conf";
  ifstream fichierConf(fichierConfName.c_str(), ios::in);
  if(fichierConf)
  {
      std::string ligne;
      while(getline(fichierConf, ligne))
        {
          std::string delimiter = "_";
          std::string action = ligne.substr(0, ligne.find(delimiter));
          std::string key = ligne.substr(ligne.find(delimiter)+1,ligne.size());
          std::string blanc(20-action.size(),' ');
          std::string newline = action + blanc + key;
          lc->addItem(newline);
        }
      fichierConf.close();
  }
  else
    cerr << "Erreur à l'ouverture !" << endl;

}
int interface_initiale() 
{
	//Définition des sons
	sf::SoundBuffer changementMenuBuffer;
    if (!changementMenuBuffer.loadFromFile("../son/SFB-arme-pompe.wav"))
        return 1;
    sf::Sound changementMenu;
    changementMenu.setBuffer(changementMenuBuffer);

	sf::SoundBuffer testBuffer;
    if (!testBuffer.loadFromFile("../son/SF-bullet-time_04sf.wav"))
        return 1;
    sf::Sound test;
    test.setBuffer(testBuffer);
    //Fin Définition des sons
    //Définition de la musique
    sf::Music interfaceMusic;
    if (!interfaceMusic.openFromFile("../son/Age_of_Empires_Main_Theme_Dubstep_Remix_Age_of_Dub.wav"))
        return -1; // error
    //Fin de la définition de la musique
  static sf::VideoMode video_mode = sf::VideoMode::getDesktopMode(); 	
  sf::RenderWindow window(video_mode, "Game Interface",sf::Style::Fullscreen);
  tgui::Gui gui(window);

  if (gui.setGlobalFont("../fonts/leadcoat.ttf") == false)
        return 1;


  sf::Vector2u size = window.getSize();
  unsigned int w = size.x;
  unsigned int h = size.y;
  tgui::Picture::Ptr picture(gui);
  picture->load("pic.jpg");
  picture->setSize(w, h);
  picture->setPosition(0, 0);
  
  tgui::Button::Ptr bcreate(gui);
  bcreate->load(THEME_CONFIG_FILE);
  bcreate->setPosition(w/3, h/5);
  bcreate->setText("Create Game");
  bcreate->setCallbackId(1);
  bcreate->bindCallback(tgui::Button::LeftMouseClicked);
  bcreate->setSize(w/3, 40);

  tgui::Button::Ptr bjoin(gui);
  bjoin->load(THEME_CONFIG_FILE);
  bjoin->setPosition(w/3,2* h/5);
  bjoin->setText("Join Game");
  bjoin->setCallbackId(2);
  bjoin->bindCallback(tgui::Button::LeftMouseClicked);
  bjoin->setSize(w/3, 40);

  tgui::Button::Ptr boptions(gui);
  boptions->load(THEME_CONFIG_FILE);
  boptions->setPosition(w/3, 3*h/5);
  boptions->setText("Options");
  boptions->setCallbackId(3);
  boptions->bindCallback(tgui::Button::LeftMouseClicked);
  boptions->setSize(w/3, 40);

  tgui::Button::Ptr bquit(gui);
  bquit->load(THEME_CONFIG_FILE);
  bquit->setPosition(w/3, 4*h/5);
  bquit->setText("Quit");
  bquit->setCallbackId(4);
  bquit->bindCallback(tgui::Button::LeftMouseClicked);
  bquit->setSize(w/3, 40);
  
  tgui::Gui opt(window);
  tgui::Picture::Ptr picture2(opt);
  picture2->load("pic.jpg");
  picture2->setSize(w, h);
  picture2->setPosition(0, 0);
  
  if (opt.setGlobalFont("../fonts/leadcoat.ttf") == false)
        return 1;

  tgui::Button::Ptr breturnOptM(opt);
  breturnOptM->load(THEME_CONFIG_FILE);
  breturnOptM->setPosition(w/3, 4*h/5);
  breturnOptM->setText("Back to Menu");
  breturnOptM->setCallbackId(4);
  breturnOptM->bindCallback(tgui::Button::LeftMouseClicked);
  breturnOptM->setSize(w/3, 40);

  tgui::Button::Ptr bgraph(opt);
  bgraph->load(THEME_CONFIG_FILE);
  bgraph->setPosition(w/3, h/5);
  bgraph->setText("Graphic Options");
  bgraph->setCallbackId(1);
  bgraph->bindCallback(tgui::Button::LeftMouseClicked);
  bgraph->setSize(w/3, 40);

  tgui::Button::Ptr baudio(opt);
  baudio->load(THEME_CONFIG_FILE);
  baudio->setPosition(w/3, 2*h/5);
  baudio->setText("Audio Options");
  baudio->setCallbackId(2);
  baudio->bindCallback(tgui::Button::LeftMouseClicked);
  baudio->setSize(w/3, 40);

  tgui::Button::Ptr bgame(opt);
  bgame->load(THEME_CONFIG_FILE);
  bgame->setPosition(w/3, 3*h/5);
  bgame->setText("Game Options");
  bgame->setCallbackId(3);
  bgame->bindCallback(tgui::Button::LeftMouseClicked);
  bgame->setSize(w/3, 40);

  tgui::Gui gopt(window);
  tgui::Picture::Ptr picture3(gopt);
  picture3->load("pic.jpg");
  picture3->setSize(w, h);
  picture3->setPosition(0, 0);

  if (gopt.setGlobalFont("../fonts/leadcoat.ttf") == false)
          return 1;

  tgui::Button::Ptr breturnGOptOpt(gopt);
  breturnGOptOpt->load(THEME_CONFIG_FILE);
  breturnGOptOpt->setPosition(w/3, 4*h/5);
  breturnGOptOpt->setText("Back to Menu");
  breturnGOptOpt->setCallbackId(1);
  breturnGOptOpt->bindCallback(tgui::Button::LeftMouseClicked);
  breturnGOptOpt->setSize(w/3, 40);

  tgui::Label::Ptr label(gopt);
  label->load(THEME_CONFIG_FILE);
  label->setText("Maximum framerate :");
  label->setPosition(w/3, 3*h/5-45);
  label->setTextColor(sf::Color(0, 0,0));
  label->setTextSize(40);

  tgui::ComboBox::Ptr resol(gopt);
  resol->load(THEME_CONFIG_FILE);
  resol->setSize(w/3, 50);
  resol->setPosition(w/3, h/5);
  for (std::size_t i = 0; i < vect_fs_vm.size(); ++i)
   {
     sf::VideoMode mode = vect_fs_vm[i];
     if (mode.bitsPerPixel == 32) {
       std::stringstream ss;
       ss << mode.width << "x" << mode.height;
       resol->addItem(ss.str());
     }
   };
  tgui::Checkbox::Ptr sync_vertical(gopt);
  sync_vertical->load(THEME_CONFIG_FILE);
  sync_vertical->setPosition(w/3, 2*h/5);
  sync_vertical->setText("Enable Vert. Sync.");
  sync_vertical->setTextSize(40);
  sync_vertical->setSize(40, 40);
  sync_vertical->setTextColor(sf::Color(0,0,0));  

  tgui::EditBox::Ptr framerate(gopt);
  framerate->load(THEME_CONFIG_FILE);
  framerate->setPosition(w/3, 3*h/5);
  framerate->setSize(w/3, 40);


  tgui::Gui gaopt(window);
  tgui::Picture::Ptr picture4(gaopt);
  picture4->load("pic.jpg");
  picture4->setSize(w, h);
  picture4->setPosition(0, 0);

  if (gaopt.setGlobalFont("../fonts/leadcoat.ttf") == false)
          return 1;

  tgui::Button::Ptr breset(gaopt);
  breset->load(THEME_CONFIG_FILE);
  breset->setPosition(w/5, 9*h/10);
  breset->setText("Reset Defaults");
  breset->setCallbackId(1);
  breset->bindCallback(tgui::Button::LeftMouseClicked);
  breset->setSize(w/5, 40);

  tgui::Button::Ptr breturnGaOptOpt(gaopt);
  breturnGaOptOpt->load(THEME_CONFIG_FILE);
  breturnGaOptOpt->setPosition(3*w/5, 9*h/10);
  breturnGaOptOpt->setText("Save and Quit");
  breturnGaOptOpt->setCallbackId(2);
  breturnGaOptOpt->bindCallback(tgui::Button::LeftMouseClicked);
  breturnGaOptOpt->setSize(w/5, 40);

  tgui::ListBox::Ptr listCommande(gaopt);
  listCommande->load(THEME_CONFIG_FILE);
  listCommande->setSize(3*w/5, 7*h/10);
  listCommande->setBackgroundColor(sf::Color(50,50,50,100));
  listCommande->setItemHeight(40);
  listCommande->setPosition(w/5, h/10);
  listCommande->setTransparency(100);
  listCommande->setSelectedBackgroundColor(sf::Color(200,200,200,100));
  sf::Font gameOptionFont;
  gameOptionFont.loadFromFile("../fonts/cour.ttf");
  listCommande->setTextFont(gameOptionFont);
  // Modularité oblige :
  string fichierConfName = "../../keymap.conf";
  ifstream fichierConf(fichierConfName.c_str(), ios::in);
  if(fichierConf)
  {
      std::string ligne;
      while(getline(fichierConf, ligne))
        {
          std::string delimiter = "_";
          std::string action = ligne.substr(0, ligne.find(delimiter));
          std::string key = ligne.substr(ligne.find(delimiter)+1,ligne.size());
          std::string blanc(20-action.size(),' ');
          std::string newline = action + blanc + key;
          listCommande->addItem(newline);
        }
      fichierConf.close();
  }
  else
    cerr << "Erreur à l'ouverture !" << endl;

  tgui::Gui aopt(window);
  tgui::Picture::Ptr picture5(aopt);
  picture5->load("pic.jpg");
  picture5->setSize(w, h);
  picture5->setPosition(0, 0);

  if (aopt.setGlobalFont("../fonts/leadcoat.ttf") == false)
          return 1;

  int audioVol = 0; int soundVol = 0 ;
  string fichierConfAudioName = "../../audio.conf";
  ifstream fichierConfAudio(fichierConfAudioName.c_str(), ios::in);
  if(fichierConfAudio)
  {
      std::string ligne;
      std::string delimiter = "_";
      getline(fichierConfAudio, ligne);
      std::string key = ligne.substr(ligne.find(delimiter)+1,ligne.size());
      audioVol = atoi(key.c_str());
      getline(fichierConfAudio, ligne);
      key = ligne.substr(ligne.find(delimiter)+1,ligne.size());
      soundVol = atoi(key.c_str());
      fichierConf.close();
  }
  else
    cerr << "Erreur à l'ouverture !" << endl;

  tgui::Button::Ptr breturnAOptOpt(aopt);
  breturnAOptOpt->load(THEME_CONFIG_FILE);
  breturnAOptOpt->setText("Return to Menu");
  breturnAOptOpt->setCallbackId(1);
  breturnAOptOpt->bindCallback(tgui::Button::LeftMouseClicked);
  breturnAOptOpt->setPosition(w/3, 3*h/4);
  breturnAOptOpt->setSize(w/3, 40);

  tgui::Label::Ptr labelvolume(aopt);
  labelvolume->load(THEME_CONFIG_FILE);
  labelvolume->setText("Sound Volume :");
  labelvolume->setPosition(w/3, h/4 - 45);
  labelvolume->setTextColor(sf::Color(0, 0,0));
  labelvolume->setTextSize(40);

  tgui::Scrollbar::Ptr scrollbarVolumeSound(aopt);
  scrollbarVolumeSound->load(THEME_CONFIG_FILE);
  scrollbarVolumeSound->setVerticalScroll(false);
  scrollbarVolumeSound->setPosition(w/3, h/4);
  scrollbarVolumeSound->setSize(w/3, 40);
  scrollbarVolumeSound->setMaximum(100);
  scrollbarVolumeSound->setLowValue(1);
  scrollbarVolumeSound->setValue(soundVol);
  scrollbarVolumeSound->setTransparency((unsigned char) 200);

  tgui::Label::Ptr labelmusic(aopt);
  labelmusic->load(THEME_CONFIG_FILE);
  labelmusic->setText("Music Volume :");
  labelmusic->setPosition(w/3, 2*h/4 - 45);
  labelmusic->setTextColor(sf::Color(0, 0,0));
  labelmusic->setTextSize(40);

  tgui::Scrollbar::Ptr scrollbarVolumeMusic(aopt);
  scrollbarVolumeMusic->load(THEME_CONFIG_FILE);
  scrollbarVolumeMusic->setVerticalScroll(false);
  scrollbarVolumeMusic->setPosition(w/3, 2*h/4);
  scrollbarVolumeMusic->setSize(w/3, 40);
  scrollbarVolumeMusic->setMaximum(100);
  scrollbarVolumeMusic->setLowValue(1);
  scrollbarVolumeMusic->setValue(audioVol);
  scrollbarVolumeMusic->setTransparency((unsigned char) 200);

  int wim = 0 ; int wima = 0;
  int waitingKey = 0; int waitingKeyReady = 0;
  tgui::Gui* todo = &gui;
  changementMenu.setVolume(soundVol);
  test.setVolume(soundVol);
  interfaceMusic.setVolume(audioVol);
  interfaceMusic.play();
  interfaceMusic.setLoop(true);
  while (window.isOpen())
    {
      wim = wima;
      switch (wim)
      	{
      	case 0 : {todo = &gui; break ;}
      	case 1 : {todo = &opt; break ;}
      	case 2 : {todo = &gopt; break;}
        case 3 : {todo = &gaopt; break;}
        case 4 : {todo = &aopt; break;}
      	}
  
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (waitingKey !=0)
	    {
	      if (event.type == sf::Event::KeyPressed)
	        {
	          std::string keyPressed = getKeyName(event.key.code);
	          modifyConfig(waitingKey-1,keyPressed);
                  reloadKeyMapping(listCommande);
                  listCommande->deselectItem();
                  waitingKey =0;
                  listCommande->setSelectedBackgroundColor(sf::Color(200,200,200,100));
	        }
	      if (event.type == sf::Event::MouseButtonPressed)
	        {
	          if (event.mouseButton.button == sf::Mouse::Right)
	            {
	              modifyConfig(waitingKey-1,"Right Mouse Button");
	              reloadKeyMapping(listCommande);
	              listCommande->deselectItem();
	              waitingKey =0;
	              listCommande->setSelectedBackgroundColor(sf::Color(200,200,200,100));
	            }
	          if (event.mouseButton.button == sf::Mouse::Left)
	            {
	              modifyConfig(waitingKey-1,"Left Mouse Button");
	              reloadKeyMapping(listCommande);
	              listCommande->deselectItem();
	              waitingKey =0;
	              listCommande->setSelectedBackgroundColor(sf::Color(200,200,200,100));
	            }
	        }
	  }

          (*todo).handleEvent(event);
        }
      
      tgui::Callback callback;
      while ( (*todo).pollCallback(callback))
        {
	  if (wim == 0) {
	    if (callback.id == 1)
	      {
		wima = 0;
		changementMenu.play();
	      }
	    if (callback.id == 2) 
	      {
		wima = 0;
		changementMenu.play();
	      }
	    if (callback.id == 3)
	      {
	    	wima = 1;
	    	changementMenu.play();
	      }
	    if (callback.id == 4)
	      {
	    	changementMenu.play();
	    	window.close();
	      }
	  }
	  if (wim == 1) {
	      if (callback.id == 4) {
	          wima = 0;
	          changementMenu.play();
	      }
	      if(callback.id == 3) {
	          wima = 3;
	          changementMenu.play();
	      }
	      if(callback.id == 1) {
	          wima = 2;
	          changementMenu.play();
	      }
	      if(callback.id == 2) {
	          wima = 4;
	          changementMenu.play();
	      }
	  }
	  if (wim ==2) {
	    if (callback.id == 1) {
	        wima = 1;
			changementMenu.play();
			int ind_selected_items = resol->getSelectedItemIndex();
			if (ind_selected_items != (-1)) {
				int compt = 0;
				int index = 0;
				while (compt < ind_selected_items || (vect_fs_vm[index]).bitsPerPixel != 32) {
					if (((vect_fs_vm[index]).bitsPerPixel) == 32) {
						compt ++;
					}
					index ++;
				}
				sf::VideoMode mode = vect_fs_vm[index];
				sf::Vector2u size = window.getSize();
				unsigned int w = size.x;
				unsigned int h = size.y;
				if (w != mode.width || h != mode.height) {
					window.create(mode,"test",sf::Style::Fullscreen);
					//Resize of Widgets :
					sf::Vector2u size = window.getSize();
					w = size.x;
					h = size.y;
					bcreate->setPosition(w/3,h/5); bcreate->setSize(w/3,40);
					bjoin->setPosition(w/3,2*h/5); bjoin->setSize(w/3,40);
					boptions->setPosition(w/3,3*h/5);boptions->setSize(w/3,40);
		    bquit->setPosition(w/3,4*h/5);bquit->setSize(w/3,40);
		    resol->setPosition(w/3,h/5);resol->setSize(w/3,40);
		    breturnOptM->setPosition(w/3,4*h/5);breturnOptM->setSize(w/3,40);
		    sync_vertical->setPosition(w/3,2*h/5);
		    label->setPosition(w/3, 3*h/5-45);
		    bgraph->setPosition(w/3,h/5);bgraph->setSize(w/3,40);
		    baudio->setPosition(w/3,2*h/5);baudio->setSize(w/3,40);
		    bgame->setPosition(w/3,3*h/5);bgame->setSize(w/3,40);
		    breturnGOptOpt->setPosition(w/3,4*h/5);breturnGOptOpt->setSize(w/3,40);
		    breset->setPosition(w/5, 9*h/10);
		    breturnGaOptOpt->setPosition(3*w/5, 9*h/10);
		    listCommande->setSize(3*w/5, 7*h/10);
		    listCommande->setPosition(w/5, h/10);
		    breturnAOptOpt->setPosition(w/3, 3*h/4);
		    breturnAOptOpt->setSize(w/3, 40);
		    scrollbarVolumeMusic->setPosition(w/3, 2*h/4);
		    scrollbarVolumeMusic->setSize(w/3, 40);
		    scrollbarVolumeSound->setPosition(w/3, h/4);
		    scrollbarVolumeSound->setSize(w/3, 40);
		    framerate->setPosition(w/3, 3*h/5);
		    framerate->setSize(w/3, 40);
		    labelvolume->setPosition(w/3, h/4 - 45);
		    labelmusic->setPosition(w/3, 2*h/4 - 45);
		    //Resize of Pictures :
                    picture->setSize(w, h);
                    picture2->setSize(w, h);
                    picture3->setSize(w, h);
                    picture4->setSize(w, h);
		  }
		}
		if (sync_vertical->isChecked()) {
		  window.setVerticalSyncEnabled(true);
		}
		sf::String frameRatesfString  = framerate->getText();
		std::string frameRatestdString  = frameRatesfString.toAnsiString();
		int frameRateint = atoi(frameRatestdString.c_str());
		std::cout << "framerate :" << frameRateint << std::endl;
		window.setFramerateLimit(frameRateint);
		if (frameRateint !=0 ) {
		    window.setFramerateLimit(frameRateint);
		}
	      }
	  }
	  if (wim == 3) {
	      if (callback.id == 2) {
	          wima = 1;
	          changementMenu.play();
	      }
	      if (callback.id == 1)
	      {
	    	  remove("../../keymap.conf");
	    	  if (copierFichier("../../defaultkeymap.conf","../../keymap.conf") != 0) {
	    		  return 1;
	    	  };
              reloadKeyMapping(listCommande);
	      }
	  }
	  if (wim == 4) {
		  if (callback.id ==1) {
			  wima = 1;
	          changementMenu.play();
	          modifyConfigAudio(interfaceMusic.getVolume(),changementMenu.getVolume());
		  }
	  }

        }
      if (listCommande->getSelectedItemIndex() != -1) {
          std::cout << "#SWAG "<< listCommande->getSelectedItemIndex() << std::endl;
          waitingKey = listCommande->getSelectedItemIndex() +1 ;
          listCommande->setSelectedBackgroundColor(sf::Color(238,44,44,100));
      }
      if (wim == 4) {
    	  if (interfaceMusic.getVolume() != scrollbarVolumeMusic->getValue()) {
    		  interfaceMusic.setVolume(scrollbarVolumeMusic->getValue());
    	  }
    	  if (changementMenu.getVolume() != scrollbarVolumeSound->getValue()) {
    		  changementMenu.setVolume(scrollbarVolumeSound->getValue());
    		  test.setVolume(scrollbarVolumeSound->getValue());
    		  test.play();
    	  }
      }
      window.clear();
      (*todo).draw();
      window.display();
    }
  usl = chdir("../../");
  return 0;
}
