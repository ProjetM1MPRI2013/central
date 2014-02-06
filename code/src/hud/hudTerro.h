/*
 * @Author: Anthony 
 */
#ifndef HUD_H
#define HUD_H 

#include "SFML/Window.hpp"
#include <TGUI/TGUI.hpp> 
#include <string> 
#include <iostream> 
#include <sstream> 
#include "../scenario/Stack.h"

enum ButtonState {
	BS_INVENT, BS_ACTIONS
};

//enum WaitFor {WF_NONE, WF_CLICK};

class Simulation;

void printcwd ();
class HudTerro: public PreHud {
public:
	HudTerro(sf::RenderWindow* window, Simulation& simulation);
	void init();
	void event(sf::RenderWindow* window, sf::Event e);
	void callback(unsigned int callback_id);
	void draw();
	void setwf(WaitFor w);
	Stack* stack;

	/* In the main loop, the 4 methods must be called in this specific order :
	 * init();
	 * event(window, event);
	 * callback(callback);
	 * draw();
	 */

private:
	unsigned int w;
	unsigned int h;
	int i;
	Simulation& simulation;
	bool bup;
	bool bdown;
	bool bleft;
	bool bright;
	tgui::Gui hud;
	std::vector<int> inventory;
	std::list<ActionType> actionTypeList;
	std::list<tgui::Button::Ptr> buttonsList;
	WaitFor waitFor;
	ButtonState currentState;
	ButtonState nextState;
	int currentStuffID;

};

#endif

