/*
 * def_button.h
 *
 *  Created on: 20 févr. 2014
 *      Author: matthieu
 */

#ifndef DEF_BUTTON_H_
#define DEF_BUTTON_H_

extern GuiExtended mainWidgetsMenu;
extern GuiExtended optWidgetsMenu;

int callbackMain(int n , std::string* str, Interface* inter);//Fonction qui gère les callback de la fenetre main
int funcEventMain(sf::Event* event,int n,Interface* inter);//Fonction qui gère les events de la fenetre main
int callbackOpt(int n , std::string* str,Interface* inter);//Fonction qui gère les callback de la fenetre Option
int funcEventOpt(sf::Event* event,int n,Interface* inter);//Fonction qui gère les events de la fenetre Option
int callbackGopt(int n , std::string* str,Interface* inter);//Fonction qui gère les callback de la fenetre Graphic Option
int funcEventGopt(sf::Event* event,int n,Interface* inter);//Fonction qui gère les events de la fenetre Graphic Option
int callbackGaopt(int n , std::string* str,Interface* inter);//Fonction qui gère les callback de la fenetre Game Option
int funcEventGaopt(sf::Event* event,int n,Interface* inter);//Fonction qui gère les events de la fenetre Game Option
int callbackAopt(int n , std::string* str,Interface* inter);//Fonction qui gère les callback de la fenetre Audio Option
int funcEventAopt(sf::Event* event,int n,Interface* inter);//Fonction qui gère les events de la fenetre Audio Option
int callbackJgm(int n , std::string* str,Interface* inter);//Fonction qui gère les callback de la fenetre Join Game
int funcEventJgm(sf::Event* event,int n,Interface* inter);//Fonction qui gère les events de la fenetre Join Game
#endif /* DEF_BUTTON_H_ */
