#include "../include/Being.h"

Companion::Companion()
{
	ID = 0;
	Name = "NULL";
	Type = "Companion";
	Level = 0;
	Health = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Strength = 0;
	Intelligence = 0;
	Agility = 0;
	Experience = 0;
	Opinion = 0;
	Gold = 0;
	LevelReq = 30;

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	InCombat = false;
	Stealthed = true;
}
void Companion::Reset()
{
	ID = 0;
	Name = "NULL";
	Type = "Companion";
	Level = 0;
	Health = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Strength = 0;
	Intelligence = 0;
	Agility = 0;
	Experience = 0;
	Opinion = 0;
	Gold = 0;
	LevelReq = 30;

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;
	
	InCombat = false;
	Stealthed = true;

	EquippedWeapon.Reset();
	for (int i = 0; i < 7; i++)
		EquippedArmor[i].Reset();
	for (int i = 0; i < MAX_EFFECTS; i++)
		Effect[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		wInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		aInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		pInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		sInventory[i].Reset();

}
Companion::Companion(int id, string name, string title, string type, int level, int health, int mana, int strength, int intelligence, int agility, int opinion)
{
	ID = id;
	Name = name;
	Title = title;
	Type = type;
	Level = level;
	Health = health;
	MaxHealth = health;
	Mana = mana;
	MaxMana = mana;
	Strength = strength;
	Intelligence = intelligence;
	Agility = agility;
	Experience = 0;
	Opinion = opinion; 
	LevelReq = 30;

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	for (int i = 0; i < Level; i++)
		LevelReq += (LevelReq / 2) + (Level * 5);
	Gold = 0;

	InCombat = false;
	Stealthed = true;
}
void Companion::Mutate(Companion companion)
{
	ID = companion.idGet();
	Name = companion.nameGet();
	Title = companion.titleGet();
	Type = companion.typeGet();
	levelSet(companion.levelGet());
	Health = companion.healthGet();
	MaxHealth = companion.maxHealthGet();
	Mana = companion.manaGet();
	MaxMana = companion.maxManaGet();
	Strength = companion.strengthGet();
	Intelligence = companion.intGet();
	Agility = companion.agilityGet();
	Experience = companion.expGet();
	Opinion = companion.opinionGet();
	LevelReq = companion.levelReqGet();
	Gold = companion.goldGet(); 
	ypos = 0;

	EquippedWeapon.idTransform(companion.EquippedWeapon.idGet());
	for (int i = 0; i < INVENTORY_SIZE; i++)
		EquippedArmor[i].idTransform(companion.EquippedArmor[i].idGet());
	for (int i = 0; i < MAX_SPELLS; i++)
		spell[i].Mutate(*companion.getSpell(i));
}
Companion::~Companion(){}

void Companion::Attack(Player* hero)
{
	int enemyCount = 0;
	for (int i = 0; i < ENEMY_LIMIT; i++)
	{
		if (hero->Opponent[i].nameGet() != "NULL")
			enemyCount++;
	}

	int random = rand() % enemyCount;
	while (hero->Opponent[random].healthGet() <= 0 || hero->Opponent[random].Stealthed)
		random = rand() % enemyCount;

	srand(time(NULL));
	int damage = Strength + EquippedWeapon.damageGet() + (rand() % 3 - 1);
	int chance = rand() % 100 + 1;
	int crit = (Agility + (Strength / 3) + (Intelligence / 2) * 2) - hero->Opponent[random].agilityGet();
	int miss = hero->Opponent[random].agilityGet() - Agility;

	for (int i = 0; i < MAX_EFFECTS; i++)
	{	//Checks and applies debuffs/buffs relevant to combat
		if (getEffect(i)->typeGet() == "Accuracy")
			miss -= getEffect(i)->valueGet();
		if (getEffect(i)->typeGet() == "+Damage")
			damage += getEffect(i)->valueGet();
		if (hero->Opponent[random].Effect[i].typeGet() == "Armor")
			damage -= hero->Opponent[random].getEffect(i)->valueGet();
		if (hero->Opponent[random].getEffect(i)->typeGet() == "Avoid")
			miss += 80;
	}

	if (miss >= chance)
	{
		mvprintw(hero->yPosGet(), 0, "%s misses!", Name.c_str()); hero->yPosAdd(2);
		SleepC(1000);
		return;
	}
	if (crit >= chance)
	{
		mvprintw(hero->yPosGet(), 0, "Critical hit!!"); hero->yPosAdd(1);
		damage *= 1.5;
	}
	hero->Opponent[random].healthMod(-damage);
	mvprintw(hero->yPosGet(), 0, "%s hits %s for %i health", Name.c_str(), hero->Opponent[random].nameGet().c_str(), damage);
	printw("! (%i/%i", hero->Opponent[random].healthGet(), hero->Opponent[random].maxHealthGet());
	ColoredString(" hp", HealthColorCode(&hero->Opponent[random]));
	printw(")\n"); hero->yPosAdd(2);

	SleepC(1000);
}

void Companion::viewStatus()
{
	clear();
	printw("STATUS\n\n");
	printw("Name: \t%s\n", Name.c_str());
	printw("Level \t%i %s\n", Level, Type.c_str());

	if (EquippedWeapon.nameGet() != "NULL")
		printw("Weapon:\t%s\n", EquippedWeapon.nameGet().c_str());

	for (int i = 0; i < 7; i++)
	{
		if (EquippedArmor[i].nameGet() != "NULL")
		{
			printw("%i", EquippedArmor[i].slotGet());
			if (EquippedArmor[i].slotGet() == 0)
				printw("Head");
			if (EquippedArmor[i].slotGet() == 1)
				printw("Neck");
			if (EquippedArmor[i].slotGet() == 2)
				printw("Shoulders");
			if (EquippedArmor[i].slotGet() == 3)
				printw("Chest");
			if (EquippedArmor[i].slotGet() == 4)
				printw("Leggs");
			if (EquippedArmor[i].slotGet() == 5)
				printw("Gloves");
			if (EquippedArmor[i].slotGet() == 6)
				printw("Boots");

			printw(":\t%s\n", EquippedArmor[i].nameGet().c_str());
		}
	}
	printw("Health:\t%i/%i\n", Health, MaxHealth);
	printw("Mana:\t%i/%i\n\n", Mana, MaxMana);
	printw("Attributes: \n%i STR\t%i INT\t%i AGI\n\n", Strength, Agility, Intelligence);
	Pause(); clear();
}
int Companion::opinionGet(){
	return Opinion;
}
int Companion::idGet(){
	return ID;
}

void Companion::opinionSet(int opinion){
	Opinion = opinion;
}
void Companion::opinionMod(int opinion){
	Opinion += opinion;
}

void Companion::idMutate(int id)
{
	//ID, Name, Type, Level, Health, Mana, Strength, Intelligence, Agility, Opinion
	Companion Soldier(1, "Soldier", "Private", "Companion", 1, 15, 0, 3, 0, 1, 0);
	Companion Golem(2, "Stone Golem", "Elemental", "Conjured", 3, 20, 0, 3, 0, 0, 0);
	Companion Gerald(3, "Gerald", "Lieutenant", "Companion", 3, 30, 5, 5, 2, 4, 5);
	Companion AchalioVessel(4, "Achalios Vessel", "Lich", "Companion", 3, 25, 10, 2, 5, 0, -5);

	Soldier.EquippedArmor[3].idTransform(6);
	Gerald.EquippedArmor[3].idTransform(6);
	Gerald.EquippedArmor[0].idTransform(30);
	Gerald.EquippedWeapon.idTransform(1);

	if (id == 1)
		Mutate(Soldier);
	if (id == 2)
		Mutate(Golem);
	if (id == 3)
		Mutate(Gerald);
	if (id == 4)
		Mutate(AchalioVessel);
}
void Companion::expGive(int exp)
{
	if (Type == "Companion")
	{
		Experience += exp;
		if (Experience >= LevelReq)
		{
			Experience -= LevelReq;
			LevelReq += (LevelReq / 2) + (Level * 5);
			Level++;
			printw("%s has gained a level!\n", Name.c_str());

			if (Level % 2 == 1)
			{
				strMod(1);
				intMod(1);
			}
			else
			{
				strMod(1);
				agiMod(1);
			}
		}
	}
}
void Companion::levelSet(int level) 
{
	Level = level;
	LevelReq = 30;
	for (int i = 1; i < level; i++)
		LevelReq += (LevelReq / 2) + (Level * 5);
}