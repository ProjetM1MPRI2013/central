/* 
 * @Author: Anthony
 */
#include "hudTerro.h"
class Clickable;
#include "../scenario/Stack.h"
#include "../scenario/PreStack.h"
#include "../graphism/graphic_context_iso.h"
#include "localState.h"

#define DEBUG false
#include "debug.h"
#define THEME_CONFIG_FILE_HUD_TERRO "../widgets/Black.conf"
#ifdef WINDOWSTEST
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define WithNetwork true //just for test (nobody)

//todo nobody inser in a new .cc

/*********************************************************
 ** end of Generated code**
 *********************************************************/





void printcwd() {
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
		std::cerr << "main: printcwd failed" << std::endl;
	}
	std::cerr << "The current working directory is "<< cCurrentPath << std::endl;
}


;

HudTerro::HudTerro(sf::RenderWindow* window, LocalState& simulation, GraphicContextIso& context) :
				simulation(simulation), context(context) {
	this->stack = (new Stack (&simulation,this));
	this->w = (*window).getSize().x;
	this->h = (*window).getSize().y;
  this->mouseMovement = false;
	this->bup = false;
	this->bdown = false;
	this->bleft = false;
	this->bright = false;
	this->hud = tgui::Gui((*window));
	this->inventory = simulation.getOwner().getInventory();
	(this->inventory).clear();
	this->waitFor = WF_NONE;
	this->currentState = BS_INVENT;
	this->nextState = BS_INVENT;
	DBG << "created Hudterro";
	(this->hud).setGlobalFont("../fonts/leadcoat.ttf");

	//tgui::Picture::Ptr picture3(this->hud);
	//picture3->load("../interfaceinit/pic.jpg");
	//picture3->setSize(w, h);
	//picture3->setPosition(0, 0);

}
;

HudTerro::~HudTerro(){
  delete stack;
}

void HudTerro::init() {

/*switch (waitFor) {
  case WF_NONE:
    std::cout << "WF_NONE" << std::endl;
    break;
  case WF_CLICK:
    std::cout << "WF_CLICK" << std::endl;
    break;
  case WF_PICK:
    std::cout << "WF_PICK" << std::endl;
    break;
  case WF_STUFF:
    std::cout << "WF_STUFF" << std::endl;
    break;
   case WF_ERROR:
    std::cout << "WF_ERROR" << std::endl;
    break;
};
*/



	this->currentState = this->nextState;
	//std::cerr << "KOUKOU" << std::endl;
	//if ((this-> currentState) == BS_INVENT) {std::cerr << "BS_INVENT" << std::endl;};
	//if ((this-> currentState) == BS_ACTIONS) {std::cerr << "BS_ACTIONS" << std::endl;};
	if (this->currentState == BS_INVENT) {
		// if the inventory must be updated


		//FIXME We don't check that inventory has changed for now (temporary)
		if (((this->inventory) != (simulation.getOwner().getInventory()))
        ||(this->inventory).empty()) // for the case we just dropped the last item
    {
			//Delete the old buttons
			for (std::list<tgui::Button::Ptr>::iterator it =
					(this->buttonsList).begin();
					it != (this->buttonsList).end(); ++it) {
				hud.remove(*it);
			};
			(this->buttonsList).clear();

			//Updtate the inventory
			(this->inventory).clear();
			this->inventory = (simulation.getOwner().getInventory());

			// Create the new buttons of the inventory
			this->i = 0;
			for (int stuffID : inventory) {

				std::cout << "id du stuff : " <<  stuffID << std::endl;

				Clickable stuff = simulation.getOwner().getItemByID<Clickable>(stuffID);
				tgui::Button::Ptr button(this->hud);
				button->load(THEME_CONFIG_FILE_HUD_TERRO);
				button->setSize(80, 40);
				button->setPosition(50 + (this->i) * 100, this->h - 100);
				DBG << "button placed at " << (50 + (this->i) * 100) << "x" << this->h - 100;
				button->setText(stuff.name);
				//button->setCallbackId(this->i + 1);
				button->bindCallback(std::bind(&HudTerro::callback, this, (i+1)), 
						tgui::Button::LeftMouseClicked);
				(this->buttonsList).push_back(button);
				(this->i)++;
				DBG << "adding " << stuff.name;
			};

      // Create the 'pick' button
      tgui::Button::Ptr b_pick(this->hud);
      b_pick->load(THEME_CONFIG_FILE_HUD_TERRO);
      b_pick->setSize(80,40);
      b_pick->setPosition(50 + this->w - 200, this->h - 100);
      b_pick->setText("Pick");
      b_pick->bindCallback(std::bind(&HudTerro::callback, this, 0), 
            tgui::Button::LeftMouseClicked);
      (this->buttonsList).push_back(b_pick);
		};
	};
}
;

void HudTerro::event(sf::RenderWindow* window, sf::Event event, GraphicContextIso& context) {
	if (event.type == sf::Event::Closed)
		(*window).close();

	if (waitFor == WF_NONE) {
		if (event.type == sf::Event::KeyPressed) {
			// Je crois qu'on veut rajouter une action terro newmovement
			// je verrai plus tard comment on fait exactement
			switch (event.key.code) {
			case sf::Keyboard::Z:
				if (not this->bup) {
					newMovement (NewMov::P_UP,(&this->simulation));
          mouseMovement = false;
					this->bup = true;
				};
				break;
			case sf::Keyboard::Q:
				if (not this->bleft) {
					newMovement (NewMov::P_LEFT,(&this->simulation));
          mouseMovement = false;
					this->bleft = true;
				};
				break;
			case sf::Keyboard::S:
				if (not this->bdown) {
					newMovement (NewMov::P_DOWN,(&this->simulation));
          mouseMovement = false;
					this->bdown = true;
				};
				break;
			case sf::Keyboard::D:
				if (not this->bright) {
					newMovement (NewMov::P_RIGHT,(&this->simulation));
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
				newMovement (NewMov::R_UP,(&this->simulation));
				this->bup = false;
				break;
			case sf::Keyboard::Q:
				newMovement (NewMov::R_LEFT,(&this->simulation));
				this->bleft = false;
				break;
			case sf::Keyboard::S:
				newMovement (NewMov::R_DOWN,(&this->simulation));
				this->bdown = false;
				break;
			case sf::Keyboard::D:
				newMovement (NewMov::R_RIGHT,(&this->simulation));
				this->bright = false;
				break;
			default:
				break;
			};
		};
    if (event.type == sf::Event::MouseWheelMoved) {
      std::cout << "Molette : " << event.mouseWheel.delta << std::endl;
      if (event.mouseWheel.delta != 0) {
        if (event.mouseWheel.delta > 0) {
          context.zoom(0.9);
        } else {
          context.zoom(1.1);
        };
      }; 
    };
	};

	if (waitFor == WF_CLICK) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				// envoyer le clic si c'est sur la hitbox d'un NPC
        sf::Vector2i clicPosition = sf::Mouse::getPosition(*window); 
        Position mapPosition = context.screenToMap(clicPosition.x,clicPosition.y);
        std::list<NPC*> NPCList = mapPosition.getNPCList(*(simulation.getMap()));       
        std::cout << "Taille de NPCList : " << NPCList.size() << std::endl;
        if (!NPCList.empty()) {
          stack->sendNpc((*(NPCList.front())).getUuid());
        }
			} else {
				stack->cancel();
			};
		} else {
			if (event.type == sf::Event::KeyPressed) {
				stack->cancel();
			}
		};
	};

  if (waitFor == WF_PICK) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i clicPosition = sf::Mouse::getPosition(*window); 
        Position mapPosition = context.screenToMap(clicPosition.x,clicPosition.y);
        // pick the closest item to the position
        // if there is such an item
        setwf(WF_NONE);
      } else {
        setwf(WF_NONE);
      };
    } else {
      if (event.type == sf::Event::KeyPressed) {
        setwf(WF_NONE); 
      }
    };
  };
  

  // Pass the event to all the current widgets
  bool consumed = (this->hud).handleEvent(event);

  // If a click wasn't used by the widgets, pass it to the game area.
  if (!consumed && waitFor != WF_CLICK) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        mouseMovement = true;
      }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        mouseMovement = false;
      }
    }
  }
  // Moving player with the mouse. Moving is true if the left mouse button is 
  // pressed and the player hasn't pressed direction keys.
  if (mouseMovement) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    newMouseMovement(context.screenToMap(mousePos.x, mousePos.y), (&this->simulation));
  }
}
;

void HudTerro::callback(unsigned int callback_id) {
	//tgui::Callback callback;
	//while ((this->hud).pollCallback(callback)) {
	std::cerr << "callback : " << callback_id << std::endl;
	if ((this->currentState) == BS_INVENT) {
    if (waitFor == WF_NONE) {
      // The 'pick' button is clicked
      if (callback_id == 0) {
        setwf(WF_PICK);
      };

      // An item of the inventory is clicked
		  if (callback_id > 0 && callback_id <= (this->buttonsList).size()) {
			  // Save the selected item
			  this->currentStuffID = inventory[((int)callback_id) - 1]; // horrible
			  // Get the possible actions for the item
			  // test without network nobody
			  if (WithNetwork) {
				  this->actionTypeList = simulation.getOwner().getItemByID<Clickable>(currentStuffID).getActionTypePossible();
			  } 
			  else {
				  std::list<ActionType> actionTypeList;
				  this->actionTypeList = actionTypeList;
				  this->actionTypeList.push_back(ToA_Drop);
			  };
			  // Delete the old buttons
			  for (std::list<tgui::Button::Ptr>::iterator it =
			  		(this->buttonsList).begin();
				  	it != (this->buttonsList).end(); ++it) {
				  hud.remove(*it);
				  //delete &it;
			  };
			  (this->buttonsList).clear();
			  (this->inventory).clear();

			  // Create the new buttons
			  this->i = 0;
			  for (std::list<ActionType>::iterator it =
					  (this->actionTypeList).begin();
					  it != (this->actionTypeList).end(); ++it)
			  {
				  tgui::Button::Ptr button(this->hud);
				  button->load(THEME_CONFIG_FILE_HUD_TERRO);
				  button->setSize(80, 40);
				  button->setPosition(50 + (this->i) * 100, this->h - 100);
				  button->setText(stringOfActions(*it));
				  button->bindCallback(std::bind(&HudTerro::callback, this, (i+1)),
						  tgui::Button::LeftMouseClicked);
				  //button->setCallbackId(this->i + 1);
				  (this->buttonsList).push_back(button);
				  (this->i)++;
			  };

			  // Create the 'Inventory' button.
			  tgui::Button::Ptr button(this->hud);
			  button->load(THEME_CONFIG_FILE_HUD_TERRO);
			  button->setSize(80, 40);
			  button->setPosition(50 + (this->w - 200), this->h - 100);
			  button->setText("Inventory");
			  button->bindCallback(std::bind(&HudTerro::callback, this, 0),
					  tgui::Button::LeftMouseClicked);
			  //button->setCallbackId(0);
			  (this->buttonsList).push_back(button);

			  // Update the flag
			  this->nextState = BS_ACTIONS;
		  };
    };
    if (waitFor == WF_STUFF) {
		  if (callback_id > 0 && callback_id <= (this->buttonsList).size()) {
	      this->currentStuffID = inventory[((int)callback_id) - 1]; 
        // envoyer le stuff à Rémy
      };
    };
	};

	if (this->currentState == BS_ACTIONS) {
		// the button 'Inventory' is clicked.
		if (callback_id == 0) {
			std::cerr << "Inventory" << std::endl;
			this->nextState = BS_INVENT;
			(this->actionTypeList).clear();
		};

		// an action is clicked.
		if (callback_id > 0 && callback_id < (this->buttonsList).size()) {
			std::list<ActionType>::iterator it = (this->actionTypeList).begin();
			for (unsigned int i = 1; i < callback_id; i++) {
				++it;
			};
			stack->newAction((*it), this->currentStuffID);
      this->nextState = BS_INVENT;
			(this->actionTypeList).clear();

		};
	};
}
;

void HudTerro::draw() {
	(this->hud).draw();
	std::vector<sf::String> t = (this->hud).getWidgetNames();
	//std::cerr << "I'm drawing, Bitch " << t.size() << std::endl;
}
;

void HudTerro::setwf(WaitFor w) {
	this->waitFor = w;
}
;
