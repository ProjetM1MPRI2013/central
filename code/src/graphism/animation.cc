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
      this->animT = 0;
      this->tex = tex;
      
      (this->spr).setTexture(tex->texture);
      (this->spr).setTextureRect(sf::IntRect(0,0,tex->widthSprite[0] - 1,tex->heightSprite - 1));
    }
}

void Animation::nextFrame()
{
  if (currentFrame < tex->nbFrames[animT] - 1)
    currentFrame++;
  else if (currentFrame == tex->nbFrames[animT] - 1 && tex->isLoop[animT])
    currentFrame = 0;
  
  spr.setTextureRect(sf::IntRect(currentFrame * tex->widthSprite[animT], animT * tex->heightSprite, (currentFrame + 1) * tex->widthSprite[animT] - 1,  (animT + 1) * tex->heightSprite - 1));
  
  return;
}

void Animation::setAnim(const int t)
{
  animT = t;
  currentFrame = 0;
  spr.setTextureRect(sf::IntRect(0,animT * tex->heightSprite ,tex->widthSprite[0] - 1, (animT + 1) * tex->heightSprite - 1 ));
  return;
}

sf::Sprite Animation::getSprite()
{
  return this->spr;
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
