#include "graphic_context_iso.h"
#include "../simulation/npc.h"
#include <list>
#include "../simulation/position.h"
#include <iostream>
#include <unistd.h>


  GraphicContextIso::GraphicContextIso(Geography* map, Simulation* sim)
  {
    this->map = map;
    this->sim = sim;  
  }
  
  
  void GraphicContextIso::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    int w = map->getMapWidth(), h = map->getMapHeight();
    states.transform *= getTransform();
    
    for(int k = w-1; k > -h; k--)
      {
        for(int j = std::min(w - 1, h+k-1); j >= std::max(k,0); j--)          // Vérifié par le calcul
          {
            int i = j - k;
            Tile* tilec = map->getTile(i,j);
            
            assert(tilec);
            assert(tilec->TextureIsInit());
            
            if(tilec->isBatOrigin())
            {
              sf::Sprite& sp = tilec->getSprite();
              sp.setPosition(sf::Vector2f( i * DOWN_TILE(0) + j * RIGHT_TILE(0) - tilec->getOriginSpriteX() + OFFSET_X,  i * DOWN_TILE(1) + j * RIGHT_TILE(1) - tilec->getOriginSpriteY() + OFFSET_Y - w * RIGHT_TILE(1) ));
              target.draw(sp, states);
            }
            std::list<NPC *> lnpc = tilec->getNPCs();
            for(std::list<NPC*>::const_iterator ci = lnpc.begin(); ci != lnpc.end(); ++ci)
              {
                assert((**ci).TextureIsInit());
                
                sf::Sprite& sfn = (**ci).getSprite();
                Position& p = (**ci).getPosition();
                sfn.setPosition(sf::Vector2f( floor(p.getX() * DOWN_TILE(0) + p.getY() * RIGHT_TILE(0) + OFFSET_X - (**ci).TextureOffsetX()) - 8, floor(p.getX() * DOWN_TILE(1) + p.getY() * RIGHT_TILE(1) + OFFSET_Y - w * RIGHT_TILE(1) - (**ci).TextureOffsetY() - 32 /* !!!! */)));
                target.draw(sfn,states);
              }
            
          }
      }
    return;
  }

void GraphicContextIso::load()
{
  int w = map->getMapWidth(), h = map->getMapHeight();
  
  for(int k = w-1; k > -h; k--)
    {
      for(int j = std::min(w - 1, h+k-1); j >= std::max(k,0); j--)
        {
          int i = j - k;
          Tile* tilec = map->getTile(i,j);

          assert(tilec != NULL);
          
          if(!tilec->TextureIsInit())
            {
              std::string s = tilec->getFilePictures();
	      s.pop_back();
	      try
		{
		  tilec->setTexture(&(tilemap.at(s)));
		}
              catch(...)
		{
		  sf::Texture t;
		  std::cout << "chargement de " << s << std::endl;
		  assert(t.loadFromFile(s));
		  SpriteTilePack stp = { .texture = t, .originX = tilec->getPictureX(), .originY = tilec->getPictureY()};
		  tilemap[s] = stp;
		  tilec->setTexture(&tilemap[s]);
		}
            }
          
          std::list<NPC *> lnpc = tilec->getNPCs();
          for(std::list<NPC*>::const_iterator ci = lnpc.begin(); ci != lnpc.end(); ++ci)
            {
              if(!(**ci).TextureIsInit())
                {
                  (**ci).TextureAnim(&(texVector.at(0))); // prends la première animation par défaut. S'il n'y a aucune animation de chargée, renvoie une erreur. A changer
                }
            }
        }
    }
  
  return;
}
void GraphicContextIso::addTexturePack(TexturePack t)
{
  texVector.push_back(t);
  return;
}

void GraphicContextIso::addSpriteTilePack(SpriteTilePack stp)
{
  tilepackVector.push_back(stp);
  return;
}

void GraphicContextIso::run(sf::RenderWindow* window)
{
  window->clear();
  Position p = *sim->getPlayer()->getPosition();
  this->view.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
  this->view.setCenter(sf::Vector2f(p.getX() + OFFSET_X,p.getY() + OFFSET_Y - (map->getMapWidth()) * RIGHT_TILE(1) ));
  window->setView(this->view);
  window->draw(*this);
    
  return;
}
