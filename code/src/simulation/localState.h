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

class Terrain : public Positionable {
  private:
  /*
   * type of the batiment of the case
   */
  TerrainType type;
  Sprite sprite;
  bool destructible;
  float anxiety;
  float populationDensity;
  float destructionLevel;
  /*
   * speed to go straight, between 0 and 1
   */
  float speedh;
  /*
   * speed to go above, between 0 and 1
   */
  float speedu;
  /*
   * speed to go to the right, between 0 and 1
   */
  float speedr;
  /*
   * speed to go to the left, between 0 and 1
   */
  float speedl;
  /*
   * the origin of the batiment, which is rectangular
   */
  Position batOrigin;
  /*
   * total lenght of the bat
   */
  int lenghtBat;
  /*
   * total weight of the bat
   */
  int weightBat;
  
  public:
    Type getType();
    void setType(TerrainType t);
    bool isDestructible();
    float getAnxiety();
    void setAnxiety(float a);
    float getPopulationDensity();
    void setPopulationDensity(float d);
    float getDestructionLevel();
    void setDestructionLevel(float dl);
    float getSpeedh();
    void setSpeedh(float sh);
    float getSppedu();
    void setSpeedu(float su);
    float getSpeedr();
    void setSpeedr(float sr);
    float getSpeedl();
    void setSpeedl(float sl);
    Position getBatOrigin();
    void setBatOrigin(Position p);
    int getLenghtBat();
    void setLenghtBat(int l);
    int getWeightBat();
    void setWeightBat(int w);
    Sprite getSprite();
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
