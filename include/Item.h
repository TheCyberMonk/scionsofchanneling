#include <iostream>
#include <string>
using namespace std;

enum EqSlot { Head, Neck, Shoulders, Chest, Leggs, Gloves, Boots };
enum ItemType { armor, weapon, spellscroll, potion, tome, other };

#ifndef ITEM_H
#define ITEM_H

class Being;
class Player;

class Item
{
protected:
	int ID;
	string Name;
	ItemType Type;
	string SubType;
	string Description;
	int Value;
private:
public:
	Item();
	Item(int, string, ItemType, string, string, int);
	~Item();

	int pickUp(Being* being);
	void Use(Being* being);

	int idGet();
	string nameGet();
	string descGet();
	string typeGet();
	int valueGet();

	void idSet(int);
	void nameSet(string);
	void descSet(string);
	void typeSet(string);
	void valueSet(int);

	void Status(Being* being);
	//virtual void Status(Being* being){};
	void Transform(Item);
	virtual void idTransform(int) {};
	virtual void Use(void);
	void Reset();
};

class Weapon : public Item
{
protected:
	bool Ranged; //NYI
	int Damage;
	int MagicEssence;
private:
public:
	Weapon();
	Weapon(int, string, string, string, int, int, int);
	~Weapon();

	int pickUp(Being* being);
	void Use(Being* being);

	void Status(Being* being);
	void Reset();

	int damageGet();
	int magicGet();

	void damageSet(int);
	void magicSet(int);

	void Transform(Weapon);
	void idTransform(int);
};

class Armor : public Item
{
protected:
	//int Slot;
	EqSlot Slot;
	int Defence;
	int MagicDefence;
	int MagicEssence; 
private:
public:
	Armor();
	Armor(int id, string name, string type, EqSlot slot, string desc, int defence, int magic, int mdefence, int value);
	~Armor();

	void Use(Being* being);

	void Status(Being*);
	void Reset();

	EqSlot slotGet();
	int defenceGet();
	int magicDefenceGet();
	int magicGet();

	void defenceSet(int);
	void magicDefenceSet(int);
	void magicSet(int);

	void Transform(Armor);
	void idTransform(int);
};

class Potion : public Item
{
private:
	int Healing;
	int Amount;
	int StackSize;
protected:
public:
	Potion();
	Potion(int id, string name, string type, string desc, int heal, int stacksize, int value);
	~Potion();

	bool Status(int y, int x);
	void Reset();
	void Use(Being* hero, Being* consumer);

	int healingGet();
	void healingSet(int);

	int amountGet();
	void amountSet(int);
	void amountMod(int);
	int stackSizeGet();

	void Transform(Potion);
	void idTransform(int);
};

class Scroll : public Item
{
public:
	Scroll();
	Scroll(int id, int spellid, string name, string type, string desc, int value);
	~Scroll();

	bool Status(Being* hero, bool vendor);

	bool Use(Player*, Being*, Being*, Being*[10]);

	void Transform(Scroll);
	void idTransform(int);

	int spellIDGet();

private:
	int SpellID;
}; 

class SpellTome : public Item
{
public:
	SpellTome();
	SpellTome(int id, int spellid, string name, string type, string desc, int value);
	~SpellTome();

	bool Status(Being* hero, bool vendor);
	void Use(Player*);

	void Transform(SpellTome);
	void idTransform(int);

	int spellIDGet();

private:
	int SpellID;
};
#endif ITEM_H