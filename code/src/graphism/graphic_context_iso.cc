#include "graphic_context_iso.h"
#include "../simulation/npc.h"
#include <list>
#include "../simulation/position.h"


  GraphicContextIso::GraphicContextIso(Geography* map)
  {
    this->map = map;
    texArray = NULL; // A remplir
    tilepackArray = NULL; // A remplir 
  
  }
  
  
  void GraphicContextIso::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    int w = map->getMapWidth(), h = map->getMapHeight();
    states.transform *= getTransform();
    
    for(int k = w-1; k > -h; k--)
    {
      for(int j = min(w - 1, h+k-1); j >= max(k,0); j--)          // Vérifié par le calcul
      {
        int i = j - k;
        Tile* tilec = map->getTile(i,j);
        sf::Sprite sp = tilec->getSprite();
        sp.setPosition(sf::Vector2f( i * DOWN_TILE(0) + j * RIGHT_TILE(0) - tilec->getOriginSpriteX() + OFFSET_X,  i * DOWN_TILE(1) + j * RIGHT_TILE(1) - tilec->getOriginSpriteY() + OFFSET_Y));
        target.draw(sp, states);
        
        std::list<NPC *> lnpc = tilec->getNPCs();
        for(std::list<NPC*>::const_iterator ci = lnpc.begin(); ci != lnpc.end(); ++ci)
        {
	  if(!(**ci).TextureIsInit())
	    {
	      assert(texArray != NULL);
	      (**ci).TextureAnim(&(texArray[0])); // prends la première animation par défaut. S'il n'y a aucune animation de chargée, renvoie une erreur.
	    }
          sf::Sprite sfn = (**ci).getSprite();
          Position& p = (**ci).getPosition();
          sfn.setPosition(sf::Vector2f( floor(p.getX() * DOWN_TILE(0) + p.getY() * RIGHT_TILE(0) + OFFSET_X - (**ci).TextureOffsetX()), floor(p.getX() * DOWN_TILE(1) + p.getY() * RIGHT_TILE(1) + OFFSET_Y - (**ci).TextureOffsetY())));
          target.draw(sfn,states);
        }
      }
    }
  
  
  
  }
