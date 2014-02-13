#include "generator.h"
#include <list>
#include <iostream>
#include <fstream>



using namespace std;
int main() {

	Generator* g = new Generator;
	string s = (string) "source.txt";
	MainReader* m = new MainReader (g,'+',';',':',s ) ;
	cout << "1" << endl;
	m->read();
	cout << "1.1" << endl;

	affiche(g->actions);
	cout << "2" << endl;
	g->addAction(new PreAction ("Drop"));
	g->AddIap(
			"(isInThePack(this->simulation,this->stuff))"
	);
	g->AddConsequence("DropItem");
	cout << "3" << endl;
	g->AddActionField(new Field (FT_Clickable,"stuff","Stuff"));
	g->AddActionField((Field*) new Variable (VT_BOTH,"playerID","int","this->simulation->getPlayer()->getID()"));
	cout << "4" << endl;
	affiche (g->actions);
	g->write();
	delete g;
};
