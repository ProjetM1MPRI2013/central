#ifndef INTERFACE_INIT_H
#define INTERFACE_INIT_H

#include <../network/network.h>
#include <../network/netEvent.h>
#include <chat_event.h>
#include <TGUI/TGUI.hpp>
int interface_initiale (int sizeFenetre[3] , bool * isFullScreenParam, Server* serverPtr,Client* clientPtr);
std::string getKeyName(const sf::Keyboard::Key key);
std::string loadNick();
int copierFichier(char const * const source, char const * const destination);
void modifyConfig(int index, std::string s);
void modifyConfigAudio(int music, int sound);
void reloadKeyMapping(tgui::ListBox::Ptr lc);
#endif
