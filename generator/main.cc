#include "generator.h"
#include <list>
#include <iostream>
#include <fstream>



using namespace std;
/*
int main () {
	Loader l;
	ToLoad* t = new ToLoad("bla");
	l.add(t);
	l.~Loader();
	cout << "yep" <<endl;
};*/

int main() {

	Generator* g = new Generator;
	string s = (string) "source.txt";
	MainReader m = MainReader (g,'+',';',':',s ) ;
	cout << "1" << endl;
	m.read();
	cout << "1.1" << endl;

	affiche(g->actions);
	cout << "2" << endl;
	g->addAction(new PreAction ("Drop"));
	g->AddIap(
			"(isInThePack(this->simulation,this->stuff))"
	);
	g->AddConsequence("DropItem(this->stuff,this->playerID,this->simulation);");
	cout << "3" << endl;
	g->AddActionField((Field*) new Clickable("stuff","Stuff"));
	g->AddActionField((Field*) new Clickable("zone","Tile"));
	cout << "4" << endl;
	affiche (g->actions);
	g->write();
	g->clear();
	//delete g;
};
