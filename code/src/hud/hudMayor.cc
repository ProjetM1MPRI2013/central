#include "hudMayor.h"
class Stuff;
#include "../scenario/Stack.h"
#include "../graphism/tilemap.h"


HudMayor::HudMayor(sf::RenderWindow* window, Simulation& simulation) :
	simulation(simulation) {
	this->w = (*window).getSize().x;
	this->h = (*window).getSize().y;
	this->hud = tgui::Gui((*window));
	this->waitFor = WF_NONE;
	stack.setHud((PreHud*) this);

}
;

void HudMayor::init() {
}

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
	// Pass the event to all the current widgets
	(this->hud).handleEvent(event);
}
;

void HudMayor::callback(tgui::Callback callback) {
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
