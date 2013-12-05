#include "hudTerro.h" 
#include "../scenario/Stack.cc"


HudTerro::HudTerro(sf::RenderWindow window) 
{
  Stack stack(Stack.Stack()); 
  this->w = window.getsize().x; 
  this->h = window.getsize().y; 
  tgui::Gui (this->hud)(window); 
  this->inventory = simulation->getPlayer()->getInventory(); 
  this->waitFor = NONE; 
  this->currentState = INVENT; 
  this->nextState = INVENT; 
  stack.setHud(this);

};

HudTerro::init() = 
{
  this->currentState = this->nextState; 
  if (this->currentState = INVENT) 
  {
    // if the inventory must be updated
    if ((this->inventory) != (simulation->getPlayer()->getInventory())) 
    {

      // Delete the old buttons 
      for (std::list<tgui::Button::Ptr>::iterator it = (this->buttonsList).begin(); it != (this->buttonsList).end(); ++it)
	    { 
        delete (*it);  
	    }; 
      (this->buttonsList).clear; 

      // Updtate the inventory 
      (this->inventory).clear; 
      this->inventory = (simulation->getPlayer()->getInventory()); 

      // Create the new buttons 
      this->i = 0; 
      for (std::list<Stuff*>::iterator it = (this->inventory).begin(); it != (this->inventory).end(); ++it) 
      {
        tgui::Button::Ptr button(this->hud); 
        button->load("../widgets∕Black.conf"); 
        button->setSize(80,40); 
        button->setPosition(50+(this->i)*100, this->h-100); 
        button->setText((*it).name()); 
        button->bindCallback(tgui::Button::LeftMouseClicked); 
        button->setCallbackId(this->i+1);
        (this->buttonsList).push_back(button); 
        (this->i)++; 
      };
    };
  };
};

HudTerro::event(sf::RenderWindow window, sf::Event event) = 
{
  while (window.pollEvent(event)) 
  {
    if (event.type == sf::Event::Closed) 
      window.close(); 

    if (waitFor == NONE) 
    {
      if (event.type == sf::Event::KeyPressed) 
      {
        switch (event.key.code) 
        {
          case sf::Keyboard::Z: 
            newMovement (NewMov::P_UP); 
            break;
          case sf::Keyboard::Q: 
            NewMovement (NewMov::P_LEFT); 
            break; 
          case sf::Keyboard::S: 
            NewMovement (NewMov::P_DOWN); 
            break; 
          case sf::Keyboard::D: 
            NewMovement (NewMov::P_RIGHT); 
            break; 
        };
      };

      if (event.type == sf::Event::KeyReleased) 
      {
        switch (event.key.code) 
        {
          case sf::Keyboard::Z: 
            newMovement (NewMov::R_UP); 
            break;
          case sf::Keyboard::Q: 
            NewMovement (NewMov::R_LEFT); 
            break; 
          case sf::Keyboard::S: 
            NewMovement (NewMov::R_DOWN); 
            break; 
          case sf::Keyboard::D: 
            NewMovement (NewMov::R_RIGHT); 
            break; 
        };
      };
    };

    if (waitFor == CLICK) 
    {
      if (event.type == sf::Event::MouseButtonPressed) 
      {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
          // TODO : envoyer le clic si c'est un NPC 
        };
        else 
        {
          stack.cancel();
        };
      };
      else 
      {
        if (event.type == sf::Event::KeyPressed) 
        {
          stack.cancel(); 
        };
      };
    };

    // Pass the event to all the current widgets 
    (this->hud)->handleEvent(event); 
  };
  
};

HudTerro::callback(tgui::Callback callback) = 
{
  while((this->hud)->pollCallback(callback))
  {
    if ((this->currentState) == INVENT)
    {
      if (callback.id > 0 && callback.id <= (this->buttonsList).size()) 
      {
        // Save the selected item 
        std::list<Stuff*>::iterator it = (this->inventory).begin();
        for (int i = 1, i < callback.id, i++) 
        {
          ++it; 
        };
        this->currentStuff = (*it); 

        // Get the possible actions for the item 
        this->actionsList = (this->currentStuff)->getActionsPossible();
        
        // Delete the old buttons 
        for (std::list<tgui::Button::Ptr>::iterator it = (this->buttonsList).begin(); it != (this->buttonsList).end(); ++it)
	      { 
          delete (*it);  
	      };
        (this->buttonsList).clear; 

        // Create the new buttons 
        this->i = 0; 
        for (std::list<Actions>::iterator it = (this->actionsList).begin(); it != (this->actionsList).end(); ++it) 
        {
          tgui::Button::Ptr button(this->hud); 
          button->load("../widgets∕Black.conf"); 
          button->setSize(80,40); 
          button->setPosition(50+(this->i)*100, this->h-100); 
          button->setText(stringOfActions(*it)); 
          button->bindCallback(tgui::Button::LeftMouseClicked); 
          button->setCallbackId(this->i+1);
          (this->buttonsList).push_back(button); 
          (this->i)++; 
        };

        // Create the 'Inventory' button. 
        tgui::Button::Ptr button(this->hud); 
        button->load("../widgets∕Black.conf"); 
        button->setSize(80,40); 
        button->setPosition(50+(this->w-100, this->h-100); 
        button->setText("Inventory"); 
        button->bindCallback(tgui::Button::LeftMouseClicked); 
        button->setCallbackId(0);
        (this->buttonsList).push_back(button); 

        // Update the flag 
        this->nextState = ACTIONS; 
      };
    };

    if (this->currentState == ACTIONS) 
    {
      // the button 'Inventory' is clicked. 
      if (callback.id == 0) 
      {
        this->nextState = INVENT;
        (this->actionsList).clear;   
      };

      // an action is clicked. 
      if (callback.id > 0 && callback.id < (this->buttonList).size())
      {
        std::list<Actions>::iterator it = (this->actionsList).begin();
        for (int i = 1, i < callback.id, i++) 
        {
          ++it; 
        };
        stack.newAction((*it),this->currentStuff); 
      };
    };
  };  
}; 


HudTerro::draw() = 
{
  (this->hud)->draw(); 
};

HudTerro::setwf(WaitFor w) = 
{
  this->waitFor = w; 
};


