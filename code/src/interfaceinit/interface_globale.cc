/*
 * @Author : Matthieu
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
#include "interface_globale.h"
#define DEBUG true
#include <debug.h>
using namespace std;

GuiExtended::GuiExtended(): tgui::Gui() {
	this->flag = 0;
}

GuiExtended::GuiExtended(sf::RenderWindow* window) : tgui::Gui(*window) {
  this->flag = 0;}

int GuiExtended::handleCallbackgui(int n,std::string* str) {
	int m = (this->funcCallBack)(n,str,this->inter);
	return m;
}
Interface* GuiExtended::getInterface() {
	return this->inter;
}
void GuiExtended::setInterface(Interface* interface) {
	this->inter = interface;
}
void GuiExtended::setFuncCallback(int (*f)(int,std::string*,Interface*)) {
	this->funcCallBack = f;
}
void GuiExtended::setFuncEvent(int (*f)(sf::Event* event,int flag,Interface*)) {
	this->funcEvent = f;
}
void GuiExtended::handleEventgui(sf::Event* event) {
	//DBG << "I am in the handleEventgui";
	//DBG << this->flag;
	(this->funcEvent)(event,this->flag,this->inter);
	//DBG << "I am after the handleEventgui";
}
void GuiExtended::setFlag(int n) {
	this->flag = n;
}
int GuiExtended::getFlag() {
	return this->flag;
}
Interface::Interface(sf::RenderWindow* window,sf::VideoMode* video_mode,Server* server, Client* client) {
	win = window;
	videoMode = video_mode;
	out = 0;
	serverPtr = server;
	clientPtr = client;
}
std::list<GuiExtended*>& Interface::getGuilist () {
	return this->guiList;
}
sf::RenderWindow* Interface::getWindow() {
	return (this->win);
}
void Interface::setMenuChange(std::string str) {
	sf::SoundBuffer changementMenuBuffer;
	if ((changementMenuBuffer).loadFromFile(str)) {
		DBG << "loading sound with success";
		(this->changementMenu).setBuffer(changementMenuBuffer);
		(this->changementMenu).setVolume(soundvol);
	}
	else {
		DBG << "loading sound fail";
	}
	this->changementMenu.play();
}

void Interface::setMusic(std::string str) {
	interfaceMusic.openFromFile(str);
}
void Interface::setAudioVol(int av) {
	this->audiovol = av;
	this->interfaceMusic.setVolume(audiovol);
}
void Interface::setSoundVol(int sv) {
	this->soundvol = sv;
	this->changementMenu.setVolume(soundvol);
}
int Interface::getAudioVol() {
	return (this->audiovol);
}
int Interface::getSoundVol() {
	return (this->soundvol);
}
void Interface::addtgui(GuiExtended* gui , std::string name) {
	gui->setInterface(this);
	(this->guiList).push_back(gui);
	(this->nameList).push_back(new std::string(name));
}
void Interface::handleEvent(sf::Event* event) {
	//DBG << "I am in the handleEvent";
	(this->toDraw)->handleEventgui(event);
	//DBG << "I am after the handleEventgui";
	(this->toDraw)->handleEvent((*event));
	//DBG << "I hope you will pass this";
}
void Interface::handleCallBack() {

	tgui::Callback callback;
	std::string goTo = "";
	while (toDraw->pollCallback(callback)) {
		DBG << "I am in the handleCallBack and there is a callback";
		int nb = toDraw->handleCallbackgui(callback.id,&goTo);
		DBG << "valeur de nb : " << nb;
		if (nb >= 1) {
			DBG << "supposed to play sound";
			this->changementMenu.play();
			DBG << "supposed to play sound fin ";
			int n = 0;
			list<std::string*>::iterator i;
			for(i = nameList.begin() ; i != nameList.end() && (*i)->compare(goTo) !=0 ; ++i) {n++;};
			if (i == nameList.end()) {
				DBG<< "il n'y a pas de " << (goTo);
			}
			else {
				list<GuiExtended*>::iterator j;
				for(j = guiList.begin() ; n !=0 ; ++j) {n--;};
				toDraw = (*j);
				current = "main";
			}
		}
	}
}
void Interface::init() {
	this->interfaceMusic.play();
	this->interfaceMusic.setLoop(true);
	this->interfaceMusic.setVolume(audiovol);
	isFullScreen = true;
	int n = 0;
	list<std::string*>::iterator i;
	for(i = nameList.begin() ; i != nameList.end() && (*i)->compare("main") !=0 ; ++i) {n++;};
	if (i == nameList.end()) {
		DBG<< "il n'y a pas de main\n";
	}
	else {
		list<GuiExtended*>::iterator j;
		for(j = guiList.begin() ; n !=0 ; ++j) {n--;};
		toDraw = (*j);
		current = "main";
	}

}
void Interface::setVideoMode(sf::VideoMode* video_mode) {
	videoMode = video_mode;
}
sf::VideoMode* Interface::getVideoMode() {
	return videoMode;
}
GuiExtended* Interface::getCurrent () {
	return (this->toDraw);
}
Server* Interface::getServer() {
	return this->serverPtr;
}
void Interface::setServer(Server* serv) {
	this->serverPtr = serv;
}
Client* Interface::getClient() {
	return this->clientPtr;
}
void Interface::setClient(Client* client) {
	this->clientPtr = client;
}
void Interface::draw() {
	//DBG << "drawing the Interface";
	this->toDraw->draw();
}
