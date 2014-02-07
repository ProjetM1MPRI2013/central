#ifndef LOCALSTATEUPDATER_H
#define LOCALSTATEUPDATER_H
#include "client.h"
#include "playerUpdate.h"
#include "npcUpdate.h"

class LocalState;

/**
 * @brief The LocalStateUpdater class : class used to handle and apply updates received by the server
 * @author mheinric
 */
class LocalStateUpdater
{
public:
  /**
   * @brief LocalStateUpdater : creates a new updater attached to the given local state, using the given client to
   * receive updates
   * @param state : the local state this updater is attached to
   * @param client : the client used to receive the updates
   */
  LocalStateUpdater(LocalState* state, Client* client);

  /**
   * @brief update : updates the local state according to the updates received from the server.
   * This function performs the following :
   *  -> call receiveMessages<GameUpdate>() on the client
   *  -> apply the received updates to the local state.
   */
  void update(sf::Time dt) ;

private :
  LocalState * localState ;
  Client * client ;

  /**
   * @brief lastUpdate : time corresponding to the last received update
   */
  sf::Time lastUpdate ;

  /**
   * @brief diffPos : difference of position when the last opdate was received
   */
  Position diffPos ;

  void applyPlayerUpdate(PlayerUpdate &p_update, sf::Time dt) ;
  void applyNpcUpdate(NpcUpdate & npc_update) ;

  void updatePlayerPosition(sf::Time dt) ;

};

#endif // LOCALSTATEUPDATER_H
