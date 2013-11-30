#ifndef POSITION_H
#define POSITION_H


class Tile;
class Coordinates;
class Geography;

class Position {
 private:
  int TILE_SIZE_X = 1;
  int TILE_SIZE_Y = 1;
  float x;
  float y;
 public:
  Position();
  Position(float x,float y);
  Position(Position& p);
  Position(Tile& t);
  float getX();
  void setX(float x);
  float getY();
  void setY(float y);
  void add(float a,float b);
  Tile& isInTile(Geography& map);
  float distance(Position& p);
};
#endif
