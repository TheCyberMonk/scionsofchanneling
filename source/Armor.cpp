#include "../include/Being.h"

#pragma region Initializers

Armor::Armor()
{
	ID = 0;
	Name = "NULL";
	Type = armor;
	SubType = "NULL";
	Slot = Head;
	Description = "NULL";
	Defence = 0;
	MagicDefence = 0;
	MagicEssence = 0;
	Value = 0;
}
void Armor::Reset()
{
	ID = 0;
	Name = "NULL";
	SubType = "NULL";
	Slot = Head;
	Description = "NULL";
	Defence = 0;
	MagicDefence = 0;
	MagicEssence = 0;
	Value = 0;
}
Armor::Armor(int id, string name, string type, EqSlot slot, string desc, int defence, int magic, int mdefence, int value)
{
	ID = id;
	Name = name;
	Type = armor;
	SubType = type;
	Slot = slot;
	Description = desc;
	Defence = defence;
	MagicDefence = mdefence;
	MagicEssence = magic;
	Value = value;
}
void Armor::Transform(Armor armor)
{
	ID = armor.idGet();
	Name = armor.nameGet();
	SubType = armor.typeGet();
	Slot = armor.slotGet();
	Description = armor.descGet();
	Defence = armor.defenceGet();
	MagicDefence = armor.magicDefenceGet();
	MagicEssence = armor.magicGet();
	Value = armor.valueGet();
}
Armor::~Armor() {}
#pragma endregion

EqSlot Armor::slotGet(){
	return Slot;
}
int Armor::defenceGet(){
	return Defence;
}
int Armor::magicGet(){
	return MagicEssence;
}
int Armor::magicDefenceGet(){
	return MagicDefence;
}

void Armor::defenceSet(int defence){
	Defence = defence;
}
void Armor::magicSet(int magic){
	MagicEssence = magic;
}
void Armor::magicDefenceSet(int mdefence){
	MagicDefence = mdefence;
}

void Armor::Status(Being* being)
{
	int y = 0; int x = 0; 
	bool Equipped = false;
	if(being->InCombat)
	{
		y = being->yPosGet() + 1;
	}
	else
		y = 9;

	mvprintw(y, x, "%s\n", Name.c_str());
	if (Defence > 0)
		printw("Defence: %i\n", Defence);
	if (MagicEssence > 0)
		printw("Magic Essence: %i\n", MagicEssence);
	if (MagicDefence > 0) 
		printw("Magic Defence: %i\n", MagicDefence);
	printw("\n%s\n", Description.c_str());	
	
	if (Question(being, "Do you wish to equip the " + Name + '?'))
	{
		being->equipArmor(this);
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
void Armor::Use(Being* being)
{
	if (Question(being, "Do you wish to equip the " + Name + '?'))
	{
		being->equipArmor(this);
	}
}


void Armor::idTransform(int id) 
{
	Armor Leather(4, "Leather Cuirass", "Leather", Chest, "Made from animal hides, it's sturdy and of decent quality.", 2, 0, 0, 20);
	Armor Robes(5, "Tattered Robes", "Cloth", Chest, "These robes are quite worn out, but a previous wearer seem to have \nimprinted some magical essence into them.", 0, 2, 1, 20);
	Armor IronArmor(6, "Iron Armor", "Iron", Chest, "Standard armor made out of iron.", 3, 0, 0, 70);
	Armor LeatherCap(30, "Leather Cap", "Leather", Head, "Basic head protection, looks kinda silly though.", 1, 0, 0, 30);
	Armor LeatherGloves(31, "Leather Gloves", "Leather", Gloves, "Some standard leather gloves", 1, 0, 0, 40);
	Armor LeatherPads(32, "Leather Shoulder Pads", "Leather", Shoulders, "Bulky shoulder pads, to protect those important joints", 1, 0, 0, 45);
	Armor LeatherLeggings(33, "Leather Leggings", "Leather", Leggs, "Some standard leather leggings", 1, 0, 0, 50);

	if (id == 4)
		Transform(Leather);
	if (id == 5)
		Transform(Robes);
	if (id == 6)
		Transform(IronArmor);
	if (id == 30)
		Transform(LeatherCap);
	if (id == 31)
		Transform(LeatherGloves);
	if (id == 32)
		Transform(LeatherPads);
	if (id == 33)
		Transform(LeatherLeggings);
}