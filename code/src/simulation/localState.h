#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H

class Position;
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
   Tile getTile(Position p, Layers l) {
   }

} ;

class Positionable {
  private: 
    Position position;
  public: 
      Position getPosition();
      void setPosition(Position p);
};



class NPC : public Positionable {
  private:
    Trajectory trajectory;
    float fear;
    bool shocked;
  public:
    float getFear();
    void setFear(float f);
    bool isShocked();
    void setShocked(bool s);
    void updateTrajectory(Trajectory t);
};





#endif // SIMULATION_H
