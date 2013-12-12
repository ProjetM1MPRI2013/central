#ifndef HUDM_H
#define HUDM_H

#include "SFML/Window.hpp"
#include <TGUI/TGUI.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "../scenario/Stack.h"
class TileMap;

//enum WaitFor {WF_NONE, WF_CLICK};

class Simulation;

class HudMayor: public PreHud {
public:
	HudMayor(sf::RenderWindow* window, Simulation& simulation);
	void init();
	void event(sf::RenderWindow* window, sf::Event e, TileMap* tilemap);
	void callback(tgui::Callback callback);
	void draw();
	void setwf(WaitFor w);
	Stack stack;

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
	tgui::Gui hud;
	std::list<Actions> actionsList;
	std::list<tgui::Button::Ptr> buttonsList;
	WaitFor waitFor;

};

#endif
