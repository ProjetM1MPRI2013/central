#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>

/**
 * @brief TexturePack
 * A package of all the informations needed for an animation
 **/
struct TexturePack {
  sf::Texture texture;
  std::vector<int> nbFrames;
  std::vector<int> widthSprite;
  int heightSprite;
  std::vector<int> offsetX;
  std::vector<int> offsetY;
  std::vector<bool> isLoop;
};

enum AnimType {IDLE, RUN, DEAD};

/**
 * @brief The Animation class
 * Represents the animation of an object on the map
 */ 
class Animation
{
 public:

  Animation();

  /**
   * @brief Constructor for the Animation class
   * @param tex: Texture pack of the animation
   **/
  Animation(TexturePack* tex);
 
  /**
   * @brief Goes to the next frame of the animation
   **/
  virtual void nextFrame();
  
  /**
   * @brief Changes the animation
   * @param t: New animation
   **/
  virtual void setAnim(const AnimType t);

  /**
   * @brief getAnim
   * Return the current animation
   */
  virtual AnimType getAnim ();
  
  /**
   * @brief Give the sprite of the animation
   **/
  virtual sf::Sprite& getSprite();
  
  /**
   * @brief Gives the horizontal offset of the location of where the sprite should be drawn
   **/
  
  virtual int getOffsetX();
  
  /**
   * @brief Gives the vertical offset of the location of where the sprite should be drawn
   **/
  virtual int getOffsetY();

  /**
   * @brief isNull
   * @return is true iff tex != Null, ie if there is an actual texture pack applied to the animation.
   **/
  virtual bool isInit();

 private:
  /**
   * @brief The Texture Pack
   **/
  TexturePack* tex;
 
  /**
   * @brief The sprite of the animation
   **/
  sf::Sprite spr;

  /**
   * @brief The current frame of the animation
   **/
  int currentFrame;

  /**
   * @brief The current animation
   **/
  AnimType animT;

  sf::Clock clock;
};

#endif
