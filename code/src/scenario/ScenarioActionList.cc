#include "ScenarioActionList.h"
#include "simulation.h"
#include "ActionsPC.h"
#include "ActionsTerro.h"

/*****************
 *ChangeDirection*
 *****************/

class Couple {
public:
  int x;
  int y;
  Couple (int x, int y);
};

Couple::Couple (int a, int b){
  x = a;
  y = b;
};

Couple* directionToInt(Direction a){
  switch (a){
  case UP :
    return new Couple(0,1);
  case UPRIGHT :
    return new Couple(1,1);    
  case RIGHT:
    return new Couple(1,0);    
  case RIGHTDOWN :
    return new Couple(1,-1);    
  case DOWN :
    return new Couple(0,-1);    
  case DOWNLEFT :
    return new Couple(-1,-1);    
  case LEFT :
    return new Couple(-1,0);    
  case LEFTUP :
    return new Couple(-1,1);   
  case STOP :
    return new Couple(0,0);
  };
  //ne doit pas arriver
  std::cerr << "ScenarioActionList::directionToInt : Direction not correct " << (int) a << "\n";
  return new Couple (10,10);
};

Couple* newMovToInt(NewMov a){
  switch (a){
  case NewMov::R_UP :
    return new Couple (0,-1);
  case NewMov::R_DOWN :
    return new Couple (0,1);
  case NewMov::R_LEFT :
    return new Couple (1,0);
  case NewMov::R_RIGHT :
    return new Couple (-1,0);
  case NewMov::P_UP :
    return new Couple (0,1);
  case NewMov::P_DOWN :
    return new Couple (0,-1);
  case NewMov::P_LEFT :
    return new Couple (-1,0);
  case NewMov::P_RIGHT :
    return new Couple (1,0);
  };
  std::cerr << "ScenarioActionList::newMovToInt : Direction not correct " << (int) a << "\n";
  return new Couple (10,10);
};

Direction intToDirection(Couple* a){
  if ((a->x == 0)&&(a->y == 1)) {return Direction::UP;};
  if ((a->x == 1)&&(a->y == 1)) {return Direction::UPRIGHT;};
  if ((a->x == 1)&&(a->y == 0)) {return Direction::RIGHT;};
  if ((a->x == 1)&&(a->y == -1)) {return Direction::RIGHTDOWN;};
  if ((a->x == 0)&&(a->y == -1)) {return Direction::DOWN;};
  if ((a->x == -1)&&(a->y == -1)) {return Direction::DOWNLEFT;};
  if ((a->x == -1)&&(a->y == 0)) {return Direction::LEFT;};
  if ((a->x == -1)&&(a->y == 1)) {return Direction::LEFTUP;};
  if ((a->x == 0)&&(a->y == 0)) {return Direction::STOP;};
  //ne doit pas arriver
  std::cerr << "ScenarioActionList::intToDirection : Couple not correct " << a->x << " " << a->y << "\n";
  return Direction::STOP;
};

ChangeDirection::ChangeDirection(int id, NewMov mov,Simulation* s) : ScenarioAction ("ChangeDirection",s){
  playerID = id;
  newMovement = mov;
};

void ChangeDirection::run(){
  Direction a = simulation->getPlayerByID(playerID)->getDirection();
  Couple* b = directionToInt(a);
  Couple* c = newMovToInt(this->newMovement);
  Couple* newDir = new Couple(b->x + c->x, b->y + c->y);
  simulation->getPlayerByID(playerID)->setDirection(intToDirection(newDir));
  delete b;
  delete c;
  delete newDir;
  return;
};

/*********
 *KillNPC*
 *********/
KillNPC::KillNPC(NPC* t,Simulation* s) : ScenarioAction("KillNPC",s){
  target = t;
};

void KillNPC::run(){
    simulation->supprimerNPC(target);
  return;
};

/***********
 *Explosion*
 ***********/
Explosion::Explosion(Tile* t,int p,Simulation* s) : ScenarioAction("Explosion",s){
  location = t;
  power = p;
};
bool isInTheMap (int x, int y, Geography* m ) {
	//TODO verifier avec chatan
	return (
			(x >= 0)
			// TODO && (x <= m->getMapWeight()) && (y >= 0) && (y <= m->getMapLenght())
			);
};


void neighborsaux (int x,int y , std::list<Tile*> result ,Geography* m ) {
	if (isInTheMap (x,y,m)) {
					result.push_front(
							m->getTile(x,y)
					);
	};
};

std::list<Tile*> neighbors (int n,Tile* t0,Geography* m) {
	Coordinates c0 = t0->getCoord();
	int x0 = c0.abs ;
	int y0 = c0.ord ;
	std::list<Tile*> result;
	for (int i = 0 ; i <= n; ++i){
		for (int j = 0  ; j <= n-i; ++j){
			neighborsaux (x0+i,y0+j,result,m);
			if (i > 0) {
				neighborsaux (x0-i,y0+j,result ,m);
				if (j>0) {neighborsaux(x0-i,y0-j,result ,m);};
			};
			if (j>0) {
				{neighborsaux(x0-i,y0-j,result ,m);};
			}
		};
	};
	return result;
};

void Explosion::run() {
	std::list<Tile*> nb = neighbors (this->power, this->location,this->simulation->getMap());
	for (std::list<Tile*>::iterator t = nb.begin(); t != nb.end();++t) {
		// kill npc in the case:
		std::list<NPC*> npcs = (*t)->getNPCs();
		for(std::list<NPC*>::iterator n = npcs.begin(); n != npcs.end(); ++n){
			this->simulation->addAction(new KillNPC(*n, this->simulation));
		};
		//TODO détruire les batiments
	};
};


AddCops::AddCops(int n,float xx,float yy,Simulation* s) : ScenarioAction("AddCops",s){
  x = xx;
  y = yy;
  number = n;
  this->simulation = s;
};

void AddCops::run(){
  for (int i=0;i<number;i++) {
    simulation->addAgent(new Agent(x+i,y+i,(float)COST_COP1,0));
  };
  simulation->enleveSous((int)COST_COP2*number);
  return;
};

AddCams::AddCams(int n,float xx,float yy,Simulation* s) : ScenarioAction("AddCams",s){
  x = xx;
  y = yy;
  number = n;
  this->simulation = s;
};

void AddCams::run(){
  for (int i=1;i<number/4;i++) {
    simulation->addCam(new Camera(x+i,y+i,(float)COST_CAM1));
    simulation->addCam(new Camera(x+i,y-i,(float)COST_CAM1));
    simulation->addCam(new Camera(x-i,y+i,(float)COST_CAM1));
    simulation->addCam(new Camera(x-i,y-i,(float)COST_CAM1));
  };
  for (int i= number/4 + 1;i<number%4 + number/4 +1;i++) {
	  simulation->addCam(new Camera(x+i,y+i,(float)COST_CAM1));
  };
  simulation->enleveSous((int)COST_CAM2*number);
};


DropItem::DropItem(Stuff* stuffO, int id, Simulation* s) : ScenarioAction("DropItem",s){
  this->stuff = stuffO;
  this->simulation = s;
  this->playerID = id;
}

void DropItem::run (){
  this->simulation->getPlayerByID(this->playerID)->removeItem(stuff);
}
