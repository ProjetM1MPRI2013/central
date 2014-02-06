/**
 * @author: MrKulu
 */

#include "animation.h"

Animation::Animation() { }

Animation::Animation(TexturePack* tex)
{
  if(tex == NULL)
    {
      this->tex = NULL;
    }
  else
    {

      this->currentFrame = 0;
      this->animT = IDLE;
      this->tex = tex;
      
      (this->spr).setTexture(tex->texture);
      (this->spr).setTextureRect(sf::IntRect(0,0,tex->widthSprite[0],tex->heightSprite));
    }
}

void Animation::nextFrame()
{
  if(clock.getElapsedTime().asMilliseconds() > 1000./tex->fps[animT])
    {
      clock.restart();
      if (currentFrame + 1 < tex->nbFrames[animT])
	currentFrame++;
      else if (currentFrame + 1 == tex->nbFrames[animT] && tex->isLoop[animT])
	currentFrame = 0;
      
      spr.setTextureRect(sf::IntRect(currentFrame * tex->widthSprite[animT], animT * tex->heightSprite,tex->widthSprite[animT],tex->heightSprite));
    }
  return;
}

void Animation::setAnim(const AnimType t)
{
  animT = t;
  currentFrame = 0;
  spr.setTextureRect(sf::IntRect(0,animT * tex->heightSprite ,tex->widthSprite[0],tex->heightSprite));
  return;
}

AnimType Animation::getAnim()
{
  return animT;
}

sf::Sprite& Animation::getSprite()
{
  sf::Sprite& rs = spr;
  return rs;
}


int Animation::getOffsetX()
{
  return tex->offsetX[animT];
}
  
int Animation::getOffsetY()
{
  return tex->offsetY[animT];
}

bool Animation::isInit()
{
  return tex != NULL;
}
