#ifndef HUD_H
#define HUD_H 

#include <TGUI/TGUI.hpp> 
#include <string> 
#include <iostream> 
#include <sstream> 
#include "scenario/ActionsTerro.h" 

enum ButtonState {INVENT, ACTIONS} 

class Hud 
{
  public: 
    void event(sf::Event event); 
    void callback(tgui::Callback callback); 
    void draw(); 


  private: 
    unsigned int w; 
    unsigned int h; 
    tgui::Gui hud; 
    std::list<Stuff*> inventory; 
    std::list<std::string> currentActions; 
    std::list<tgui::Button::Ptr> buttonsList; 
    bool waitForClick; 
    ButtonState currentState; 
    ButtonState nextState; 

};

Hud (sf::RenderWindow window);  


#endif

