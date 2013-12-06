#ifndef HUD_H
#define HUD_H 

#include <TGUI/TGUI.hpp> 
#include <string> 
#include <iostream> 
#include <sstream> 
#include "../scenario/ActionsTerro.h" 

enum ButtonState {BS_INVENT, BS_ACTIONS} ;

enum WaitFor {WF_NONE, WF_CLICK};

class HudTerro 
{
  public: 
    HudTerro (sf::RenderWindow window);  
    void init(); 
    void event(sf::RenderWindow window, sf::Event event); 
    void callback(tgui::Callback callback); 
    void draw(); 
    void setwf(WaitFor w); 

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

