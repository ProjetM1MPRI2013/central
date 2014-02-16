/*
 * @Author: Anthony 
 */
#include "hudMayor.h"
class Stuff;
#include "../scenario/Stack.h"
#include "../graphism/tilemap.h"


HudMayor::HudMayor(sf::RenderWindow* window, Simulation& simulation) :
	simulation(simulation) {
	this->w = (*window).getSize().x;
	this->h = (*window).getSize().y;
  this->mouseMovement = false;
  this->bup = false;
  this->bdown = false; 
  this->bleft = false;
  this->bright = false; 
	this->hud = tgui::Gui((*window));
	this->currentState = MAYOR_NUMBERS;
	this->nextState = MAYOR_ACTIONS;
	this->waitFor = WF_NONE;
  (this->hud).setGlobalFont("../fonts/leadcoat.ttf");

}
;

void HudMayor::init() 
{
  if (this->currentState != this->nextState) 
  {
    this->currentState = this->nextState;
    // Delete the old buttons 
		for (std::list<tgui::Button::Ptr>::iterator it =
		(this->buttonsList).begin();
		it != (this->buttonsList).end(); ++it) 
    {
      hud.remove(*it);
		};
		(this->buttonsList).clear();

    // Create the new buttons 
    if (this->currentState == MAYOR_ACTIONS)
    {
      // Create the "Add Cameras" button
		  tgui::Button::Ptr b_cam(this->hud);
			b_cam->load("../widgets∕Black.conf");
			b_cam->setSize(80, 40);
			b_cam->setPosition(150, this->h - 100);
			b_cam->setText("Add Cameras");
			b_cam->bindCallback(std::bind(&HudMayor::callback, this, 2), 
                          tgui::Button::LeftMouseClicked);
			//b_cam->setCallbackId(2);
			(this->buttonsList).push_back(b_cam);

      // Create the "Add Cops" button
		  tgui::Button::Ptr b_cop(this->hud);
			b_cop->load("../widgets∕Black.conf");
			b_cop->setSize(80, 40);
			b_cop->setPosition(50, this->h - 100);
			b_cop->setText("Add Cops");
			b_cop->bindCallback(std::bind(&HudMayor::callback, this, 1), 
                          tgui::Button::LeftMouseClicked);
			//b_cop->setCallbackId(1);
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
			  button->bindCallback(std::bind(&HudMayor::callback, this, k), 
                            tgui::Button::LeftMouseClicked);
			  //button->setCallbackId(k);
			  (this->buttonsList).push_back(button);
      };

      // Create the "Back" button
      tgui::Button::Ptr b_back(this->hud);
	    b_back->load("../widgets∕Black.conf");
	    b_back->setSize(80, 40);
	    b_back->setPosition(this->w - 100, this->h - 100);
	    b_back->setText("Back");
	    b_back->bindCallback(std::bind(&HudMayor::callback, this, 0), 
                          tgui::Button::LeftMouseClicked);
	    //b_back->setCallbackId(0);
	    (this->buttonsList).push_back(b_back);
 
    };
  };
};

void HudMayor::event(sf::RenderWindow* window, sf::Event event , TileMap* tilemap) {
	if (event.type == sf::Event::MouseWheelMoved)
	{
		int zoom = tilemap->getZoom();
		tilemap->setZoom(zoom + event.mouseWheel.delta);
	}
  if (event.type == sf::Event::Closed)
		(*window).close();

	if (waitFor == WF_NONE) {
		// Je crois qu'on veut rajouter une action Mayor newmovement
		// je verrai plus tard comment on fait exactement
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Z:
				if (not this->bup) {
					//newMovement (NewMov::P_UP,(&this->simulation));
          mouseMovement = false;
					this->bup = true;
				};
				break;
			case sf::Keyboard::Q:
				if (not this->bleft) {
					//newMovement (NewMov::P_LEFT,(&this->simulation));
          mouseMovement = false;
					this->bleft = true;
				};
				break;
			case sf::Keyboard::S:
				if (not this->bdown) {
					//newMovement (NewMov::P_DOWN,(&this->simulation));
          mouseMovement = false;
					this->bdown = true;
				};
				break;
			case sf::Keyboard::D:
				if (not this->bright) {
					//newMovement (NewMov::P_RIGHT,(&this->simulation));
          mouseMovement = false;
					this->bright = true;
				};
				break;
			default:
				break;
			};
		};

		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
			case sf::Keyboard::Z:
				//newMovement (NewMov::R_UP,(&this->simulation));
				this->bup = false;
				break;
			case sf::Keyboard::Q:
				//newMovement (NewMov::R_LEFT,(&this->simulation));
				this->bleft = false;
				break;
			case sf::Keyboard::S:
				//newMovement (NewMov::R_DOWN,(&this->simulation));
				this->bdown = false;
				break;
			case sf::Keyboard::D:
				//newMovement (NewMov::R_RIGHT,(&this->simulation));
				this->bright = false;
				break;
			default:
				break;
			};
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

void HudMayor::callback(unsigned int callback_id) 
{
  //while ((this->hud).pollCallback(callback)) 
  //{
    // an action is clicked. 
    if ((this->currentState) == MAYOR_ACTIONS) 
    {
      if (callback_id == 1) 
      {
        this->currentAction = CA_COP; 
        this->nextState = MAYOR_NUMBERS; 
      };
      if (callback_id == 2) 
      {
        this->currentAction = CA_CAM; 
        this->nextState = MAYOR_NUMBERS; 
      };
    };
     
    if ((this->currentState) == MAYOR_NUMBERS)
    {
      // a number is clicked.
      if (callback_id > 0 && callback_id < 11) 
      {
        this->currentNumber = callback_id; 
        setwf(WF_CLICK); 
      }
      // The "Back" button is clicked. 
      if (callback_id == 0)
        this->nextState = MAYOR_ACTIONS; 
    }
  //}; 
}
;

void HudMayor::draw() {
	(this->hud).draw();
  std::cout << "Il y a " << (this->buttonsList).size() << " bouttons." << std::endl;
}
;

void HudMayor::setwf(WaitFor w) {
	this->waitFor = w;
}
;
