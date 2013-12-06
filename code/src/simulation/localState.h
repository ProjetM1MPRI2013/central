#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H

#include "player.h"
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
   * @param _simul : a simulator which creates a local state for a user.
   * Default constructor
   */
  //TODO{denys} : I don't know how to implement a link with map and other parameters, and this should be re-done later
  //It's an example how not to do, but i'm very sorry...
  LocalState(Player* _player, Simulation* _simul);
  /**
   * @brief getTile
   * @param p : position of the tile
   * @param l : layers to return (see enum Layers)w
   * @return a copy of the tile at position p, limited to the layers specified by L
   */
  Tile& getTile(Position p, Layers l);

  /**
   * @brief getViewedTiles
   * @param l : layers to return
   * @return a pointer to the massive of tiles which a viewed
   */
  Tile*** getViewedTiles(Layers l);

  /**
   * @brief getPlayerLocalState
   * @return a pointe of the player to whom belongs this localState
   */
  Player* getPlayerLocalState();

  /**
   * @brief getRelativePlayerTile
   * @param x : difference by absciss
   * @param y : difference by ordinate
   * @return a relative tile of the player view_range map.
   * getRelativePlayerTile(1, 0) returns a right neighbor tile
   */
  Tile* getRelativePlayerTile(int x, int y);

  float getLocalTime();
  /**
   * @brief update
   * Updates all parameters of local state.
   */
  void update();

  private :
  /**
   * @brief localtime_ms
   * local time in milliseconds
   */
  float localtime_ms;
  /**
   * @brief local_npc
   * An npc for which this local state exists
   */
  Player* owner_player;
  Tile ***potential_viewed;
  int view_range;

  //TODO{denys} : this should be remade later
  Geography &local_map;

  Simulation *parent_sim;

  /**
   * @brief rebuildLocalMap
   * rebuilds a local map shich is viewed by player
   */
  void rebuildLocalMap();
} ;
#endif
