#include "../include/Being.h"

Status::Status()
{
	ID = 0;
	Name = "NULL";
	Type = "NULL";
	Value = 0;
	IntelligenceModifier = 0;
	Variance = 0;
	Time = 0;
}
Status::Status(int id, string name, string type, int value, int intmod, int variance, int time)
{
	ID = id;
	Name = name;
	Type = type;
	Value = value;
	IntelligenceModifier = intmod;
	Variance = variance;
	Time = time;
}
void Status::Transform(Status* status)
{
	ID = status->idGet();
	Name = status->nameGet();
	Type = status->typeGet();
	Value = status->valueGet();
	IntelligenceModifier = status->intModGet();
	Variance = status->varianceGet();
	Time = status->timeGet();
}
void Status::Reset()
{
	ID = 0;
	Name = "NULL";
	Type = "NULL";
	Value = 0;
	IntelligenceModifier = 0;
	Variance = 0;
	Time = 0;
}
Status::~Status(){}

int Status::idGet(){
	return ID;
}
string Status::nameGet(){
	return Name;
}
string Status::typeGet(){
	return Type;
}
int Status::valueGet(){
	return Value;
}
int Status::intModGet(){
	return IntelligenceModifier;
}
int Status::varianceGet(){
	return Variance;
}
int Status::timeGet(){
	return Time;
}

void Status::modTime(Being* being, Being* hero, int value)
{
	Time += value;
	if (Time < 0)
	{
		mvprintw(hero->yPosGet(), 0, "%s fades from %s.", Name.c_str(), being->nameGet().c_str());
		hero->yPosAdd(1);

		if (this->typeGet() == "Strength")
			being->strMod(-this->valueGet()); 
		if (this->typeGet() == "Agility") 
			being->agiMod(-this->valueGet());
		if (this->typeGet() == "Intelligence")
			being->intMod(-this->valueGet());
		Reset();
	}
}
void Status::modValue(int var){
	Value += var;
}
void Status::setValue(int value){
	Value = value;
}

void Status::idTransform(int id)
{ 
	//ID, Name, Type, Value, IntelligenceMod, Variance, Time
	Status BlurredVision(1, "Blurred Vision", "Accuracy", -30, 0, 0, 2);
	Status WeakPoison(2, "Poison", "Damage", 2, 0, 0, 2);
	Status Regen(3, "Regeneration", "Heal", 1, 4, 1, 4);
	Status Corruption(4, "Corruption", "Damage", 1, 5, 0, 3);
	Status Prone(5, "Knocked prone", "Stun", 0, 0, 0, 1);
	Status Barrier(6, "Mana Barrier", "Armor", 3, 5, 0, 4);
	Status Enchant(7, "Enchant Weapon", "+Damage", 1, 0, 0, 10);
	Status Dodge(8, "Dodge", "Avoid", 75, 0, 0, 0);
	Status Strike(9, "Stunning Strike", "Stun", 0, 0, 0, 1);
	Status Strength(10, "Enhanced Strength", "Strength", 2, 0, 0, 10);
	Status Rage(11, "Rage", "Strength", 0, 0, 0, 10);
	Status Uninhibited(12, "Uninhibited", "Strength", 1, 0, 0, 2);
	Status Drunk(13, "Drunk", "Intelligence", -1, 0, 0, 20);

	if (id == 1)
		Transform(&BlurredVision);
	if (id == 2) 
		Transform(&WeakPoison);
	if (id == 3) 
		Transform(&Regen);
	if (id == 4) 
		Transform(&Corruption);
	if (id == 5)
		Transform(&Prone);
	if (id == 6)
		Transform(&Barrier);
	if (id == 7)
		Transform(&Enchant);
	if (id == 8)
		Transform(&Dodge);
	if (id == 9)
		Transform(&Strike);
	if (id == 10)
		Transform(&Strength);
	if (id == 11)
		Transform(&Rage);
	if (id == 12)
		Transform(&Uninhibited);
	if (id == 13)
		Transform(&Drunk);
}