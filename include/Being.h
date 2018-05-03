#include "Library.h"

#define BEING_H
#ifdef BEING_H

class Companion;

enum Type{PC, NPC, Monster};

class Being
{
public:
	Being();
	Being(string name, string title, string type, int level, int health, int mana, int strength, int intelligence, int agility, int exp, int gold);
	~Being();

	//Access Functions
	string nameGet();
	string titleGet();
	string typeGet();
	int strengthGet();
	int intGet();
	int agilityGet();
	int healthGet();
	int maxHealthGet();
	int manaGet();
	int maxManaGet();
	int goldGet();
	int levelGet();
	int expGet();
	int essenceGet();
	int levelReqGet();
	int yPosGet();
	int xPosGet();

	//Active Functions
	void Talk(Being* hero, string, bool cls1, bool cls2, bool pause, int speed);
	virtual void Attack(Player* hero);
	bool killCheck(Being*, Being*);

	//Mutator Functions
	void Reset();
	void nameSet(string);
	void titleSet(string);
	void typeSet(string);
	void healthSet(int);
	void healthMod(int);
	void maxHealthSet(int);
	void manaSet(int);
	void manaMod(int);
	void maxManaSet(int);
	void strSet(int);
	void strMod(int);
	void intSet(int);
	void intMod(int);
	void agiSet(int);
	void agiMod(int);
	void goldSet(int);
	void goldMod(int);
	void expSet(int);
	void expGive(int);
	void levelSet(int);
	void yPosAdd(int);
	void yPosReset();
	void yPosSet(int);
	void xPosAdd(int, int);
	void xPosReset();
	void xPosSet(int);
	void yResetSet(int);
	void xResetSet(int);

	//Item Functions
	void equipWeapon(Weapon*);
	void equipWeapon(int);
	virtual void equipArmor(Armor*);
	Item pickupItem(int id);
	int pickupWeapon(Weapon);
	int pickupArmor(Armor);
	int pickupPotion(Potion, int);
	int pickupScroll(Scroll);
	int pickupTome(SpellTome);
	Weapon* getWeapon();
	Armor* getArmor(int);
	Potion getPotion(int);
	Scroll* getScroll(int);

	virtual void addCompanion(int);
	virtual Companion getCompanion(int);
	virtual void addLoot(int i, int id, int drop);
	virtual int lootGet(int i);
	virtual int dropGet(int i);

	bool InCombat;
	bool Stealthed;
	bool hasCompanion;
	bool Unconscious;
	int CombatTurn;

	Weapon wInventory[9];
	Weapon* wPointer[9] = { &wInventory[0], &wInventory[1], &wInventory[2], &wInventory[3], &wInventory[4], &wInventory[5], &wInventory[6], &wInventory[7], &wInventory[8] };
	Armor aInventory[9];
	Armor* aPointer[9] = { &aInventory[0], &aInventory[1], &aInventory[2], &aInventory[3], &aInventory[4], &aInventory[5], &aInventory[6], &aInventory[7], &aInventory[8] };
	Potion pInventory[9];
	Potion* pPointer[9] = { &pInventory[0], &pInventory[1], &pInventory[2], &pInventory[3], &pInventory[4], &pInventory[5], &pInventory[6], &pInventory[7], &pInventory[8] };
	Scroll sInventory[9];
	Scroll* sPointer[9] = { &sInventory[0], &sInventory[1], &sInventory[2], &sInventory[3], &sInventory[4], &sInventory[5], &sInventory[6], &sInventory[7], &sInventory[8] };
	SpellTome tInventory[9];
	SpellTome* tPointer[9] = { &tInventory[0], &tInventory[1], &tInventory[2], &tInventory[3], &tInventory[4], &tInventory[5], &tInventory[6], &tInventory[7], &tInventory[8] };
	Item Inventory[9];
	Item* iPointer[9] = { &Inventory[0], &Inventory[1], &Inventory[2], &Inventory[3], &Inventory[4], &Inventory[5], &Inventory[6], &Inventory[7], &Inventory[8] };
	Spell spell[9];
	Spell scrollSpell;
	Status Effect[9];

	Status* getEffect(int);
	bool hasEffect(string);
	int addEffect(int);

	Spell* getSpell(int);
	int learnSpell(int);

private:
protected:
	// Member Variables
	string Name;
	string Type;
	string Title;
	Weapon EquippedWeapon; 
	Armor EquippedArmor[9];

	int Health;
	int MaxHealth;
	int Mana;
	int MaxMana;

	int Strength;
	int Intelligence;
	int Agility;

	int Level;
	int LevelReq;
	int Experience;
	int Gold;
	
	int ypos;
	int xpos;
	int yReset;
	int xReset;
};

class Companion : public Being
{
public:
	Companion();
	Companion(int id, string name, string title, string type, int level, int health, int mana, int strength, int intelligence, int agility, int opinion);
	~Companion();

	void Attack(Player* hero);
	void Reset();
	void Mutate(Companion);

	void opinionSet(int);
	void opinionMod(int);
	void idMutate(int);
	void expGive(int);
	void levelSet(int);

	void viewStatus();
	int opinionGet();
	int idGet();
private:
	int ID;
	int Opinion;
};

class Enemy : public Being
{
public:
	Enemy();
	Enemy(int id, string name, string attack, string desc, int health, int mana, int intelligence, int spellID, int strength, int agility, int experience, int gold);
	~Enemy();

	void viewStatus();
	int idGet();
	string descGet();
	string attackDescGet();
	bool nameTrueGet();

	void setAttackDesc(string);
	void addLoot(int i, int id, int dropchance);
	int lootGet(int i);
	int dropGet(int i);

	void Attack(Player* hero);
	void nameTrue();
	void Mutate(Enemy enemy);
	void idMutate(int);
	void Reset();

private:
	int ID;
	string Description;
	string AttackDescription;
	bool Named; //Determines if the enemy is named or is a normal monster of a type. It helps with formulating combat text.
	int Loot[10];
	int Drop[10];
};

class Player : public Being
{
public:
	Player();
	Player(string name, string setclass, int health, int mana, int strength, int intelligence, int agility, int gold);
	~Player();

	Companion Party[5];
	Enemy Opponent[9];
	KeyBinding Binding[25];
	int TutorialState;
	bool RunningPossible;
	bool ActionUsed;
	bool ExtraActionUsed;
	bool RageUsed;

	void viewStatus();
	string classGet();
	bool stageGet(int);
	int varGet(int);

	void Attack(Player* hero);
	void Inspect(Enemy*);
	void spellDisplay();
	bool spellCast(Being*[9], Companion*[5]);
	void equipArmor(Armor*);
	bool inventoryDisplay();
	void addCompanion(int);
	Companion getCompanion(int);
	void setBinding();
	bool keyBindingCheck(int);

	void Reset();
	void classSet(string);
	void stageSet(int, bool);
	void stageFlip(int);
	void stageReset(int);
	void varSet(int, int);
	void varMod(int, int);
	void varReset(int);
	void expGive(int);
	void levelSet(int);
private:
	string Class;
	bool Stage[100];
	int Variable[100];
};

#endif BEING_H