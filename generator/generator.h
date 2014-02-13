#ifndef GENERATOR_H
#define GENERATOR_H
#include <string>
#include <list>
#include <utility>
#include<fstream>
using namespace std;

//loader
class ToLoad {
public:
	string name;
	ToLoad(string);
};

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

void affiche (Loader);

//field et preclass

enum FieldType {FT_Clickable, FT_Variable, FT_IAP, FT_Consequence};
enum VariableType {VT_Nothing,VT_Get,VT_Set,VT_BOTH};
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
// pourra etre mis private: mais il faut pouvoir iterer
	Loader fields;
	PreClass* herite ;
	Loader toInitialised;
};

class PreAction : public PreClass {
public:
	PreAction (string name);
	string isActionPossible;
	bool* firstfield;
	string consequence;
};


class PreClickable : public PreClass {
public:
	PreClickable (string name);
	PreClickable (string name, PreClass* p);
	void addAction (PreAction*);
	list<PreAction*> getActionPossible();
private:
	list<PreAction*> actionPossible;
};

//writer

class Writer {
public:
	Writer (list<ToLoad*>,list<ToLoad*>);
	void write ();
private:
	void changeFile (string);
	void writeAuthor ();
	void writeInclude (string);
	void writeInclude2 (string);
	void writeIfndef (string);
	list<ToLoad*> actions;
	list<ToLoad*> clickables;
	void writeCommentName (string);
	void writeAction(PreClass*);
	void writeHAction(PreClass*);
	void writeStufflistcc (PreClickable* );
	void writeHGet (Field* f);
	void writeHSet (Field* f);
	void writeStuffh (PreClickable*);
	void writeType (Field* f) ;
	void writeArguments(PreClass*);
	void writeWord(string);
	void endLine ();
	ofstream* fichier;
	void writeActionTypeH();
	void writeActionTypeCC();
	void writeSAction(PreAction*);
	void writeGet(PreClickable* c, Variable* v);
	void writeSet(PreClickable* c, Variable* v);
	void writeGetAndSet(PreClickable* c, Variable* v);
	void writeCCconstructeur (PreClass*);
	void writeCopy (PreClass*);
	void writeDoAction (PreClass*);
	void writeAddPendingAction(PreClass*);
	void writeIsActionPossible(PreAction*);
	void writeAbstractMessage (PreClass* p);
	void writeSerialisation (PreClass* p);
	string ActionName (PreClass*);
	string ClickableName (PreClass*);
	void writeSClickable(PreClickable*);
	void writeConstructorClickable(PreClass*);
	void writeBoost();
};


class Generator {
public :
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
//private: need to be public
	Loader clickables;
	Loader actions;
	Loader fields;
};

// reader

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

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

class ForStringGenerator {
public:
	int fieldNeeded;
	char toSwitch;

};

class StringGenerator {
public:
	StringGenerator();
	string generate(list<string>*);
protected:
	string result;
	int fieldNeeded;
};

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
