#ifndef HUD_H
#define HUD_H 

#include <TGUI/TGUI.hpp> 
#include <string> 
#include <iostream> 
#include <sstream> 
#include "scenario/ActionsTerro.h" 

class Hud 
{
  public: 
    void event(); 
    void callback(); 
    void draw(); 


  private: 
    unsigned int w; 
    unsigned int h; 
    tgui::Gui hud; 
    std::list<Stuff*> inventory; 
    std::list<std::string> currentActions; 
    std::list<tgui::Button::Ptr> buttonsList; 
    bool waitForClick; 


};

Hud (sf::RenderWindow window);  


#endif

