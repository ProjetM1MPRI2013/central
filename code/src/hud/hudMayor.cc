/*
 * @Author: Anthony 
 */
#include "hudMayor.h"
#include "../scenario/Stack.h"
#include "../graphism/tilemap.h"
#include "../scenario/PreScenarioActionList.h"
#include "../simulation/simulation.h"
#include "localState.h"
#define THEME_CONFIG_FILE_HUD_MAYOR "../widgets/Black.conf"


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
  this->gold = simulation.getSous();
  tgui::Label::Ptr l_gold(this->hud);
  l_gold->load(THEME_CONFIG_FILE_HUD_MAYOR);
  l_gold->setText("Gold : "+std::to_string(gold));
  l_gold->setPosition(this->w - 200, 50);
  l_gold->setTextColor(sf::Color(255, 255, 0));
  l_gold->setTransparency(0);
  (this->goldList).push_back(l_gold);
}
;

void HudMayor::init(Simulation& simulation) 
{
  // Refresh the gold displayed
  if (gold != simulation.getSous()) {
    gold = simulation.getSous();
    hud.remove((this->goldList).front());
    (this->goldList).clear();
    tgui::Label::Ptr l_gold(this->hud);
    l_gold->load(THEME_CONFIG_FILE_HUD_MAYOR);
    l_gold->setText("Gold : "+std::to_string(gold));
    l_gold->setPosition(this->w - 200, 50);
    l_gold->setTextColor(sf::Color(255, 255, 0));
    l_gold->setTransparency(0);
    (this->goldList).push_back(l_gold);
  };
  // If we must change the buttons
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
      // Create the "Add other Cameras" button
      tgui::Button::Ptr b_ocam(this->hud);
			b_ocam->load(THEME_CONFIG_FILE_HUD_MAYOR);
			b_ocam->setSize(80, 40);
			b_ocam->setPosition(250, this->h - 100);
			b_ocam->setText("Add other Cameras");
			b_ocam->bindCallback(std::bind(&HudMayor::callback, this, 3), 
                          tgui::Button::LeftMouseClicked);
			(this->buttonsList).push_back(b_ocam);


      // Create the "Add Cameras" button
		  tgui::Button::Ptr b_cam(this->hud);
			b_cam->load(THEME_CONFIG_FILE_HUD_MAYOR);
			b_cam->setSize(80, 40);
			b_cam->setPosition(150, this->h - 100);
			b_cam->setText("Add Cameras");
			b_cam->bindCallback(std::bind(&HudMayor::callback, this, 2), 
                          tgui::Button::LeftMouseClicked);
			(this->buttonsList).push_back(b_cam);

      // Create the "Add Cops" button
		  tgui::Button::Ptr b_cop(this->hud);
			b_cop->load(THEME_CONFIG_FILE_HUD_MAYOR);
			b_cop->setSize(80, 40);
			b_cop->setPosition(50, this->h - 100);
			b_cop->setText("Add Cops");
			b_cop->bindCallback(std::bind(&HudMayor::callback, this, 1), 
                          tgui::Button::LeftMouseClicked);
			(this->buttonsList).push_back(b_cop);
    }
    else 
    {
      // Create the Number buttons 
      for (int k = 1; k<11; k++) 
      {
        tgui::Button::Ptr button(this->hud);
			  button->load(THEME_CONFIG_FILE_HUD_MAYOR);
			  button->setSize(40, 20);
			  button->setPosition(50 + k*50, this->h - 90);
			  button->setText(std::to_string(k));
			  button->bindCallback(std::bind(&HudMayor::callback, this, k), 
                            tgui::Button::LeftMouseClicked);
			  (this->buttonsList).push_back(button);
      };

      // Create the "Back" button
      tgui::Button::Ptr b_back(this->hud);
	    b_back->load(THEME_CONFIG_FILE_HUD_MAYOR);
	    b_back->setSize(80, 40);
	    b_back->setPosition(this->w - 100, this->h - 100);
	    b_back->setText("Back");
	    b_back->bindCallback(std::bind(&HudMayor::callback, this, 0), 
                          tgui::Button::LeftMouseClicked);
	    (this->buttonsList).push_back(b_back);
 
    };
  };
};

void HudMayor::event(sf::RenderWindow* window, sf::Event event , TileMap* tilemap, 
                      LocalState* localState) {
	if (event.type == sf::Event::MouseWheelMoved)
	{
		int zoom = tilemap->getZoom();
		tilemap->setZoom(zoom + event.mouseWheel.delta);
	}
  if (event.type == sf::Event::Closed)
		(*window).close();

	if (waitFor == WF_NONE) {
    // Movement with keyboard
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Z:
				if (not this->bup) {
					tilemap->newMovement (NewMov::P_UP,(this->simulation));
          mouseMovement = false;
					this->bup = true;
				};
				break;
			case sf::Keyboard::Q:
				if (not this->bleft) {
					tilemap->newMovement (NewMov::P_LEFT,(this->simulation));
          mouseMovement = false;
					this->bleft = true;
				};
				break;
			case sf::Keyboard::S:
				if (not this->bdown) {
					tilemap->newMovement (NewMov::P_DOWN,(this->simulation));
          mouseMovement = false;
					this->bdown = true;
				};
				break;
			case sf::Keyboard::D:
				if (not this->bright) {
					tilemap->newMovement (NewMov::P_RIGHT,(this->simulation));
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
				tilemap->newMovement (NewMov::R_UP,(this->simulation));
				this->bup = false;
				break;
			case sf::Keyboard::Q:
				tilemap->newMovement (NewMov::R_LEFT,(this->simulation));
				this->bleft = false;
				break;
			case sf::Keyboard::S:
				tilemap->newMovement (NewMov::R_DOWN,(this->simulation));
				this->bdown = false;
				break;
			case sf::Keyboard::D:
				tilemap->newMovement (NewMov::R_RIGHT,(this->simulation));
				this->bright = false;
				break;
			default:
				break;
			};
		};
	};
  
  // Selecting where to add the Cameras/Cops
  if (waitFor == WF_CLICK) 
  {
    if (event.type == sf::Event::MouseButtonPressed) 
    { 
      if (event.mouseButton.button == sf::Mouse::Left) 
      {
        sf::Vector2i clicPosition = sf::Mouse::getPosition(*window);
        Position mapPosition = (*tilemap).CoordMouse(clicPosition);
        if (this->currentAction == CA_COP) {
          AddCops addCops = AddCops(this->currentNumber, mapPosition.getX(),
                                  mapPosition.getY(), localState);
          addCops.run();
        };
        if (this->currentAction == CA_CAM1) {
          AddCams addCams = AddCams(this->currentNumber, mapPosition.getX(),
                                  mapPosition.getY(), localState);
          addCams.run();
        };
        if (this->currentAction == CA_CAM2) {
          AddCams addCams = AddCams(this->currentNumber, mapPosition.getX(),
                                  mapPosition.getY(), localState);
          addCams.run2();
        };
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
      this->currentAction = CA_CAM1; 
      this->nextState = MAYOR_NUMBERS; 
    };
    if (callback_id == 3)
    {
      this->currentAction = CA_CAM2;
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
    };
    // The "Back" button is clicked. 
    if (callback_id == 0)
    {
      this->nextState = MAYOR_ACTIONS; 
    };
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

void HudMayor::newMessage(std::string message) {
    tgui::Label::Ptr l_message(this->hud);
    l_message->load(THEME_CONFIG_FILE_HUD_MAYOR);
    l_message->setText(message);
    l_message->setPosition(this->w/2, this->h -150);
    l_message->setTextColor(sf::Color(255, 0, 0));
    l_message->setTransparency(0);
    (this->messagesList).push_back(l_message);
}
;

void HudMayor::deleteMessage() {
	for (std::list<tgui::Label::Ptr>::iterator it =
	    	(this->messagesList).begin();
		    it != (this->messagesList).end(); ++it) {
		hud.remove(*it);
	};
	(this->messagesList).clear();
}
;


