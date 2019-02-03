#include "../include/Being.h"

Enemy::Enemy()
{
	ID = 0;
	Name = "NULL";
	Type = "Enemy";
	AttackDescription = "NULL";
	Health = 0;
	Mana = 0;
	Strength= 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Intelligence = 0;
	Agility = 0; 
	Experience = 0;
	Gold = 0;

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	for (int i = 0; i < 10; i++)
	{
		Loot[i] = 0;
		Drop[i] = 0; 
	}

	Named = false;
	InCombat = false;
	Stealthed = false;
}
Enemy::Enemy(int id, string name, string attack, string desc, int health, int mana, int intelligence, int spellID, int strength, int agility, int experience, int gold)
{
	ID = id;
	Name = name;
	Type = "Enemy";
	Description = desc;
	AttackDescription = attack;
	Health = health;
	MaxHealth = health;
	Mana = mana;
	MaxMana = mana;
	Intelligence = intelligence;
	Strength = strength;
	Agility = agility;
	Experience = experience;
	Gold = gold;
	learnSpell(spellID);

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	for (int i = 0; i < 10; i++)
	{
		Loot[i] = 0;
		Drop[i] = 0;
	}

	Named = false;
	InCombat = false;
	Stealthed = false;
}
void Enemy::Mutate(Enemy enemy)
{
	ID = enemy.idGet();
	Name = enemy.nameGet();
	Description = enemy.descGet();
	AttackDescription = enemy.attackDescGet();
	Health = enemy.healthGet();
	MaxHealth = enemy.maxHealthGet();
	Mana = enemy.manaGet();
	MaxMana = enemy.maxManaGet();
	Intelligence = enemy.intGet();
	Strength = enemy.strengthGet();
	Agility = enemy.agilityGet();
	Experience = enemy.expGet();
	Gold = enemy.goldGet();

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	for (int i = 0; i < MAX_SPELLS; i++)
		spell[i].Mutate(*enemy.getSpell(i));
	for (int i = 0; i < MAX_EFFECTS; i++)
		Effect[i].Transform(enemy.getEffect(i));

	for (int i = 0; i < 10; i++)
	{
		Loot[i] = enemy.lootGet(i);
		Drop[i] = enemy.dropGet(i);
	}

	Named = enemy.nameTrueGet();
}
void Enemy::Reset()
{
	ID = 0;
	Name = "NULL";
	Health = 0;
	Mana = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Intelligence = 0;
	Strength = 0;
	Agility = 0;
	Experience = 0;
	Gold = 0;
	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	Named = false;

	for (int i = 0; i < MAX_SPELLS; i++)
		spell[i].Reset();
	for (int i = 0; i < MAX_EFFECTS; i++)
			Effect[i].Reset();
	for (int i = 0; i < 10; i++)
	{
		Loot[i] = 0;
		Drop[i] = 0;
	}
}
Enemy::~Enemy(){}

void Enemy::setAttackDesc(string attack){
	AttackDescription = attack;
}

void Enemy::addLoot(int i, int id, int drop)
{
	Loot[i] = id;
	Drop[i] = drop;
}
int Enemy::lootGet(int i){
	return Loot[i];
}
int Enemy::dropGet(int i){
	return Drop[i];
}

int Enemy::idGet(){
	return ID;
}
string Enemy::attackDescGet(){
	return AttackDescription;
}
string Enemy::descGet(){
	return Description;
}
bool Enemy::nameTrueGet(){
	return Named;
}
void Enemy::nameTrue(){
	Named = true;
}


void Enemy::Attack(Player* hero)
{
	int y, x, my, mx;
	getyx(stdscr, y, x);
	getmaxyx(stdscr, my, mx);
	int ty = y - my;

	if(ty+5 > my)
	{
		move(x, hero->yPosGet());
	}

	int aliveCount = 1;
	for (int i = 0; i < FOLLOWER_LIMIT; i++)
	{
		if (hero->Party[i].healthGet() > 0)
			aliveCount++;
	}

	srand(time(NULL));
	int selection = 0;
	Being* target = &*hero;

	int j = 1;
	while (j != selection)
	{
		selection = rand() % aliveCount;
		if (selection == 0)
			break;

		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (hero->Party[i].healthGet() > 0)
			{
				target = &hero->Party[i];
				j++;

				if (j == selection)
					break;
			}
		}
	}

	double damage = (Strength * 2) + EquippedWeapon.damageGet() + (rand() % 3 - 1);
	int spellcount = 0;
	int chance = rand() % 100 + 1;
	int crit = (Agility + (Strength / 3) + (Intelligence / 2) * 2) - target->agilityGet();
	int miss = target->agilityGet() - Agility;
	bool crithit = false;
	bool targetRaged = false;

	if (chance <= crit && damage > 0)
	{
		mvprintw(hero->yPosGet(), 0, "Critical hit!!"); hero->yPosAdd(1);
		damage = ((Strength * 2) + EquippedWeapon.damageGet() + (rand() % 3 - 1)) * 1.5;
		crithit = true;
	}

	for (int i = 0; i < 7; i++)
		damage -= target->getArmor(i)->defenceGet();


	for (int i = 0; i < MAX_EFFECTS; i++)
	{	//Checks and applies debuffs/buffs relevant to combat
		if (getEffect(i)->typeGet() == "Accuracy")
			miss -= getEffect(i)->valueGet();
		if (target->Effect[i].typeGet() == "Armor")
			damage -= target->getEffect(i)->valueGet();
		if (target->getEffect(i)->typeGet() == "Avoid")
			miss += target->getEffect(i)->valueGet();
		if (target->getEffect(i)->nameGet() == "Rage")
			targetRaged = true;
	}
	for (int i = 0; i < MAX_SPELLS; i++)
	{
		if (getSpell(i)->nameGet() != "NULL")
			spellcount++;
	}
	if (damage < 0) { damage = 0; }

	int action = rand() % 4;
	if (chance <= miss && crithit == false)
	{
		mvprintw(hero->yPosGet(), 0, "%s attacks ", Name.c_str()); hero->yPosAdd(2);
		if (target->typeGet() == "Player") 
		{ 
			printw("you"); 
		}
		else 
		{ 
			printw("%s", target->nameGet().c_str());
		}
		printw(", but misses!");
	}
	else if (spellcount != 0)
	{
		for (int i = 0; i < spellcount; i++)
		{
			if (getSpell(i)->typeGet() == "Heal" && rand() % 4 != 0)
			{
				if (Health <= (MaxHealth / 2))
				{
					getSpell(i)->Cast(hero, &*this, &*this, false, false);
					return;
				}
				for (int j = 0; j < ENEMY_LIMIT; j++)
				{
					if (hero->Opponent[j].healthGet() <= (hero->Opponent[j].maxHealthGet() / 2))
					{
						getSpell(i)->Cast(hero, &*this, &hero->Opponent[j], false, false);
						return;
					}
				}
			}
			if (getSpell(i)->typeGet() == "Dispel" && rand() % 4 != 0)
			{
				for (int j = 0; j < ENEMY_LIMIT; j++)
				{
					for (int n = 0; n < MAX_EFFECTS; n++)
					{
						if(hero->Opponent[j].getEffect(n)->typeGet() == "Damage")
						{
							getSpell(i)->Cast(hero, &*this, &hero->Opponent[j], false, false);
							return;
						}
					}
				}
			}
		}
		if (action != 0)
		{
			bool effectActive = false;
			action = rand() % spellcount;
			if (Mana >= getSpell(action)->costGet())
			{
				if (getSpell(action)->typeGet() == "+Effect" || getSpell(action)->typeGet() == "SelfBuff")
				{
					for (int n = 0; n < MAX_EFFECTS; n++)
					{
						if (Effect[n].nameGet() == getSpell(action)->nameGet())
							effectActive = true;
					}
					if (!effectActive)
					{
						getSpell(action)->Cast(hero, &*this, &*this, false, false);
						manaMod(-getSpell(action)->costGet());
						return;
					}
				}
				else if (getSpell(action)->typeGet() == "Damage" || getSpell(action)->typeGet() == "Drain" || getSpell(action)->typeGet() == "-Effect")
				{
					getSpell(action)->Cast(hero, &*this, target, false, false);
					manaMod(-getSpell(action)->costGet());
					return;
				}
			}
		}
	}

	if (AttackDescription != "NULL")
	{
		mvprintw(hero->yPosGet(), 0, "%s", AttackDescription.c_str()); hero->yPosAdd(1);
	}
	if (damage == 0)
	{
		if (rand() % 2 == 0)
			damage = 1;
		else
		{
			mvprintw(hero->yPosGet(), 0, "A glancing blow."); hero->yPosAdd(1);
		}
	}
	if (targetRaged)
		damage *= 0.66;

	target->healthMod(-damage);
	target->Stealthed = false;

	// if (target->typeGet() == "Player") 
	// { 
	// 	mvprintw(0, 18, "%i/%i" , target->healthGet(), target->maxHealthGet());
	// 	ColoredString(" HP", HealthColorCode(target));
	// }

	mvprintw(hero->yPosGet(), 0, "%s attacks and deals %i damage to ", Name.c_str(), (int)damage); 
	if (target->typeGet() == "Player") 
	{ 
		printw("you");
	}
	else
	{ 
		printw("%s", target->nameGet().c_str()); 
	}
	printw("! (%i/%i" , target->healthGet(), target->maxHealthGet());
	ColoredString(" hp", HealthColorCode(target));
	printw(")\n"); hero->yPosAdd(2);
	SleepC(1000);
}
void Enemy::viewStatus()
{
	//clear();
	printw("STATUS\n\n");
	printw("Name: \t%s\n", Name.c_str());

	if (EquippedWeapon.nameGet() != "NULL")
		printw("Weapon:\t%s\n", EquippedWeapon.nameGet().c_str());

	for (int i = 0; i < 7; i++)
	{
		if (EquippedArmor[i].nameGet() != "NULL")
		{
			if (EquippedArmor[i].slotGet() == 0)
				printw("Head");
			if (EquippedArmor[i].slotGet() == 1)
				printw("Neck");
			if (EquippedArmor[i].slotGet() == 2)
				printw("Shoulder");
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

	printw("%s\n\n", Description.c_str());

	bool caster = false;
	printw("Spells:\n");
	for (int i = 0; i < MAX_SPELLS; i++)
	{
		if (spell[i].nameGet() != "NULL")
		{
			printw("%s", spell[i].nameGet().c_str());
			caster = true;
		}
	}
	if (!caster)
		printw("Knows no spells\n");
	printw("\n");
	Pause();
}

void Enemy::idMutate(int id)
{
	srand(time(NULL));
	//Name, AttackSound, Description, Health, Mana, Intelligence, SpellID, Strength, Agility, Experience, Gold
	Enemy Rat(1, "Mutant Rat", "NULL", 
		"A rat once quite normal, now bloated and twisted by the corruption. \nIt is in clear decay, but somehow still very vigorous.",
		10, 0, 0, 0, 3, 2, 5, rand() % 4 + 2);

	Enemy Goo(2, "Black Goo", "Bllgh blllgggh blllllgggghh...", 
		"A collection of decaying matter, gained sentience by reasons \nbeyond your understanding.", 
		20, 0, 0, 0, 2, 0, 5, rand() % 3 + 1);

	Enemy Crow(3, "One-eyed Crow", "CAWW!", 
		"It is said that these creatures were created by powerful life \nchannelers long ago to act as advanced scouts.", 
		6, 0, 1, 0, 2, 5, 5, rand() % 3 + 1);

	Enemy Bandit(4, "Mutant Bandit", "RAAAA!",
		"You can see a glimmer of conciousness within its eyes, but mostly they're filled with rage and suffering.",
		10, 2, 1, 12, 4, 4, 5, 1);

	Enemy DustDevil(5, "Dust Devil", "NULL", 
		"A collection of sand, spinning around itself. Its form shifts constantly, \nbut it often imitates the shape of man.", 
		10, 4, 4, 9, 2, 3, 7, rand() % 5 + 1);

	Enemy Viper(6, "Giant Viper", "NULL", 
		"A viper, mutated to gigantic proportion. \nIt towers over you, ready to strike.", 
		20, 0, 0, 0, 3, 2, 10, (rand() % 5 + 3));

	Enemy Abomination(7, "Abomination", "NULL",
		"Once a man, but can now be called nothing less than an abomination. \nIts characteristics morphed by the channelers to serve as an instrument of brute force.",
		30, 0, 0, 0, 5, 3, 20, rand() % 4 + 2);

	Enemy Channeler(8, "Channeler", "NULL",
		"A man wearing a hooded black robe. He is constantly muttering to himself, wheter it's incantations or crazy ramblings is hard to discern.",
		15, 10, 5, 7, 2, 2, 15, rand() % 6 + 3);

	Enemy Husk(9, "Slave Husk", "NULL",
		"The humanoid figure doesn't seem to be conscious at all, it's soul probably long since harvested.",
		20, 0, 0, 0, 4, 6, 5, 1);

	Enemy Scion(10, "Achalio, Scion of Channeling", "NULL", 
		"An incredible skilled channeler. Since he lived before the event, he must be decades old. But his face doesn't look a day over 30.", 
		100, 50, 8, 0, 4, 4, 100, rand() % 25 + 25);

	Enemy Townsman(20, "Townsman", "NULL",
		"A villager, brave enough to attend the tournament.",
		10, 0, 0, 0, 2, 2, 3, rand() % 2 + 1);
	Enemy Ruffian(21, "Ruffian", "NULL",
		"A quick tempered individual seeking to earn some easy money",
		15, 0, 0, 0, 3, 5, 10, rand() % 5 + 1);

	//Drop chance: 1/x chance of dropping
	Abomination.addLoot(0, 1, 10);
	Abomination.addLoot(1, 3, 10);
	Abomination.addLoot(2, 34, 5);
	Channeler.addLoot(0, 2, 10);
	Channeler.addLoot(1, 5, 10);
	Channeler.addLoot(2, 35, 5);
	Husk.addLoot(0, 4, 10);
	Husk.addLoot(1, 30, 10);
	Husk.addLoot(2, 31, 15);
	Husk.addLoot(3, 32, 20);
	Husk.addLoot(4, 33, 30);

	Scion.learnSpell(1);
	Scion.learnSpell(2);
	Scion.learnSpell(3);
	Scion.learnSpell(4);
	Scion.learnSpell(5);
	Scion.learnSpell(6);
	Scion.learnSpell(7);

	if (id == 1)
		Mutate(Rat);
	else if (id == 2)
		Mutate(Goo);
	else if (id == 3)
		Mutate(Crow);
	else if (id == 4)
		Mutate(Bandit);
	else if (id == 5)
		Mutate(DustDevil);
	else if (id == 6)
		Mutate(Viper);
	else if (id == 7)
		Mutate(Abomination);
	else if (id == 8)
		Mutate(Channeler);
	else if (id == 9)
		Mutate(Husk);
	else if (id == 10)
		Mutate(Scion);
	else if (id == 20)
		Mutate(Townsman);
	else if (id == 21)
		Mutate(Ruffian);
	else
		return;
}