/**
 * @author MrKulu
 **/

#include "drawableObject.h"



sf::Sprite& DrawableObject::getSprite(){
  assert(this->anim.isInit());
  return this->anim.getSprite();
}

Animation DrawableObject::getAnim() const {
  return anim;
}

void DrawableObject::setAnim(const AnimType t){
  this->anim.setAnim(t);
  return;
}

void DrawableObject::TextureAnim(TexturePack* tex){
  anim = Animation(tex);
  return;
}

int DrawableObject::TextureOffsetX(){
  return anim.getOffsetX();
}

int DrawableObject::TextureOffsetY(){
  return anim.getOffsetY();
}

bool DrawableObject::TextureIsInit(){
  return anim.isInit();
}



void DrawableObject::nextFrame()
{
  anim.nextFrame();
  return;
}
