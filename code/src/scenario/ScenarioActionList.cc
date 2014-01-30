#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "ScenarioActionList.h"
#include "simulation.h"
#include "ActionsPC.h"
#include "ActionsTerro.h"
#include "geography.h"

BOOST_CLASS_EXPORT(ChangeDirection)
BOOST_CLASS_EXPORT(KillNPC)
BOOST_CLASS_EXPORT(Explosion)
BOOST_CLASS_EXPORT(AddCams)
BOOST_CLASS_EXPORT(AddCops)
BOOST_CLASS_EXPORT(DropItem)


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
  default:
    break;
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
  return Direction::ERROR;
};

ChangeDirection::ChangeDirection(int id, NewMov mov,Simulation* s) : ScenarioAction ("ChangeDirection",s){
  playerID = id;
  newMovement = mov;
};

ChangeDirection::ChangeDirection(const ChangeDirection& a) : ScenarioAction("ChangeDirection",a.simulation){
  this->playerID = a.playerID;
  this->newMovement = a.newMovement;
}

void ChangeDirection::run(){
  Direction a = simulation->getPlayerByID(playerID).getDirection();
  Couple* b = directionToInt(a);
  Couple* c = newMovToInt(this->newMovement);
  Couple* newDir = new Couple(b->x + c->x, b->y + c->y);
  Direction d = intToDirection(newDir);
  if (d != Direction::ERROR){
    simulation->getPlayerByID(playerID).setDirection(d);
  }
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

KillNPC::KillNPC(const KillNPC& a) : ScenarioAction("KillNPC",a.simulation){
  this->target = a.target;
}

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

Explosion::Explosion(const Explosion& a) : ScenarioAction("Explosion",a.simulation){
  this->location = a.location;
  this->power = a.power;
}

void Explosion::run() {
  std::list<Tile*>* nb = this->simulation->getMap()->neighbors(this->power, this->location);
  for (std::list<Tile*>::iterator t = nb->begin(); t != nb->end();++t) {
    // kill npc in the case. Only the server had to dot this. The client only destroys the buildings
    if (this->simulation->simIsServer()){
      std::list<NPC*> npcs = (*t)->getNPCs();
      for(std::list<NPC*>::iterator n = npcs.begin(); n != npcs.end(); ++n){
	this->simulation->addAction(new KillNPC(*n, this->simulation));
      };
    }
    //TODO détruire les batiments
    //TODO juste pour les test
    (*t)->setAnxiety(100);
  };
};


/***********
 * AddCops *
 ***********/

AddCops::AddCops(int n,float xx,float yy,Simulation* s) : ScenarioAction("AddCops",s){
  x = xx;
  y = yy;
  number = n;
  this->simulation = s;
};

AddCops::AddCops(const AddCops& a) : ScenarioAction("AddCops",a.simulation){
  this->number = a.number;
  this->x = a.x;
  this->y = a.y;
}

void AddCops::run(){
	 for (int i=1;i<number/4;i++) {
	    simulation->addAgent(new Agent(x+i,y+i,(float)COST_COP1,0));
	    simulation->addAgent(new Agent(x+i,y+i,(float)COST_COP1,0));
	    simulation->addAgent(new Agent(x+i,y+i,(float)COST_COP1,0));
	    simulation->addAgent(new Agent(x+i,y+i,(float)COST_COP1,0));
	  };
	  if (number%4 == 1) {
		  simulation->addAgent(new Agent(x+number/4,y+number/4,(float)COST_COP1,0));
	  };
	  if (number%4 == 2) {
		  simulation->addAgent(new Agent(x+number/4,y+number/4,(float)COST_COP1,0));
		  simulation->addAgent(new Agent(x-number/4,y+number/4,(float)COST_COP1,0));
	   };
	  if (number%4 == 3) {
		  simulation->addAgent(new Agent(x+number/4,y+number/4,(float)COST_COP1,0));
		  simulation->addAgent(new Agent(x-number/4,y+number/4,(float)COST_COP1,0));
		  simulation->addAgent(new Agent(x+number/4,y-number/4,(float)COST_COP1,0));


	     };
  simulation->enleveSous((int)COST_COP2*number);
  return;
};

/***********
 * AddCams *
 ***********/

AddCams::AddCams(int n,float xx,float yy,Simulation* s) : ScenarioAction("AddCams",s){
  x = xx;
  y = yy;
  number = n;
  this->simulation = s;
};

AddCams::AddCams(const AddCams& a) : ScenarioAction("AddCams",a.simulation){
  this->number = a.number;
  this->x = a.x;
  this->y = a.y;
}

void AddCams::run(){
  for (int i=1;i<number/4;i++) {
    simulation->addCam(new Camera(x+i,y+i,(float)COST_CAM1));
    simulation->addCam(new Camera(x+i,y-i,(float)COST_CAM1));
    simulation->addCam(new Camera(x-i,y+i,(float)COST_CAM1));
    simulation->addCam(new Camera(x-i,y-i,(float)COST_CAM1));
  };
  if (number%4 == 1) {
	  simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1));
  };
  if (number%4 == 2) {
	  simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1));
	  simulation->addCam(new Camera(x-number/4,y+number/4,(float)COST_CAM1));
   };
  if (number%4 == 3) {
	  simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1));
	  simulation->addCam(new Camera(x-number/4,y+number/4,(float)COST_CAM1));
	  simulation->addCam(new Camera(x+number/4,y-number/4,(float)COST_CAM1));


     };
  simulation->enleveSous((int)COST_CAM2*number);
};


/************
 * DropItem *
 ************/

DropItem::DropItem(int stuffID, int id, Simulation* s) : ScenarioAction("DropItem",s){
  this->stuffID = stuffID;
  this->simulation = s;
  this->playerID = id;
}

DropItem::DropItem(const DropItem& a) : ScenarioAction("DropItem",a.simulation){
  this->stuffID = a.stuffID;
  this->playerID = a.playerID;
}

void DropItem::run (){
  this->simulation->getPlayerByID(this->playerID).removeItem(stuffID);
}


/***********************************
 * AbstractMessage implementations *
 **********************************/

AbstractMessage* ChangeDirection::copy(){
    return (AbstractMessage*) new ChangeDirection(*this);
}


AbstractMessage* AddCops::copy(){
    return (AbstractMessage*) new AddCops(*this);
}


AbstractMessage* AddCams::copy(){
    return (AbstractMessage*) new AddCams(*this);
}


AbstractMessage* Explosion::copy(){
    return (AbstractMessage*) new Explosion(*this);
}


AbstractMessage* KillNPC::copy(){
    return (AbstractMessage*) new KillNPC(*this);
}


AbstractMessage* DropItem::copy(){
    return (AbstractMessage*) new DropItem(*this);
}
