#include "../include/Being.h"
//Access and Mutator functions

Player::Player() 
{
	Name = "NULL";
	Type = "Player";
	Class = "NULL";
	Health = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Gold = 0;
	Strength = 0;
	Intelligence = 0;
	Agility = 0;
	Level = 0;
	Experience = 0;
	LevelReq = 0;

	ypos = 0;
	xpos = 0;
	xReset = 0;
	yReset = 0;

	TutorialState = 0;

	InCombat = false;
	Stealthed = true;
	ExtraActionUsed = false;
	RageUsed = false;
}
Player::Player(string name, string setclass, int health, int mana, int strength, int intelligence, int agility, int gold) 
{
	Name = name;
	Type = "Player";
	Class = setclass;
	Health = health;
	MaxHealth = health;
	Mana = mana;
	MaxMana = mana;
	Strength = strength;
	Intelligence = intelligence;
	Agility = agility;
	Gold = gold;

	ypos = 0;
	xpos = 0;
	xReset = 0;
	yReset = 0;

	TutorialState = 0;

	Level = 1;
	Experience = 0;
	LevelReq = 30;
	for (int i = 0; i < 100; i++){ Stage[i] = false; }
	for (int i = 0; i < 100; i++){ Variable[i] = 0; }

	InCombat = false;
	Stealthed = true;
	ExtraActionUsed = false;
	RageUsed = false;
}
void Player::Reset()
{
	Name = "NULL";
	Health = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Gold = 0;
	Strength = 0;
	Intelligence = 0;
	Agility = 0;
	Level = 0;
	Experience = 0;
	LevelReq = 0;

	ypos = 0;
	xpos = 0;
	xReset = 0;
	yReset = 0;

	TutorialState = 0;

	for (int i = 0; i < 100; i++){ Stage[i] = false; }
	for (int i = 0; i < 100; i++){ Variable[i] = 0; }

	EquippedWeapon.Reset();
	for (int i = 0; i < 7; i++)
		EquippedArmor[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		Effect[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		wInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		aInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		pInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		sInventory[i].Reset();
	for (int i = 0; i < FOLLOWER_LIMIT; i++)
		Party[i].Reset();
	for (int i = 0; i < MAX_SPELLS; i++)
		spell[i].Reset();

	InCombat = false;
	Stealthed = true;
	ExtraActionUsed = false;
	RageUsed = false;
}
Player::~Player() {}

//Defining Access Functions
void Player::viewStatus()
{
	int input = -1;
	while (input != '0')
	{
		clear();
		printw("PLAYER STATUS\n\n");
		printw("Name: \t%s\n", Name.c_str());
		printw("Level \t%i %s\n", Level, Class.c_str());
		printw("Exp:\t%i / %i\n\n", Experience, LevelReq);

		ColoredString("Health:\t", HealthColorCode(this));
		printw("%i/%i\n", this->Health, MaxHealth);


		ColoredString("Mana:\t", ManaColorCode(this));
		printw("%i/%i\n\n", Mana, MaxMana); 

		printw("Attributes: \n%i STR\t%i INT\t%i AGI\n\n", Strength, Intelligence, Agility);
		printw("Gold: %i\n\n", Gold);

		printw("1. Display equipment\n");
		printw("2. Display abilities\n");
		if (hasCompanion)
			printw("3. Display companions\n");
		printw("0. Exit Status Screen\n>");
		input = getch();

		printw("\n");
		if (input == '1')
		{
			clear();
			if (EquippedWeapon.nameGet() != "NULL")
			{
				printw("Weapon\n\t%s |", EquippedWeapon.nameGet().c_str());
				if (EquippedWeapon.damageGet() > 0)
					printw(" +%i Damage ", EquippedWeapon.damageGet());
				if (EquippedWeapon.magicGet() > 0)
					printw(" +%i Magic Essence ", EquippedWeapon.magicGet());
			}

			printw("\n\n");
			for (int i = 0; i < 7; i++)
			{
				if (EquippedArmor[i].nameGet() != "NULL")
				{
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

					printw("\n\t%s |", EquippedArmor[i].nameGet().c_str());
					if (EquippedArmor[i].defenceGet() > 0)
						printw(" +%i Defence ", EquippedArmor[i].defenceGet());
					if (EquippedArmor[i].magicGet() > 0)
						printw(" +%i MagicEssence ", EquippedArmor[i].magicGet());
					if (EquippedArmor[i].magicDefenceGet() > 0)
						printw(" +%i MagicDefence ", EquippedArmor[i].magicDefenceGet());
					printw("\n");
				}
			}
		}
		if (input == '2')
		{
			clear();
			for (int i = 0; i < 9; i++)
			{
				if (spell[i].idGet() > 0)
				{
					printw("%s - %i MP\n", spell[i].nameGet().c_str(), spell[i].costGet());
					Paragraph(&*this, spell[i].descGet() + "\n\n", false, false, false, 0);
				}
			}
		}
		if (input == '3' && hasCompanion)
		{
			printw("\nCompanions:\n");
			for (int i = 0; i < FOLLOWER_LIMIT; i++)
			{
				if (Party[i].nameGet() != "NULL")
				{
					printw("%s %i/%i", Party[i].nameGet().c_str(), Party[i].healthGet(), Party[i].maxHealthGet());
					ColoredString(" HP\n", HealthColorCode(&Party[i]));
				}
			}
		}
		if (input == '1' || input == '2' || (input == '3' && hasCompanion))
		{
			printw("\n\n");
			Pause(); clear();
		}
	}
}
string Player::classGet(){
	return Class;
}
bool Player::stageGet(int var){
	return Stage[var];
}
int Player::varGet(int id){
	return Variable[id];
}

Companion Player::getCompanion(int i){
	return Party[i];
}
void Player::addCompanion(int id)
{
	for (int i = 0; i < FOLLOWER_LIMIT; i++)
	{
		if (Party[i].nameGet() == "NULL")
		{
			Party[i].idMutate(id);
			break;
		}
	}
}

//Defining Mutator Funtions

void Player::classSet(string newClass){
	Class = newClass;
}
void Player::stageSet(int var, bool loading)
{
	Stage[var] = true;
	if(!loading)
		Save(this, true);
}
void Player::stageFlip(int id){
	if (Stage[id])
		Stage[id] = false;
	else if (!Stage[id])
		Stage[id] = true;
}
void Player::stageReset(int var){
	Stage[var] = false;
}
void Player::varSet(int id, int var){
	Variable[id] = var;
}
void Player::varMod(int id, int var){
	Variable[id] += var;
}
void Player::varReset(int id){
	Variable[id] = 0;
}
void Player::levelSet(int level){
	Level = level;
	LevelReq = 30;
	for (int i = 1; i < level; i++)
		LevelReq += (LevelReq / 2) + (Level * 5);
}
void Player::expGive(int var)
{
	char input = ' ';
	int strength = 0;
	int intelligence = 0;
	int agility = 0;
	Experience += var;

	if (Experience >= LevelReq)
	{
		Experience -= LevelReq;
		LevelReq += (LevelReq / 2) + (Level * 5);
		Level++;

		Paragraph(&*this, "You have gained a level!\n", true, false, false, 39);

		if (classGet() == "Berserker")
		{ 
			strMod(1);
			strength++;

			while (input != '1' && input != '2')
			{
				printw("Strength focus: +1 Strength\n\n");
				printw("Choose a second stat:\n");
				printw("1: Agility\n");
				printw("2: Intelligence\n");
				printw(">");
				input = getch();

				if (input == '1')
				{
					agiMod(1);
					agility++;
				}
				else if (input == '2')
				{
					intMod(1);
					intelligence++;
				}
				clear();
			}
		}
		if (classGet() == "Channeler")
		{
			intMod(1);
			intelligence++;

			while (input != '1' && input != '2')
			{
				printw("Intelligence focus: +1 Intelligence\n\n");
				printw("Choose a second stat:\n");
				printw("1: Agility\n");
				printw("2: Strength\n");
				printw(">");
				input = getch();

				if (input == '1')
				{
					agiMod(1);
					agility++;
				}
				else if (input == '2')
				{
					strMod(1);
					strength++;
				}
				clear();
			}
		}
		if (classGet() == "Nightblade")
		{
			for (int i = 0; i < 2; i++)
			{
				while (agility + intelligence + strength < 2)
				{
					printw("No focus: Choose two stats\n\n");
					if (i == 0)
						printw("Choose the first stat:\n");
					if (i == 1)
						printw("Choose the second stat:\n");

					if (agility == 0)
						printw("1: Agility\n");
					if (intelligence == 0)
						printw("2: Intelligence\n");
					if (strength == 0)
						printw("3: Strength\n");
					printw(">");
					input = getch();

					if (input == '1' && agility == 0)
					{
						agiMod(1);
						agility++;
					}
					else if (input == '2' && intelligence == 0)
					{
						intMod(1); 
						intelligence++;
					}
					else if (input == '3' && strength == 0)
					{
						strMod(1);
						strength++;
					}
					clear();
				}
			}
		}
		if (classGet() == "Gunslinger" || classGet() == "Monk")
		{
			agiMod(1);
			agility++;

			while (input != '1' && input != '2')
			{
				printw("Agility focus: +1 Agility\n\n");
				printw("Choose a second stat:\n");
				printw("1: Intelligence\n");
				printw("2: Strength\n");
				printw(">");
				input = getch();

				if (input == '1')
				{
					intMod(1);
					intelligence++;
				}
				else if (input == '2')
				{
					strMod(1);
					strength++;
				}
				clear();
			}
		}
		if (classGet() == "Peasant")
		{
			if (Level % 2 == 0)
			strMod(1);
			else
			{
				agiMod(1);
				intMod(1);
			}
		}
		clear();
		printw("Level %i attained!\n", Level);
		if (agility > 0)
			printw("+%i Agility\n", agility);
		if (strength > 0)
			printw("+%i Strength\n", strength);
		if (intelligence > 0)
			printw("+%i Intelligence\n", intelligence);
		printw("\n");

		Pause(); clear();
	}
}

void Player::Attack(Player* hero)
{
	int enemyCount = 0;
	for (int i = 0; i < ENEMY_LIMIT; i++)
	{
		if (hero->Opponent[i].nameGet() != "NULL")
			enemyCount++;
	}

	Companion* companionPointer[5] = { &hero->Party[0], &hero->Party[1], &hero->Party[2], &hero->Party[3], &hero->Party[4] };
	Being* enemyPointer[ENEMY_LIMIT] = { &hero->Opponent[0], &hero->Opponent[1], &hero->Opponent[2], &hero->Opponent[3], &hero->Opponent[4], &hero->Opponent[5], &hero->Opponent[6], &hero->Opponent[7], &hero->Opponent[8] };
	Enemy* ePointer[ENEMY_LIMIT] = { &hero->Opponent[0], &hero->Opponent[1], &hero->Opponent[2], &hero->Opponent[3], &hero->Opponent[4], &hero->Opponent[5], &hero->Opponent[6], &hero->Opponent[7], &hero->Opponent[8] };


	ActionUsed = false;
	ExtraActionUsed = false;
	bool FirstRound = true; 
	while (!ActionUsed)
	{
		int input = 0;
		input = mvgetch(6, 29);
		move(yPosGet(), 0);
		
		ActionUsed = hero->keyBindingCheck(input);

		int target = 1;
		if (input == '1')
		{
			target = ChooseEnemy("Who do you choose to attack?", hero, 1);

			if (target >= 0)
			{
				if (hero->Opponent[target].healthGet() > 0)
				{
					srand(time(NULL));
					double damage = 0;
					bool raged = false;

					for (int i = 0; i < MAX_EFFECTS; i++)
					{
						if (getEffect(i)->nameGet() == "Rage")
							raged = true;
					}

					if (Class == "Berserker")
						damage += 2;

					if (Class == "Monk")
						damage += (Agility * 1.5) + EquippedWeapon.damageGet() + (rand() % 3 - 1);
					else if (raged)
						damage += (Strength * 3) + EquippedWeapon.damageGet() + (rand() % 3 - 1);
					else
						damage += (Strength * 2) + EquippedWeapon.damageGet() + (rand() % 3 - 1);

					int chance = rand() % 100 + 1;
					int crit = (Agility + (Strength / 3) + (Intelligence / 2) * 2) - Opponent[target].agilityGet();
					int miss = Opponent[target].agilityGet() - Agility;

					for (int i = 0; i < 9; i++)
					{	//Checks and applies debuffs/buffs relevant to combat
						if (getEffect(i)->typeGet() == "Accuracy")
							miss -= getEffect(i)->valueGet();
						if (getEffect(i)->typeGet() == "+Damage")
							damage += getEffect(i)->valueGet();
						if (Opponent[target].Effect[i].typeGet() == "Armor")
							damage -= Opponent[target].getEffect(i)->valueGet();
					}

					if (chance <= crit)
					{
						mvprintw(yPosGet(), 0, "Critical hit!!"); hero->yPosAdd(1);
						damage *= 1.5;
					}

					for (int i = 0; i < 9; i++){
						damage -= Opponent[target].getArmor(i)->defenceGet();
					}

					if (chance <= miss)
					{
						mvprintw(yPosGet(), 0, "You miss!\n"); hero->yPosAdd(2);
						SleepC(1000);
						return;
					}
					Opponent[target].healthMod(-damage);
					mvprintw(yPosGet(), 0, "Your %s damages %s for %i health! ", EquippedWeapon.nameGet().c_str(), Opponent[target].nameGet().c_str(), (int)damage); hero->yPosAdd(2);
					printw("(%i/%i" , Opponent[target].healthGet(), Opponent[target].maxHealthGet());
					ColoredString(" hp", HealthColorCode(&Opponent[target]));
					printw(")\n");
					refresh();
					if (Opponent[target].healthGet() > 0){
						; //pause and clear
					}
					SleepC(1000);
					killCheck(&*hero, &Opponent[target]);
					ActionUsed = true;
				}
			}
		}
		if (input == '2')
			ActionUsed = hero->spellCast(&*enemyPointer, &*companionPointer);
		if (input == '3')
			ActionUsed = hero->inventoryDisplay();
		if (input == '4')
		{
			target = ChooseEnemy("Inspect who?", hero, 1);

			if (target >= 0)
				hero->Inspect(&hero->Opponent[target]);
		}

		if (RunningPossible && input == '9')
		{
			hero->InCombat = false;

			for (int i = 0; i < ENEMY_LIMIT; i++)
				hero->Opponent[i].Reset();

			for (int i = 0; i < MAX_EFFECTS; i++)
			{
				if (hero->getEffect(i)->typeGet() == "Strength")
					hero->strMod(-hero->getEffect(i)->valueGet());
				if (hero->getEffect(i)->typeGet() == "Agility")
					hero->agiMod(-hero->getEffect(i)->valueGet());
				if (hero->getEffect(i)->typeGet() == "Intelligence")
					hero->intMod(-hero->getEffect(i)->valueGet());
				hero->getEffect(i)->Reset();
			}

			for (int i = 0; i < FOLLOWER_LIMIT; i++)
			{
				if (hero->Party[i].typeGet() == "Conjured")
					hero->Party[i].Reset();

				for (int j = 0; j < MAX_EFFECTS; j++)
					hero->Party[i].getEffect(j)->Reset();
			}
			return;
		}
		else if (input == '9')
			Paragraph(&*this, "You can't run from this battle!", false, false, false, 19);

		if (ActionUsed)
			break;

		if (EnemiesDead(hero))
			break;
	}
}

bool Player::spellCast(Being* enemy[9], Companion* party[5])
{
	int selection = 99;
	int target = 99;
	Being* targetPointer;

	while (selection >= 0)
	{
		selection = 99;
		if (Class == "Channeler")
			selection = ChooseSpell("Choose a spell", &*this, spell);
		else
			selection = ChooseSpell("Choose a skill", &*this, spell);

		move(yPosGet(), 0);

		if (selection < 0)
			break;
		if (spell[selection].nameGet() == "Rage" && RageUsed)
		{
			mvprintw(yPosGet(), 0, "You need to rest before raging again."); yPosAdd(2);
			return false;
		}
		else if (spell[selection].nameGet() == "Rage" && !RageUsed)
			RageUsed = true;

		if (spell[selection].quickAction())
		{
			if (ExtraActionUsed)
			{
				mvprintw(yPosGet(), 0, "You can only use a quick action once per turn."); yPosAdd(2);
				return false;
			}
			else
				ExtraActionUsed = true;
		}

		if (Mana >= spell[selection].costGet())
		{
			if (Intelligence >= spell[selection].intReqGet())
			{
				while (target != -2)
				{
					if (spell[selection].typeGet() == "Healing" || spell[selection].typeGet() == "+Effect" || spell[selection].typeGet() == "Misc")
					{
						target = ChooseCompanion(-1, -1, "Cast on?", &*this, party);

						if (target == -2)
							return false;

						if (target == -1)
						{
							if (spell[selection].Cast(&*this, &*this, &*this, true, false))
							{
								if (spell[selection].quickAction())
									return false;
								else
									return true;
							}
							else
								return false;
						}
						else if (target >= 0 && target < FOLLOWER_LIMIT)
						{
							if (spell[selection].Cast(&*this, &*this, party[target], false, false))
							{
								if (spell[selection].quickAction())
									return false;
								else
									return true;
							}
							else
								return false;
							}
					}
					else if (spell[selection].typeGet() == "SelfBuff")
					{

						if (spell[selection].Cast(&*this, &*this, &*this, true, false))
						{
							if (spell[selection].quickAction())
								return false;
							else
								return true;
						}
						else
							return false;
					}
					else if (spell[selection].typeGet() == "AoE")
					{
						for (int i = 0; i < ENEMY_LIMIT; i++)
						{
							if (enemy[i]->healthGet() > 0)
								spell[selection].Cast(&*this, &*this, enemy[i], false, false);
						}
						Mana -= spell[selection].costGet();
						if (spell[selection].quickAction())
							return false;
						else
							return true;
					}
					else if (spell[selection].typeGet() == "Conjuring")
					{
						if (spell[selection].Cast(&*this, &*this, &*this, true, false))
						{
							if (spell[selection].quickAction())
								return false;
							else
								return true;
						}
						else
							return false;
					}
					else if (spell[selection].typeGet() == "Dispel")
					{
						targetPointer = ChooseTarget("Cast on?", &*this, party, enemy);
						if (targetPointer->nameGet() != "NULL")
						{
							if (spell[selection].Cast(&*this, &*this, targetPointer, true, false))
							{
								if (spell[selection].quickAction())
									return false;
								else
									return true;
							}
							else
								return false;
						}
						else
							return false;
					}
					else // DAMAGE SPELLS
					{
						while (true)
						{
							if (Class == "Channeler")
								target = ChooseEnemy("Who is the target of the spell?", this, 2);
							if (Class == "Berserker" || Class == "Nightblade" || Class == "Monk")
								target = ChooseEnemy("Who is the target of the skill?", this, 2);

							if (target >= 0)
							{
								if (enemy[target]->healthGet() > 0)
								{
									if (spell[selection].Cast(&*this, &*this, enemy[target], false, false))
									{
										if (spell[selection].quickAction())
											return false;
										else
											return true;
									}
									else
										return false;
								}
							}
							if (target == -1)
								return false;
						}
					}
				}
			}
			else
				Paragraph(&*this, "You lack the intelligence to fully comprehend this spell.", false, false, true, 0);
		}
		else
			Paragraph(&*this, "You don't have enough mana to cast that spell!", false, false, true, 0);
	}
	return false;
}
void Player::Inspect(Enemy* target)
{
	target->viewStatus();
}

void Player::spellDisplay()
{
	Companion* companionPointer[5] = { &Party[0], &Party[1], &Party[2], &Party[3], &Party[4] };
	int selection = 0;

	while (true)
	{
		selection = ChooseSpell("Use an Ability?", &*this, spell);
		if (selection == -1)
			break;

		if (!spell[selection].inCombat())
		{
			if (selection >= 0 && selection < MAX_SPELLS)
			{
				int input = ChooseCompanion(-1, -1, "Cast on?", &*this, companionPointer);

				if (spell[selection].costGet() <= this->manaGet())
				{
					if (input == -1)
						spell[selection].Cast(&*this, &*this, &*this, true, false);
					if (input >= 0 && input < 5)
						spell[selection].Cast(&*this, &*this, companionPointer[input], false, false);
				}
				else if (input != -2)
					Paragraph(&*this, "You don't have enough mana!", false, false, true, 0);
			}
		}
		else
			Paragraph(&*this, "You can't use this spell outside of combat.", false, false, true, 0);
	}
}

void Player::equipArmor(Armor* equip)	//DO SOMETHING HERE!
{
	bool wearable = true;
	if (equip->typeGet() == "Iron")
	{
		if (Class != "Berserker")
		{
			Paragraph(&*this, "You can't wear this.", false, false, false, 0);
			wearable = false;
		}
	}
	if (equip->typeGet() == "Leather")
	{
		if (Class == "Channeler")
		{
			Paragraph(&*this, "You can't wear this.", false, false, false, 0);
			wearable = false;
		}
	}
	if(wearable)
	{
		for (int i = 0; i < 7; i++)
		{
			if (i == equip->slotGet())
			{
				if (EquippedArmor[i].valueGet() > 0)
				{
					for (int j = 0; j < INVENTORY_SIZE; j++)
					{
						if (aInventory[j].nameGet() == "NULL")
						{
							aInventory[j].Transform(EquippedArmor[i]);
							break;
						}
					}
				}
				EquippedArmor[i].Transform(*equip);
				equip->Reset();
			}
		}
		Paragraph(&*this, "\nArmor Equipped!", false, false, false, 0);
	}
}

bool Player::inventoryDisplay()
{
	Being* enemy[ENEMY_LIMIT] = { &Opponent[0], &Opponent[1], &Opponent[2], &Opponent[3], &Opponent[4], &Opponent[5], &Opponent[6], &Opponent[7], &Opponent[8]};
	Companion* companionPointer[FOLLOWER_LIMIT] = { &Party[0], &Party[1], &Party[2], &Party[3], &Party[4] };
	int input = 99;
	int selection = -1;
	int y, x;

	while (input != '0')
	{
		y = 0; x = 0;

		if(InCombat)
			x = 50;
		else
			Clear(&*this);

		mvprintw(0, x, "1. Weapons"); ypos++;
		mvprintw(1, x, "2. Armor"); ypos++;
		mvprintw(2, x, "3. Potions"); ypos++;
		mvprintw(3, x, "4. Scrolls"); ypos++;
		mvprintw(4, x, "5. Spell Tomes"); ypos++;
		mvprintw(5, x, "6. Equipped Armor"); ypos++;
		//mvprintw(6, x, "7. Inventory");
		mvprintw(6, x, "0. Back"); ypos++;
		mvprintw(7, x, ">"); ypos++;
		input = getch();


		if (input == '1')
		{
			selection = 99;
			while (selection != '0')
			{
				y = 0;
				if(InCombat)
					x = 75;
				else
					x = 20;

				int number = 0;
				SortWeaponInventory(wPointer);
				
				mvprintw(y, x, "Weapons:"); y++;
				if (EquippedWeapon.nameGet() != "NULL")
				{
					mvprintw(y, x, "1. %s [E]", EquippedWeapon.nameGet().c_str()); y++;
				}
				for (int i = 0; i < INVENTORY_SIZE; i++)
				{	//Generate list from weapons in inventory
					if (wInventory[i].nameGet() != "NULL")
					{
						mvprintw(y, x, "%i. %s", i+2, wInventory[i].nameGet().c_str());
						number++;
						y++;
					}
				}
				mvprintw(y, x, "%i/%i in inventory", number, INVENTORY_SIZE); 
				y += 2;

				mvprintw(y, x, "0. Back"); y++;
				mvprintw(y, x, ">");
				selection = getch();

				if (selection == '1' && EquippedWeapon.nameGet() != "NULL")
					EquippedWeapon.Status(&*this);
				else if (selection >= 50 && selection <= 58)
				{
					if (wInventory[selection - 50].nameGet() != "NULL")
						wInventory[selection - 50].Status(&*this);
				}
			}
			ClearX(y, x);
		}
		if (input == '2')
		{
			y = 0;
			if(InCombat)
				x = 75;
			else
				x = 20;

			SortArmorInventory(aPointer);
			selection = ChooseArmor("Armor Inventory:", &*this, aInventory, false);

			if (selection >= 0 && selection <= INVENTORY_SIZE && aInventory[selection].nameGet() != "NULL")
			{
				aInventory[selection].Status(&*this);
			}
			ClearX(y, x);
		}
		if (input == '3')
		{
			printw("\n");
			selection = 99;
			while (selection >= 0)
			{
				y = 0;
				if(InCombat)
					x = 75;
				else
					x = 20;

				SortPotionInventory(pPointer);
				selection = ChoosePotion("Potions:", &*this, pInventory, false);
				bool confirmation = false;

				if (selection == -1)
					break;

				if (!InCombat)
					confirmation = pInventory[selection].Status(y, x+30);
				else
					confirmation = true;

				if (confirmation)
				{
					int target = ChooseCompanion(10, 0, "Use the potion on whom?", &*this, &*companionPointer);

					if (target == -1){
						pInventory[selection].Use(&*this, &*this);
					}
					else if (target != -2){
						pInventory[selection].Use(&*this, &*companionPointer[target]);
					}

					ActionUsed = true;

					if (InCombat)
					{
						ClearX(y, x);
						return ActionUsed;
					}
				}
			}
			ClearX(y, x);
		}
		if (input == '4')
		{
			printw("\n");
			bool confirmation = false;
			while (true)
			{
				y = 0;
				if(InCombat)
					x = 75;
				else
					x = 20;

				SortScrollInventory(sPointer);
				selection = ChooseScroll("Scrolls:", &*this, sInventory, false);
				if (selection == -1)
					break;
				if (selection >= 0 && !InCombat)
					confirmation = sInventory[selection].Status(&*this, false);
				else if (selection >= 0 && InCombat)
					confirmation = true;

				if (selection >= 0 && selection < INVENTORY_SIZE && confirmation)
				{
					if (getScroll(selection)->typeGet() == "Conjuring" || getScroll(selection)->typeGet() == "AoE")
						ActionUsed = getScroll(selection)->Use(&*this, &*this, &*this, enemy);

					else if (getScroll(selection)->typeGet() == "Healing" || getScroll(selection)->typeGet() == "+Effect")
					{
						int target = ChooseCompanion(-1, -1, "Use scroll on who?", &*this, companionPointer);
						if (target == -1)
						{
							ActionUsed = getScroll(selection)->Use(&*this, &*this, &*this, enemy);
						}
						if (target >= 0)
						{
							ActionUsed = getScroll(selection)->Use(&*this, &*this, companionPointer[target], enemy);
						}
					}
					else if (getScroll(selection)->valueGet() > 0 && InCombat)
					{
						int target = ChooseEnemy("Who do you use the scroll on?", this, 2);
						if (target >= 0)
						{
							ActionUsed = getScroll(selection)->Use(&*this, &*this, enemy[target], enemy);
						}
					}
					else if (!InCombat && selection != -1)
					{
						PausedString("You can't use this outside of combat.");
					}

					if (InCombat && ActionUsed)
					{
						ClearX(y, x);
						return true;
					}
				}
			}
		}
		if (input == '5')
		{
			y = 0;
			if(InCombat)
				x = 75;
			else
				x = 20;

			if (InCombat)
			{
				mvprintw(y, 75, "You can't read in combat!");
				SleepC(1000);
			}
			else
			{
				printw("\n");
				SortTomeInventory(tPointer);
				int selection = ChooseTome("Spell Tomes:", &*this, tInventory, false);
				if (selection >= 0)
				{
					bool confirmation = tInventory[selection].Status(&*this, false);
					if (confirmation)
						tInventory[selection].Use(&*this);
				}
			}
			ClearX(y, x);
		}
		if (input == '6')
		{
			while (true)
			{
				y = 0;
				if(InCombat)
					x = 75;
				else
					x = 20;

				printw("\n");
				SortArmorInventory(aPointer);
				selection = ChooseArmor("Armor Inventory:", &*this, EquippedArmor, false);
				if (selection >= 0)
				{
					EquippedArmor[selection].Status(&*this);
					Pause();
				}
				else
					break;
			}
			ClearX(y, x);
		}
		if (false) //input == '7'
		{
			selection = 99;
			while (selection != '0')
			{
				y = 0;
				if(InCombat)
					x = 75;
				else
					x = 20;
				printw("\n");
				int number = 0;
				for (int i = 0; i < INVENTORY_SIZE; i++)
				{
					if (Inventory[i].nameGet() != "NULL")
					{
						printw("%i. %s\n", i+1, Inventory[i].nameGet().c_str());
						number++;
					}
				}
				printw("%i/%i in inventory\n\n", number, INVENTORY_SIZE);
				printw("0. Back\n>");
				selection = getch();
				if (selection > 48 && selection <= 48 + INVENTORY_SIZE)
				{
					if(Inventory[selection - 49].nameGet() != "NULL")
						Inventory[selection - 49].Status(&*this);
				}
			}
			ClearX(y, x);
		}
	}
	ClearX(8, x);
	return ActionUsed;
}

void Player::setBinding()
{
	int input = 99;
	while (input != '0')
	{
		Clear(&*this);
		mvprintw(yPosGet(), 0, "What key do you wish to bind to an action?\n"); yPosAdd(1);
		for (int i = 97; i < 122; i++)
		{
			mvprintw(yPosGet(), 0, "%c: ", (char)i);
			if (Binding[i - 97].keyGet() == i && Binding[i - 97].nameGet() != "NULL"){
				printw("%s", Binding[i - 97].nameGet().c_str());
			}
			else{
				printw("Not bound.");
			} 
			i++;
			mvprintw(yPosGet(), 25, "%c: ", (char)i);
			if (Binding[i - 97].keyGet() == i && Binding[i - 97].nameGet() != "NULL"){
				printw("%s", Binding[i - 97].nameGet().c_str()); yPosAdd(1);
			}
			else{
				printw("Not bound."); yPosAdd(1);
			}
		}
		mvprintw(yPosGet(), 0, "0: Cancel"); yPosAdd(1);
		mvprintw(yPosGet(), 0, ">");
		input = getch();

		if (input >= 97 && input <= 122)
		{
			int type = 99;
			while (type != '0')
			{
				Clear(&*this);
				mvprintw(yPosGet(), 0, "What type of action do you wish to bind?"); yPosAdd(1);
				mvprintw(yPosGet(), 0, "1: Spell"); yPosAdd(1);
				mvprintw(yPosGet(), 0, "2: Potion"); yPosAdd(1);
				mvprintw(yPosGet(), 0, "3: Scroll"); yPosAdd(1);
				mvprintw(yPosGet(), 0, "4: Weapon"); yPosAdd(1);
				mvprintw(yPosGet(), 0, "5: Armor"); yPosAdd(1);
				mvprintw(yPosGet(), 0, "0: Reset binding"); yPosAdd(1);
				mvprintw(yPosGet(), 0, ">");
				type = getch();

				if (type == '0')
					Binding[input - 97].Reset();

				if (type == '1')
				{
					int spell_ = ChooseSpell("Which spell do you wish to bind?", &*this, spell);
					if (spell_ >= 0)
					{
						Binding[input - 97].setBinding(input, "Spell", spell[spell_].idGet());
						break;
					}
				}
				if (type == '2')
				{
					int potion_ = ChoosePotion("What potion do you wish to bind?", &*this, pInventory, false);
					if (potion_ >= 0)
					{
						Binding[input - 97].setBinding(input, "Potion", pInventory[potion_].idGet());
						break;
					}
				}
				if (type == '3')
				{
					int scroll_ = ChooseScroll("What scroll do you wish to bind?", &*this, sInventory, false);
					if (scroll_ >= 0)
					{
						Binding[input - 97].setBinding(input, "Scroll", sInventory[scroll_].idGet());
						break;
					}
				}
				if (type == '4')
				{
					int weapon_ = ChooseWeapon("What weapon do you wish to bind?", &*this, wInventory, false);
					if (weapon_ >= 0)
					{
						Binding[input - 97].setBinding(input, "Weapon", wInventory[weapon_].idGet());
						break;
					}
				}
				if (type == '5')
				{
					int armor_ = ChooseArmor("What armor do you wish to bind?", &*this, aInventory, false);
					if (armor_ >= 0)
					{
						Binding[input - 97].setBinding(input, "Armor", aInventory[armor_].idGet());
						break;
					}
				}
			}
		}
	}
}

bool Player::keyBindingCheck(int key)
{
	Being* enemyPointer[10] = { &Opponent[0], &Opponent[1], &Opponent[2], &Opponent[3], &Opponent[4], &Opponent[5], &Opponent[6], &Opponent[7], &Opponent[8], &Opponent[9] };
	Companion* companionPointer[5] = { &Party[0], &Party[1], &Party[2], &Party[3], &Party[4] };

	for (int i = 0; i < 25; i++)
	{
		if (Binding[i].keyGet() == key)
		{
			if (Binding[i].typeGet() == "Spell")
			{
				for (int y = 0; y < MAX_SPELLS; y++)
				{
					if (Binding[i].nameGet() == spell[y].nameGet() && Binding[i].nameGet() != "NULL")
					{
						if (spell[y].inCombat() && !InCombat)
							return false;

						if (spell[y].quickAction() )
						{
							if (ExtraActionUsed)
							{
								Paragraph(&*this, "You can only use a quick action once per turn.", false, false, false, 0);
								return false;
							}
							else
								ExtraActionUsed = true;
						}

						if (spell[y].typeGet() == "AoE")
						{
							for (int i = 0; i < ENEMY_LIMIT; i++)
							{
								if (Opponent[i].healthGet() > 0)
									spell[y].Cast(&*this, &*this, &Opponent[i], false, false);
							}
							Mana -= spell[y].costGet();
							return true;
						}

						if (spell[y].nameGet() == "Rage" && RageUsed)
						{
							Paragraph(&*this, "You need to rest before raging again.", false, false, false, 0);
							return false;
						}
						else if (spell[y].nameGet() == "Rage" && !RageUsed)
							RageUsed = true;

						if (spell[y].typeGet() == "SelfBuff")
						{
							return spell[y].Cast(&*this, &*this, &*this, true, false);
						}
						else if (spell[y].inCombat() && spell[y].typeGet() != "+Effect")
						{
							int enemy = ChooseEnemy("Use on?", this, 2);
							if (enemy >= 0)
							{
								return spell[y].Cast(&*this, &*this, &Opponent[enemy], true, false);
							}
						}
						else
						{
							int target = ChooseCompanion(-1, -1, "Use on?", &*this, companionPointer);

							if (target == -2)
								return false;

							if (target == -1)
							{
								if (spell[y].Cast(&*this, &*this, &*this, true, false))
									return true;
								else
									return false;
							}
							else if (target >= 0 && target < 5)
							{
								if (spell[y].Cast(&*this, &*this, companionPointer[target], false, false))
									return true;
								else
									return false;
							}
						}
					}
				}
			}
			if (Binding[i].typeGet() == "Potion")
			{
				for (int y = 0; y < INVENTORY_SIZE; y++)
				{
					if (Binding[i].nameGet() == pInventory[y].nameGet() && Binding[i].nameGet() != "NULL")
					{
						if(!InCombat)
							pInventory[y].Use(&*this, &*this);
						if(InCombat)
							pInventory[y].Use(&*this, &*this);
						return true;
					}
				}
				clear();
				printw("You don't have any %ss left.\n", Binding[i].nameGet().c_str());
				Pause();
				return false;
			}
			if (Binding[i].typeGet() == "Scroll")
			{
				for (int y = 0; y < INVENTORY_SIZE; y++)
				{
					if (Binding[i].nameGet() == sInventory[y].nameGet() && Binding[i].nameGet() != "NULL")
					{
						sInventory[y].Use(&*this, &*this, &*this, enemyPointer);
						return true;
					}
				}
				clear();
				printw("You don't have another %s left.\n", Binding[i].nameGet().c_str());
				Pause();
				return false;
			}
			if (Binding[i].typeGet() == "Weapon")
			{
				for (int y = 0; y < INVENTORY_SIZE; y++)
				{
					if (Binding[i].nameGet() == wInventory[y].nameGet() && Binding[i].nameGet() != "NULL")
					{
						equipWeapon(&wInventory[y]);
						return true;
					}
				}
			}
			if (Binding[i].typeGet() == "Armor")
			{
				for (int y = 0; y < INVENTORY_SIZE; y++)
				{
					if (Binding[i].nameGet() == aInventory[y].nameGet() && Binding[i].nameGet() != "NULL")
					{
						equipArmor(&aInventory[y]);
						return true;
					}
				}
			}
		}
	}
	return false;
}