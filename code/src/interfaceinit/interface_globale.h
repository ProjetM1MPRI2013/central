#ifndef INTERFACE_GLOBALE_H
#define INTERFACE_GLOBALE_H

#include <../network/network.h>
#include <../network/netEvent.h>
#include <chat_event.h>
#include <TGUI/TGUI.hpp>
#endif

class Interface;

class GuiExtended : public tgui::Gui {
private :
	int (*funcCallBack)(int,std::string*,Interface* inter);
	int (*funcEvent)(sf::Event* event,int flag,Interface* inter);
	int flag;
	Interface* inter;
public :
	GuiExtended();
	GuiExtended(sf::RenderWindow* window);
	void setFlag(int n);
	void setInterface (Interface* inter);
	Interface* getInterface ();
	int getFlag();
	int handleCallbackgui(int n, std::string* str);
	void handleEventgui(sf::Event* event);
	void setFuncCallback(int (*f)(int,std::string*,Interface* inter));
	void setFuncEvent(int (*f)(sf::Event* event,int flag,Interface* inter));
};

class Interface {
 public :
  Interface(sf::RenderWindow* win,sf::VideoMode* video_mode,Server* server, Client* client);
  void addtgui(GuiExtended* gui , std::string name);
  std::list<GuiExtended*>& getGuilist ();
  GuiExtended* getCurrent ();
  void init();
  void draw();
  void handleCallBack();
  void handleEvent(sf::Event* event);
  void setMenuChange(std::string str);
  void setMusic(std::string str);
  void setAudioVol(int av);
  void setSoundVol(int sv);
  int getAudioVol();
  int getSoundVol();
  sf::RenderWindow * getWindow();
  bool isFullScreen;
  void setVideoMode(sf::VideoMode* video_mode);
  sf::VideoMode* getVideoMode();
  int out;
  Server* getServer();
  void setServer(Server*);
  Client* getClient();
  void setClient(Client*);

 private :
  sf::VideoMode* videoMode;
  Server* serverPtr;
  Client* clientPtr;
  int audiovol;
  int soundvol;
  sf::Sound changementMenu;
  sf::Music interfaceMusic;
  std::string current;
  GuiExtended* toDraw;
  std::list<GuiExtended*> guiList;
  std::list<std::string*> nameList;
  sf::RenderWindow* win;
};
