/*
 * interface_init2.cc
 *
 *  Created on: 18 févr. 2014
 *      Author: matthieu
 */
#include <TGUI/TGUI.hpp>
#include <iostream>
// #include <string.hpp>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <SFML/Audio.hpp>
#include <../network/network.h>
#include <../network/netEvent.h>
#include <chat_event.h>
#include <interface_globale.h>
#include <interface_init.h>
#include <def_button.h>
#define DEBUG false
#include <debug.h>
using namespace std;
int usl2 = chdir("./src/interfaceinit");
#define THEME_CONFIG_FILE "../widgets/Black.conf"
static const std::vector<sf::VideoMode> vect_fs_vm =
		sf::VideoMode::getFullscreenModes();
bool synchro_vert2 = false;

/* getKeyName : give a String corresponding to a Keyboard::key in order to be able to write it on screen*/

int interface_initiale2 (int sizeFenetre[3] , bool * isFullScreenParam,Server* serverPtr,Client* clientPtr) {
	string fichierConfName = "../../conf/keymap.conf";
	ifstream fichierConf(fichierConfName.c_str(), ios::in);
	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(video_mode, "Game Interface", sf::Style::Fullscreen);
	//bool isFullScreen = true;
	(*isFullScreenParam) = true;
	sizeFenetre[0] = video_mode.width;
	sizeFenetre[1] = video_mode.height;
	sizeFenetre[2] = video_mode.bitsPerPixel;
	sf::Vector2u size = window.getSize();
	//unsigned int w = size.x;
	//unsigned int h = size.y;
	Interface interface(&window,&video_mode,serverPtr,clientPtr);
	/*
	 * Définition de main
	 */
	string fichierConfAudioName = "../../conf/audio.conf";
	ifstream fichierConfAudio(fichierConfAudioName.c_str(), ios::in);
	if (fichierConfAudio) {
		std::string ligne;
		std::string delimiter = "_";
		getline(fichierConfAudio, ligne);
		std::string key = ligne.substr(ligne.find(delimiter) + 1, ligne.size());
		interface.setAudioVol(atoi(key.c_str()));
		getline(fichierConfAudio, ligne);
		key = ligne.substr(ligne.find(delimiter) + 1, ligne.size());
		interface.setSoundVol(atoi(key.c_str()));
		fichierConfAudio.close();
	} else
		cerr << "Erreur à l'ouverture !" << endl;

	interface.setMenuChange("../son/SFB-arme-pompe.wav");
	interface.setMusic("../son/Age_of_Empires_Main_Theme_Dubstep_Remix_Age_of_Dub.wav");


	unsigned int w = size.x;
	unsigned int h = size.y;

	//Definition of the main menu widgets set (tui)
	GuiExtended mainWidgetsMenu(&window);

	if (mainWidgetsMenu.setGlobalFont("../fonts/leadcoat.ttf") == false) /*Définition of the global gui font*/
		return 1;

	//Definition of the background picture of the gui
	tgui::Picture::Ptr picture(mainWidgetsMenu);
	picture->load("pic.jpg");
	picture->setSize(w, h);
	picture->setPosition(0, 0);
	//End Definition of the background picture of the gui

	//Definition of the Button that links to create game menu
	tgui::Button::Ptr bcreate(mainWidgetsMenu);
	bcreate->load(THEME_CONFIG_FILE);
	bcreate->setPosition(w / 3, h / 5);
	bcreate->setText("Create Game");
	bcreate->setCallbackId(1);
	bcreate->bindCallback(tgui::Button::LeftMouseClicked);
	bcreate->setSize(w / 3, 40);
	//End Definition of the Button that links to create game menu

	//Definition of the Button that links to the join game menu
	tgui::Button::Ptr bjoin(mainWidgetsMenu);
	bjoin->load(THEME_CONFIG_FILE);
	bjoin->setPosition(w / 3, 2 * h / 5);
	bjoin->setText("Join Game");
	bjoin->setCallbackId(2);
	bjoin->bindCallback(tgui::Button::LeftMouseClicked);
	bjoin->setSize(w / 3, 40);
	//End Definition of the Button that links to join game menu

	//Definition of the Button that links to the option menu
	tgui::Button::Ptr boptions(mainWidgetsMenu);
	boptions->load(THEME_CONFIG_FILE);
	boptions->setPosition(w / 3, 3 * h / 5);
	boptions->setText("Options");
	boptions->setCallbackId(3);
	boptions->bindCallback(tgui::Button::LeftMouseClicked);
	boptions->setSize(w / 3, 40);
	//End Definition of the Button that links to the option menu

	//Definition of the Button that quit the game
	tgui::Button::Ptr bquit(mainWidgetsMenu);
	bquit->load(THEME_CONFIG_FILE);
	bquit->setPosition(w / 3, 4 * h / 5);
	bquit->setText("Quit");
	bquit->setCallbackId(4);
	bquit->bindCallback(tgui::Button::LeftMouseClicked);
	bquit->setSize(w / 3, 40);
	//End Definition of the Button that quit the game
	mainWidgetsMenu.setWidgetName(bcreate,"bcreate");
	mainWidgetsMenu.setWidgetName(bjoin,"bjoin");
	mainWidgetsMenu.setWidgetName(boptions,"boptions");
	mainWidgetsMenu.setWidgetName(bquit,"bquit");
	mainWidgetsMenu.setFuncCallback(&callbackMain);
	mainWidgetsMenu.setFuncEvent(&funcEventMain);
	//End Definition of the main menu widgets set (tui)

	//Definition of the option menu widgets set (opt)
	GuiExtended optWidgetsMenu(&window);
	//Definition of the background picture of the gui
	tgui::Picture::Ptr picture2(optWidgetsMenu);
	picture2->load("pic.jpg");
	picture2->setSize(w, h);
	picture2->setPosition(0, 0);
	//End Definition of the background picture of the gui

	if (optWidgetsMenu.setGlobalFont("../fonts/leadcoat.ttf") == false) /*Definition of the Gloabal font of the optWidgetsMenu tgui*/
		return 1;

	//Definition of the Button that return to main menu
	tgui::Button::Ptr breturnOptM(optWidgetsMenu);
	breturnOptM->load(THEME_CONFIG_FILE);
	breturnOptM->setPosition(w / 3, 4 * h / 5);
	breturnOptM->setText("Back to Menu");
	breturnOptM->setCallbackId(4);
	breturnOptM->bindCallback(tgui::Button::LeftMouseClicked);
	breturnOptM->setSize(w / 3, 40);
	//End Definition of the Button that return to main menu

	//Definition of the Button that links to graphic option menu
	tgui::Button::Ptr bgraph(optWidgetsMenu);
	bgraph->load(THEME_CONFIG_FILE);
	bgraph->setPosition(w / 3, h / 5);
	bgraph->setText("Graphic Options");
	bgraph->setCallbackId(1);
	bgraph->bindCallback(tgui::Button::LeftMouseClicked);
	bgraph->setSize(w / 3, 40);
	//End Definition of the Button that links to graphic option menu

	//Definition of the Button that links to audio option menu
	tgui::Button::Ptr baudio(optWidgetsMenu);
	baudio->load(THEME_CONFIG_FILE);
	baudio->setPosition(w / 3, 2 * h / 5);
	baudio->setText("Audio Options");
	baudio->setCallbackId(2);
	baudio->bindCallback(tgui::Button::LeftMouseClicked);
	baudio->setSize(w / 3, 40);
	//End Definition of the Button that links to audio option menu

	//Definition of the Button that links to game option menu
	tgui::Button::Ptr bgame(optWidgetsMenu);
	bgame->load(THEME_CONFIG_FILE);
	bgame->setPosition(w / 3, 3 * h / 5);
	bgame->setText("Game Options");
	bgame->setCallbackId(3);
	bgame->bindCallback(tgui::Button::LeftMouseClicked);
	bgame->setSize(w / 3, 40);
	//End Definition of the Button that links to game option menu
	optWidgetsMenu.setWidgetName(breturnOptM,"breturnOptM");
	optWidgetsMenu.setWidgetName(bgraph,"bgraph");
	optWidgetsMenu.setWidgetName(baudio,"baudio");
	optWidgetsMenu.setWidgetName(bgame,"bgame");
	optWidgetsMenu.setFuncCallback(&callbackOpt);
	optWidgetsMenu.setFuncEvent(&funcEventOpt);
	//End Definition of the option menu widgets set (opt)


	//Definition of the graphic option menu widgets set (gopt)
	GuiExtended goptWidgetsMenu(&window);

	//Definition of the background picture of the gopt
	tgui::Picture::Ptr picture3(goptWidgetsMenu);
	picture3->load("pic.jpg");
	picture3->setSize(w, h);
	picture3->setPosition(0, 0);
	//End Definition of the background picture of the gopt
	if (goptWidgetsMenu.setGlobalFont("../fonts/leadcoat.ttf") == false) /*Definition of the Gloabal font of the gopt tgui*/
		return 1;

	goptWidgetsMenu.setFuncCallback(&callbackGopt);
	goptWidgetsMenu.setFuncEvent(&funcEventGopt);
	//Definition of the Button that links to option menu
	tgui::Button::Ptr breturnGOptOpt(goptWidgetsMenu);
	breturnGOptOpt->load(THEME_CONFIG_FILE);
	breturnGOptOpt->setPosition(w / 3, 4 * h / 5);
	breturnGOptOpt->setText("Back to Menu");
	breturnGOptOpt->setCallbackId(1);
	breturnGOptOpt->bindCallback(tgui::Button::LeftMouseClicked);
	breturnGOptOpt->setSize(w / 3, 40);
	//End Definition of the Button that links to option menu

	//Definition of the label Max Framerate
	tgui::Label::Ptr label(goptWidgetsMenu);
	label->load(THEME_CONFIG_FILE);
	label->setText("Maximum framerate :");
	label->setPosition(w / 3, 3 * h / 5 - 45);
	label->setTextColor(sf::Color(0, 0, 0));
	label->setTextSize(40);
	//End Definition of the label Max Framerate

	//Definition of the box to choose the resolution
	tgui::ComboBox::Ptr resol(goptWidgetsMenu);
	resol->load(THEME_CONFIG_FILE);
	resol->setSize(w / 3, 50);
	resol->setPosition(w / 3, h / 5);
	for (std::size_t i = 0; i < vect_fs_vm.size(); ++i) {
		sf::VideoMode mode = vect_fs_vm[i];
		if (mode.bitsPerPixel == 32) {
			std::stringstream ss;
			ss << mode.width << "x" << mode.height;
			resol->addItem(ss.str());
		}
	};
	//End Definition of the box to choose the resolution

	//Definition of the checkbox to enable vert sync
	tgui::Checkbox::Ptr sync_vertical(goptWidgetsMenu);
	sync_vertical->load(THEME_CONFIG_FILE);
	sync_vertical->setPosition(w / 3, 2 * h / 5);
	sync_vertical->setText("Enable Vert. Sync.");
	sync_vertical->setTextSize(40);
	sync_vertical->setSize(40, 40);
	sync_vertical->setTextColor(sf::Color(0, 0, 0));
	//End Definition of the checkbox to enable vert sync

	//Definition of the framerate EditBox
	tgui::EditBox::Ptr framerate(goptWidgetsMenu);
	framerate->load(THEME_CONFIG_FILE);
	framerate->setPosition(w / 3, 3 * h / 5);
	framerate->setSize(w / 3, 40);
	//End Definition of the framerate EditBox
	goptWidgetsMenu.setWidgetName(breturnGOptOpt,"breturnGOptOpt");
	goptWidgetsMenu.setWidgetName(label,"label");
	goptWidgetsMenu.setWidgetName(resol,"resol");
	goptWidgetsMenu.setWidgetName(sync_vertical,"sync_vertical");
	goptWidgetsMenu.setWidgetName(framerate,"framerate");
	//End Definition of the graphic option menu widgets set (gopt)



	//Definition of the game option menu widgets set (gopt)
	GuiExtended gaoptWidgetsMenu(&window);
	//Definition of the background picture of the gopt
	tgui::Picture::Ptr picture4(gaoptWidgetsMenu);
	picture4->load("pic.jpg");
	picture4->setSize(w, h);
	picture4->setPosition(0, 0);
	//End Definition of the background picture of the gopt

	if (gaoptWidgetsMenu.setGlobalFont("../fonts/leadcoat.ttf") == false)/*Definition of the Global font of the gaoptWidgetsMenu tgui*/
		return 1;

	//Definition of the Button that reset default option
	tgui::Button::Ptr breset(gaoptWidgetsMenu);
	breset->load(THEME_CONFIG_FILE);
	breset->setPosition(w / 5, 9 * h / 10);
	breset->setText("Reset Defaults");
	breset->setCallbackId(1);
	breset->bindCallback(tgui::Button::LeftMouseClicked);
	breset->setSize(w / 5, 40);
	//End Definition of the Button that reset default option

	//Definition of the Button that return to Option Menu
	tgui::Button::Ptr breturnGaOptOpt(gaoptWidgetsMenu);
	breturnGaOptOpt->load(THEME_CONFIG_FILE);
	breturnGaOptOpt->setPosition(3 * w / 5, 9 * h / 10);
	breturnGaOptOpt->setText("Save and Quit");
	breturnGaOptOpt->setCallbackId(2);
	breturnGaOptOpt->bindCallback(tgui::Button::LeftMouseClicked);
	breturnGaOptOpt->setSize(w / 5, 40);
	//End Definition of the Button that return to Option Menu

	//Definition of the Nick Name Label
	tgui::Label::Ptr labelNick(gaoptWidgetsMenu);
	labelNick->load(THEME_CONFIG_FILE);
	std::string nickFromFile = loadNick();
	labelNick->setText((std::string) "NickName (" + nickFromFile
			+ (std::string) ")");
	labelNick->setPosition(w / 5, 7 * h / 10 - 45);
	labelNick->setTextColor(sf::Color(0, 0, 0));
	labelNick->setTextSize(40);
	//End Definition of the Nick Name Label

	//Definition of the Nick Name Editbox
	tgui::EditBox::Ptr nickbox(gaoptWidgetsMenu);
	nickbox->load(THEME_CONFIG_FILE);
	nickbox->setPosition(w / 5, 7 * h / 10);
	nickbox->setSize(2 * w / 5, 40);
	//End Definition of the Nick Name Editbox

	//Definition of the Button that applies the nick Name
	tgui::Button::Ptr bapplynick(gaoptWidgetsMenu);
	bapplynick->load(THEME_CONFIG_FILE);
	bapplynick->setPosition(3.5 * w / 5, 7 * h / 10);
	bapplynick->setText("Apply");
	bapplynick->setCallbackId(3);
	bapplynick->bindCallback(tgui::Button::LeftMouseClicked);
	bapplynick->setSize(0.5 * w / 5, 40);
	//End Definition of the Button that applies the nick Name

	//Definition of the ListBox that presents keymap
	tgui::ListBox::Ptr listCommande(gaoptWidgetsMenu);
	listCommande->load(THEME_CONFIG_FILE);
	listCommande->setSize(3 * w / 5, 5 * h / 10);
	listCommande->setBackgroundColor(sf::Color(50, 50, 50, 100));
	listCommande->setItemHeight(40);
	listCommande->setPosition(w / 5, h / 10);
	listCommande->setTransparency(100);
	listCommande->setSelectedBackgroundColor(sf::Color(200, 200, 200, 100));
	sf::Font gameOptionFont;
	gameOptionFont.loadFromFile("../fonts/cour.ttf");
	listCommande->setTextFont(gameOptionFont);
	// Modularité oblige :
	if (fichierConf) {
		std::string ligne;
		while (getline(fichierConf, ligne)) {
			std::string delimiter = "_";
			std::string action = ligne.substr(0, ligne.find(delimiter));
			std::string key = ligne.substr(ligne.find(delimiter) + 1,
					ligne.size());
			std::string blanc(20 - action.size(), ' ');
			std::string newline = action + blanc + key;
			listCommande->addItem(newline);
			DBG << action << " " << key;
		}
		fichierConf.close();
	} else
		cerr << "Erreur à l'ouverture !" << endl;
	//End Definition of the ListBox that presents keymap
	gaoptWidgetsMenu.setWidgetName(breset,"breset");
	gaoptWidgetsMenu.setWidgetName(breturnGaOptOpt,"breturnGaOptOpt");
	gaoptWidgetsMenu.setWidgetName(labelNick,"labelNick");
	gaoptWidgetsMenu.setWidgetName(bapplynick,"bapplynick");
	gaoptWidgetsMenu.setWidgetName(listCommande,"listCommande");
	gaoptWidgetsMenu.setWidgetName(nickbox,"nickbox");
	gaoptWidgetsMenu.setFuncCallback(&callbackGaopt);
	gaoptWidgetsMenu.setFuncEvent(&funcEventGaopt);
	//End Definition of the game option menu widgets set (gopt)

	//Definition of the audio option menu widgets set (aopt)
	GuiExtended aoptWidgetsMenu(&window);
	//Definition of the background picture of the gopt
	tgui::Picture::Ptr picture5(aoptWidgetsMenu);
	picture5->load("pic.jpg");
	picture5->setSize(w, h);
	picture5->setPosition(0, 0);
	//End Definition of the background picture of the gopt
	if (aoptWidgetsMenu.setGlobalFont("../fonts/leadcoat.ttf") == false)/*Definition of the Global font of the gaoptWidgetsMenu tgui*/
		return 1;

	//Récupération des valeurs du volume dans le fichier ../../conf/audio.con
	//Definition of the Button that returns to Option Menu
	tgui::Button::Ptr breturnAOptOpt(aoptWidgetsMenu);
	breturnAOptOpt->load(THEME_CONFIG_FILE);
	breturnAOptOpt->setText("Return to Menu");
	breturnAOptOpt->setCallbackId(1);
	breturnAOptOpt->bindCallback(tgui::Button::LeftMouseClicked);
	breturnAOptOpt->setPosition(w / 3, 3 * h / 4);
	breturnAOptOpt->setSize(w / 3, 40);
	//End Definition of the Button that returns to Option Menu

	//Definition of the "Sound Volume" Label
	tgui::Label::Ptr labelvolume(aoptWidgetsMenu);
	labelvolume->load(THEME_CONFIG_FILE);
	labelvolume->setText("Sound Volume :");
	labelvolume->setPosition(w / 3, h / 4 - 45);
	labelvolume->setTextColor(sf::Color(0, 0, 0));
	labelvolume->setTextSize(40);
	//Definition of the "Sound Volume" Label

	//Definition of the scrollbar sound
	tgui::Scrollbar::Ptr scrollbarVolumeSound(aoptWidgetsMenu);
	scrollbarVolumeSound->load(THEME_CONFIG_FILE);
	scrollbarVolumeSound->setVerticalScroll(false);
	scrollbarVolumeSound->setPosition(w / 3, h / 4);
	scrollbarVolumeSound->setSize(w / 3, 40);
	scrollbarVolumeSound->setMaximum(100);
	scrollbarVolumeSound->setLowValue(1);
	scrollbarVolumeSound->setValue(interface.getSoundVol());
	scrollbarVolumeSound->setTransparency((unsigned char) 200);
	//End Definition of the scrollbar sound

	//Definition of the "Music Volume" Label
	tgui::Label::Ptr labelmusic(aoptWidgetsMenu);
	labelmusic->load(THEME_CONFIG_FILE);
	labelmusic->setText("Music Volume :");
	labelmusic->setPosition(w / 3, 2 * h / 4 - 45);
	labelmusic->setTextColor(sf::Color(0, 0, 0));
	labelmusic->setTextSize(40);
	//End Definition of the "Music Volume" Label

	//Definition of the scrollbar sound
	tgui::Scrollbar::Ptr scrollbarVolumeMusic(aoptWidgetsMenu);
	scrollbarVolumeMusic->load(THEME_CONFIG_FILE);
	scrollbarVolumeMusic->setVerticalScroll(false);
	scrollbarVolumeMusic->setPosition(w / 3, 2 * h / 4);
	scrollbarVolumeMusic->setSize(w / 3, 40);
	scrollbarVolumeMusic->setMaximum(100);
	scrollbarVolumeMusic->setLowValue(1);
	scrollbarVolumeMusic->setValue(interface.getAudioVol());
	scrollbarVolumeMusic->setTransparency((unsigned char) 200);
	//End Definition of the scrollbar sound

	aoptWidgetsMenu.setWidgetName(scrollbarVolumeMusic,"scrollbarVolumeMusic");
	aoptWidgetsMenu.setWidgetName(labelmusic,"labelmusic");
	aoptWidgetsMenu.setWidgetName(scrollbarVolumeSound,"scrollbarVolumeSound");
	aoptWidgetsMenu.setWidgetName(labelvolume,"labelvolume");
	aoptWidgetsMenu.setWidgetName(breturnAOptOpt,"breturnAOptOpt");
	aoptWidgetsMenu.setFuncCallback(&callbackAopt);
	aoptWidgetsMenu.setFuncEvent(&funcEventAopt);
	//End Definition of the audio option menu widgets set (aoptWidgetsMenu)
	//Definition of the create server menu widgets (pour l'instant join game menu jgmWidgetsMenu)
	GuiExtended jgmWidgetsMenu(&window);
	tgui::Picture::Ptr picture6(jgmWidgetsMenu);
	picture6->load("pic.jpg");
	picture6->setSize(w, h);
	picture6->setPosition(0, 0);
	if (jgmWidgetsMenu.setGlobalFont("../fonts/leadcoat.ttf") == false)
		return 1;

	tgui::EditBox::Ptr chatinsert(jgmWidgetsMenu);
	chatinsert->load(THEME_CONFIG_FILE);
	chatinsert->setPosition(w / 10, 19 * h / 20);
	chatinsert->setSize(5 * w / 10, 30);

	tgui::ChatBox::Ptr chatbox(jgmWidgetsMenu);
	chatbox->load(THEME_CONFIG_FILE);
	chatbox->setSize(5 * w / 10, 5 * h / 20);
	chatbox->setTextSize(20);
	chatbox->setPosition(w / 10, 13 * h / 20);
	chatbox->setTransparency(100);
	chatbox->setBackgroundColor(sf::Color(200, 200, 200, 100));

	tgui::Button::Ptr breturnJgmM(jgmWidgetsMenu);
	breturnJgmM->load(THEME_CONFIG_FILE);
	breturnJgmM->setText("Return");
	breturnJgmM->setCallbackId(1);
	breturnJgmM->bindCallback(tgui::Button::LeftMouseClicked);
	breturnJgmM->setPosition(7 * w / 10, 15 * h / 20);
	breturnJgmM->setSize(2 * w / 10, 2 * h / 20);

	tgui::Panel::Ptr panel(jgmWidgetsMenu);
	panel->setSize(5 * w / 10, 11 * h / 20);
	panel->setPosition(w / 10, h / 20);
	panel->setBackgroundColor(sf::Color(200, 200, 200, 100));
	panel->setTransparency(100);

	jgmWidgetsMenu.setWidgetName(panel,"panel");
	jgmWidgetsMenu.setWidgetName(breturnJgmM,"breturnJgmM");
	jgmWidgetsMenu.setWidgetName(chatbox,"chatbox");
	jgmWidgetsMenu.setWidgetName(chatinsert,"chatinsert");
	jgmWidgetsMenu.setFuncCallback(&callbackJgm);
	jgmWidgetsMenu.setFuncEvent(&funcEventJgm);
	//End Definition of the create server menu widgets (pour l'instant join game menu jgmWidgetsMenu)

	interface.addtgui(&mainWidgetsMenu,"main");
	interface.addtgui(&optWidgetsMenu,"opt");
	interface.addtgui(&goptWidgetsMenu,"gopt");
	interface.addtgui(&gaoptWidgetsMenu,"gaopt");
	interface.addtgui(&aoptWidgetsMenu,"aopt");
	interface.addtgui(&jgmWidgetsMenu,"jgm");
	interface.init();
	DBG << "I will enter the loop";
	while (window.isOpen() && (interface.out == 0)) {
		sf::Event event;
		while (window.pollEvent(event)) {

			//DBG << "I am in the event";
			if (event.type == sf::Event::Closed) {
				window.close();
				//DBG << "I am in the event";
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F11) {
					if (interface.isFullScreen) {
						interface.getWindow()->create(*(interface.getVideoMode()), "Game Interface");
						interface.isFullScreen = false;
					}
					else {
						interface.getWindow()->create(*(interface.getVideoMode()), "Game Interface", sf::Style::Fullscreen);
						interface.isFullScreen = true;
					}
				}
			}
			interface.handleEvent(&event);
		}
		interface.handleCallBack();
		window.clear();
		interface.draw();
		window.display();
	}
	sizeFenetre[0] = interface.getVideoMode()->width;
	sizeFenetre[1] = interface.getVideoMode()->height;
	sizeFenetre[2] = interface.getVideoMode()->bitsPerPixel;
	*isFullScreenParam = interface.isFullScreen;
	window.close();
	return 1;
}
