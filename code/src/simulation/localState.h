#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H
#include "position.h"
#include "positionable.h"
class Tile; // forward declaration

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
   * @brief getTile
   * @param p : position of the tile
   * @param l : layers to return (see enum Layers)
   * @return a copy of the tile at position p, limited to the layers specified by L
   */
  Tile& getTile(Position p, Layers l);
} ;
#endif
