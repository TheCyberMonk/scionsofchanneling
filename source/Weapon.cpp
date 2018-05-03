#include "../include/Being.h"

Weapon::Weapon()
{
	ID = 0;
	Name = "NULL";
	Type = weapon;
	SubType = "NULL";
	Description = "You have no weapon equipped...";
	Damage = 0;
	MagicEssence = 0;
	Value = 0;
}
Weapon::Weapon(int id, string name, string type, string desc, int damage, int magic, int value)
{
	ID = id;
	Name = name;
	Type = weapon;
	SubType = type;
	Description = desc;
	Damage = damage;
	MagicEssence = magic;
	Value = value;
}
Weapon::~Weapon(){}

int Weapon::pickUp(Being* being)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (being->Inventory[i].nameGet() == "NULL") {
			being->Inventory[i].Transform(*this);
			return i;
		}
	}
	if(being->typeGet() == "Player")
	{
		int selection = ChooseWeapon("Your inventory is full, choose an item to replace.", &*being, being->wInventory, false);
		if (selection != -1)
		{
			being->wInventory[selection].Transform(*this);
			return selection;
		}
		return -1;
	}
	return -1;
}
void Weapon::Use(Being* being)
{
	if (Question(&*being, "Do you wish to equip the " + Name + '?')) 
	{
		being->equipWeapon(this);
		mvprintw(being->yPosGet(), 0, "Weapon equipped!"); being->yPosAdd(1);
	}
}

int Weapon::damageGet(){
	return Damage;
}
int Weapon::magicGet(){
	return MagicEssence;
}

void Weapon::damageSet(int damage){
	Damage = damage;
}
void Weapon::magicSet(int magic){
	MagicEssence = magic;
}

void Weapon::Transform(Weapon weapon)
{
	ID = weapon.idGet();
	Name = weapon.nameGet();
	SubType = weapon.typeGet();
	Description = weapon.descGet();
	Damage = weapon.damageGet();
	MagicEssence = weapon.magicGet();
	Value = weapon.valueGet();
}
void Weapon::Reset()
{
	ID = 0;
	Name = "NULL";
	Description = "You have no weapon equipped...";
	Damage = 0;
	MagicEssence = 0;
	Value = 0;
}
void Weapon::Status(Being* being)
{
	int y = 0; int x = 0;
	bool Equipped = false;
	if(being->InCombat)
	{
		y = being->yPosGet() + 1;
	}
	else
		y = 9;

	mvprintw(y, x, "%s", Name.c_str()); y++;
	mvprintw(y, x, "Damage: %i", Damage); y++;
	if (MagicEssence > 0)
		mvprintw(y, x, "Magic Essence: %i", MagicEssence); y++; 
	mvprintw(y, x, "%s", Description.c_str()); y++; 
	
	if (Question(&*being, "Do you wish to equip the " + Name + '?')) 
	{
		y += 2;
		being->equipWeapon(this);
		mvprintw(y, x, "Weapon equipped!");
		Equipped = true;
	}
	int cy, cx;
	getyx(stdscr, cy, cx); 

	int oy = 9;
	if(being->InCombat)
		oy = being->yPosGet();
	
	if(Equipped)
		SleepC(1500);

	for(int i = cy; i >= oy; i--)
	{
		move(i, x);
		deleteln();
	}
}

void Weapon::idTransform(int id)
{
	//ID, Name, Type, Desc, Dmg, Magic, Value
	Weapon IronMace(1, "Iron Mace", "1H Mace", "A solid mace made from iron. \nThe mace is quite old, and the spikes are dull.", 3, 0, 10);
	Weapon OakStaff(2, "Oak Staff", "Staff", "A staff made from oak, infused with magic essence", 1, 2, 10);
	Weapon Broadsword(3, "Broadsword", "2H Sword", "A wide sturdy blade forged in iron..", 4, 0, 30);
	Weapon Sword(36, "Short Sword", "1h Sword", "A short sword, a light, piercing melee weapon", 2, 0, 2);

	/*
	Weapon Dagger(3, "Small Dagger", "Dagger", "A normal dagger, nothing unusual about it.", 2, 0, 2);
	Weapon FireGun(4, "Fire Gun", "1H Gun", "An ancient fire weapon. Made with techniques long since lost.\nIt's in a very poor state, but should still hold together for some time.", 3, 0, 10);
	Weapon Pitchfork(5, "Pitchfork", "Staff", "A standard pitchfork used for farming.", 1, 0, 1);
	Weapon BloodSword(50, "Blood Broadsword", "2H Sword", "A great weapon infused with the blood of a powerful demon.", 15, 3, 1500);
	*/

	if (id == 1)
		Transform(IronMace);
	if (id == 2)
		Transform(OakStaff);
	if (id == 3)
		Transform(Broadsword);
	if (id == 36)
		Transform(Sword);
}