#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "main.h"
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
#include <time.h>
#include <thread>
#include "graphism/tilemap.h"
#include "graphism/graphic_context_iso.h"
#include <unistd.h>
#include <stdio.h>
#include "hud/hudMayor.h"
#include "hud/hudTerro.h"
#include "HScenario.h"
#include <TGUI/TGUI.hpp>
#include <string>
#include <random>

#include "localState.h"
#include "globalState.h"

#define DEBUG true
#define TERRO true // ~TERRO => MAYOR
#include "debug.h"

#ifdef __APPLE__
#define CLOSE_KEYS ((event.key.code == sf::Keyboard::Q) && event.key.system)
#else
#define CLOSE_KEYS ((event.key.code == sf::Keyboard::F4) && event.key.alt)
#endif
void clientLoop(int id, int nbPlayers, bool isFullScreen,
                sf::VideoMode video_mode, Client* clientPtr, std::string seed,
                sf::RenderWindow* window) {

  Geography geo = Generation1(seed);

  LocalState loc = LocalState(&geo,nbPlayers, 1);
  HScenario scenar = HScenario(loc);
  loc.setScenario(&scenar);
  loc.setClient(clientPtr);
  GraphicContextIso graContIso = GraphicContextIso(&geo, &loc);
  TileMap tilemap = TileMap(&loc, &geo);
  //geo.printMatrix();
  if (TERRO) {
    // graContIso.load();
   } else {
     /* MAYOR */
   }

  std::default_random_engine npcGen (42);

  if (TERRO) {
      //[joseph] ceci est un NPC de test
      //on en génère 500 à la création de la map, puis plus après
      //(pour l'instant, après la classe simulation les fera apparaître et disparaître)
    dummy::createNPCs(500, loc, graContIso, geo, npcGen);
  }
        
  sf::Clock clock;
  sf::Time dt = sf::Time::Zero;
  HudTerro hudTerro = HudTerro(window, loc);
  //hudTerro.init();
  while ((*window).isOpen()) {
    dt = clock.restart();
    hudTerro.init(); 
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

    loc.run(dt);
    window->clear();
    if (TERRO) {
      graContIso.run(window);
      (*window).setView((*window).getDefaultView());
    } else { // MAYOR
      tilemap.run(window);
    }
    hudTerro.draw();
    (*window).display();
  }

  return;
}

void serverLoop(int id,int nbPlayers, Server* serverPtr,
		std::string seed, sf::RenderWindow* window) {

    Geography geo = Generation1(seed);
    GlobalState glob = GlobalState(&geo,nbPlayers, id);
    glob.addPlayer(Player(1,99,99));
    glob.getPlayerByID(1).isServer = 1;
    glob.setServer(serverPtr);

    sf::Clock clock;
    sf::Time dt = sf::Time::Zero;
    while (window->isOpen()) {
        dt = clock.restart();
//        sf::Event event;
        glob.run(dt);
    }

  return;
}

int main(int argc, char ** argv) {
  
  if (argc > 2 && (std::string)argv[1] == "test") {
    test::run(argv[2]);
    exit(0);
  }

  int sizeFenetre[3], b;
  bool isFullScreen;
  sf::VideoMode video_mode;
  /*  if (DEBUG) {
    b = 1;
    isFullScreen = true;
    video_mode = sf::VideoMode::getDesktopMode();
    } else {*/
  Server* serverPtr = Network::createDummyServer();
  Client* clientPtr = Network::createDummyClient(serverPtr);
    b = interface_initiale(sizeFenetre, &isFullScreen, serverPtr, clientPtr);
    video_mode = sf::VideoMode(sizeFenetre[0], sizeFenetre[1],
			       sizeFenetre[2]);
    //}

  if (b == 0) {
    return 0;
  } else {
    sf::RenderWindow window;
    if (isFullScreen) {
      window.create(video_mode, "Game Interface", sf::Style::Fullscreen);
    } else
      window.create(video_mode, "Game Interface");
    window.setKeyRepeatEnabled(false);
    int nbPlayers = 1;
    std::string seed;
    std::cout << argc << std::endl;
    if (argc <= 1) {
      seed = "424242";
    }
    else {
      seed = argv[1];
    }

    //geo.printMatrix();


    std::thread serverThread { std::bind(serverLoop, 0,
					 nbPlayers, serverPtr, seed ,&window) };

    clientLoop(1, nbPlayers, isFullScreen, video_mode,
	       clientPtr, seed, &window);
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

namespace dummy {
  void createNPCs(int number, LocalState& simu, GraphicContextIso& graContIso, Geography& geo, std::default_random_engine npcGen) {
    std::uniform_real_distribution<float> npcDistX(0.01,geo.getMapWidth()-0.01);
    std::uniform_real_distribution<float> npcDistY(0.01,geo.getMapHeight()-0.01);
    for (int i=0;i<number;i++) {
      Position start = Position(npcDistX(npcGen),npcDistY(npcGen));
      Position target = Position(npcDistX(npcGen),npcDistY(npcGen));
      while (start.isInTile(geo).getSpeed()==0) {
        start = Position(npcDistX(npcGen),npcDistY(npcGen));
      }
      while (target.isInTile(geo).getSpeed()==0||target.isInTile(geo).equals(start.isInTile(geo))) {
        target = Position(npcDistX(npcGen),npcDistY(npcGen));
      }
      simu.addNPC(start,target,1,graContIso.getTexturePack(i%2));

      //simu.addNPC(Position(8.5,0.5),Position(8.5,25.5),1,&tp1);

      //simu.addNPC(Position(8.5,25.5),Position(8.5,0.5),1,&tp1);
    }
  }
}
