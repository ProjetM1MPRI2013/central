#include "generator.h"
#include <iostream>
#include <fstream>

#define DEBUG false

void debug (string s) {
	if (DEBUG) {cout << s << endl;}
};

// LOADEtofoR

// justification new toload :
// un toload à vocation à être stocké sous forme de liste et repéré par un pointeur
// chaque classe qui héritera de toload aura vocation à être créer par new
ToLoad::ToLoad(string n) {
	name = n;
}
;

Loader::Loader() {
	current = NULL;
	list<ToLoad*> table;
	this->table = table;
}
;

Loader::~Loader() {
	current = NULL;
	/* if (current == NULL) {delete current}*/
	this->table.clear();
}
;

ToLoad* Loader::find(string s) {
	for (list<ToLoad*>::iterator it = table.begin(); it != table.end();
			++it) {
		if ((*it)->name.compare(s) == 0) {
			return (*it);
		};
	};
	if (DEBUG) {cout << "not found "+ s << endl;};
	return NULL;
}
;

void Loader::erase(string s) {
	list<ToLoad*>::iterator it0;
	for (list<ToLoad*>::iterator it = table.begin(); it != table.end();
			++it) {
		if ((*it)->name.compare(s) == 0) {
			it0 =it ;
			break;
		};
	};
	if ((*it0) != NULL) {table.erase(it0);}
	else {
		if (DEBUG) {cout << "not found in erase "+ s << endl;}
	};
}
;

ToLoad* Loader::Load(string s) {
	current = this->find(s);
	return current;
}
;

list<ToLoad*> Loader::getTable() {
	return (this->table);
}
;

void Loader::add(ToLoad* p) {
	//if (DEBUG) {cout << "add " + p->name << endl; affiche (*this);};

	this->table.push_back(p);
	//if (DEBUG) {affiche (*this);};
	current = p;
}
;

ToLoad* Loader::get() {
	return current;
}
;


Loader Loader::copy() {
	Loader result;
	// on pourrait utiliser la copie de liste mais au moins on sait ce qu'on fait
	list<ToLoad*> l = this->table;
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end();
			++it) {
		result.add(*it);
	};
	return result;
};


void affiche(Loader loader) {
	if (DEBUG) {cout<< "affiche"<< endl;};
	list<ToLoad*> l =  loader.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end();
			++it) {
		if (DEBUG) {cout << (*it)->name << endl;};
	}
	if (DEBUG) {cout<< "fin affiche"<< endl;};
	;
};
//preclass and field


Field::Field(FieldType ft, string name, string type) :
																																																																																														ToLoad(name) {
	this->type = type;
	this->initialisation = "";
	this->fieldtype = ft;
}
;
Field::Field(FieldType ft,string name, string type, string init) :
																																																																																														ToLoad(name) {
	this->type = type;
	this->initialisation = init;
	this->fieldtype = ft;
}
;

Variable::Variable(VariableType vt, string name, string type ) :
																																																																																														Field (FT_Variable, name,type ) {
	this->variabletype = vt;
	this->isVirtual =false;

	;};

Variable::Variable(VariableType vt, string name, string type, string init ) :
																																																																																														Field (FT_Variable, name,type,init ) {
	this->variabletype = vt;
	this->isVirtual =false;
	;};


ClickableType stringToClickableType (string type) {
	debug("type : " + type );
	debug  ("renvoie : ");
	if (type.compare("NPC") == 0) {debug ("npc");return CT_NPC;};
	if (type.compare("Tile") == 0) {debug("tile"); return CT_Tile;};
	debug ("stuff");
	return CT_Stuff;

}

Clickable::Clickable (string name, string type): Field (FT_Clickable, name,type ) {
	this->clickableType = stringToClickableType(type);
	;};

Clickable::Clickable (string name, string type, string init ) :
																																																																																														Field (FT_Clickable, name,type,init ) {
	this->clickableType = stringToClickableType(type);
	;};


PreClass::PreClass(string name) :
																																																																																														ToLoad(name) {
	Loader f ;
	Loader toInitialised ;
	this->fields = f;
	this->toInitialised = toInitialised;
	herite = NULL;

}
;

PreClass::PreClass(string name, PreClass* heritage) :
																																																																																														ToLoad(name) {
	Loader f ;
	toInitialised = heritage->toInitialised.copy();
	this->fields = f;
	herite = heritage;
}
;

void PreClass::add(Field* f) {
	this->fields.add(f);
	if (this->toInitialised.find(f->name) == NULL) {
		if (f->initialisation == "") {
			{this->toInitialised.add((ToLoad*)f);}
		};
	}
	else {
		if (f->initialisation == "") {

		}
		else{
			if (DEBUG) {cout<< "try erase " + f->name << endl;};
			this->toInitialised.erase(f->name);
			if (DEBUG) {cout<< "did erase" << endl;}
		}
	};
};

PreAction::PreAction(string name) : PreClass(name) {
	this->isActionPossible = "true";
	this->firstfield = true;
	list<string> consequence;
	this->consequence = consequence;
}
;

PreClickable::PreClickable(string name) : PreClass (name) {
	list<PreAction*> l ;
	this->actionPossible = l;
	this->isAbstract = false;

};

PreClickable::PreClickable(string name, PreClass* heritage) : PreClass (name,heritage) {
	list<PreAction*> l;
	this->actionPossible = l;
	this->isAbstract = false;

};

void PreClickable::addAction(PreAction* p) {
	this->actionPossible.push_back(p);
};

list<PreAction*> PreClickable::getActionPossible() {
	return this->actionPossible;
};

// writer

Writer::Writer(list<ToLoad*> actions, list<ToLoad*> clickables) {
	fichier = NULL;
	this->actions = actions;
	if (DEBUG){
		cout << "size" <<  actions.size() << endl;
	}
	if (DEBUG){
		cout << "size" <<  this->actions.size() << endl;
	}
	this->clickables = clickables;
}
;


void Writer::write() {
	writeActionTerroCC();
	writeActionTerroH();
	writePreStuffH();
	writePreStackCC();
	writeStuffListCC();
	writeStuffListH();
	writeActionBoostH();
	writeScenarioActionListCC();
	writeScenarioActionListH();
	fichier->close();
}
;

/*need to write*/
void Writer::changeFile(string s) {
	string direction = "../code/src/scenario/";
	if (DEBUG) {cout << "fichier " + s << endl;};
	if ((fichier != NULL) &&(fichier->is_open())) {fichier->close();};
	string s2 = direction + s;
	ofstream*  f = new ofstream (s2.c_str() , std::ios::out) ;
	this->fichier = f ;
	writeAuthor();

}
;

void Writer::writeAuthor() {
	writeCommentName("@author: Remy (generated code)");
};
void Writer::writeInclude (string s) {
	writeWord("#include \""+s +"\"" );
	endLine();
};

void Writer::writeInclude2 (string s) {
	writeWord("#include <"+s +">" );
	endLine();
};


void Writer::writeIfndef (string s) {
	writeWord("#ifndef " +s + "_H");
	endLine();
	writeWord("#define " +s + "_H");
	endLine();
}


FieldType FTOfString (string s) {
	switch (s[0]){
	case 'C': return FT_Clickable;break;
	case 'I': {return FT_IAP;break;}
	case 'Q': {return FT_Consequence; break;}
	default : return FT_Variable;
	};
}

VariableType VTOfString (string s) {
	switch (s[0]){
	case 'G': return VT_Get;break;
	case 'S': return VT_Set;break;
	case 'B': return VT_BOTH;break;
	case 'N': return VT_Nothing;break;
	default : {if (DEBUG) {cout << "erreur in VTOfString avec " + s << endl;}; return VT_BOTH;}
	};
};

string StringOfVT (VariableType vt) {
	switch (vt){
	case VT_Get: return "G";break;
	case VT_Set: return "S" ; break;
	case VT_BOTH: return "B" ;break;
	case VT_Nothing: return "N" ;break;
	default : return ""; break;
	};
};

string StringOfFT (Field* f) {
	switch (f->fieldtype){
	case FT_Clickable : return "C";break;
	case FT_IAP : {return "I";break;}
	case FT_Consequence: {return "Q";  break;}
	case FT_Variable : return StringOfVT(((Variable*)f)->variabletype) ;
	default : return ""; break;
	};
}
void Writer::writeType (Field* f) {
	if(f->fieldtype == FT_Clickable) {
		switch (((Clickable*) f)->clickableType) {
		case CT_Tile:
			writeWord("std::pair<int,int>");
			break;
		case CT_NPC:
			writeWord("boost::uuids::uuid");
			break;
		default:
			writeWord("int");
			break;
		};
	}
	else {writeWord(f->type);};
};

void Writer::writeArguments(PreClass* p) {
	writeWord(" (");
	list<ToLoad*> l = p->toInitialised.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (f->initialisation == "" ){
			if (it != l.begin()) {writeWord(", ");};
			writeType (f);
			writeWord(" ");
			writeWord(f->name);
		};
	};
};


/* writing of ActionsTerro.cc */

void Writer::writeActionTerroCC (){
	changeFile("ActionsTerro.cc");
	writeInclude("ActionsTerro.h");
	for (list<ToLoad*>::iterator it = actions.begin(); it != actions.end();
			++it) {
		writeAction((PreClass*) (*it));
	};
};

void Writer::writeAction(PreClass* p) {
	writeCommentName(((ToLoad*) p)->name);
	endLine();
	this->writeCCconstructeur(p);
	endLine();
	this->writeCopy(p);
	endLine();
	this->writeDoAction(p);
	endLine();
	this->writeIsActionPossible((PreAction*) p);
	endLine();
	this->writeAddPendingAction(p);
	endLine();
	this->writeAbstractMessage(p);
}
;

void Writer::writeCCconstructeur(PreClass* p) {
	string s = ActionName(p);
	writeWord(s);
	writeWord("::");
	writeWord(s);
	writeArguments(p);
	writeWord(", LocalState* sim) ");
	if (p->herite != NULL) {
		writeWord(": ");
		writeWord("A_" + (((ToLoad*) p->herite)->name));
		writeWord(" (");
		list<ToLoad*> l2 = p->herite->fields.getTable();
		for (list<ToLoad*>::iterator it = l2.begin(); it != l2.end(); ++it) {
			Field* f = (Field*) (*it);
			if (f->initialisation == "") {
				if (it != l2.begin()) {
					writeWord(", ");
				};
				writeWord(f->name);
			}
		};
		writeWord(") ");
	} else {
		writeWord(": Action ( \"To" + ActionName(p) + "\", sim) ");
	};
	writeWord("{");
	endLine();
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (f->initialisation == "") {
			writeWord("this->");
			writeWord((*it)->name);
			writeWord(" = (");
			writeType (f);
			writeWord(")");
			writeWord((*it)->name);
		} else {
			writeWord("this->");
			writeWord((*it)->name);
			writeWord(" = (");
			writeType (f);
			writeWord(")(");
			writeWord(f->initialisation);
			writeWord(")");
		};
		writeWord(";");
		endLine();
	};
	writeWord("};");
	endLine();
}
;

void Writer::writeCopy(PreClass* p) {
	string s = ActionName(p);
	writeWord(s);
	writeWord("::");
	writeWord(s);
	writeWord ("(const "+ s + "& a) : Action(\" To" + ActionName(p) + "\", a.simulation){");
	endLine();
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		writeWord("this->"+ f->name + "= a." + f->name  + ";");
		endLine();
	};
	writeWord("};");
	endLine();
}
;

void Writer::writeDoAction(PreClass* p) {
	writeWord("void " + ActionName(p) + "::doAction() {");
	endLine();
	writeWord("this->simulation->getClient()->sendMessage<Action>(*this,true);");
	endLine();
	writeWord("};");
	endLine();
};

void Writer::writeIsActionPossible(PreAction* a) {
	writeWord("bool " + ActionName((PreClass*) a) + "::isActionPossible() {");
	endLine();
	writeWord("//return true;");
	endLine();
	writeWord("return " + a->isActionPossible + ";");
	endLine();
	writeWord("};");
	endLine();
}
;


void Writer::writeAddPendingAction(PreClass* p) {
	writeWord(
			"void " + ActionName(p) + "::addPendingActions(GlobalState* gs){"

	);
	endLine();
	writeWord("gs->addAction(new Co" + ActionName(p) + " (");
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		writeWord("this->");
		writeWord(f->name);
		writeWord(", ");
	};
	writeWord("((Action*)this)->playerID,(Simulation*) gs));");
	endLine();
	writeWord("gs->deleteAction(this);");
	endLine();
	writeWord("};");
	endLine();
}
;


void Writer::writeAbstractMessage(PreClass* p) {
	writeWord("AbstractMessage* " + ActionName(p) + "::copy() {");
	endLine();
	writeWord("return (AbstractMessage*) new " + ActionName(p) + "(*this);");
	endLine();
	writeWord("};");
	endLine();
};



/* writing of ActionsTerro.h */


void Writer::writeActionTerroH (){
	changeFile("ActionsTerro.h");
	writeInclude ("PreActionTerro.h");
	writeInclude ("simulation/npc.h");
	writeInclude2 ("boost/serialization/base_object.hpp");
	writeInclude2 ("boost/serialization/access.hpp");
	writeInclude ("Action.h");
	writeInclude ("StuffList.h");
	writeInclude ("simulation/npc.h");
	writeInclude ("generation/tile.h");
	writeInclude ("Actions.h");
	writeInclude ("ScenarioActionList.h");
	writeInclude ("NewMov.h");
	writeInclude ("tile.h");
	writeInclude ("position.h");
	writeInclude ("npc.h");
	writeInclude ("localState.h");
	writeInclude ("globalState.h");
	writeIfndef("ACTIONTERRO");
	for (list<ToLoad*>::iterator it = actions.begin(); it != actions.end();
			++it) {
		writeHAction((PreClass*) (*it));
	};
	endLine();
	writeWord("#endif");

};



void Writer::writeHAction(PreClass* p) {
	string s = ActionName(p);
	writeCommentName(((ToLoad*)p)->name);
	writeWord("class " + s + ": public Action {");
	endLine();
	writeWord("public:");
	endLine();
	writeWord(s + " ");
	writeArguments(p);
	writeWord(", LocalState* s);");
	endLine();
	writeWord(s + "(const " + s + "&);");
	endLine();
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (f->fieldtype== FT_Clickable)
		{writeWord("public:"); endLine();}
		else {
			string s = f->name ;
			switch (((Variable*)f)->variabletype) {
			case VT_BOTH:
				writeHGet(f);
				writeHSet(f);
				break;
			case VT_Get:
				writeHGet(f);
				break;
			case VT_Set:
				writeHSet(f);
				break;
			case VT_Nothing:
				break;
			default:
				break;
			}
			writeWord("protected:");
			endLine();
		};
		writeType (f);
		writeWord(" ");
		writeWord(f->name);
		writeWord("; ");
		endLine();
	};
	writeWord(
			"public: \n bool isActionPossible (); \n  void doAction (); \n  void addPendingActions(GlobalState* gs); \n  virtual AbstractMessage* copy();"
	);
	endLine();
	writeWord("protected :");
	endLine();
	writeWord("//Serialization");
	endLine();
	string name = ActionName(p);
	if (not p->toInitialised.getTable().empty()) {writeWord( name +"(){};");};
	endLine();
	writeWord("SIMPLE_MESSAGE(" +name +", Action");
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeWord(", ");
		Field* f = (Field*) (*it);
		writeWord(f->name);
	};
	writeWord(");");
	endLine();
	writeWord("};");
}
;


void Writer::writeHGet (Field* f) {
	string s = f->name ;
	writeWord("public:");
	endLine();
	if (((Variable*) f)->isVirtual){
		writeWord("virtual ");
	};
	writeWord(f->type + " get" + s + " ()");
	if (((Variable*) f)->isVirtual){
		writeWord(" = 0");
	};
	writeWord(";");
	endLine();
}

void Writer::writeHSet (Field* f) {

	string s = f->name ;
	writeWord("public:");
	endLine();
	if (((Variable*) f)->isVirtual){
		writeWord("virtual ");
	};
	writeWord("void set" + s + " (" + f->type + ")");
	if (((Variable*) f)->isVirtual){
		writeWord(" = ()");
	};
	writeWord(";");
	endLine();
}

/* writing of PreStuff.h */


void Writer::writePreStuffH (){
	changeFile("PreStuff.h");
	writeIfndef("PRESTUFF");
	writeActionTypeH();
	endLine();
	writeWord("#endif");

};

void Writer::writeActionTypeH() {
	writeWord("enum ActionType {");
	list<ToLoad*> l = this->actions;
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		if (it != l.begin()) {writeWord(",");};
		writeWord("To"+ ActionName(
				((PreClass*)(*it))
		));
	};
	writeWord("};");
	endLine();
};



/* writing of PreStack.cc */


void Writer::writePreStackCC (){
	changeFile("PreStack.cc");
	writeInclude("PreStack.h");
	writeActionTypeCC();
};
void Writer::writeActionTypeCC() {
	writeWord("std::string stringOfActions(ActionType a) {");
	endLine();
	writeWord("switch (a) {");
	endLine();
	list<ToLoad*> l = this->actions;
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeWord("case To"+ ActionName(((PreClass*)(*it)))+ ":{");
		endLine();
		writeWord("return \""+ (((ToLoad*) (*it))->name)+ "\";}");
		endLine();
	};
	writeWord("default: \n //Should not happens \n return \"should not happen in stringofaction\"; \n  }; \n };");
	endLine();
	writeWord("std::list<SoN> SoNOfActions(ActionType a){");
	endLine();
	writeWord("	std::list<SoN> l;");
	endLine();
	writeWord("switch (a) {");
	endLine();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeWord("case To"+ ActionName(((PreClass*)(*it)))+ ":{");
		list<ToLoad*> fields = ((PreClass*)(*it))->fields.getTable();
		bool isBasic = true;
		for (list<ToLoad*>::iterator it2 = fields.begin(); it2 != fields.end(); ++it2) {
			Field* f = (Field*)(*it2);
			if (f->fieldtype == FT_Clickable) {
				if (isBasic) {
					debug("is basic " +f->name);
					isBasic = false;
				}
				else{
					ClickableType ct = ((Clickable*)f)->clickableType;
					if (ct == CT_NPC){
						writeWord("l.push_front(SON_NPC);" );
						endLine();
					}
					else if (ct == CT_Stuff){
						writeWord("l.push_front(SON_STUFF);" );
						endLine();
					};

				};
			};
		};
		endLine();
		writeWord("}; break;");
		endLine();
	};
	writeWord("default:  \n	//Should not happens \n	break; \n  }; \n return l; \n };");
	endLine();
	writeWord("Action* createAction(ActionType a,int basicStuff, std::list<boost::uuids::uuid> npcList, std::list<int> stuffList,LocalState* sim) {"
	);
	endLine();
	writeWord("switch (a) {");
	endLine();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		string name = ActionName(((PreClass*)(*it)));
		writeWord("case To"+ name + ":{");
		endLine();
		list<ToLoad*> fields = ((PreClass*)(*it))->fields.getTable();
		bool isBasic = true;
		for (list<ToLoad*>::iterator it2 = fields.begin(); it2 != fields.end(); ++it2) {
			Field* f = (Field*)(*it2);
			if (f->fieldtype == FT_Clickable) {
				if (isBasic) {
					isBasic = false;
					writeWord("int "+ f->name +" = basicStuff;");
					endLine();
				}
				else{
					ClickableType ct = ((Clickable*)f)->clickableType;
					if (ct == CT_Tile ) {
						writeWord("std::pair<int,int> " + f->name +"= sim->getCurrentTile();" );
						endLine();
					}
					else {
						string s ;
						if (ct == CT_Stuff) {s = "stuffList";}
						else {s = "npcList";};
						writeType(f);
						writeWord(" " +f->name +"= "+ s+".back();");
						endLine();
						writeWord(s+".pop_back();");
						endLine();
					};
				};
			};
		};
		writeWord("return (new "+ name + " (" );
		for (list<ToLoad*>::iterator it2 = fields.begin(); it2 != fields.end(); ++it2) {
			Field* f = (Field*)(*it2);
			if (f->fieldtype == FT_Clickable) {
				if (it2 != fields.begin()) {writeWord(", ");}
				writeWord(f->name);
			};
		};
		writeWord(", sim));");
		endLine();
		writeWord("};");
		endLine();
	};
	writeWord("default:\n	//Should not happens\n	return (new Action(\"fake\", sim));\n	break;\n   }; \n };");
	endLine();

};


/* writing StuffList.cc */

void Writer::writeStuffListCC(){
	changeFile("StuffList.cc");
	writeInclude("StuffList.h");
	for (list<ToLoad*>::iterator it = clickables.begin(); it != clickables.end();
			++it) {
		writeCCStuff ((PreClickable*) (*it));
	};
};

void Writer::writeCCStuff (PreClickable* c) {
	writeCommentName(((ToLoad*) c)->name);
	writeConstructorClickable( (PreClass*) c);
	list<ToLoad*> l = ((PreClass*) c)->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end();
			++it) {
		Field* f = (Field*) (*it);
		if (f->fieldtype == FT_Variable)
		{ writeGetAndSet(c,(Variable*) f);};
	};
	if (not c->isAbstract) {writeAbstractMessageClickable((PreClass*) c);};

};

void Writer::writeConstructorClickable(PreClass* p) {
	string s = ClickableName(p);
	writeWord(s);
	writeWord("::");
	writeWord(s);
	writeArguments(p);
	writeWord(")");
	if (p->herite != NULL) {
		writeWord(": ");
		writeWord(ClickableName(p->herite));
		writeWord(" (");
		list<ToLoad*> l2 = p->herite->toInitialised.getTable();
		for (list<ToLoad*>::iterator it = l2.begin(); it != l2.end(); ++it) {
			Field* f = (Field*) (*it);
			if (it != l2.begin()) {
				writeWord(", ");
			};
			Field* f2 =(Field*) p->fields.find(f->name);
			if (f2 == NULL) {
				writeWord(f->name);}
			else {
				writeWord("(");
				writeType(f);
				writeWord(") " + f2->initialisation);
			};
		};
		writeWord(") ");
	} else {
		writeWord(": Clickable () ");
	};
	writeWord("{");
	endLine();
	writeWord("((Clickable*)this)->name =  \"" + ((ToLoad*)p)->name +"\";"  );
	endLine();

	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (not ((f->fieldtype ==FT_Variable) && ((Variable*)f)->isVirtual )) {
			if (f->initialisation == "") {
				writeWord("this->");
				writeWord((*it)->name);
				writeWord(" = (");
				writeType(f);
				writeWord(")");
				writeWord((*it)->name);
			}
			else {
				writeWord("this->");
				writeWord((*it)->name);
				writeWord(" = (");
				writeType(f);
				writeWord(")(");
				writeWord(f->initialisation);
				writeWord(")");
			};
			writeWord(";");
			endLine();
		};
	};
	list<PreAction*> la = ((PreClickable*) p)->getActionPossible();
	for (list<PreAction*>::iterator it = la.begin(); it != la.end(); ++it) {
		writeWord("this->ActionTypePossible.push_back(ActionType::ToA_" + ((ToLoad*) (*it))->name + ");");
		endLine();

	};
	writeWord("};");
	endLine();

}
;

void Writer::writeAbstractMessageClickable(PreClass* p) {
	writeWord("AbstractMessage* " + ClickableName(p) + "::copy() {");
	endLine();
	writeWord("return (AbstractMessage*) new " + ClickableName(p) + "(*this);");
	endLine();
	writeWord("};");
	endLine();
};



void Writer::writeGet(PreClickable* c, Variable* v) {
	if (not v->isVirtual){
		writeWord (
				v->type
				+ " C_"
				+ ((ToLoad*) c)->name
				+ "::get"
				+ v->name
				+ " () {return this->"
				+ v->name
				+ ";};");
		endLine();
	};
};


void Writer::writeSet(PreClickable* c, Variable* v) {
	if (not v->isVirtual){
		writeWord (
				"void C_"
				+ ((ToLoad*) c)->name
				+ "::set"
				+ v->name
				+ " ( "
				+ v->type
				+ " "
				+ v->name
				+ " ) { this->"
				+ v->name
				+ " = ("
				+ v->type
				+ ")"
				+ v->name
				+";};"
		);
		endLine();
	};
};

void Writer::writeGetAndSet (PreClickable* c, Variable* v) {
	switch (v->variabletype) {
	case VT_BOTH:
		writeGet(c,v );
		writeSet(c,v);
		break;
	case VT_Get:
		writeGet(c,v);
		break;
	case VT_Set:
		writeSet(c,v);
		break;
	case VT_Nothing:
		break;
	default:
		break;
	};
};


/* writing StuffList.h */

void Writer::writeStuffListH(){
	changeFile("StuffList.h");
	writeIfndef("STUFFLIST");
	writeInclude("Stuff.h");
	writeInclude2("list");
	for (list<ToLoad*>::iterator it = clickables.begin(); it != clickables.end();
			++it) {
		writeHStuff ((PreClickable*) (*it));
	};
	endLine();
	writeWord("#endif");
};



void Writer::writeHStuff (PreClickable* p) {
	writeCommentName(((ToLoad*) p)->name);
	string s = ClickableName( (PreClass*) p);
	writeWord("class " + s + ": public ");
	if (p->herite == NULL){
		writeWord("Clickable");
	}
	else {
		writeWord("C_"+((ToLoad*) p->herite)->name);
	};
	writeWord(" {");
	endLine();
	writeWord(" public:");
	endLine();
	writeWord(s + " ");
	writeArguments(p);
	writeWord(");");
	endLine();
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (f->fieldtype== FT_Clickable)
		{writeWord("public:"); endLine();}
		else {
			switch (((Variable*)f)->variabletype) {
			case VT_BOTH:
				writeHGet(f);
				writeHSet(f);
				break;
			case VT_Get:
				writeHGet(f);
				break;
			case VT_Set:
				writeHSet(f);
				break;
			case VT_Nothing:
				break;
			default:
				break;
			}
			writeWord("protected:");
			endLine();
		};
		if (not ((f->fieldtype ==FT_Variable) && ((Variable*)f)->isVirtual )) {
			writeWord(f->type);
			writeWord(" ");
			writeWord(f->name);
			writeWord("; ");
			endLine();
		};
	};
	writeWord("//Serialization");
	endLine();
	writeWord("protected :");
	if (not p->isAbstract) {
		endLine();
		writeWord("virtual AbstractMessage* copy();");};
	endLine();
	if (not p->toInitialised.getTable().empty()) {writeWord( s +"(){};");};
	endLine();
	writeWord("SIMPLE_MESSAGE(" +s + ", ");
	if (p->herite == NULL ) { writeWord("Clickable");}
	else {writeWord ("C_" + (((ToLoad*)p->herite)->name));};
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (not ((f->fieldtype ==FT_Variable) && ((Variable*)f)->isVirtual )) {
			writeWord(", ");
			writeWord(f->name);
		};
	};

	writeWord(");");
	endLine();
	writeWord("};");
	endLine();
	if (p->isAbstract){
		writeWord("BOOST_SERIALIZATION_ASSUME_ABSTRACT("+s+");");
		endLine();
	};

};

/*writing ActionBoost.h*/

void Writer::writeActionBoostH () {
	changeFile("../network/ActionBoost.h");
	writeInclude2("boost/archive/text_iarchive.hpp");
	writeInclude2("boost/archive/text_oarchive.hpp");
	writeInclude2 ("boost/serialization/utility.hpp"); // nobody : i need it to serialise pair
	writeInclude ("boost/uuid/uuid_io.hpp");
	writeInclude ("boost/uuid/uuid_serialize.hpp");
	writeInclude("abstractMessage.h");
	writeInclude("netEvent.h");
	writeInclude("test/test_net.h");
	writeInclude("gameUpdate.h");
	writeInclude("scenario/Action.h");
	writeInclude("scenario/ActionsPC.h");
	writeInclude("scenario/ActionsTerro.h");
	writeInclude("scenario/NewMov.h");
	writeInclude("scenario/ScenarioAction.h");
	writeInclude("scenario/ScenarioActionList.h");
	writeInclude("interfaceinit/chat_event.h");
	writeInclude("abstractMessage.h");
	writeIfndef("ACTIONBOOST");
	writeBoost();
	writeWord("#endif");
};

void Writer::writeBoost(){
	list<ToLoad*> l =this->actions;
	for(list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeWord("BOOST_CLASS_EXPORT(A_" + (*it)->name + ");");
		endLine();
		writeWord("BOOST_CLASS_EXPORT(CoA_" + (*it)->name + ");");
		endLine();
	};
	list<ToLoad*> l2 =this->clickables;
	for(list<ToLoad*>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		writeWord("BOOST_CLASS_EXPORT(C_" + (*it2)->name + ");");
		endLine();
	};

};

/*writing ScenarioActionList.cc*/

void Writer::writeScenarioActionListCC(){
	changeFile("ScenarioActionList.cc");
	writeInclude("ScenarioActionList.h");
	for (list<ToLoad*>::iterator it = actions.begin(); it != actions.end();
			++it) {
		writeCommentName("Consequences of "+((ToLoad*)(*it))->name);
		writeSAConstructor((PreAction*) (*it));
		endLine();
		writeSACopy((PreAction*) (*it));
		endLine();
		writeSAAbstractMessage((PreAction*) (*it));
		endLine();
		writeSARun((PreAction*) (*it));
		endLine();
	};
};


void Writer::writeSAConstructor (PreAction* p) {
	string s = "Co" + ActionName(p);
	writeWord(s);
	writeWord("::");
	writeWord(s+ "(");
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		writeType(f);
		writeWord(" " + f->name);
		writeWord(", ");
	};
	writeWord("int playerID,Simulation* sim)");
	endLine();
	writeWord(": ScenarioAction(\""+((ToLoad*)p)->name+"\",playerID,sim){ ");
	endLine();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		if (f->initialisation == "") {
			writeWord("this->");
			writeWord((*it)->name);
			writeWord(" = (");
			writeType (f);
			writeWord(")");
			writeWord((*it)->name);
		} else {
			writeWord("this->");
			writeWord((*it)->name);
			writeWord(" = (");
			writeType (f);
			writeWord(")(");
			writeWord(f->initialisation);
			writeWord(")");
		};
		writeWord(";");
		endLine();
	};
	writeWord("};");
	endLine();
}
;
void Writer::writeSACopy(PreAction* p){
	string s = "Co" + ActionName(p);
	writeWord(s);
	writeWord("::");
	writeWord(s);
	writeWord ("(const "+ s + "& a) : ScenarioAction(\"" + ((ToLoad* )p)->name + "\",a.playerID, a.simulation){");
	endLine();
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		writeWord("this->"+ f->name + "= a." + f->name  + ";");
		endLine();
	};
	writeWord("};");
	endLine();
};

void Writer::writeSAAbstractMessage(PreAction* p ) {
	writeWord("AbstractMessage* Co" + ActionName((PreClass*)p) + "::copy() {");
	endLine();
	writeWord("return (AbstractMessage*) new Co" + ActionName((PreClass*)p) + "(*this);");
	endLine();
	writeWord("};");
	endLine();
};

void Writer::writeSARun (PreAction* p){
	string s = "Co" + ActionName(p);
	writeWord("void " + s + "::run () {");
	endLine();
	list<string> l = p->consequence;
	for (list<string>::iterator it = l.begin() ;it != l.end(); ++it) {
		writeWord((*it));
		endLine();
	};
	writeWord(";};");
	endLine();
}








/*writing ScenarioActionList.h*/

void Writer::writeScenarioActionListH(){
	changeFile("ScenarioActionList.h");
	writeInclude("PreScenarioActionList.h");
	writeIfndef("SCENARIOACTIONLIST");
	for (list<ToLoad*>::iterator it = actions.begin(); it != actions.end();
			++it) {
		writeSAH((PreAction*) (*it));
		endLine();

	};
	writeWord("#endif");
};

void Writer::writeSAH(PreAction* p) {
	string s = "Co" + ActionName(p);
	writeWord("class " + s + ": public ScenarioAction {");
	endLine();
	writeWord("public:");
	endLine();
	writeWord(s + "(");
	list<ToLoad*> l = p->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		writeType(f);
		writeWord(" " + f->name);
		writeWord(", ");
	};
	writeWord("int playerID,Simulation* s);");
	endLine();
	writeWord(s + "(const " + s + "&);");
	endLine();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		Field* f = (Field*) (*it);
		writeWord("public:");
		endLine();
		writeType (f);
		writeWord(" ");
		writeWord(f->name);
		writeWord("; ");
		endLine();
	};
	writeWord(
			"public: \n virtual void run (); \n  virtual AbstractMessage* copy();"
	);
	endLine();
	writeWord("protected :");
	endLine();
	writeWord("//Serialization");
	endLine();
	if (not p->toInitialised.getTable().empty()) {writeWord( s +"(){};");};
	endLine();
	writeWord("SIMPLE_MESSAGE(" + s +", ScenarioAction");
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeWord(", ");
		Field* f = (Field*) (*it);
		writeWord(f->name);
	};
	writeWord(");");
	endLine();
	writeWord("};");
}
;




void Writer::writeCommentName (string s) {
	endLine();
	writeWord( "/*********************************************************");
	endLine();
	writeWord( "** " + s + "**" );
	endLine();
	writeWord( "*********************************************************/");
	endLine();

};

string Writer::ActionName(PreClass* p) {
	return ("A_" + ((ToLoad*) p)->name);
}

void Writer::writeWord(string s) {
	*fichier << s;
}
;

void Writer::endLine() {
	*fichier << endl;
}
;


string Writer::ClickableName (PreClass* p){
	return ("C_"+ ((ToLoad*) p)->name);
};

/*writing Sauvegarde.txt*/
void Writer::writeSauvegardeTXT(){
	changeFile("sauvegarde.txt");
	for (list<ToLoad*>::iterator it = clickables.begin(); it != clickables.end();
			++it) {
		writeSClickable((PreClickable*) (*it));
	};
	for (list<ToLoad*>::iterator it = actions.begin(); it != actions.end();
			++it) {
		writeSAction((PreAction* ) (*it));
		endLine();
	};
};



void Writer::writeSField (Field* f) {
	writeWord(StringOfFT(f) +":" + f->name + ":" + f->type);
	if (f->initialisation != "") {writeWord(":"+ f->initialisation);}
	else if ((f->fieldtype ==FT_Variable) && ((Variable*)f)->isVirtual ) {
		writeWord(":V");
	}
	endLine();
};


void Writer::writeSAction(PreAction* a) {
	writeWord("+a:" + ((ToLoad*) a)->name );
	endLine();
	list<ToLoad*> l = ((PreClass*)a)->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeSField((Field*) (*it));
	};
	writeWord("I:" + a->isActionPossible);
	endLine();
	if (not a->consequence.empty()) {writeWord("E");};
	for (list<string>::iterator it = a->consequence.begin(); it != a->consequence.end(); ++it) {
		writeWord(":");
		writeWord((*it));
		endLine();
	};
	writeWord(";");

	endLine();
}
;


void Writer::writeSClickable(PreClickable* c) {
	writeWord("+c:" + ((ToLoad*) c)->name );
	endLine();
	list<ToLoad*> l = ((PreClass*)c)->fields.getTable();
	for (list<ToLoad*>::iterator it = l.begin(); it != l.end(); ++it) {
		writeSField((Field*) (*it));
	};
	writeWord(";");
	endLine();

}
;


//GENERATOR

Generator::Generator() {
	Loader actions;
	Loader clickables;
	this->actions = actions;
	this->clickables = clickables;
}
;

void Generator::clear() {
	if (this->actions.get() == NULL) {cout << "null" << endl;};
	cout << this->actions.getTable().size() << endl;
	this->actions.~Loader();
	cout << this->actions.getTable().size() << endl;
	if (this->actions.get() == NULL) {cout << "null" << endl;};
	this->clickables.~Loader();
	this->fields.~Loader();
};

void Generator::addAction(PreAction* a) {
	if (DEBUG) {cout << "on ADD ACTION dans le gen " << endl;};
	affiche(this->actions);
	this->actions.add((ToLoad*) a);
	affiche(this->actions);
	fields = ((PreClass*) a)->fields;
}
;

void Generator::addClickable(PreClickable* c) {
	clickables.add((ToLoad*) c);
	fields = ((PreClass*)c)->fields;
}
;


void Generator::AddIap(string s) {
	((PreAction*) (this->actions.get()))->isActionPossible = s;
}
;

void Generator::AddConsequence(string s) {
	((PreAction*) (this->actions.get()))->consequence.push_back(s);
}
;

PreAction* Generator::LoadAction(string name) {
	ToLoad* t = actions.Load(name);
	fields = ((PreClass*) this->actions.get())->fields;
	return (PreAction*) t;
}
;
PreClickable* Generator::LoadClickable(string name) {
	ToLoad* t = clickables.Load(name);
	fields = ((PreClass*) this->clickables.get())->fields;
	return (PreClickable*) t;
}
;

void Generator::AddActionField(Field* f) {
	PreAction* p = ((PreAction*) (this->actions.get()));
	((PreClass *)p)->add(f);
	if (p->firstfield) {
		p->firstfield = false;
		//ajoute l'action à l'object
		PreClickable* c = (PreClickable*) (this->clickables.find(f->type));
		if (c == NULL) {debug ("Pas trouver l'action dans add action field");}
		else {c->addAction(p);}
	};
}
;

void Generator::AddClickableField(Field* f) {
	ToLoad* c = this->clickables.get();
	((PreClass*) c)->add(f);
}
;

void Generator::write() {
	if (DEBUG) {cout << "lààà" << endl;}
	affiche(this->actions);
	Writer w = Writer(this->actions.getTable(),this->clickables.getTable());
	w.write();
}
;



//reader

ReadBlocker::ReadBlocker(char delimiter,std::ifstream* fichier){
	this->delimiter = delimiter;
	this->fichier = fichier;
};

void ReadBlocker::readBlock(string buffer) {
	debug ("read block");
	debug (buffer);
	debug ("read block.2");

	treatName(buffer);

	if (not (getline(*fichier, buffer))) {
		debug ("read block.3");

		if (DEBUG) {cout << "fin de page avant fin de block " << endl;};
	}
	while (not ((buffer)[0] == delimiter)) {
		this->readLine( buffer);
		if (not (getline(*fichier, buffer))) {
			if (DEBUG) {cout << "fin de page avant fin de block " << endl;};
		};
	};
}
;

readLiner::readLiner() {
	position = 0;
	length = 0;
}
;

void readLiner::readLine(string s) {
	debug("read liner read the line");
	position = 0;
	debug(s);
	length = s.length();
	while (position < length) {
		debug("read liner dans la boucle");
		position = this->readField(position, s);
	};
}
;

readFielder::readFielder(char delimiter) {
	this->delimiter = delimiter;
	this->position = 0;
}
;

int readFielder::readField(int initialPosition, string str) {
	debug("read fielder read the field");
	this->position = initialPosition;
	int n = str.length();
	int i = 0;
	while ((position < n) && (not (str[position] == delimiter))) {
		position++;
		i++;
	};
	char s[i];
	int p = str.copy(s, i, initialPosition);
	s[p] = '\0'; //ON FAIT UN SUBSTRING
	this->onAField(s);
	return (position + 1);
}
;

//My reader

stackFieldReader::stackFieldReader(char delimiter) :	readFielder(delimiter) {

}
;

void stackFieldReader::setstack(list<string>* s) {
	this->stack = s;
}
;


void stackFieldReader::onAField(char* s) {
	debug ("on push "+ ((string) s));
	stack->push_back((string) s);
	debug ("on a push "+ ((string) s));

}
;

stackLineReader::stackLineReader( char delimiter) : readLiner() , rf ( delimiter){

}
;

void stackLineReader::setstack(list<string>* s) {
	this->stack = s;
	this->rf.setstack(s);
}
;

int stackLineReader::readField(int initialPosition, string s) {
	debug( "stackLineReader::readField");
	return (rf.readField(initialPosition, s));
}
;

stackBlockReader::stackBlockReader(char blockDelimiter, char fieldDelimiter,std::ifstream* fichier, string buffer) :
																																																																							ReadBlocker(blockDelimiter, fichier),
																																																																							rl (fieldDelimiter)
{
	this->stack = new list<string>;
	rl.setstack(this->stack);
}
;
void stackBlockReader::readLine(string s) {

	this->rl.readLine(s);
	this->onALine(stack);
	stack->clear();
}
;

void stackBlockReader::setstack(list<string>* s) {
	this->stack = s;
	this->rl.setstack(s);
}
;

ActionCreator::ActionCreator(Generator* g, char blockDelimiter,char fieldDelimiter, std::ifstream* fichier, string buffer) :
																																																																					stackBlockReader(blockDelimiter, fieldDelimiter, fichier, buffer),
																																																																					nameTreater (':') {
	this->generator = g;
	this->nameTreater.setstack(this->stack);

};



string ActionCreator::ById (Clickable* c) {
	ClickableType ct = c->clickableType;
	switch (ct) {
	case CT_Stuff:
			return ("(((C_"+c->type+"*)(&((Simulation*)this->simulation)->getItemByID<C_"+c->type+">(this->"+c->name+"))))");
	case CT_NPC:
		return ("(this->simulation->getNPCByID(this->"+c->name+"))");
	case CT_Tile:
		return ("((Tile*) ((Simulation*)this->simulation)->getMap()->getTile(this->"+ c->name +"))");
	default:
		return ("trololol");
		break;
	}
	return ("trololol");
};

string ActionCreator::ById (string name){
	return ById((Clickable*) ((PreClass*)(this->generator->actions.get()))->fields.find(name));
};

string ActionCreator::get (string name, string toget) {
	return ("(" +ById(name) +")->get"+toget+"()");
};



string ActionCreator::generateIAP (list<string>* l) {
	string s;
	string t ;
	while (l->size() > 0) {
		t = l->front();
		// P : isInThePack; G : get, T :  this, D : distance
		if (t== "P") {  //TODO assert l->size > 0
			l->pop_front();
			s = s + "isInThePack (this->simulation,this->" + l->front() + ")";
		}
		else if (t== "G") {  //TODO assert l->size > 1
			l->pop_front();
			string name = l->front();
			l->pop_front();
			s = s + get(name,l->front());
		}
		else if (t== "T") {  //TODO assert l->size > 0
			l->pop_front();
			s = s + ById(l->front()) ;
		}
		else if (t== "D") {  //TODO assert l->size > 0
			l->pop_front();
			s = s + "distance (this->simulation," + ById(l->front()) + ")";
		}
		else {s = s+ t;};
		l->pop_front();
	}
	return s;
};

void ActionCreator::treatName(string s) {
	debug ("treat name");
	list<string>* l = this->stack;
	debug ("treat name.2");

	this->nameTreater.readLine(s);
	debug ("treat name.3");
	//TODO tester la string quand on pop;
	l->pop_front(); //enleve le "+a"
	string name = l->front();
	l->pop_front();
	PreAction* a = new PreAction(name);
	if (DEBUG) {cout << "là add " + name << endl;};
	this->generator->addAction(a);
};
void ActionCreator::onALine(list<string>* l) {
	if (l->size() >= 2) {
		string fts = l->front();
		l->pop_front();
		FieldType ft = FTOfString (fts);
		if (ft == FT_IAP ) {
			generator->AddIap(generateIAP(l));
		}
		else if (ft == FT_Consequence) {
			generator->AddConsequence(l->front());
			l->pop_front();
		}
		else{
			string name = l->front();
			l->pop_front();
			string type = l->front();
			l->pop_front();
			if (l->size() == 0) {
				if (ft == FT_Clickable) {
					Field* f = (Field*) (new Clickable(name, type));
					this->generator->AddActionField(f);
				}
				else {
					Variable* v = new Variable (VTOfString(fts), name,type);
					this->generator->AddActionField((Field*)v);
				}
			}
			else {
				string init = l->front();
				l->pop_front();
				if (ft == FT_Clickable) {
					Field* f = (Field*) (new Clickable (name, type , init));
					this->generator->AddActionField(f);
				}
				else {
					Variable* v = new Variable (VTOfString(fts), name,type,init);
					this->generator->AddActionField((Field*)v);
				}
			};
		};
	}
	else {
		if (DEBUG) {cout << "pas bonne taille" << endl;};
	};
}
;

// Clickable creator


ClickableCreator::ClickableCreator(Generator* g, char blockDelimiter,char fieldDelimiter, std::ifstream* fichier, string buffer) :
																																																																							stackBlockReader(blockDelimiter, fieldDelimiter, fichier, buffer),
																																																																							nameTreater (':'){
	this->generator = g;
	this->nameTreater.setstack(this->stack);
};

void ClickableCreator::treatName(string s) {
	this->nameTreater.readLine(s);
	list<string>* l = this->stack;
	debug ("treat name.3");

	//TODO tester la string quand on pop;
	l->pop_front();
	debug ("treat name.3.1");

	string name = l->front();
	l->pop_front();
	debug ("treat name.4");

	if (l->size() == 0) {
		PreClickable*  c= new PreClickable(name);
		this->generator->addClickable(c);
		debug ("treat name.5");

	}
	else {
		string heritage = l->front();
		l->pop_front();
		PreClickable* c= new PreClickable(name,(PreClass*)this->generator->LoadClickable(heritage));
		this->generator->addClickable(c);
		debug ("treat name.6");

	};
};

void ClickableCreator::onALine(list<string>* l) {
	if (l->size() > 2) {
		string fts = l->front();
		FieldType ft = FTOfString (fts);
		l->pop_front();
		string name = l->front();
		l->pop_front();
		string type = l->front();
		l->pop_front();
		if (l->size() == 0) {
			if (ft == FT_Clickable) {
				Field* f = (Field*) (new Clickable (name, type));
				this->generator->AddClickableField(f);
			}
			else {
				Variable* v = new Variable (VTOfString(fts), name,type);
				this->generator->AddClickableField((Field*)v);
			}
		}
		else {
			string init = l->front();
			l->pop_front();
			if (ft == FT_Clickable) {
				Field* f = (Field*) (new Clickable (name, type , init));

				this->generator->AddClickableField(f);
			}
			else {
				Variable* v = new Variable (VTOfString(fts), name,type,init);
				if (init == "V") {
					v->isVirtual = true;
					((PreClickable*) (this->generator->clickables.get()))->isAbstract = true;
				};
				this->generator->AddClickableField((Field*)v);


			}

		};
	}
	else {
		if (DEBUG) {cout << "pas bonne taille" << endl;};
	};
}
;


MainReader::MainReader(Generator* g, char addChar, char blockDelimiter, char fieldDelimiter, string& fichier) :
																														ac (g, blockDelimiter, fieldDelimiter,this->fichier, buffer), cc (g, blockDelimiter, fieldDelimiter,this->fichier, buffer)
{
	this->generator = g;
	this->fichier= new ifstream (fichier.c_str());
	// pour des questions de droits que je ne peux pas utiliser un ifstream&
	//et il est plus facile de modifier un ifstream*
	ac.fichier = this->fichier;
	cc.fichier = this->fichier;
	this->addChar = addChar;
	string bu;
	this->buffer = bu;
}
;

void MainReader::readLine() {
	debug ("read line");
	if (buffer.length() == 0) {
		if (DEBUG) {cout << "vide" << endl;};
	} else {
		if ((buffer[0]) == this->addChar) {
			if ((buffer[1]) == 'a') {
				ac.readBlock(buffer);
			}
			else if ((buffer[1]) == 'c') {
				cc.readBlock(buffer);
			}
			else {
				if (DEBUG) {cout << "pas un block" << endl;};
			};
		};
	};
}
;

void MainReader::read() {
	if ((fichier != NULL) &&(fichier->is_open())) {
		while (getline(*fichier, buffer)) {
			this->readLine();
			if (DEBUG) {cout << "chaque ligne on affiche" << endl;};
			affiche(this->generator->actions);
		};
		fichier->close();
		//delete fichier;
	} else {
		if (DEBUG) {cout << "le fichier n'existe pas  " << endl;};
	};
}
;
