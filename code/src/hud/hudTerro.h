#ifndef HUD_H
#define HUD_H 

#include "SFML/Window.hpp"
#include <TGUI/TGUI.hpp> 
#include <string> 
#include <iostream> 
#include <sstream> 
#include "../scenario/ActionsTerro.h" 

enum ButtonState {BS_INVENT, BS_ACTIONS} ;

enum WaitFor {WF_NONE, WF_CLICK};
class Stack;
#include "Stack.h"
class Simulation;

class HudTerro 
{
  public: 
    HudTerro (sf::RenderWindow window, Simulation& simulation);  
    void init(); 
    void event(sf::RenderWindow window, sf::Event e); 
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
    std::list<Stuff*> inventory; 
    std::list<Actions> actionsList; 
    std::list<tgui::Button::Ptr> buttonsList; 
    WaitFor waitFor; 
    ButtonState currentState; 
    ButtonState nextState; 
    Stuff* currentStuff; 
    
};



#endif

