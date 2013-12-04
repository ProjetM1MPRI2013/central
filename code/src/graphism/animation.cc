#include "animation.h"
#include <assert.h>

Animation::Animation(sf::Texture& tex, unsigned int *nbFrames, unsigned int *widthSprite, unsigned int heightSprite, int *offsetX, int *offsetY, bool *isLoop)
{

  this->nbFrames = nbFrames;
  this->widthSprite = widthSprite;
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  this->isLoop = isLoop;
  this->currentFrame = 0;
  this->animT = IDLE;
  this->heightSprite = heightSprite;
  
  (this->spr).setTexture(tex);
  (this->spr).setTextureRect(sf::IntRect(0,0,widthSprite[0] - 1,heightSprite - 1));
  
}

void Animation::nextFrame()
{
  if (currentFrame < nbFrames[animT] - 1)
    currentFrame++;
  else if (currentFrame == nbFrames[animT] - 1 && isLoop)
    currentFrame = 0;
  
  spr.setTextureRect(sf::IntRect(currentFrame * widthSprite[animT], animT * heightSprite, (currentFrame + 1) * widthSprite[animT] - 1,  (animT + 1) * heightSprite - 1));
  
  return;
}

void Animation::setAnim(AnimType t)
{
  animT = t;
  currentFrame = 0;
  spr.setTextureRect(sf::IntRect(0,animT * heightSprite ,widthSprite[0] - 1, (animT + 1) * heightSprite - 1 ));
  return;
}

sf::Sprite Animation::getSprite()
{
  return this->spr;
}


int Animation::getOffsetX();
{
  return offsetX;
}
  
int Animation::getOffsetY();
{
  return offsetY;
}