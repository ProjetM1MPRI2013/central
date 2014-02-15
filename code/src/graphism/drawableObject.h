/**
 * @author MrKulu
 **/

#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "animation.h"
#include <cassert>

class DrawableObject {

 protected:
  
  Animation anim;

 public :

  DrawableObject();

  DrawableObject(TexturePack* tex);

  /**
   * @brief getSprite
   * @return returns the sprite of the object
   */  
  sf::Sprite& getSprite();
  
  /**
   * @brief getAnim
   * @return the object's Animation
   **/
  Animation getAnim() const;

  /**
   * @brief setAnim
   * Sets the animation of the object
   * @param t: New animation
   **/  
  virtual void setAnim(const AnimType t);

  /**
   * @brief TextureAnim
   * Changes the texture of the animation of the object
   **/
  void TextureAnim(TexturePack* tex);
  
  
  /**
   * @brief TextureOffsetX
   * Get the abscissa of the origin of the animation in the texture
   **/
  int TextureOffsetX();
  
  /**
   * @brief TextureOffsetY
   * Get the ordinate of the origin of the animation in the texture
   **/
  int TextureOffsetY();

  /**
   * @brief TextureIsInit
   * Returns true iff the animation texture has been initialized
   **/
  bool TextureIsInit();

  /**
   * @brief nextFrame
   * Changes the state of the animation to the next frame, according to the
   * different parametters of the object.
   */
  virtual void nextFrame();

  int getTexID();

};

#endif
