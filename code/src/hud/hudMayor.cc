#include "hudMayor.h"
class Stuff;
#include "../scenario/Stack.h"
#include "../graphism/tilemap.h"


HudMayor::HudMayor(sf::RenderWindow* window, Simulation& simulation) :
	simulation(simulation) {
	this->w = (*window).getSize().x;
	this->h = (*window).getSize().y;
	this->hud = tgui::Gui((*window));
	this->currentState = MAYOR_ACTIONS;
	this->nextState = MAYOR_NUMBERS;
	this->waitFor = WF_NONE;

}
;

void HudMayor::init() 
{
  if (this->currentState != this->nextState) 
  {
    // Delete the old buttons 
		for (std::list<tgui::Button::Ptr>::iterator it =
		(this->buttonsList).begin();
		it != (this->buttonsList).end(); ++it) 
    {
			delete &it;
		};
		(this->buttonsList).clear();

    // Create the new buttons 
    if (this->nextState == MAYOR_ACTIONS)
    {
      // Create the "Add Cameras" button
		  tgui::Button::Ptr b_cam(this->hud);
			b_cam->load("../widgets∕Black.conf");
			b_cam->setSize(80, 40);
			b_cam->setPosition(150, this->h - 100);
			b_cam->setText("Add Cameras");
			b_cam->bindCallback(tgui::Button::LeftMouseClicked);
			b_cam->setCallbackId(2);
			(this->buttonsList).push_back(b_cam);

      // Create the "Add Cops" button
		  tgui::Button::Ptr b_cop(this->hud);
			b_cop->load("../widgets∕Black.conf");
			b_cop->setSize(80, 40);
			b_cop->setPosition(50, this->h - 100);
			b_cop->setText("Add Cops");
			b_cop->bindCallback(tgui::Button::LeftMouseClicked);
			b_cop->setCallbackId(1);
			(this->buttonsList).push_back(b_cop);
    }
    else 
    {
      // Create the Number buttons 
      for (int k = 1; k<11; k++) 
      {
        tgui::Button::Ptr button(this->hud);
			  button->load("../widgets∕Black.conf");
			  button->setSize(40, 40);
			  button->setPosition(50 + k*50, this->h - 100);
			  button->setText(std::to_string(k));
			  button->bindCallback(tgui::Button::LeftMouseClicked);
			  button->setCallbackId(k);
			  (this->buttonsList).push_back(button);
      };
      // Create the "Back" button
      tgui::Button::Ptr b_back(this->hud);
	    b_back->load("../widgets∕Black.conf");
	    b_back->setSize(80, 40);
	    b_back->setPosition(this->w - 100, this->h - 100);
	    b_back->setText("Back");
	    b_back->bindCallback(tgui::Button::LeftMouseClicked);
	    b_back->setCallbackId(0);
	    (this->buttonsList).push_back(b_back);
 
    };
  };
  
  this->currentState = this->nextState; 

};

void HudMayor::event(sf::RenderWindow* window, sf::Event event , TileMap* tilemap) {
	if (event.type == sf::Event::MouseWheelMoved)
	{
		int zoom = tilemap->getZoom();
		tilemap->setZoom(zoom + event.mouseWheel.delta);
	}
  if (event.type == sf::Event::Closed)
		(*window).close();

	if (event.type == sf::Event::KeyPressed) {
		// Je crois qu'on veut rajouter une action Mayor newmovement
		// je verrai plus tard comment on fait exactement
		switch (event.key.code) {
		case sf::Keyboard::Z:
			//newMovement (NewMov::P_UP);
			break;
		case sf::Keyboard::Q:
			//NewMovement (NewMov::P_LEFT);
			break;
		case sf::Keyboard::S:
			//NewMovement (NewMov::P_DOWN);
			break;
		case sf::Keyboard::D:
			//NewMovement (NewMov::P_RIGHT);
			break;
		default:
			break;
		};
	};
  
  if (waitFor == WF_CLICK) 
  {
    if (event.type == sf::Event::MouseButtonPressed) 
    { 
      if (event.mouseButton.button == sf::Mouse::Left) 
      {
        // TODO : obtenir les coordonnées de la map
        /* TODO : envoyer les coordonnées et currentNumber, 
         *        en fonction de currentAction
         *        avec AddCams ou AddCops
         */
        setwf(WF_NONE); 
      }
      else 
      {
        setwf(WF_NONE); 
      };
    }
    else 
    {
      if (event.type == sf::Event::KeyPressed) 
      {
        setwf(WF_NONE); 
      };
    }; 
  }; 
   

	// Pass the event to all the current widgets
	(this->hud).handleEvent(event);
}
;

void HudMayor::callback(tgui::Callback callback) 
{
  while ((this->hud).pollCallback(callback)) 
  {
    // an action is clicked. 
    if ((this->currentState) == MAYOR_ACTIONS) 
    {
      if (callback.id == 1) 
      {
        this->currentAction = CA_COP; 
        this->nextState = MAYOR_NUMBERS; 
      };
      if (callback.id == 2) 
      {
        this->currentAction = CA_CAM; 
        this->nextState = MAYOR_NUMBERS; 
      };
    };
     
    if ((this->currentState) == MAYOR_NUMBERS)
    {
      // a number is clicked.
      if (callback.id > 0 && callback.id < 11) 
      {
        this->currentNumber = callback.id; 
        setwf(WF_CLICK); 
      }
      // The "Back" button is clicked. 
      if (callback.id == 0)
        this->nextState = MAYOR_ACTIONS; 
    }
  }; 
}
;

void HudMayor::draw() {
	(this->hud).draw();
}
;

void HudMayor::setwf(WaitFor w) {
	this->waitFor = w;
}
;
