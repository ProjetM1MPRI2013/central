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

int callbackMain(int n , std::string* str, Interface* inter);
int funcEventMain(sf::Event* event,int n,Interface* inter);
int callbackOpt(int n , std::string* str,Interface* inter);
int funcEventOpt(sf::Event* event,int n,Interface* inter);
int callbackGopt(int n , std::string* str,Interface* inter);
int funcEventGopt(sf::Event* event,int n,Interface* inter);
int callbackGaopt(int n , std::string* str,Interface* inter);
int funcEventGaopt(sf::Event* event,int n,Interface* inter);
int callbackAopt(int n , std::string* str,Interface* inter);
int funcEventAopt(sf::Event* event,int n,Interface* inter);
int callbackJgm(int n , std::string* str,Interface* inter);
int funcEventJgm(sf::Event* event,int n,Interface* inter);
#endif /* DEF_BUTTON_H_ */
