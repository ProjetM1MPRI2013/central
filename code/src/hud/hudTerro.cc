#include "hudTerro.h"
class Stuff;
#include "../scenario/Stack.h"

#define DEBUG false
#define THEME_CONFIG_FILE_HUD_TERRO "../widgets/Black.conf"
#ifdef WINDOWSTEST
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

void printcwd() {
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
		std::cerr << "main: printcwd failed" << std::endl;
	}
	std::cerr << "The current working directory is "<< cCurrentPath << std::endl;
}

std::string stringOfActions(Actions a) {
	switch (a) {
	case DROP:
		return "Drop";
		break;
	case ATTACK:
		return "Attack";
		break;
	case RELOAD:
		return "Reload";
		break;
	case PLANT:
		return "Plant";
		break;
	case NONE:
	  return "None";
	  break;
	};
	//Should not happens
	return "Error";
}
;

HudTerro::HudTerro(sf::RenderWindow* window, Simulation& simulation) :
		simulation(simulation) {
	this->stack = Stack();
	this->w = (*window).getSize().x;
	this->h = (*window).getSize().y;
	this->hud = tgui::Gui((*window));
	this->inventory = simulation.getPlayer()->getInventory();
	(this->inventory).clear();
	this->waitFor = WF_NONE;
	this->currentState = BS_INVENT;
	this->nextState = BS_INVENT;
	stack.setHud((PreHud*) this);
	std::cerr << "created Hudterro" << std::endl;
	(this->hud).setGlobalFont("../fonts/leadcoat.ttf");

	//tgui::Picture::Ptr picture3(this->hud);
	//picture3->load("../interfaceinit/pic.jpg");
	//picture3->setSize(w, h);
	//picture3->setPosition(0, 0);

}
;

void HudTerro::init() {
	this->currentState = this->nextState;
	if (this->currentState == BS_INVENT) {
		// if the inventory must be updated
		if ((this->inventory) != (simulation.getPlayer()->getInventory())) {
			// Delete the old buttons
			for (std::list<tgui::Button::Ptr>::iterator it =
					(this->buttonsList).begin();
					it != (this->buttonsList).end(); ++it) {
				delete &it;
			};
			(this->buttonsList).clear();

			// Updtate the inventory
			(this->inventory).clear();
			this->inventory = (simulation.getPlayer()->getInventory());

			// Create the new buttons
			this->i = 0;
			for (std::list<Stuff*>::iterator it = (this->inventory).begin();
					it != (this->inventory).end(); ++it) {
				tgui::Button::Ptr button(this->hud);
				button->load(THEME_CONFIG_FILE_HUD_TERRO);
				button->setSize(80, 40);
				button->setPosition(50 + (this->i) * 100, this->h - 100);
				std::cerr << "button placed at " << (50 + (this->i) * 100) << "x" << this->h - 100 << std::endl;
				button->setText((*it)->name);
				button->setCallbackId(this->i + 1);
				button->bindCallback(tgui::Button::LeftMouseClicked);
				(this->buttonsList).push_back(button);
				(this->i)++;
				std::cerr << "adding " << (*it)->name << std::endl;
			};
		};
	};
}
;

void HudTerro::event(sf::RenderWindow* window, sf::Event* event) {
		if (event->type == sf::Event::Closed)
			(*window).close();

		if (waitFor == WF_NONE) {
			if (event->type == sf::Event::KeyPressed) {
				// Je crois qu'on veut rajouter une action terro newmovement
				// je verrai plus tard comment on fait exactement
				switch (event->key.code) {
				case sf::Keyboard::Z:
					newMovement (NewMov::P_UP,(&this->simulation));
					break;
				case sf::Keyboard::Q:
					newMovement (NewMov::P_LEFT,(&this->simulation));
					break;
				case sf::Keyboard::S:
					newMovement (NewMov::P_DOWN,(&this->simulation));
					break;
				case sf::Keyboard::D:
					newMovement (NewMov::P_RIGHT,(&this->simulation));
					break;
				default:
					break;
				};
			};

			if (event->type == sf::Event::KeyReleased) {
				switch (event->key.code) {
				case sf::Keyboard::Z:
					newMovement (NewMov::R_UP,(&this->simulation));
					break;
				case sf::Keyboard::Q:
					newMovement (NewMov::R_LEFT,(&this->simulation));
					break;
				case sf::Keyboard::S:
					newMovement (NewMov::R_DOWN,(&this->simulation));
					break;
				case sf::Keyboard::D:
					newMovement (NewMov::R_RIGHT,(&this->simulation));
					break;
				default:
					break;
				};
			};
		};

		if (waitFor == WF_CLICK) {
			if (event->type == sf::Event::MouseButtonPressed) {
				if (event->mouseButton.button == sf::Mouse::Left) {
					// TODO : envoyer le clic si c'est un NPC
				} else {
					stack.cancel();
				};
			} else {
				if (event->type == sf::Event::KeyPressed) {
					stack.cancel();
				};
			};
		};

		// Pass the event to all the current widgets
		//std::cerr << "passe dedans" << std::endl;
		(this->hud).handleEvent((*event));
}
;

void HudTerro::callback() {
	tgui::Callback callback;
	while ((this->hud).pollCallback(callback)) {
		std::cerr<< "in callback" << std::endl;
		if ((this->currentState) == BS_INVENT) {
			if (callback.id > 0 && callback.id <= (this->buttonsList).size()) {
				// Save the selected item
				std::list<Stuff*>::iterator it = (this->inventory).begin();
				for (unsigned int i = 1; i < callback.id; i++) {
					++it;
				};
				this->currentStuff = (*it);

				// Get the possible actions for the item
				this->actionsList = (this->currentStuff)->getActionsPossible();

				// Delete the old buttons
				for (std::list<tgui::Button::Ptr>::iterator it =
						(this->buttonsList).begin();
						it != (this->buttonsList).end(); ++it) {
					delete &it;
				};
				(this->buttonsList).clear();

				// Create the new buttons
				this->i = 0;
				for (std::list<Actions>::iterator it =
						(this->actionsList).begin();
						it != (this->actionsList).end(); ++it) {
					tgui::Button::Ptr button(this->hud);
					button->load(THEME_CONFIG_FILE_HUD_TERRO);
					button->setSize(80, 40);
					button->setPosition(50 + (this->i) * 100, this->h - 100);
					button->setText(stringOfActions(*it));
					button->bindCallback(tgui::Button::LeftMouseClicked);
					button->setCallbackId(this->i + 1);
					(this->buttonsList).push_back(button);
					(this->i)++;
				};

				// Create the 'Inventory' button.
				tgui::Button::Ptr button(this->hud);
				button->load(THEME_CONFIG_FILE_HUD_TERRO);
				button->setSize(80, 40);
				button->setPosition(50 + (this->w - 100), this->h - 100);
				button->setText("Inventory");
				button->bindCallback(tgui::Button::LeftMouseClicked);
				button->setCallbackId(0);
				(this->buttonsList).push_back(button);

				// Update the flag
				this->nextState = BS_ACTIONS;
			};
		};

		if (this->currentState == BS_ACTIONS) {
			// the button 'Inventory' is clicked.
			if (callback.id == 0) {
				this->nextState = BS_INVENT;
				(this->actionsList).clear();
			};

			// an action is clicked.
			if (callback.id > 0 && callback.id < (this->buttonsList).size()) {
				std::list<Actions>::iterator it = (this->actionsList).begin();
				for (unsigned int i = 1; i < callback.id; i++) {
					++it;
				};
				stack.newAction((*it), this->currentStuff);
			};
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
