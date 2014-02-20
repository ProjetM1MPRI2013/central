/*
 * def_button.cc
 *
 *  Created on: 20 févr. 2014
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
int usl3 = chdir("./src/interfaceinit");
#define THEME_CONFIG_FILE "../widgets/Black.conf"
static const std::vector<sf::VideoMode> vect_fs_vm =
		sf::VideoMode::getFullscreenModes();
bool synchro_vert3 = false;

tgui::Widget::Ptr& getWidget(Interface* inter,std::string str) { //trouve un widget associé à un nom donné
	std::vector<sf::String> nametab = (inter->getCurrent())->getWidgetNames();
	std::vector<tgui::Widget::Ptr> widtab = (inter->getCurrent())->getWidgets();
	int widtabn = widtab.size();
	for (int j = 0 ; j < widtabn ; j++) {
		std::string totest = nametab[j].toAnsiString();
		if (totest.compare(str) == 0) {
			return (widtab[j]);
		}
	};
	return (widtab[0]);
}

int callbackMain(int n , std::string* str, Interface* inter) {
	DBG << "I am in callbackMain";
	if (n == 1) {
		//go to create game menu
		DBG << "gg1";
		*str = "jgm";
		return 1;

	}
	if (n == 2) {
		//go to join game menu
		inter->out = 1;
		DBG << "gg2";
	}
	if (n == 3) {
		//go to option menu
		*str = "opt";
		DBG << "gg3";
		return 1;
	}
	if (n == 4) {
		//Leave the Game
		inter->out = 2;
		return 1;
	}
	return (0);
}
int funcEventMain(sf::Event* event,int n,Interface* inter) {
	//DBG<< "I am in funcEventMain";
	return 0;
}


int callbackOpt(int n , std::string* str,Interface* inter) {
	if (n == 4) {
		//go back to main menu
		*str = "main";
		return 1;
	}
	if (n == 3) {
		// go to game option menu
		*str = "gaopt";
		return 1;
	}
	if (n == 1) {
		//go to graphic menu option
		*str = "gopt";
		return 1;
	}
	if (n == 2) {
		//go to audio option menu
		*str = "aopt";
		return 1;
	}
	return 0;
}
void resizeInterface(int w , int h , Interface * inter) { //resize tout les boutons de l'interface
	std::list<GuiExtended*> guiList = inter->getGuilist ();
	std::list<GuiExtended*>::iterator i;
	for(i = guiList.begin() ; i != guiList.end() ; ++i) {
		std::vector<sf::String> nametab = (*i)->getWidgetNames();
		std::vector<tgui::Widget::Ptr> widtab = (*i)->getWidgets();
		int widtabn = widtab.size();
		for (int j = 0 ; j < widtabn ; j++) {
			std::string totest = nametab[j].toAnsiString();
			if (totest.compare("bcreate")==0) {
				widtab[j]->setPosition(w / 3, h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("bjoin")==0) {
				widtab[j]->setPosition(w / 3, 2 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("boptions")==0) {
				widtab[j]->setPosition(w / 3, 3 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("bquit")==0) {
				widtab[j]->setPosition(w / 3, 4 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("resol")==0) {
				widtab[j]->setPosition(w / 3, h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("breturnOptM")==0) {
				widtab[j]->setPosition(w / 3, 4 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("sync_vertical")==0) {
				widtab[j]->setPosition(w / 3, 2 * h / 5);
			} else if (totest.compare("label")==0) {
				widtab[j]->setPosition(w / 3, 3 * h / 5 - 45);
			} else if (totest.compare("bgraph")==0) {
				widtab[j]->setPosition(w / 3, h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("baudio")==0) {
				widtab[j]->setPosition(w / 3, 2 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("bgame")==0) {
				widtab[j]->setPosition(w / 3, 3 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("breturnGOptOpt")==0) {
				widtab[j]->setPosition(w / 3, 4 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("breset")==0) {
				widtab[j]->setPosition(w / 5, 9 * h / 10);
			} else if (totest.compare("breturnGaOptOpt")==0) {
				widtab[j]->setPosition(3 * w / 5, 9 * h / 10);
			} else if (totest.compare("listCommande")==0) {
				widtab[j]->setSize(3 * w / 5, 7 * h / 10);
				widtab[j]->setPosition(w / 5, h / 10);
			} else if (totest.compare("breturnAOptOpt")==0) {
				widtab[j]->setPosition(w / 3, 3 * h / 4);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("scrollbarVolumeMusic")==0) {
				widtab[j]->setPosition(w / 3, 2 * h / 4);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("scrollbarVolumeSound")==0) {
				widtab[j]->setPosition(w / 3, h / 4);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("framerate")==0) {
				widtab[j]->setPosition(w / 3, 3 * h / 5);
				widtab[j]->setSize(w / 3, 40);
			} else if (totest.compare("labelvolume")==0) {
				widtab[j]->setPosition(w / 3, h / 4 - 45);
			} else if (totest.compare("labelmusic")==0) {
				widtab[j]->setPosition(w / 3, 2 * h / 4 - 45);
			} else {};


		}
	};
}
int funcEventOpt(sf::Event* event,int n,Interface* inter) {
	return 0;
}
int callbackGopt(int n , std::string* str,Interface* inter) {
	DBG << "I m in callbackGopt";
	if (n == 1) {
		DBG << "I m in callbackGopt plus loin";
		*str ="opt";
		std::vector<sf::String> nametab = (inter->getCurrent())->getWidgetNames();
		std::vector<tgui::Widget::Ptr> widtab = (inter->getCurrent())->getWidgets();
		int widtabn = widtab.size();
		for (int j = 0 ; j < widtabn ; j++) {
			std::string totest = nametab[j].toAnsiString();
			if (totest.compare("resol") == 0) {
				int ind_selected_items = ((tgui::ComboBox::Ptr)widtab[j])->getSelectedItemIndex();
				if (ind_selected_items != (-1)) {
					int compt = 0;
					int index = 0;
					while (compt < ind_selected_items
							|| (vect_fs_vm[index]).bitsPerPixel != 32) {
						if (((vect_fs_vm[index]).bitsPerPixel) == 32) {
							compt++;
						}
						index++;
					}
					sf::VideoMode mode = vect_fs_vm[index];
					sf::Vector2u size = (inter->getWindow())->getSize();
					unsigned int w = size.x;
					unsigned int h = size.y;
					if (w != mode.width || h != mode.height) {
						DBG << "I need to resize";
						if (inter->isFullScreen) {
							(inter->getWindow())->create(mode, "test", sf::Style::Fullscreen);
						}
						else {
							(inter->getWindow())->create(mode, "test");
						}
						inter->setVideoMode(&mode);
						//Resize of Widgets :
						sf::Vector2u size = (inter->getWindow())->getSize();
						w = size.x;
						h = size.y;
						resizeInterface(w , h , inter);
					}
				}
			}
			if (totest.compare("sync_vertical") == 0 ){
				if (((tgui::Checkbox::Ptr)widtab[j])->isChecked()) { //Check wether the vert. sync. checkbox was checked
					inter->getWindow()->setVerticalSyncEnabled(true);
				}
			}
			if (totest.compare("framerate") == 0 ){
				sf::String frameRatesfString = ((tgui::EditBox::Ptr)widtab[j])->getText(); //Change the fps if there is a modification
				std::string frameRatestdString = frameRatesfString.toAnsiString();
				int frameRateint = atoi(frameRatestdString.c_str());
				std::cout << "framerate :" << frameRateint << std::endl;
				if (frameRateint != 0) {
					inter->getWindow()->setFramerateLimit(frameRateint);
				}
			}
		}
		return 1;
	}
	return 0;
}
int funcEventGopt(sf::Event* event,int n,Interface* inter) {
	return 0;
}
int funcEventGaopt(sf::Event* event,int n,Interface* inter) {
	tgui::ListBox::Ptr listCommande = (tgui::ListBox::Ptr)getWidget(inter,"listCommande");
	if (listCommande->getSelectedItemIndex() != -1) { //An element of the keymapping list is selected
		DBG << "Un element est séléctionné";
		inter->getCurrent()->setFlag(listCommande->getSelectedItemIndex() + 1); //Start waiting for a key
		listCommande->setSelectedBackgroundColor(
				sf::Color(238, 44, 44, 100));
	}
	if (n != 0) /*The Game Option interface is waiting for a key */
	{
		tgui::ListBox::Ptr listCommande = (tgui::ListBox::Ptr)getWidget(inter,"listCommande");
		if ((*event).type == sf::Event::KeyPressed) {
			//We get the name of the key pressed, we modify the config file and set the listcommand in its original state
			std::string keyPressed = getKeyName(event->key.code);
			modifyConfig(n - 1, keyPressed);
			reloadKeyMapping(listCommande);
			listCommande->deselectItem();
			inter->getCurrent()->setFlag(0);
			listCommande->setSelectedBackgroundColor(sf::Color(200,
					200, 200, 100));
		}
		if (event->type == sf::Event::MouseButtonPressed) {
			//We get the button pressed, we modify the config file and set the listcommand in its original state
			if (event->mouseButton.button == sf::Mouse::Right) {
				modifyConfig(n - 1, "Right Mouse Button");
				reloadKeyMapping(listCommande);
				listCommande->deselectItem();
				inter->getCurrent()->setFlag(0);
				listCommande->setSelectedBackgroundColor(sf::Color(200,
						200, 200, 100));
			}
			if (event->mouseButton.button == sf::Mouse::Left) {
				modifyConfig(n - 1, "Left Mouse Button");
				reloadKeyMapping(listCommande);
				listCommande->deselectItem();
				inter->getCurrent()->setFlag(0);
				listCommande->setSelectedBackgroundColor(sf::Color(200,
						200, 200, 100));
			}
		}
	}
	return 0;
}


int callbackGaopt(int n , std::string* str,Interface* inter) {
	DBG << "callbackGaopt";

	if (n == 2) {
		*str = "opt"; // go back to option menu
		return 1;
	}
	if (n == 1) { //reset default key map button pushed
		remove("../../conf/keymap.conf");
		if (copierFichier("../../defaultkeymap.conf",
				"../../conf/keymap.conf") != 0) {
			return 0;
		};
		std::vector<sf::String> nametab = (inter->getCurrent())->getWidgetNames();
		std::vector<tgui::Widget::Ptr> widtab = (inter->getCurrent())->getWidgets();
		int widtabn = widtab.size();
		for (int j = 0 ; j < widtabn ; j++) {
			std::string totest = nametab[j].toAnsiString();
			if (totest.compare("listCommande") == 0) {
				reloadKeyMapping(widtab[j]);
			}
		}
	}
	if (n == 3) { //Apply Nick button pushed
		std::vector<sf::String> nametab = (inter->getCurrent())->getWidgetNames();
		std::vector<tgui::Widget::Ptr> widtab = (inter->getCurrent())->getWidgets();
		int widtabn = widtab.size();
		tgui::Label::Ptr labelNick;
		DBG<< "apply pressed & nickbox not found";
		for (int j = 0 ; j < widtabn ; j++) {

			std::string totest = nametab[j].toAnsiString();
			if (totest.compare("nickbox") == 0) {
				DBG<< "apply pressed & nickbox found";
				sf::String newNickString = ((tgui::EditBox::Ptr)widtab[j])->getText();
				std::string newNickStdString = newNickString.toAnsiString();
				if (newNickStdString.compare("") != 0) {
					DBG<< "string non vide";
					FILE * fnick = fopen("../../conf/nick.conf", "wb");
					fprintf(fnick, "%s\n", newNickStdString.c_str());
					std::cout << newNickStdString.c_str();
					fclose(fnick);
					((tgui::Label::Ptr)getWidget(inter,"labelNick"))->setText((std::string) "NickName ("
							+ newNickStdString + (std::string) ")");
				}
			}
		}
		return 0;
	}
	return 0;
}
int callbackAopt(int n , std::string* str,Interface* inter) {
	if (n == 1) { //Return to option menu button pushed
		*str = "opt"; //option menu
		modifyConfigAudio(inter->getAudioVol(),
				inter->getAudioVol());
		return 1;
	}
	return 0;
}
int funcEventAopt(sf::Event* event,int n,Interface* inter) {
	tgui::Scrollbar::Ptr scrollbarVolumeMusic = (tgui::Scrollbar::Ptr) getWidget(inter,"scrollbarVolumeMusic");
	tgui::Scrollbar::Ptr scrollbarVolumeSound = (tgui::Scrollbar::Ptr) getWidget(inter,"scrollbarVolumeSound");
	if (inter->getAudioVol() != (int) scrollbarVolumeMusic->getValue()) { //the music volume cursor position changed
		inter->setAudioVol(scrollbarVolumeMusic->getValue());
	}
	if (inter->getAudioVol() != (int) scrollbarVolumeSound->getValue()) { //the sound volume cursor position changed
		inter->setAudioVol(scrollbarVolumeSound->getValue());
	}
	return 0;
}
int callbackJgm(int n , std::string* str,Interface* inter) {
	if (n == 1) { //Return to main
		*str = "main";
		return 1;
	}
	return 0;
}
int funcEventJgm(sf::Event* event,int n,Interface* inter) {
	tgui::EditBox::Ptr chatinsert = (tgui::EditBox::Ptr) getWidget(inter,"chatinsert");
	tgui::ChatBox::Ptr chatbox = (tgui::ChatBox::Ptr) getWidget(inter,"chatbox");
	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Return) { //In the join game menu, the user returned a text via the chat box, we get it and send it to the chatbox and to the other users
			std::string nickName = loadNick();
			sf::String newchatString = chatinsert->getText();
			chatinsert->setText("");
			std::string newchatStdString =
					newchatString.toAnsiString();

			if (newchatStdString.compare("") != 0) {
				ChatEvent toSend;
				toSend.setData(nickName + (std::string) " : " + newchatStdString);
				inter->getClient()->sendMessage<ChatEvent>(toSend);
				//Réponse du Server
				std::vector<ChatEvent *> tabMessages ;
				if(inter->getServer() != NULL)
				{
					tabMessages = inter->getServer()->receiveMessages<ChatEvent>();
					for (int i = 0 ; i < (int) tabMessages.size() ; i++) {
						inter->getServer()->broadcastMessage(*(tabMessages[i]),false);
					};
				}
				std::vector<ChatEvent *> tabMessagesClient = inter->getClient()->receiveMessages<ChatEvent>();

				DBG << "Taille du tableau de message des serveurs : " << tabMessages.size();
				chatbox->addLine(nickName + (std::string) " : "
						+ newchatStdString, sf::Color(0, 0, 0));
				for (int i = 0 ; i < (int) tabMessagesClient.size() ; i++) {
					chatbox->addLine(tabMessagesClient[i]->getData(),sf::Color(0,0,0));
				}
			}
		}
	}
	return 0;
}
