#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "test/test.h"
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "interfaceinit/interface_init.h"
#include "generation/geography.h"
#include "generation/generation1.h"
#include "network/network.h"
#include "network/netEvent.h"
#include "network/dummyServer.h"
#include "network/dummyClient.h"
#include "simulation/simulation.h"
#include <time.h>
#include <thread>
#include "graphism/tilemap.h"
#include "graphism/graphic_context_iso.h"
#include <unistd.h>
#include <stdio.h>
#include "hud/hudMayor.h"
#include "hud/hudTerro.h"
#include <TGUI/TGUI.hpp>
#include <string>

#define DEBUG false

#ifdef __APPLE__
#define CLOSE_KEYS ((event.key.code == sf::Keyboard::Q) && event.key.system)
#else
#define CLOSE_KEYS ((event.key.code == sf::Keyboard::F4) && event.key.alt)
#endif

void clientLoop(int id, int nbPlayers, bool isFullScreen, int tileW, int tileH,
		sf::VideoMode video_mode, Client* clientPtr, Geography& geo, sf::RenderWindow* window) {

	if (isFullScreen) {
		(*window).create(video_mode, "Game Interface", sf::Style::Fullscreen);
	} else
		(*window).create(video_mode, "Game Interface");
	Simulation simu = Simulation(&geo, tileW, tileH, nbPlayers, 1);
	simu.setClient(clientPtr);
	GraphicContextIso graContIso = GraphicContextIso(&geo, &simu);
	graContIso.load();
	//TileMap tilemap = TileMap(&simu, &geo);
	//geo.printMatrix();

        //[joseph] ceci est un NPC de test, il bouge mais n'est pas dessiné
        // il marche tout droit, c'est parce que j'ai commenté les appels à gou goh gol gor qui ne sont à mon avis pas générées correctement
        //mais il marche tout droit en faisant A* !
        simu.ajouterNPC(11,1,24,2);
        
	sf::Clock clock;
	sf::Time dt = sf::Time::Zero;
	HudTerro hudTerro = HudTerro(window, simu);
  hudTerro.init();
	while ((*window).isOpen()) {
		dt = clock.restart();
		sf::Event event;
		while ((*window).pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				(*window).close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F11) {
					if (isFullScreen) {
						(*window).create(video_mode, "Game Interface");
						isFullScreen = false;
					} else {
						(*window).create(video_mode, "Game Interface",
								sf::Style::Fullscreen);
						isFullScreen = true;
					}
				}
				if (CLOSE_KEYS) {
					(*window).close();
				}

			}
			hudTerro.event(window, event);
		}

		simu.run(dt);
		//tilemap.run(window);
		graContIso.run(window);
		(*window).setView((*window).getDefaultView());
		//window.clear();
		hudTerro.draw();
		(*window).display();
	}
	return;
}

void serverLoop(int id, int tileW, int tileH, int nbPlayers, Server* serverPtr,
		Geography& geo, sf::RenderWindow* window) {

	Simulation simu = Simulation(&geo, tileW, tileH, nbPlayers, id);
	simu.setServer(serverPtr);

	sf::Clock clock;
	sf::Time dt = sf::Time::Zero;
	while (window->isOpen ()) {
		dt = clock.restart();
		sf::Event event;
		simu.run(dt);
	}

	return;
}

int main(int argc, char ** argv) {
	int sizeFenetre[3], b;
	bool isFullScreen;
	sf::VideoMode video_mode;
	if (DEBUG) {
		b = 1;
		isFullScreen = true;
		video_mode = sf::VideoMode::getDesktopMode();
	} else {
		b = interface_initiale(sizeFenetre, &isFullScreen);
		video_mode = sf::VideoMode(sizeFenetre[0], sizeFenetre[1],
				sizeFenetre[2]);
	}

	if (b == 0) {
		return 0;
	} else {
		sf::RenderWindow window;
		window.setKeyRepeatEnabled(false);
		int nbPlayers = 1;
                //[joseph] les 2 variables qui suivent sont stupides, elles doivent nécessairement valloir 1 pour que tout puisse marcher, il faudra les supprimer de simulation
		int tileW = 1;
		int tileH = 1;
		Geography geo;
		std::cout << argc << std::endl;
		if (argc <= 1) {
		  geo = (Geography) Generation1("Geriatric Terrorist Anarchy");
		}
		else {
		  geo = (Geography) Generation1(std::string (argv[1]));
		}
		//geo.printMatrix();

		Server* serverPtr = Network::createDummyServer();
		Client* clientPtr = Network::createDummyClient(serverPtr);

		std::thread serverThread { std::bind(serverLoop, 0, tileW, tileH,
				nbPlayers, serverPtr, geo ,&window) };

		clientLoop(1, nbPlayers, isFullScreen, tileW, tileH, video_mode,
				clientPtr, geo, &window);
		serverThread.join();

		return 1;
	};

	// ISO Map, not used for now
	//Defintion of the window
	/*	if (b == 0) {
	 return 0;
	 } else {
	 sf::VideoMode video_mode = sf::VideoMode(sizeFenetre[0],
	 sizeFenetre[1], sizeFenetre[2]);
	 sf::RenderWindow window;

	 if (isFullScreen) {
	 window.create(video_mode, "Game", sf::Style::Fullscreen);
	 } else {
	 window.create(video_mode, "Game");
	 }

	 sf::Vector2u size = window.getSize();
	 unsigned int w = size.x;
	 unsigned int h = size.y;
	 //End Defintion of the window

	 // Loading Textures

	 Geography geo = (Geography) Generation1("424242"); // Il faudra un jour qu'on m'explique ce que dois faire main, parce que là c'est n'importe quoi ~ MrKulu

	 sf::Texture a1, b1, b2;
	 //A priori le working directory est src/interfaceinit, alors il faut remonter loin ...
	 printcwd();
	 assert(!a1.loadFromFile("../../../sprite/Anim.png"));
	 assert(!b1.loadFromFile("../../../sprite/Road_NS.png"));
	 assert(!b2.loadFromFile("../../../sprite/maison1.png"));

	 // Definition of the Context Iso

	 GraphicContextIso gci(&geo);

	 TexturePack tp1;
	 tp1.texture = a1;
	 tp1.nbAnim = {1,12,16};
	 tp1.widthSprite = {16,16,32};
	 tp1.heightSprite = 32;
	 tp1.offsetX = {0,0,0};
	 tp1.offsetY = {8,8,8};
	 tp1.isLoop = {true, true, false};
	 SpriteTilePack stp1 = {.texture = b1 , .originX = 0 , .originY = 39 , .X1 = 0 , .Y1 = 0, .X2 = 157 , .Y2 = 79 }, stp2 = {.texture = b2 , .originX = 0 , .originY = 109 , .X1 = 0, .Y1 = 0, .X2 = 157 , .Y2 = 149 };

	 gci.addTexturePack(tp1);
	 gci.addSpriteTilePack(stp1);
	 gci.addSpriteTilePack(stp2);
	 gci.load(); // Charge les textures de base de la map

	 //inputState s = { true, window };

	 // Chargement de la vue

	 sf::View isoView;
	 isoView.setSize(sf::Vector2f(size.x,size.y)); // A placer dans la boucle pricipale si on veut avoir une fenêtre de taille variable pendant le jeu.
	 isoView.setCenter(OFFSET_X+40,OFFSET_Y+20); // Pour tester

	 window.setView(isoView); // Pour tester

	 while (window.isOpen()) {
	 sf::Event event;
	 while (window.pollEvent(event)) {

	 }

	 window.clear();
	 window.draw(gci); // Dessine la map
	 window.display();
	 }
	 window.close();
	 return 0;
	 //window.close();
	 //return 0;
	 }*/
}
;
