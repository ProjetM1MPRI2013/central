#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H
//#include "tile.h"
#include "position.h"
//#include "trajectory.h"

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

//class LocalState {
 //public :
  /**
   * @brief getTile
   * @param p : position of the tile
   * @param l : layers to return (see enum Layers)
   * @return a copy of the tile at position p, limited to the layers specified by L
   */
   //Tile getTile(Position p, Layers l) {
   //}

//} ;

class Positionable {
  private: 
    Position position;
  public: 
      Position getPosition();
      void setPosition(Position p);
      Positionable(float x, float y);
      Positionable(Position p);
};
#endif // SIMULATION_H
