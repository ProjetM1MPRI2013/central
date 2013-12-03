#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>

enum AnimType {IDLE = 0, WALK = 1, DEAD = 2}


class Animation
{
 publc:

  /**
   * @brief Loads an animation
   * @param textureName: The file name of the sprite set
   * @param nbFrames_: The number of frames of the animation
   * @param widthSprite_: The fixed width of a sprite for one animation
   * @param heightSprite_ : The fixed height of the animations
   * @param offsetX_: The abscissa of the origin of the animation
   * @param offsetY_: The ordinate of the origin of the animtaion
   * @param isloop_: Is true if the animation loops
   **/
  virtual bool load(std::string textureName, unsigned int *nbFrames_, unsigned int *widthSprite_, unsigned int heightAnim_, int *offsetX_, int *offsetY_, bool *isLoop_);
  
  /**
   * @brief Goes to the next frame of the animation
   **/
  virtual void nextFrame();
  
  /**
   * @brief Give the sprite of the animation
   **/
  virtual sf::Sprite getSprite();

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
  unsigned int heigthAnim
  
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
