#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <test/test.h>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <interfaceinit/interface_init.h>
#include <generation/geography.h>

struct inputState {
  bool hasFocus;
  sf::RenderWindow& window;
};

void updateInputState(inputState& s) {
      sf::Event event;
      while (s.window.pollEvent(event)) {
        switch (event.type)
        {
          case sf::Event::LostFocus: s.hasFocus = false; break;
          case sf::Event::GainedFocus: s.hasFocus = true; break;
        }
      }
}

void handleKeys(inputState& s) {
  // Close window on Alt+F4
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && 
      sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
    s.window.close();
  }
}

int main()
{
	int sizeFenetre[3];
	bool isFullScreen;
	int b = interface_initiale(sizeFenetre, &isFullScreen);
	std::cout << "b : " << b << std::endl;
	//Defintion of the window
	if (b == 0) {
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
		Geography geo = Geography("424242");

	sf::Vector2u size = window.getSize();
    unsigned int w = size.x;
    unsigned int h = size.y;
    //End Defintion of the window
    
    inputState s = {true, window};

    while (window.isOpen()) {
      updateInputState(s);
      if (s.hasFocus) { handleKeys(s); }
      window.clear();
      window.display();
    }
    window.close();
    return 0;
  }
}
