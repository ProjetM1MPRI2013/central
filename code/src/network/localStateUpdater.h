#ifndef LOCALSTATEUPDATER_H
#define LOCALSTATEUPDATER_H
#include "client.h"
#include "simulation/localState.h"

/**
 * @brief The LocalStateUpdater class : class used to handle and apply updates received by the server
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
  LocalStateUpdater(LocalState& state, Client& client);

  /**
   * @brief update : updates the local state according to the updates received from the server.
   * This function performs the following :
   *  -> call receiveMessages<GameUpdate>() on the client
   *  -> apply the received updates to the local state.
   */
  void update() ;

private :
  LocalState * localState ;
  Client * client ;
};

#endif // LOCALSTATEUPDATER_H
