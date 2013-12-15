#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H

#include "player.h"
#include "generation1.h"
class Tile; // forward declaration
class Simulation; //forward declaration
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

class LocalState {
 public :
  /**
   * @brief LocalState
   * @param _player : a player to which this local state belongs
   * @param _seed : a seed used for map creating
   * Default constructor
   */
  LocalState(Player& _player, std::string _seed);
  /**
   * @brief getTile
   * @param p : position of the tile
   * @param l : layers to return (see enum Layers)w
   * @return a copy of the tile at position p, limited to the layers specified by L
   */
  Tile& getTile(Position p, Layers l);

   /**
   * @brief getPlayerLocalState
   * @return a reference to the player to whom belongs this localState
   */
  Player& getOwnerLocalState();

  /**
   * @brief getLocalMap
   * @return a reference to a localmap
   */
  Geography& getLocalMap();
  /**
   * @brief LocalState::getRelativePlayerTile
   * @param x : number of tiles to the right from the players position
   * @param y : number of tiles to the top from the players position
   * @return a reference to a Tile if on map, or owner's tile otherwise
   * getRelativePlayerTile(1, 0) returns a right neighbor tile
   */
  Tile& getRelativePlayerTile(int x, int y);

  /**
   * @brief addNPC
   * TODO : implement it later
   */
  void addNPC();

  sf::Time& getLocalTime();
  /**
   * @brief update
   * Updates all parameters of local state.
   */
  void update();

  private :
  sf::Time localtime;
  /**
   * @brief localtime_ms
   * local time in milliseconds
   */
  float localtime_ms;
  /**
   * @brief npc_list
   * An npc for which this local state exists
   */
  std::list<NPC> npc_list;
  Player& owner_player;
  int view_range;

  Geography *local_map;
} ;
#endif
