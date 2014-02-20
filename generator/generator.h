#ifndef GENERATOR_H
#define GENERATOR_H
#include <string>
#include <list>
#include <utility>
#include<fstream>
using namespace std;

/*J'ai laissé 4 pointeurs dans le generateur :

Les classes qui héritent de Toload car il a vocation à être stocké sous forme de liste et repéré par un pointeur
Le stack (mes fonctions marchent par effet de bord sur cet objet)
le generateur (qui contient les loader et qui doit donc être passé )
les ifstream et ofstream (j'ai des problèmes de droit si je les passe en référence)
*/
//loader

//classe qui sert à être stoquée
class ToLoad {
public:
	string name;
	ToLoad(string);
};


//c'est une liste dans la quelle on stoque des toload et qui a un état courant
class Loader {
public :
	Loader () ;
	~Loader () ;
	Loader copy();
	ToLoad* Load (string);
	void add (ToLoad*);
	ToLoad* get ();
	list<ToLoad*> getTable () ;
	ToLoad* find (string);
	void erase (string);
private :
	ToLoad* current;
	list<ToLoad*> table;

};

//pour les tests
void affiche (Loader);

//field et preclass

//une préclass sert à stoquer les information avant de créeer une classe
//ces éléments sont des fields

//il y a 4 types de fields
enum FieldType {
	FT_Clickable, //un clockable
	FT_Variable, //bool, int ,float
	FT_IAP, //pour implémenter isactionpossible()
	FT_Consequence //pour implémenter la fonction run d'une scenarioactionlist
};

//le type de la variable dit ce qu'on peut faire dessus:
enum VariableType {
	VT_Nothing, //Rien
	VT_Get, //Get
	VT_Set, //Set
	VT_BOTH //Les deux
};

//Les clickables peuvent être de trois type différents
enum ClickableType {CT_NPC,CT_Tile,CT_Stuff};


class Field : public ToLoad {
public:
	Field (FieldType, string name, string type);
	Field (FieldType, string name, string type,string initialisation);
	string type;
	string initialisation;
	FieldType fieldtype;

};

class Variable : public Field {
public:
	Variable (VariableType, string name, string type);
	Variable (VariableType, string name, string type,string initialisation);
	VariableType variabletype;
	bool isVirtual;
	//Une variable peut être "virtuelle" on peut la set ou get avec des méthodes virtuelles
	//dans ce cas la classe qui la contient est abstraite
};

class Clickable : public Field {
public:
	Clickable (string name, string type);
	Clickable (string name, string type,string initialisation);
	ClickableType clickableType;
};


class PreClass : ToLoad{
public:
	PreClass (string name);
	PreClass (string name,PreClass* herite);
	void add(Field*);
	// ON doit pouvoir iterer là dessus donc on les laisse public
	Loader fields;
	PreClass* herite ;
	Loader toInitialised;
};

class PreAction : public PreClass {
public:
	PreAction (string name);
	string isActionPossible;
	bool firstfield; //on a besoin de savoir si on a eu ou non un premier field pour ajouter l'action possible au premier
	list<string> consequence;
};


class PreClickable : public PreClass {
public:
	PreClickable (string name);
	PreClickable (string name, PreClass* p);
	void addAction (PreAction*);
	bool isAbstract; //contain a virtual
	list<PreAction*> getActionPossible();
private:
	list<PreAction*> actionPossible;
};

//writer : il écrit dans les différents fichiers

class Writer {
public:
	Writer (list<ToLoad*>,list<ToLoad*>);
	void write ();
private:
	list<ToLoad*> actions;
	list<ToLoad*> clickables;
	ofstream* fichier;

/*need to write*/
	void changeFile (string);
	void writeAuthor ();
	void writeInclude (string);
	void writeInclude2 (string);
	void writeIfndef (string);
	void writeCommentName (string);
	void writeType (Field* f) ;
	void writeArguments(PreClass*);
	void writeWord(string);
	void endLine ();
	string ActionName (PreClass*);
	string ClickableName (PreClass*);



	/* writing of ActionsTerro.cc */
	void writeActionTerroCC();
	void writeAction(PreClass*); /*for one action*/
	void writeCCconstructeur (PreClass*);
	void writeCopy (PreClass*);
	void writeDoAction (PreClass*);
	void writeAddPendingAction(PreClass*);
	void writeIsActionPossible(PreAction*);
	void writeAbstractMessage (PreClass* p);

	/* writing of ActionsTerro.h */
	void writeActionTerroH();
	void writeHAction(PreClass*); /*for one action*/
	void writeHGet (Field* f);
	void writeHSet (Field* f);

	/* writing PreStuff.h */
	void writePreStuffH();
	void writeActionTypeH();


	/* writing PreStack.cc */
	void writePreStackCC();
	void writeActionTypeCC();

	/* writing StuffList.h */

	void writeStuffListH();
	void writeHStuff (PreClickable*); /*on a clickable*/

	/* writing StuffList.cc */
	void writeStuffListCC();
	void writeCCStuff (PreClickable* ); /*on a clickable*/
	void writeConstructorClickable(PreClass*);
	void writeGet(PreClickable* c, Variable* v);
	void writeSet(PreClickable* c, Variable* v);
	void writeGetAndSet(PreClickable* c, Variable* v);
	void writeAbstractMessageClickable (PreClass* p);

	/* writing ActionBoost.h */
	void writeActionBoostH();
	void writeBoost();

	/*writing ScenarioActionList.cc*/
	void writeScenarioActionListCC();
	void writeSAConstructor (PreAction*);
	void writeSACopy (PreAction*);
	void writeSAAbstractMessage(PreAction*);
	void writeSARun(PreAction*);

	/*writing ScenarioActionList.h*/
	void writeScenarioActionListH();
	void writeSAH(PreAction*);

	/*writing Sauvegarde.txt*/
	void writeSauvegardeTXT();
	void writeSAction(PreAction*);
	void writeSClickable(PreClickable*);
	void writeSField (Field* f);




};

//Generator : il génère les actions

class Generator {
public :
	void clear ();
	Generator () ;
	void write () ;
	void addAction (PreAction*);
	void addClickable (PreClickable*);
	PreClickable* LoadClickable (string);
	PreAction* LoadAction (string);
	void AddActionField (Field*);
	void AddClickableField (Field*);
	void AddIap (string);
	void AddConsequence (string);
	Loader clickables;
	Loader actions;
	Loader fields;
};

// reader : parse un fichier

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;


// tout ceci est  un ensemble de parseur général
/* On décompose un fichier en
 *bloc
 *line
 *field
 */
/*
 chaqu'une des classes est utile pour lire ces différentes parties et appelle une classe plus petite pour lire sa sous partie
 */



class Reader {
public:
	virtual void read ()=0;
};

class ReadBlocker {
public:
	ReadBlocker (char,std::ifstream*);
	void readBlock(string);
	std::ifstream* fichier;

protected:
	virtual void readLine(string )=0;
	char delimiter;
	virtual void treatName (string)=0;
};
class readLiner {
public :
	readLiner ();
	void readLine(string s );
protected :
	int length ;
	virtual int readField(int initialPosition,string)=0;
	int position;
};

class readFielder {
public :
	readFielder (char delimiter);
	int  readField (int initialPosition,string);
protected:
	char delimiter;
	int position;
	virtual void onAField (char*)=0 ;
};

//my reader
/*ici je suis moins général et stoque chaque field dans une stakc*/

class stackFieldReader : public readFielder {
public:
	stackFieldReader (char delimiter);
	void onAField (char*);
	void setstack (list<string>*);
private:
	list<string>* stack;
};

class stackLineReader : public  readLiner {
public:
	stackLineReader (char delimiter);
	void setstack (list<string>*);
private :
	list<string>* stack;
	stackFieldReader rf;
	int readField(int initialPosition,string);
};

class stackBlockReader : public ReadBlocker {
public:
	stackBlockReader (char blockDelimiter,char fieldDelimiter, std::ifstream* fichier , string buffer);
	void setstack (list<string>*);
	void readLine(string);

protected:
	list<string>* stack;

private:
	stackLineReader rl;
	virtual void onALine (list<string>* ) = 0;
};


/*mes reader vont créer action et clickable à l'aide du générateur*/
class ActionCreator : public stackBlockReader {
public :
	ActionCreator(Generator* g, char blockDelimiter, char fieldDelimiter, std::ifstream* fichier , string buffer);
private:
	Generator* generator;
	string ById (string name);
	string ById (Clickable*);
	string get (string name, string toget);
	void onALine (list<string>*) ;
	string generateIAP (list<string>*) ;
	void treatName (string);
	stackLineReader nameTreater;
};

class ClickableCreator : public stackBlockReader {
public :
	ClickableCreator(Generator* g, char blockDelimiter, char fieldDelimiter, std::ifstream* fichier , string buffer);
private:
	Generator* generator;
	void onALine (list<string>*) ;
	void treatName (string);
	stackLineReader nameTreater;
};


class MainReader  {
public:
	MainReader (Generator* g, char addchar, char blockDelimiter, char fieldDelimiter, string& fichier );
	void read ();
private:
	Generator* generator;
	void readLine();
	char addChar;
	std::ifstream* fichier;
	string buffer;
	ActionCreator ac;
	ClickableCreator cc;
};


#endif
