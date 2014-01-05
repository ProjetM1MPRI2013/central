#include "graphic_context_iso.h"
#include "../simulation/npc.h"
#include <list>
#include <iostream>
#include <unistd.h>


  GraphicContextIso::GraphicContextIso(Geography* map, Simulation* sim)
  {
    this->map = map;
    this->sim = sim;  

    std::fstream file;
    file.open("../graphism/animations",std::fstream::in);
    assert(file);
    std::string line, tmp;
    while(getline(file,line)){
      
      TexturePack t;
      sf::Texture a;
      
      tmp = line.substr(0,line.find(" "));
      assert(a.loadFromFile(tmp));
      t.texture = a;

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
	t.nbFrames.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
	tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.nbFrames.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
	t.widthSprite.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
	tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.widthSprite.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(0,line.find(" "));
      t.heightSprite = atoi(tmp.c_str());

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
	t.offsetX.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
	tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.offsetX.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
	t.offsetY.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
	tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.offsetY.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
	t.isLoop.push_back(tmp.substr(0,tmp.find(",")).compare("T")==0);
	tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.isLoop.push_back(tmp.compare("T")==0);

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
	t.fps.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
	tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.fps.push_back(atoi(tmp.c_str()));

      addTexturePack(t);

    }
    file.close();

  }
  
  
  void GraphicContextIso::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    int w = map->getMapWidth(), h = map->getMapHeight();
    bool isDrawn[h][w];
    states.transform *= getTransform();

    for(int j = 0; j < h; j++)
      {
	for(int i = 0; i < w; i++)
	  isDrawn[j][i] = false;
      }
    
    /*
      isDrawn est une matrice qui indique quelle tile a déjà été affichée.
      Pour un affichage correct, il faut que tous les éléments au dessus d'une
      case aient été affichés avant elle-même. Ainsi, l'invariant à conserver
      est :
      \forall j,i,j',i' (j' <= j & i' >= i & isDrawn[j][i]) -> isDrawn[j'][i']
      La condition d'arrêt est donc :
      isDrawn[h-1][0]
    */
    
    while(not(isDrawn[h-1][0]))
      {
	for(int k = 0 ; k < std::min(w,h); k++)
	  {
	    for(int l = 0 ; l < std::max(w,h) - k; l++)
	      {
		for(int b = 0 ; b < 2; b++)
		  {
		    int i,j;
		    if(b)
		      {
			i = w - k - 1;
			j = k + l;
		      }
		    else
		      {
			i = w - k - l - 1;
			j = k;
		      }
		    if(i < 0 || j >= h)
		      break;
		    Tile* tilec = map->getTile(j,i);
		    
		    assert(tilec);
		    assert(tilec->TextureIsInit());
		    
		    if(tilec->isBatOrigin())
		      {
			int wb = tilec->getWidthBat(), hb = tilec->getHeightBat();
			bool c1, c2;
			if(j==0)
			  c1 = true;
			else
			  c1 = isDrawn[j-1][i+1-wb];
			
			if(i==w-1)
			  c2 = true;

			else
			  c2 = isDrawn[j-1+hb][i+1];
			
			if(c1 && c2)
			  {
			    sf::Sprite& sp = tilec->getSprite();
			    sp.setPosition(sf::Vector2f( (i + 1)  * RIGHT_TILE(0) + j * DOWN_TILE(0) - tilec->getOriginSpriteX() + OFFSET_X - 2,  (i + 1) * RIGHT_TILE(1) + j * DOWN_TILE(1) - tilec->getOriginSpriteY() + OFFSET_Y - w * RIGHT_TILE(1) - 1));
			    target.draw(sp, states);
			    

			    for(int ib = 0; ib < wb; ib++)
			      {
				for(int jb = 0; jb < hb; jb++)
				  {				    
				    Tile* tilecc = map->getTile(j+jb,i-ib);

				    std::list<NPC *> lnpc = tilecc->getNPCs();
				    for(std::list<NPC*>::const_iterator ci = lnpc.begin(); ci != lnpc.end(); ++ci)
				      {
					assert((**ci).TextureIsInit());

					(**ci).nextFrame();
					
					sf::Sprite& sfn = (**ci).getSprite();
					Position& p = (**ci).getPosition();
					sfn.setPosition(sf::Vector2f( floor(p.getY() * RIGHT_TILE(0) + p.getX() * DOWN_TILE(0) + OFFSET_X - (**ci).TextureOffsetX()), floor(p.getY() * RIGHT_TILE(1) + p.getX() * DOWN_TILE(1) + OFFSET_Y - w * RIGHT_TILE(1) - (**ci).TextureOffsetY())));
					target.draw(sfn,states);
				      }
				    isDrawn[j+jb][i-ib] = true;
				  }
			      }

			  }
		      }
		  }	
	      }
	  }
      }
    return;
  }

void GraphicContextIso::load()
{
  int w = map->getMapWidth(), h = map->getMapHeight();
  
  for(int i = 0; i < w; i ++)
    {
      for(int j = 0; j < h; j++)
        {
          Tile* tilec = map->getTile(j,i);

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

Position GraphicContextIso::screenToMap(int x, int y)
{
  sf::Vector2f v = view.getCenter();
  Position p;
  float xo = x - (view.getSize().x/2), yo = y - (view.getSize().y/2);
  float xc = v.x - OFFSET_X, 
    yc = v.y - OFFSET_Y + (map->getMapWidth()) * RIGHT_TILE(1);
  p.add((xc+xo)/(RIGHT_TILE(0)+DOWN_TILE(0)) 
	+ (yc+yo)/(DOWN_TILE(1)-RIGHT_TILE(1)),
	(xc+xo)/(RIGHT_TILE(0)+DOWN_TILE(0)) 
	- (yc+yo)/(DOWN_TILE(1)-RIGHT_TILE(1)));
  return p;
}

TexturePack* GraphicContextIso::getTexturePack(int n)
{
  return(&(texVector.at(n)));
}
