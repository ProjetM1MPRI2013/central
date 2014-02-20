/*
 * @Author: Anthony
 */
#ifndef HUDM_H
#define HUDM_H

#include "SFML/Window.hpp"
#include <TGUI/TGUI.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "../scenario/Stack.h"
#include "../scenario/ActionsPC.h"
class TileMap;

//enum WaitFor {WF_NONE, WF_CLICK};

enum MayorState {MAYOR_ACTIONS, MAYOR_NUMBERS}; 

enum CurrentAction {CA_CAM1, CA_CAM2, CA_COP}; 

class Simulation;

class HudMayor: public PreHud {
public:
	HudMayor(sf::RenderWindow* window, Simulation& simulation);
	void init(Simulation& simulation);
	void event(sf::RenderWindow* window, sf::Event e, TileMap* tilemap, LocalState* localState);
	void callback(unsigned int callback_id);
	void draw();
	void setwf(WaitFor w);
  void newMessage(std::string message);
  void deleteMessage();

	/* In the main loop, the 3 methods must be called in this specific order :
	 * init();
	 * event(window, event, tilemap);
	 * draw();
	 */

private:
  bool mouseMovement;
	unsigned int w;
	unsigned int h;
	unsigned int i;
	Simulation& simulation;
  bool bup;
  bool bdown;
  bool bleft; 
  bool bright;
	tgui::Gui hud;
	std::list<tgui::Button::Ptr> buttonsList;
  std::list<tgui::Label::Ptr> goldList;
  std::list<tgui::Label::Ptr> messagesList;
  MayorState currentState; 
  MayorState nextState; 
  CurrentAction currentAction; 
  unsigned int currentNumber; 
	WaitFor waitFor;
  int gold;
};

#endif

