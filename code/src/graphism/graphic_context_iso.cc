#include "graphic_context_iso.h"
#include "../simulation/npc.h"
#include <list>
#include "../simulation/position.h"


  GraphicContextIso::GraphicContextIso(Geography* map)
  {
    this->map = map;
    sf::Texture a1, b1, b2;
    TexturePack tp1;
    SpriteTilePack stp1, stp2;
    assert(a1.loadFromFile("Anim.png"));
    assert(b1.loadFromFile("Road_NS.png"));
    assert(b2.loadFromFile("maison1.png"));
    tp1 = {.texture = a1 , .nbAnim = {1,12,16} , .widthSprite = {16,16,32} , .heightSprite = 32 , .offsetX = {0,0,0} , .offsetY = {8,8,8} , .isLoop = {true, true, false}};
    stp1 = {.texture = b1 , .originX = 0 , .originY = 39 , .X1 = 0 , .Y1 = 0, .X2 = 157 , .Y2 = 79 };
    stp2 = {.texture = b2 , .originX = 0 , .originY = 109 , .X1 = 0, .Y1 = 0, .X2 = 157 , .Y2 = 149 };
    texArray = {tp1}; // A vérifier
    tilepackArray = {stp1,stp2}; // A vérifier 
  
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
          sfn.setPosition(sf::Vector2f( floor(p.getX() * DOWN_TILE(0) + p.getY() * RIGHT_TILE(0) + OFFSET_X - (**ci).TextureOffsetX()), floor(p.getX() * DOWN_TILE(1) + p.getY() * RIGHT_TILE(1) + OFFSET_Y - (**ci).TextureOffsetY() - 32 /* !!!! */)));
          target.draw(sfn,states);
        }
      }
    }
  
  
  
  }
