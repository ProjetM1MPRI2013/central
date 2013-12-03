#include "animation.h"

bool Animation::load(std::string textureName, unsigned int nbFrames_, unsigned int widthSprite_, int offsetX_, int offsetY_, bool isLoop_)
{
  /* TODO (cf doc SFML pour sf::Texture) */
  
  this->nbFrames = nbFrames;
  this->widthSprite = widthSprite_;
  this->offsetX = offsetX_;
  this->offsetY = offsetY_;
  this->isLoop = isLoop_;
  this->currentFrame = 0;

  return true;
}

void Animation::nextFrame()
{
  /* TODO */
  return;
}

void Animation::getSprite()
{
  return thisi->spr;
}
