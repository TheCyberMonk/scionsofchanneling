#include <iostream>
#include <string>
using namespace std;

class Being;

class Spell
{
private:
	int ID;
	string Name;
	string Class;
	string Aspect;
	string Type;
	string Chant;
	string Description;
	int Impact; // Damage, healing etc.
	double FullImpact;
	int EffectID;
	int ManaCost;
	int IntelligenceReq;
	bool Combat;
	bool QuickAction;

	double AspectMod;
	double AttributeMod;
	double EssenceMod;
public:
	Spell();
	Spell(int id, string name, string class_, string aspect, string type, bool combat, bool quick, string desc, string chant, int impact, double aspectmod, double attmod, double essencemod, int effectid, int cost, int intreq);
	~Spell();

	string nameGet();
	string classGet();
	string aspectGet();
	string descGet();
	string typeGet();
	string castGet();
	int impactGet();
	int effectGet();
	int costGet();
	int intReqGet();
	int idGet();
	bool inCombat();
	bool quickAction();

	double aspectModGet();
	double attModGet();
	double essenceModGet();

	void spellSet(int id, string name, string class_, string aspect, string type, bool combat, bool quick, string desc, string chant, int impact, double aspectmod, double attmod, double essencemod, int effectid, int cost, int lvlreq);
	void nameSet(string);
	void classSet(string);
	void typeSet(string);
	void impactSet(int);
	void effectSet(int);
	void costSet(int);
	void lvlReqSet(int);

	bool Cast(Player* player, Being* caster, Being* target, bool Self, bool scroll);
	void Mutate(Spell);
	void idTransform(int);
	void Reset();
};