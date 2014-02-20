#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "PreScenarioActionList.h"
#include "simulation.h"
#include "ActionsPC.h"
#include "ActionsTerro.h"
#include "geography.h"
#include "../simulation/npc.h"

/*****************
 *ChangeDirection*
 *****************/

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

ChangeDirection::ChangeDirection(int id, Direction dir, int ts, Simulation* s) : ScenarioAction ("ChangeDirection",s){
	playerID = id;
	newDirection = dir;
	timeStamp = ts;
};

ChangeDirection::ChangeDirection(const ChangeDirection& a) : ScenarioAction("ChangeDirection",a.simulation){
	this->playerID = a.playerID;
	this->newDirection = a.newDirection;
	this->timeStamp = a.timeStamp;
}

void ChangeDirection::run(){

	simulation->getPlayerByID(playerID).setDirection(newDirection,timeStamp);

	return;
};

/*****************
 *ChangeDestination*
 *****************/
ChangeDestination::ChangeDestination(int id, Position destination, int ts, Simulation* s) : ScenarioAction ("ChangeDestination",s),
		playerID(id),
		destination(destination),
		timeStamp(ts) { }

ChangeDestination::ChangeDestination(const ChangeDestination& a) : ScenarioAction("ChangeDestination",a.simulation){
	this->playerID = a.playerID;
	this->destination = a.destination;
	this->timeStamp = a.timeStamp;
}

void ChangeDestination::run(){

	simulation->getPlayerByID(playerID).setDestination(destination,timeStamp);

	return;
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
	if (simulation->getSous() > 0) {
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
		simulation->enleveSous((int)(COST_COP2*number));
	}

	return;
};

/***********
 * AddCams *
 ***********/

//AddCams::AddCams(int n,float xx,float yy,Simulation* s) : ScenarioAction("AddCams",s){
//	x = xx;
//	y = yy;
//	number = n;
//	this->simulation = s;
//};

//AddCams::AddCams(const AddCams& a) : ScenarioAction("AddCams",a.simulation){
//	this->number = a.number;
//	this->x = a.x;
//	this->y = a.y;
//}

void AddCams::run(){
	if (simulation->getSous() > 0) {
		for (int i=1;i<number/4;i++) {
			simulation->addCam(new Camera(x+i,y+i,(float)COST_CAM1,1));
			simulation->addCam(new Camera(x+i,y-i,(float)COST_CAM1,1));
			simulation->addCam(new Camera(x-i,y+i,(float)COST_CAM1,1));
			simulation->addCam(new Camera(x-i,y-i,(float)COST_CAM1,1));
		};
		if (number%4 == 1) {
			simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1,1));

		};
		if (number%4 == 2) {
			simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1,1));
			simulation->addCam(new Camera(x-number/4,y+number/4,(float)COST_CAM1,1));
		};
		if (number%4 == 3) {
			simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1,1));
			simulation->addCam(new Camera(x-number/4,y+number/4,(float)COST_CAM1,1));
			simulation->addCam(new Camera(x+number/4,y-number/4,(float)COST_CAM1,1));


		};
		simulation->enleveSous((int)(COST_CAM2*number));
	}
};


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
};

void AddCams::run2(){
	if (simulation->getSous() > 0) {
		for (int i=1;i<number/4;i++) {
			simulation->addCam(new Camera(x+i,y+i,(float)COST_CAM1_2,2));
			simulation->addCam(new Camera(x+i,y-i,(float)COST_CAM1_2,2));
			simulation->addCam(new Camera(x-i,y+i,(float)COST_CAM1_2,2));
			simulation->addCam(new Camera(x-i,y-i,(float)COST_CAM1_2,2));
		};
		if (number%4 == 1) {
			simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1_2,2));
		};
		if (number%4 == 2) {
			simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1_2,2));
			simulation->addCam(new Camera(x-number/4,y+number/4,(float)COST_CAM1_2,2));
		};
		if (number%4 == 3) {
			simulation->addCam(new Camera(x+number/4,y+number/4,(float)COST_CAM1_2,2));
			simulation->addCam(new Camera(x-number/4,y+number/4,(float)COST_CAM1_2,2));

			simulation->addCam(new Camera(x+number/4,y-number/4,(float)COST_CAM1_2,2));

		};
		simulation->enleveSous((int)(COST_CAM2_2*number));
	}
};



/***********************************
 * AbstractMessage implementations *
 **********************************/

AbstractMessage* ChangeDirection::copy(){
	return (AbstractMessage*) new ChangeDirection(*this);
}


AbstractMessage* ChangeDestination::copy(){
	return (AbstractMessage*) new ChangeDestination(*this);
}


AbstractMessage* AddCops::copy(){
	return (AbstractMessage*) new AddCops(*this);
}


AbstractMessage* AddCams::copy(){
	return (AbstractMessage*) new AddCams(*this);
}



RemoveNPC::RemoveNPC( boost::uuids::uuid npc,Simulation* sim): ScenarioAction("RemoveNPC",sim){
	this->npc = npc;
};

RemoveNPC::RemoveNPC(const RemoveNPC& a) : ScenarioAction("RemoveNPC", a.simulation){
	this->npc= a.npc;
};

AbstractMessage* RemoveNPC::copy() {
	return (AbstractMessage*) new RemoveNPC(*this);
};

void RemoveNPC::run () {
	simulation->supprimerNPC(this->simulation->getNPCByID(this->npc))
			;};




/*********************************************************
 ** Library for create scenario action**
 *********************************************************/


void KillNPC(boost::uuids::uuid target, Simulation* s ){
	boost::uuids::uuid t = target;
	NPC* victim = s->getNPCByID(t);
	if (victim == NULL) {
		std::cout << "null" << std::endl;
	}
	else {
		victim->kill();
	};
	std::cout << "YOU BASTARD !!!" << std::endl;
	return;
};


void DropItem (int stuffID, int playerID, Simulation* simulation){
	simulation->getPlayerByID(playerID).removeItem(stuffID);
};


void Explosion (int power, std::pair<int,int> location,Simulation* simulation) {
	std::list<Tile*>* nb = simulation->getMap()->neighbors(power, simulation->getMap()->getTile(location));
	std::cout << "nobody : ça explose!!!!!" << std::endl;
	for (std::list<Tile*>::iterator t = nb->begin(); t != nb->end();++t) {
		std::list<NPC*> npcs = (*t)->getNPCs();
		for(std::list<NPC*>::iterator n = npcs.begin(); n != npcs.end(); ++n){
			(*n)->kill();
		}
	};
	std::cout << "nobody : fin d'explosion!!!!!"<< std::endl ;
};
