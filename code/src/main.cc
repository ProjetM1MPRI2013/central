#include <SFML/Graphics.hpp>
#include <test/test.h> 
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <interfaceinit/interface_init.h>
#include <generation/geography.h>
int main()
{
	int sizeFenetre[3];
	bool isFullScreen;
    int b = interface_initiale(sizeFenetre,&isFullScreen);
    std::cout << "b : " << b << std::endl;
    //Defintion of the window
    sf::VideoMode video_mode = sf::VideoMode(sizeFenetre[0],sizeFenetre[1],sizeFenetre[2]);
    sf::RenderWindow window;
    if (isFullScreen) {
    	window.create(video_mode, "Game", sf::Style::Fullscreen);
    }
    else {
    	window.create(video_mode, "Game");
    }
    Geography geo = Geography("424242");

	sf::Vector2u size = window.getSize();
    unsigned int w = size.x;
    unsigned int h = size.y;
    //End Defintion of the window
	while (window.isOpen()) {
		sf::Event event;
				while (window.pollEvent(event)) {

				}

				window.clear();

				window.display();
	}
    window.close();
    return 0;
}

