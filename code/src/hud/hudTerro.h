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
#include "../scenario/PreStack.h"
#include "graphic_context_iso.h"
enum ButtonState {
	BS_INVENT, BS_ACTIONS
};

//enum WaitFor {WF_NONE, WF_CLICK};

class LocalState;

void printcwd ();
class HudTerro: public PreHud {
public:
	HudTerro(sf::RenderWindow* window, LocalState& simulation, GraphicContextIso& context);
	void init();
	void event(sf::RenderWindow* window, sf::Event e, GraphicContextIso& context);
	void callback(unsigned int callback_id);
	void draw();
	void setwf(WaitFor w);
  void newMessage(std::string message);
  void deleteMessage();
	Stack* stack;
  ~HudTerro();

	/* In the main loop, the 3 methods must be called in this specific order :
	 * init();
	 * event(window, event, context);
	 * draw();
	 */

private:
  bool mouseMovement;
	unsigned int w;
	unsigned int h;
	int i;
	LocalState& simulation;
  GraphicContextIso& context;
	bool bup;
	bool bdown;
	bool bleft;
	bool bright;
	tgui::Gui hud;
	std::vector<int> inventory;
	std::list<ActionType> actionTypeList;
	std::list<tgui::Button::Ptr> buttonsList;
  std::list<tgui::Label::Ptr> messagesList;
	WaitFor waitFor;
	ButtonState currentState;
	ButtonState nextState;
	int currentStuffID;

};

#endif

