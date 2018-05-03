#include "../include/Being.h"

Potion::Potion()
{
	ID = 0;
	Name = "NULL";
	Type = potion;
	SubType = "NULL";
	Description = "NULL";
	Healing = 0;
	Amount = 0;
	StackSize = 0;
	Value = 0;
}
void Potion::Reset()
{
	ID = 0;
	Name = "NULL";
	SubType = "NULL";
	Description = "NULL";
	Healing = 0;
	Amount = 0;
	StackSize = 0;
	Value = 0;
}
Potion::Potion(int id, string name, string type, string desc, int heal, int stacksize, int value)
{
	ID = id;
	Name = name;
	Type = potion;
	SubType = type;
	Description = desc;
	Healing = heal;
	Amount = 0;
	StackSize = stacksize;
	Value = value;
}
void Potion::Transform(Potion potion)
{
	ID = potion.idGet();
	Name = potion.nameGet();
	SubType = potion.typeGet();
	Description = potion.descGet();
	Healing = potion.healingGet();
	Amount = potion.amountGet();
	StackSize = potion.stackSizeGet();
	Value = potion.valueGet();
}
Potion::~Potion(){}

int Potion::healingGet(){
	return Healing;
}
void Potion::healingSet(int healing){
	Healing = healing;
}

int Potion::amountGet(){
	return Amount;
}
void Potion::amountMod(int var)
{
	Amount += var;
	if (Amount <= 0)
		Reset();
}
void Potion::amountSet(int var){
	Amount = var;
}
int Potion::stackSizeGet(){
	return StackSize; 
}

void Potion::Use(Being* hero, Being* Consumer)
{
	if (Name != "NULL")
	{
		if (Consumer->typeGet() == "Player"){
			mvprintw(hero->yPosGet(), 0, "You drink the potion and regain %i %s.", Healing, SubType.c_str()); hero->yPosAdd(2);
		}
		else{
			mvprintw(hero->yPosGet(), 0, "You make %s drink the potion, he regains %i %s.", Consumer->nameGet().c_str(), Healing, SubType.c_str()); hero->yPosAdd(2);
		}
		SleepC(1500);
		if (SubType == "Health")
			Consumer->healthMod(Healing);
		if (SubType == "Mana") 
			Consumer->manaMod(Healing);
		if (SubType == "Strength")
			Consumer->addEffect(10);	//Only 2 as value, make more flexible?

		Amount -= 1;
		if (Amount == 0)
			Reset();
	}

}
bool Potion::Status(int y, int x)
{
	if(y == -1)
		y = CurrentY();
	if(x == -1)
		x = CurrentX();

	mvprintw(y, x, "%s", Name.c_str()); y++;
	mvprintw(y, x, "Healing: %i health", Healing); y++;
	mvprintw(y, x, "Value: %i gold", Value); y++;
	bool answer = Question(y, x, "Use it?", false); y++;
	ClearX(y, x);

	return answer; 
}

void Potion::idTransform(int id)
{
	if (id == 7)
	{
		Potion smallHealthPotion(7, "Small Health Potion", "Health", "A standard magical potion contained in a small glass vial", 10, 5, 5);
		Transform(smallHealthPotion);
	}
	if (id == 8)
	{
		Potion smallManaPotion(8, "Small Mana Potion", "Mana", "A standard magical potion contained in a small glass vial", 10, 5, 10);
		Transform(smallManaPotion);
	}
	if (id == 34)
	{
		Potion HealthPotion(34, "Health Potion", "Health", "A standard magical potion contained in a glass vial", 20, 5, 15);
		Transform(HealthPotion);
	}
	if (id == 35)
	{
		Potion ManaPotion(35, "Mana Potion", "Mana", "A standard magical potion contained in a glass vial", 20, 5, 20);
		Transform(ManaPotion);
	}
	if (id == 38)
	{
		Potion StrengthElixir(38, "Elixir of Strength", "Strength", "Increases strength temporarily by +2", 2, 5, 20);
		Transform(StrengthElixir);
	}
}