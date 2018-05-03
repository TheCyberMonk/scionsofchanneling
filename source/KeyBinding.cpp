#include "../include/Being.h"

KeyBinding::KeyBinding()
{
	Number = 0;
	Type = "NULL";
	ID = 0;
}
KeyBinding::KeyBinding(int number, string type, int id)
{
	Number = number;
	Type = type;
	ID = id;
}
KeyBinding::~KeyBinding(){}

void KeyBinding::Reset()
{
	Number = 0;
	Type = "NULL";
	ID = 0; 
}

int KeyBinding::keyGet()
{
	return Number;
}
string KeyBinding::nameGet()
{
	if (Type == "Spell")
		return spell.nameGet(); 
	if (Type == "Scroll")
		return scroll.nameGet();
	if (Type == "Potion")
		return potion.nameGet();
	if (Type == "Weapon")
		return weapon.nameGet();
	if (Type == "Armor")
		return armor.nameGet();

	return "NULL";
}
string KeyBinding::typeGet()
{
	return Type;
}
int KeyBinding::idGet()
{
	return ID;
}

void KeyBinding::numberSet(int number)
{
	Number = number;
}
void KeyBinding::typeSet(string type)
{
	Type = type;
}
void KeyBinding::idSet(int id)
{
	ID = id;

	if (Type == "Spell")
		spell.idTransform(id);
	if (Type == "Scroll")
		scroll.idTransform(id);
	if (Type == "Potion")
		potion.idTransform(id);
	if (Type == "Weapon")
		weapon.idTransform(id);
	if (Type == "Armor")
		armor.idTransform(id);
}

void KeyBinding::setBinding(int number, string type, int id)
{
	Number = number;
	Type = type;
	ID = id;

	if (Type == "Spell")
		spell.idTransform(id);
	if (Type == "Scroll")
		scroll.idTransform(id);
	if (Type == "Potion")
		potion.idTransform(id);
	if (Type == "Weapon")
		weapon.idTransform(id);
	if (Type == "Armor")
		armor.idTransform(id);
}