// implement the HUD of the game 
#include <TGUI/TGUI.hpp> 
#include <iostream> 
#include <sstream> 
#include <string> 
#include <iostream> 

int main() 
{
  // Create the window 
  
  // Fullscreen 
  // sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game HUD",sf::Style::Fullscreen);
  // Not Fullscrenn 
  sf::RenderWindow window(sf::VideoMode(800, 600), "Game HUD");

  // Define the principal widgets of the HUD 
  tgui::Gui principal(window); 

  // Load the font and test if it has been successfully loaded 
  if (principal.setGlobalFont("../fonts/DejaVuSans.ttf") == false)
    return 1;

  // Create the 'Bomb' button 
  tgui::Button::Ptr b_bomb(principal); 
  b_bomb->load("../widgets/Black.conf"); 
  b_bomb->setSize(80,40); 
  b_bomb->setPosition(50, 500); 
  b_bomb->setText("Use Bomb"); 
  b_bomb->bindCallback(tgui::Button::LeftMouseClicked); 
  b_bomb->setCallbackId(1); 

  // Create the 'Weapon' button 
  tgui::Button::Ptr b_weapon(principal); 
  b_weapon->load("../widgets/Black.conf"); 
  b_weapon->setSize(80,40); 
  b_weapon->setPosition(150, 500); 
  b_weapon->setText("Use Weapon"); 
  b_weapon->bindCallback(tgui::Button::LeftMouseClicked); 
  b_weapon->setCallbackId(2); 

  // Create the 'options' button 
  tgui::Button::Ptr b_options(principal); 
  b_options->load("../widgets/Black.conf"); 
  b_options->setSize(80, 40); 
  b_options->setPosition(700, 500); 
  b_options->setText("Options"); 
  b_options->bindCallback(tgui::Button::LeftMouseClicked); 
  b_options->setCallbackId(3); 



  tgui::Gui bomb(window); 
  if (bomb.setGlobalFont("../fonts/DejaVuSans.ttf") == false)
    return 1;

  // Create the 'Bomb 1' button 
  tgui::Button::Ptr b_bomb1(bomb); 
  b_bomb1->load("../widgets/Black.conf"); 
  b_bomb1->setSize(80,40); 
  b_bomb1->setPosition(50, 500); 
  b_bomb1->setText("Use Bomb 1"); 
  b_bomb1->bindCallback(tgui::Button::LeftMouseClicked); 
  b_bomb1->setCallbackId(1); 

  // Create the 'Bomb 2' button 
  tgui::Button::Ptr b_bomb2(bomb); 
  b_bomb2->load("../widgets/Black.conf"); 
  b_bomb2->setSize(80,40); 
  b_bomb2->setPosition(150, 500); 
  b_bomb2->setText("Use Bomb 2"); 
  b_bomb2->bindCallback(tgui::Button::LeftMouseClicked); 
  b_bomb2->setCallbackId(2); 

  // Create the 'Bomb 3' button 
  tgui::Button::Ptr b_bomb3(bomb); 
  b_bomb3->load("../widgets/Black.conf"); 
  b_bomb3->setSize(80,40); 
  b_bomb3->setPosition(250, 500); 
  b_bomb3->setText("Use Bomb 3"); 
  b_bomb3->bindCallback(tgui::Button::LeftMouseClicked); 
  b_bomb3->setCallbackId(3); 

  // Create the 'Back' button 
  tgui::Button::Ptr b_back_bomb(bomb); 
  b_back_bomb->load("../widgets/Black.conf"); 
  b_back_bomb->setSize(80,40); 
  b_back_bomb->setPosition(50, 550); 
  b_back_bomb->setText("Back"); 
  b_back_bomb->bindCallback(tgui::Button::LeftMouseClicked); 
  b_back_bomb->setCallbackId(4); 

   // Create the 'options' button 
  tgui::Button::Ptr b_options_bomb(bomb); 
  b_options_bomb->load("../widgets/Black.conf"); 
  b_options_bomb->setSize(80, 40); 
  b_options_bomb->setPosition(700, 500); 
  b_options_bomb->setText("Options"); 
  b_options_bomb->bindCallback(tgui::Button::LeftMouseClicked); 
  b_options_bomb->setCallbackId(5); 

 tgui::Gui weapon(window); 
  if (weapon.setGlobalFont("../fonts/DejaVuSans.ttf") == false)
    return 1;

  // Create the 'Weapon 1' button 
  tgui::Button::Ptr b_weapon1(weapon); 
  b_weapon1->load("../widgets/Black.conf"); 
  b_weapon1->setSize(80,40); 
  b_weapon1->setPosition(50, 500); 
  b_weapon1->setText("Use Weapon 1"); 
  b_weapon1->bindCallback(tgui::Button::LeftMouseClicked); 
  b_weapon1->setCallbackId(1); 

  // Create the 'Weapon 2' button 
  tgui::Button::Ptr b_weapon2(weapon); 
  b_weapon2->load("../widgets/Black.conf"); 
  b_weapon2->setSize(80,40); 
  b_weapon2->setPosition(150, 500); 
  b_weapon2->setText("Use Weapon 2"); 
  b_weapon2->bindCallback(tgui::Button::LeftMouseClicked); 
  b_weapon2->setCallbackId(2); 

  // Create the 'Weapon 3' button 
  tgui::Button::Ptr b_weapon3(weapon); 
  b_weapon3->load("../widgets/Black.conf"); 
  b_weapon3->setSize(80,40); 
  b_weapon3->setPosition(250, 500); 
  b_weapon3->setText("Use Weapon 3"); 
  b_weapon3->bindCallback(tgui::Button::LeftMouseClicked); 
  b_weapon3->setCallbackId(3); 

  // Create the 'Back' button 
  tgui::Button::Ptr b_back_weapon(weapon); 
  b_back_weapon->load("../widgets/Black.conf"); 
  b_back_weapon->setSize(80,40); 
  b_back_weapon->setPosition(50, 550); 
  b_back_weapon->setText("Back"); 
  b_back_weapon->bindCallback(tgui::Button::LeftMouseClicked); 
  b_back_weapon->setCallbackId(4); 

   // Create the 'options' button 
  tgui::Button::Ptr b_options_weapon(weapon); 
  b_options_weapon->load("../widgets/Black.conf"); 
  b_options_weapon->setSize(80, 40); 
  b_options_weapon->setPosition(700, 500); 
  b_options_weapon->setText("Options"); 
  b_options_weapon->bindCallback(tgui::Button::LeftMouseClicked); 
  b_options_weapon->setCallbackId(5); 

  // Flag pointing out the current set of buttons 
  int currentFlag(0); 

  // Flag pointing out the next set of buttons to draw 
  int nextFlag(0); 

  // Represent the current gui to draw 
  tgui::Gui *current = &principal; 

  // Main loop 
  while (window.isOpen()) 
  {
    currentFlag = nextFlag;

    // Update the current gui to draw 
    switch (currentFlag) 
    {
      case 0: 
      {
        current = &principal; 
        break; 
      }
      case 1: 
      {
        current = &bomb; 
        break; 
      }
      case 2: 
      {
        current = &weapon; 
      }
    }

    sf::Event event; 
    while (window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed) 
        window.close(); 

      // Pass the event to all the current widgets 
      current->handleEvent(event); 

    }

    // Callback loop 
    tgui::Callback callback; 
    while (current->pollCallback(callback)) 
    {

      // Case : principal 
      if (currentFlag == 0)  
      {

        // Bomb button clicked 
        if (callback.id == 1) 
        nextFlag = 1; 

        // Weapon button clicked 
        if (callback.id == 2)
        nextFlag = 2; 

        // Options button clicked
        if (callback.id == 3) 
        {
          // Open the options... 
        }

      }
    
      // Case : Bomb 
      if (currentFlag == 1) 
      {
       
        // Bomb 1 clicked 
        if (callback.id == 1) 
        {
          // Plant Bomb 1... 
        } 

        // Bomb 2 clicked 
        if (callback.id == 2) 
        {
          // Plant Bomb 2... 
        }

        // Bomb 3 clicked 
        if (callback.id == 3) 
        {
          // Plant Bomb 3... 
        }

        // Back button clicked 
        if (callback.id == 4) 
          nextFlag = 0; 

        // Options button clicked
        if (callback.id == 5)
        {
          // Open the options...
        }
      }

      // Case : weapon 
      if (currentFlag == 2) 
      {
      
        // Weapon 1 clicked 
        if (callback.id == 1) 
        {
          // Use Weapon 1... 
        }

        // Weapon 2 clicked 
        if (callback.id == 2) 
        {
          // Use Weapon 2... 
        }

        // Weapon 3 clicked 
        if (callback.id == 3) 
        {
          // Use Weapon 3... 
        }

        // Back button clicked 
        if (callback.id == 4) 
          nextFlag = 0; 

        // Options button clicked 
        if (callback.id == 5) 
        {
          // Open the options... 
        }
      }
    }


    window.clear(); 

    // Draw the current set of buttons 
    current->draw(); 

    window.display(); 
  
  }

  return EXIT_SUCCESS; 

}


