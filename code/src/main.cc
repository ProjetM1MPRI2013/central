#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <test/test.h>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <interfaceinit/interface_init.h>
#include <generation/geography.h>
#include <network/network.h>
#include <network/netEvent.h>
#include <simulation/simulation.h>
#include <time.h>
#include <thread>

void client(int id, Geography * geo, int nbPlayer, int mapSize,
		int TileSizeX, int TileSizeY, Network net, Server* serveur,
		int sizeFenetre[3], bool isFullScreen) {

	Client* client = net.createDummyClient(serveur);
	sf::VideoMode video_mode = sf::VideoMode(sizeFenetre[0], sizeFenetre[1],
			sizeFenetre[2]);
	sf::RenderWindow window;
	Simulation simu = Simulation(mapSize, TileSizeX, TileSizeY, nbPlayer, id,
			geo);
	if (isFullScreen) {
		window.create(video_mode, "Game", sf::Style::Fullscreen);
	} else {
		window.create(video_mode, "Game");
	}

	sf::Vector2u size = window.getSize();
	unsigned int w = size.x;
	unsigned int h = size.y;
	double dt;
	time_t tPrec;
	time_t tNow;
	time(&tPrec);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F11) {
					if (isFullScreen) {
						window.create(video_mode, "Game Interface");
						isFullScreen = false;
					} else {
						window.create(video_mode, "Game Interface",
								sf::Style::Fullscreen);
						isFullScreen = true;
					}
				}
			}
		}
		time(&tNow);
		dt = difftime(tNow, tPrec);
		tPrec = tNow;
		sf::Time dtTime = sf::seconds(dt);
		simu.run(dtTime);
		window.clear();

		window.display();
	}
	return;
}

int server() {

	return 0;
}

//	struct inputState {
//		bool hasFocus;
//		sf::RenderWindow& window;
//	};
//	int
//void updateInputState(inputState& s) {
//		sf::Event event;
//		while (s.window.pollEvent(event)) {
//			switch (event.type) {
//			case sf::Event::LostFocus:
///				s.hasFocus = false;
//				break;
//			case sf::Event::GainedFocus:
//				s.hasFocus = true;
//				break;
//			}
//		}
//	}

//	void handleKeys(inputState& s) {
//		// Close window on Alt+F4
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)
//				&& sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
//			s.window.close();
//		}
//	}

int main() {
	int sizeFenetre[3];
	bool isFullScreen;
	int b = interface_initiale(sizeFenetre, &isFullScreen);
	if (b == 0) {
		return 0;
	} else {
		std::cout << 1 <<std::endl;
		Geography geo = Geography("424242");

		std::cout << 2 <<std::endl;
		Network net;

		std::cout << 3 <<std::endl;
		Server* serveur = net.createDummyServer();

		std::cout << 4 <<std::endl;
		std::thread choucroute = std::thread(&client, (int) b, &geo, 1, 100, 50,
				50, (Network) net, serveur, (int *) sizeFenetre,
				(bool) isFullScreen);

		std::cout << 5 <<std::endl;
		choucroute.join();
		std::cout << 6 <<std::endl;
		return 1;
	};
	//Defintion of the window
	//	if (b == 0) {
	//		return 0;
	//	} else {
	//		sf::VideoMode video_mode = sf::VideoMode(sizeFenetre[0],
	//				sizeFenetre[1], sizeFenetre[2]);
	//		sf::RenderWindow window;
	//		if (isFullScreen) {
	//			window.create(video_mode, "Game", sf::Style::Fullscreen);
	//		} else {
	//			window.create(video_mode, "Game");
	//		}

	//		sf::Vector2u size = window.getSize();
	//		unsigned int w = size.x;
	//		unsigned int h = size.y;
	//End Defintion of the window

	//		inputState s = { true, window };

	//		while (window.isOpen()) {
	//			sf::Event event;
	//			while (window.pollEvent(event)) {
	///
	///			}
	//
	//			window.clear();
	//
	//			window.display();
	//		}
	//		window.close();
	//		return 0;
	//		window.close();
	//		return 0;
}
;

