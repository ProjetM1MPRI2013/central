/**
 * @author MrKuluW
 */
#include "graphic_context_iso.h"
#include "../simulation/npc.h"
#include <list>
#include <iostream>
#include <fstream>
#include <unistd.h>

#define DEBUG true
#include "debug.h"

  GraphicContextIso::GraphicContextIso(Geography* map, Simulation* sim)
  {
    this->map = map;
    this->sim = sim;  
    zoomfactor = 1;
    zoommax = 3;
    zoommin = 0.3;

    unfogVector.push_front(sim->getPlayer());
    sim->getPlayer()->setActive(true);
    sim->getPlayer()->setRadius(24);


    assert(fogT.loadFromFile("../../../sprite/fogtile.png"));
    assert(baseT.loadFromFile("../../../sprite/basetile.png"));
    assert(dafont.loadFromFile("../fonts/DejaVuSans.ttf"));
    assert(playerT.loadFromFile("../../../sprite/Anim_idle.png"));

    // End fog and base

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
    
    // End Parser animations

    int w = map->getMapWidth(), h = map->getMapHeight();
    
    for(int i = 0; i < w; i ++){
      for(int j = 0; j < h; j++){
	Tile* tilec = map->getTile(i,j);
	
	assert(tilec != NULL);
	
	if(!tilec->TextureIsInit()){
	  std::string s = tilec->getFilePictures();
	  s.pop_back();
	  try{
	    tilec->setTexture(&(tilemap.at(s)));
	  }
	  catch(...){
	    sf::Texture t;
	    DBG << "chargement de " << s;
	    assert(t.loadFromFile(s));
	    SpriteTilePack stp = { .texture = t, .originX = tilec->getPictureX(),
				   .originY = tilec->getPictureY()};
	    tilemap[s] = stp;
	    tilec->setTexture(&tilemap[s]);
	  }
	}
	
	std::list<NPC *> lnpc = tilec->getNPCs();
	for(std::list<NPC*>::const_iterator ci = lnpc.begin(); 
	    ci != lnpc.end(); ++ci){
	  if(!(**ci).TextureIsInit()){
	    (**ci).TextureAnim(&(texVector.at(0))); // prends la première animation par défaut. S'il n'y a aucune animation de chargée, renvoie une erreur. A changer
	  }
	}
      }
    }
    
    // End loading tiles and NPCs

    assert(drawList.empty());

    bool isDrawn[w][h];
    for(int j = 0; j < h; j++){
      for(int i = 0; i < w; i++)
	isDrawn[i][j] = false;
    }

    /*
      isDrawn est une matrice qui indique quelle tile a déjà été affichée.
      Pour un affichage correct, il faut que tous les éléments au dessus d'une
      case aient été affichés avant elle-même. Ainsi, l'invariant à conserver
      est :
      \forall i,j,i',j' (j' <= j & i' >= i & isDrawn[i][j]) -> isDrawn[i'][j']
      La condition d'arrêt est donc :
      isDrawn[0][h-1]
      L'ordre d'affichage des tiles est enregistré dans drawList
    */
    bool be = true;
    while(!(isDrawn[0][h-1]) && be){
      be = false;
      for(int i = 0 ; i < w ; i++){
	for(int j = 0 ; j < h ; j++){
	  
	  Tile* tilec = map->getTile(i,j);
	  
	  assert(tilec);
	  
	  if(tilec->isBatOrigin() && not(isDrawn[i][j])){
	    int wb = tilec->getWidthBat(), hb = tilec->getHeightBat();
	    bool c1, c2;
	    if(j==0)
	      c1 = true;
	    else
	      c1 = isDrawn[i+1-wb][j-1];
	    
	    if(i==w-1)
	      c2 = true;
	    else
	      c2 = isDrawn[i+1][j-1+hb];
	    
	    if(c1 && c2){

	      drawList.push_back(tilec);

	      for(int ib = 0; ib < wb; ib++){
		for(int jb = 0; jb < hb; jb++){				    
		  be = true;
		  isDrawn[i-ib][j+jb] = true;
		}// Loop on y in the building
	      }// Loop on x in the bulding
	      
	    }// Drawable at this step
	  }// Not drawn
	}// Loop on y
      }// Loop on x
    }// Drawing buildings and objects

    // End drawList
  }
  
void GraphicContextIso::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  int w = map->getMapWidth(), h = map->getMapHeight();
  sf::Sprite fog, base;
  states.transform *= getTransform();
  
  fog.setTexture(fogT);
  fog.setColor(sf::Color(0,0,0,128));
  base.setTexture(baseT);

  /* Mise à jour pas subtile du brouillard de guerre */
  /* Remise à zéro */
  for(int j = 0; j < h; j++){
    for(int i = 0; i < w; i++){
      map->getTile(i,j)->setFog(true);
    }
  }

  /* Eclairage */
  for(std::list<Positionable*>::const_iterator ci = unfogVector.begin();
      ci != unfogVector.end(); ++ci){
    Position p = (**ci).getPosition();
    int r = (**ci).getRadius(), x = floor(p.getX()), y = floor(p.getY());
    for(int k = 0; k <= r; k++){
      for(int l = 0; l <= r; l++){
  	int ii = x + k - l;
  	int jj = y - r + k + l;
  	if(ii >= 0 && ii < w && jj >= 0 && jj < h)
  	  map->getTile(ii,jj)->setFog(false);
      }
    }
    for(int k = 0; k < r; k++){
      for(int l = 0; l < r; l++){
  	int ii = x + k - l;
  	int jj = y - r + 1 + k + l;
  	if(ii >= 0 && ii < w && jj >= 0 && jj < h)
  	  map->getTile(ii,jj)->setFog(false);
      }
    }
  }

  /* Mise à jour des bâtiments */
  for(int i = 0; i < w; i++){
    for(int j = 0; j < h; j++){
      Tile* tilec = map->getTile(i,j);
      if(tilec->isBatOrigin()){
  	int compt = 0;
  	for(int ii = 0; ii < tilec->getWidthBat(); ii++){
  	  for(int jj = 0; jj < tilec->getHeightBat(); jj++){
  	    if(map->getTile(i-ii,j+jj)->isInFog())
  	      compt++;
  	  }
  	}
  	tilec->setBuildFog(compt);
      }
    }
  }


  
  /* 
     Dans un premier temps, on peut afficher toutes les tiles walkable, qui
     sont supposées plates. Cela permet d'éviter des problèmes éventuels 
     lorsque les sprites des objets comme les npc sont trop larges. On va
     aussi afficher des tiles de base en dessous des batiments.
  */
  for(int j = 0; j < h; j++){
    for(int i = 0; i < w; i++){
      Tile* tilec = map->getTile(i,j);
      if(tilec->isWalkable() && tilec->isBatOrigin()){
	sf::Sprite& sp = tilec->getSprite();
	sp.setPosition(sf::Vector2f( (i + 1) * RIGHT_TILE(0) + j * DOWN_TILE(0) - tilec->getOriginSpriteX() + OFFSET_X - 2, 
				     (i + 1) * RIGHT_TILE(1) + j * DOWN_TILE(1) - tilec->getOriginSpriteY() + OFFSET_Y - w * RIGHT_TILE(1) - 1));
	target.draw(sp, states);
      }
      else if(!(tilec->isWalkable())){
      	base.setPosition(sf::Vector2f( i * RIGHT_TILE(0) + j * DOWN_TILE(0) + OFFSET_X,
				       i * RIGHT_TILE(1) + j * DOWN_TILE(1) + OFFSET_Y - w * RIGHT_TILE(1) - 11));
      	target.draw(base, states);
      }
    }
  }
  
  for(std::list<Tile*>::const_iterator cit = drawList.begin();
      cit != drawList.end(); ++cit){
    
    Tile* tilec = *cit;
    int i = tilec->getCoord().getAbs(), j = tilec->getCoord().getOrd();

    assert(tilec);
    assert(tilec->TextureIsInit());

    int wb = tilec->getWidthBat(), hb = tilec->getHeightBat();
    

    if(!(tilec->isWalkable())){
      sf::Sprite& sp = tilec->getSprite();
      sp.setPosition(sf::Vector2f( (i + 1) * RIGHT_TILE(0) + j * DOWN_TILE(0) - tilec->getOriginSpriteX() + OFFSET_X - 2,
				   (i + 1) * RIGHT_TILE(1) + j * DOWN_TILE(1) - tilec->getOriginSpriteY() + OFFSET_Y - w * RIGHT_TILE(1) - 1));
      target.draw(sp, states);
    }
    
    for(int ib = 0; ib < wb; ib++){
      for(int jb = 0; jb < hb; jb++){				    
	Tile* tilecc = map->getTile(i-ib,j+jb);
	
	std::list<NPC *> lnpc = tilecc->getNPCs();
	for(std::list<NPC*>::const_iterator ci = lnpc.begin();
	    ci != lnpc.end(); ++ci){
	  if(!(tilecc->isInFog())){
	    assert((**ci).TextureIsInit());
	    
	    (**ci).nextFrame();
	    
	    sf::Sprite& sfn = (**ci).getSprite();
	    Position& p = (**ci).getPosition();
	    sfn.setPosition(sf::Vector2f(p.getX() * RIGHT_TILE(0) + p.getY() * DOWN_TILE(0) + OFFSET_X - (**ci).TextureOffsetX(), 
					 p.getX() * RIGHT_TILE(1) + p.getY() * DOWN_TILE(1) + OFFSET_Y - w * RIGHT_TILE(1) - (**ci).TextureOffsetY()));
	    target.draw(sfn,states);
	  }// If not hidden, draw NPC 
	}// Loop on NPCs

	if(tilecc->isWalkable() && tilecc->isInFog()){
	  fog.setPosition(sf::Vector2f( (i-ib) * RIGHT_TILE(0) + (j+jb) * DOWN_TILE(0) + OFFSET_X,
					(i-ib) * RIGHT_TILE(1) + (j+jb) * DOWN_TILE(1) + OFFSET_Y - w * RIGHT_TILE(1) - 11));
	  target.draw(fog, states);
	}

      }// Loop on y in the building
    }// Loop on x in the bulding
    // End drawing NPC
    
  }// Drawing buildings and objects
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
  sf::Text fpstext;
  sf::Sprite playerSprite;
  int fps = 1000 / spf.getElapsedTime().asMilliseconds();
  spf.restart();
  fpstext.setString(std::to_string(fps));
  fpstext.setCharacterSize(16);
  fpstext.setColor(sf::Color::Red);
  Position& p = sim->getPlayer()->getPosition();
  this->view.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
  this->view.setCenter(sf::Vector2f(p.getX() * RIGHT_TILE(0) + p.getY() * DOWN_TILE(0) + OFFSET_X, 
				    p.getX() * RIGHT_TILE(1) + p.getY() * DOWN_TILE(1) + OFFSET_Y - map->getMapWidth() * RIGHT_TILE(1)));
  

  playerSprite.setTexture(playerT);
  playerSprite.setPosition(sf::Vector2f(p.getX() * RIGHT_TILE(0) + p.getY() * DOWN_TILE(0) + OFFSET_X - 8, 
				       p.getX() * RIGHT_TILE(1) + p.getY() * DOWN_TILE(1) + OFFSET_Y - map->getMapWidth() * RIGHT_TILE(1) - 32));
  
  window->setView(this->view);
  window->draw(*this);
  window->draw(playerSprite);
  window->setView(window->getDefaultView());
  window->draw(fpstext);

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

float GraphicContextIso::zoom(float f)
{
  float z = zoomfactor*f;
  z = std::min(z,zoommax);
  z = std::max(z,zoommin);
  float g = zoomfactor / z;
  view.zoom(g);
  zoomfactor = z;
  return zoomfactor;
}
