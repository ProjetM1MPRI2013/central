#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>

enum AnimType {IDLE , WALK , DEAD }

/**
 * @brief The Animation class
 * Represents the animation of an object on the map
 */
 
class Animation
{
 public:

  /**
   * @brief Constructor for the Animation class
   * @param tex: Texture of the sprite sheet
   * @param nbFrames: The number of frames of the animation
   * @param widthSprite: The fixed width of a sprite for one animation
   * @param heightSprite: The fixed height of the animations
   * @param offsetX: The abscissa of the origin of the animation
   * @param offsetY: The ordinate of the origin of the animtaion
   * @param isloop: Is true if the animation loops
   **/
  Animation(sf::Texture& tex, unsigned int *nbFrames, unsigned int *widthSprite, unsigned int heightSprite, int *offsetX, int *offsetY, bool *isLoop);
 
  /**
   * @brief Goes to the next frame of the animation
   **/
  virtual void nextFrame();
  
  /**
   * @brief Changes the animation
   * @param t: New animation
   **/
  virtual void setAnim(AnimType t)
  
  /**
   * @brief Give the sprite of the animation
   **/
  virtual sf::Sprite getSprite();
  
  /**
   * @brief Gives the horizontal offset of the location of where the sprite should be drawn
   **/
  
  virtual int getOffsetX();
  
  /**
   * @brief Gives the vertical offset of the location of where the sprite should be drawn
   **/
  virtual int getOffsetY();

 private:
  /**
   * @brief Is true if the animation loops
   **/
  bool *isLoop;
  
  /**
   * @brief The sprite of the animation
   **/
  sf::Sprite spr;
  
  /**
   * @brief The number of frames of the animation
   **/
  unsigned int *nbFrames;

  /**
   * @brief The fixed width of a sprite
   **/
  unsigned int *widthSprite;

  /**
   *@brief The fixed height for the animations
   **/
  unsigned int heigthSprite
  
  /**
   * @brief The abscissa of the origin of the animation
   **/
  int *offsetX;
  
  /**
   * @brief The ordinate of the origin of the animation
   **/
  int *offsetY;
  
  /**
   * @brief The number of the current frame
   **/
  unsigned int currentFrame; 
  
  /**
   * @brief Current animation
   **/
  AnimType animT;

};

#endif
