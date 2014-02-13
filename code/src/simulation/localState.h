/**
  *@author Denys KANUNIKOV,
  */


#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H

#include "player.h"
#include "generation1.h"
#include "simulation.h"
class Tile; // forward declaration
//class Simulation; //forward declaration
class Player;


enum Layers {
  L_Players = 1,
  L_NPC = 2,
  L_Geography = 4,
  L_Cameras = 8
} ;

/**
 * @brief The Local State Class
 * Interface to access the current game state
 */

class LocalState : public Simulation{
 public :
    /**
   * @brief LocalState
   * @param _player : a player to which this local state belongs
   * @param _seed : a seed used for map creating
   * Default constructor
   */
  LocalState(Geography* map,int nbPlayers,int id);

  /**
   * @brief getTile
   * @param p : position of the tile
   * @param l : layers to return (see enum Layers)w
   * @return a copy of the tile at position p, limited to the layers specified by L
   */
  Tile& getTile(Position p, Layers l);

  /**
   * @brief getCurrentTile
   * @return a copy of the tile (a pair of int)  where the player is.
   */
  std::pair<int,int> getCurrentTile();

   /**
   * @brief getOwner
   * @return a reference to the player to whom belongs this localState
   */
  Player& getOwner();

  /**
   * @brief getLocalMap
   * @return a reference to a localmap
   */
  Tile& getRelativePlayerTile(int x, int y);

  /**
   * @brief Set the Client object
   */
  void setClient(Client*);

  Client* getClient();

  sf::Time& getLocalTime();
  /**
   * @brief run
   * Updates all parameters of local state.
   */
  void run(sf::Time dt);

  private :
  Client* client;
  sf::Time localtime;
  /**
   * @brief npc_list
   * An npc for which this local state exists
   */
  std::list<NPC> npc_list;
  Player& owner_player;
} ;
#endif
