#include <TGUI/TGUI.hpp>
#include <iostream>
// #include <string.hpp>
#include <sstream>
#include <string>
#include <iostream>

#define THEME_CONFIG_FILE "../widgets/BabyBlue.conf"
static const std::vector<sf::VideoMode> vect_fs_vm = sf::VideoMode::getFullscreenModes();
bool synchro_vert = false;

void cut_string_x (sf::String s, sf::String* m1 , sf::String* m2) {
  std::size_t n = s.getSize();
}
int interface_initiale() 
{
  //for (std::size_t i = 0; i < vect_fs_vm.size(); ++i)
  //  {
  //    sf::VideoMode mode = vect_fs_vm[i];
  //    std::cout << "Mode #" << i << ": "
  //		<< mode.width << "x" << mode.height << " - "
  //		<< mode.bitsPerPixel << " bpp" << std::endl;
  //}
  static sf::VideoMode video_mode = sf::VideoMode::getDesktopMode(); 	
  sf::RenderWindow window(video_mode, "Game Interface",sf::Style::Fullscreen);
  tgui::Gui gui(window);
  tgui::Gui opt(window);

  if (gui.setGlobalFont("../fonts/80db.ttf") == false)
        return 1;


  sf::Vector2u size = window.getSize();
  unsigned int w = size.x;
  unsigned int h = size.y;
  tgui::Picture::Ptr picture(gui);
  picture->load("pic.jpg");
  
  tgui::Button::Ptr bcreate(gui);
  bcreate->load(THEME_CONFIG_FILE);
  bcreate->setPosition(w/3, h/5);
  bcreate->setText("Create Game");
  bcreate->setCallbackId(1);
  bcreate->bindCallback(tgui::Button::LeftMouseClicked);
  bcreate->setSize(w/3, 40);

  tgui::Button::Ptr bjoin(gui);
  bjoin->load(THEME_CONFIG_FILE);
  bjoin->setPosition(w/3,2* h/5);
  bjoin->setText("Join Game");
  bjoin->setCallbackId(2);
  bjoin->bindCallback(tgui::Button::LeftMouseClicked);
  bjoin->setSize(w/3, 40);

  tgui::Button::Ptr boptions(gui);
  boptions->load(THEME_CONFIG_FILE);
  boptions->setPosition(w/3, 3*h/5);
  boptions->setText("Options");
  boptions->setCallbackId(3);
  boptions->bindCallback(tgui::Button::LeftMouseClicked);
  boptions->setSize(w/3, 40);

  tgui::Button::Ptr bquit(gui);
  bquit->load(THEME_CONFIG_FILE);
  bquit->setPosition(w/3, 4*h/5);
  bquit->setText("Quit");
  bquit->setCallbackId(4);
  bquit->bindCallback(tgui::Button::LeftMouseClicked);
  bquit->setSize(w/3, 40);
  

  tgui::Picture::Ptr picture2(opt);
  picture2->load("pic.jpg");
  
  if (opt.setGlobalFont("../fonts/80db.ttf") == false)
        return 1;

  tgui::Button::Ptr optb(opt);
  optb->load(THEME_CONFIG_FILE);
  optb->setPosition(w/3, 2*h/3);
  optb->setText("Back to Menu");
  optb->setCallbackId(1);
  optb->bindCallback(tgui::Button::LeftMouseClicked);
  optb->setSize(w/3, 40);

  tgui::ComboBox::Ptr resol(opt);
  resol->load(THEME_CONFIG_FILE);
  resol->setSize(w/3, 50);
  resol->setPosition(w/3, h/3);
  for (std::size_t i = 0; i < vect_fs_vm.size(); ++i)
   {
     sf::VideoMode mode = vect_fs_vm[i];
     if (mode.bitsPerPixel == 32) {
       std::stringstream ss;
       ss << mode.width << "x" << mode.height;
       resol->addItem(ss.str());
     }
   }



  int wim = 0 ;
  tgui::Gui* todo = &gui;
  while (window.isOpen())
    {
      switch (wim)
      	{
      	case 0 : {todo = &gui; break ;}
      	case 1 : {todo = &opt; break ;}
      	}
  
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
	  
	  (*todo).handleEvent(event);
        }
      
      tgui::Callback callback;
      while ( (*todo).pollCallback(callback))
        {
	  if (wim == 0) {
	    if (callback.id == 1)
	      {
		wim = 0;
	      }
	    if (callback.id == 2) 
	      {
		wim = 0;
	      }
	    if (callback.id == 3)
	      {
		wim = 1;
	      }
	    if (callback.id == 4)
	      {
		window.close();
	      }
	  }
	  if (wim ==1) {
	    if (callback.id == 1)
	      wim = 0;
	      {
		int ind_selected_items = resol->getSelectedItemIndex(); 
		if (ind_selected_items != (-1)) {
		  int compt = 0;
		  int index = 0;
		  while (compt < ind_selected_items || (vect_fs_vm[index]).bitsPerPixel != 32) {
		    if (((vect_fs_vm[index]).bitsPerPixel) == 32) {
		      compt ++;
		    }
		    index ++;
		  }
		  sf::VideoMode mode = vect_fs_vm[index];
		  sf::Vector2u size = window.getSize();
		  unsigned int w = size.x;
		  unsigned int h = size.y;
		  if (w != mode.width || h != mode.height) {
		    window.create(mode,"test",sf::Style::Fullscreen);
		  }
		}
	      }
	  }
        }
      
      window.clear();
      (*todo).draw();
      window.display();
      
    }
  
  return 0;
}
