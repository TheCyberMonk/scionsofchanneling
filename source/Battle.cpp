#include "../include/Being.h"
std::ostringstream sstream;

bool BattleGroup(Player* hero, int number, int difficulty, int battleType)
{	//Battle types: 0-Lethal fight, 1-Tourament, 2-Friendly/Duel, 3-No escape

#pragma region VARIABLES

	Being* beingPointer[15] = { hero, &hero->Party[0], &hero->Party[1], &hero->Party[2], &hero->Party[3], &hero->Party[4],
	&hero->Opponent[0], &hero->Opponent[1], &hero->Opponent[2], &hero->Opponent[3], &hero->Opponent[4], &hero->Opponent[5], 
	&hero->Opponent[6], &hero->Opponent[7], &hero->Opponent[8] };
	Enemy* ePointer[ENEMY_LIMIT] = { &hero->Opponent[0], &hero->Opponent[1], &hero->Opponent[2], &hero->Opponent[3], &hero->Opponent[4], 
	&hero->Opponent[5], &hero->Opponent[6], &hero->Opponent[7], &hero->Opponent[8] };

	int input = 99;
	int battleSize = 1;
	int initiative[15] = { 0 };
	int random = 0;
	int round = 0;
	int yPos = 0;

#pragma endregion
#pragma region ENEMY GENERATION

	if (difficulty == 100)
	{
		hero->Opponent[0].idMutate(10);
		hero->Opponent[1].idMutate(8);
		hero->Opponent[2].idMutate(8);
		hero->Opponent[3].idMutate(8);
		hero->Opponent[4].idMutate(8);
	}
	if (difficulty == 101)
	{
		hero->Opponent[0].idMutate(21);
	}
	if (difficulty == 102)
	{
		hero->Opponent[0].idMutate(21);
		hero->Opponent[1].idMutate(21);
	}
	if (difficulty == 103)
	{
		hero->Opponent[0].idMutate(2);
		hero->Opponent[1].idMutate(2);
	}
	if (difficulty == 104)
	{
		hero->Opponent[0].idMutate(3);
		hero->Opponent[1].idMutate(3);
	}
	else
	{
		for (int i = 0; i < number; i++)		//Generates random enemies from assigned difficulty group
		{
			SleepC(5);							//Slight delay between each loop so the time seed is different
			srand(time(NULL) * (i + 1));
			random = rand() % 3 + 1;
			if (difficulty == 0){
				hero->Opponent[i].idMutate(20);
			}
			if (difficulty == 1){
				hero->Opponent[i].idMutate(random);
			}
			if (difficulty == 2){
				hero->Opponent[i].idMutate(random + 3);
			}
			if (difficulty == 3){
				hero->Opponent[i].idMutate(random + 6);
			}
		}
	}
#pragma endregion
#pragma region INITIALIZATION

	//Increase battlesize variable if being exists and is alive and checks if the player has a companion
	for (int i = 1; i < 15; i++)
	{
		if (beingPointer[i]->healthGet() > 0)
		{
			battleSize++;
			if(beingPointer[i]->typeGet() == "Companion") 
				hero->hasCompanion = true; 
		}
	}

	//Generates initiative for beings in the fight based on Agility and RNG.
	//Also boosts initiative for Nightblades as it's a class feature
	for (int i = 0; i < 15; i++)
	{
		if (beingPointer[i]->healthGet() > 0)
			initiative[i] = beingPointer[i]->agilityGet() + rand() % 3 - 1;
	}
	if (hero->classGet() == "Nightblade")
		initiative[0]++;
	SortInitiative(initiative, beingPointer);

	hero->InCombat = true;
	if (battleType == 0)
		hero->RunningPossible = true;
	else
		hero->RunningPossible = false;

#pragma endregion

	while (true)
	{
		refresh();
		Clear(&*hero);
		move(0, 0);

		round++;

		int enemyCount = 0;
		for (int i = 0; i < ENEMY_LIMIT; i++)
		{
			if (hero->Opponent[i].nameGet() != "NULL")
				enemyCount++;
		}
		SortEnemyOrder(ePointer);
		
		mvprintw(hero->yPosGet(), 0, "%s", hero->nameGet().c_str()); //hero->yPosAdd(1);
		mvprintw(hero->yPosGet(), 18, "%i/%i", hero->healthGet(), hero->maxHealthGet()); hero->yPosAdd(1);
		ColoredString(" HP\n", HealthColorCode(hero));

		if (hero->maxManaGet() > 0)
		{
			mvprintw(hero->yPosGet(), 18, "%i/%i", hero->manaGet(), hero->maxManaGet());  hero->yPosAdd(1);
			ColoredString(" MP\n", ManaColorCode(hero));
		}
		printw("\n"); hero->yPosAdd(1);

		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (hero->Party[i].healthGet() > 0)
			{
				printw("%s:\t   %i/%i", hero->Party[i].nameGet().c_str(), hero->Party[i].healthGet(), hero->Party[i].maxHealthGet());
				ColoredString(" HP\n", HealthColorCode(&hero->Party[i])); hero->yPosAdd(1);
			}
		}

		if (hero->hasCompanion)
			hero->yPosAdd(1);

		mvprintw(hero->yPosGet(), 0, "Versus"); hero->yPosAdd(2);

		for (int i = 0; i < enemyCount; i++)
		{
			if (hero->Opponent[i].healthGet() > 0)
			{
				mvprintw(hero->yPosGet(), 0, "%s:\t  %i/%i", hero->Opponent[i].nameGet().c_str(), hero->Opponent[i].healthGet(), hero->Opponent[i].maxHealthGet()); hero->yPosAdd(1);
				ColoredString(" HP\n", HealthColorCode(&hero->Opponent[i]));
			}
		}

		mvprintw(0, 28, "Choose an action");
		mvprintw(1, 28, "1. Attack\n");
		mvprintw(2, 28, "2. Use Ability\n");
		mvprintw(3, 28, "3. Use Item\n");
		mvprintw(4, 28, "4. Look at");
		mvprintw(5, 28, "9. Run");
		mvprintw(6, 28, ">");

		//move(7, 0);
		hero->yResetSet(7);
		hero->yPosAdd(2);
		for (int i = 0; i < battleSize; i++)
		{
			if (beingPointer[i]->healthGet() > 0)
			{
				bool stunned = false;
				for (int j = 0; j < MAX_EFFECTS; j++)
				{
					if (beingPointer[i]->getEffect(j)->nameGet() != "NULL")
						beingPointer[i]->getEffect(j)->modTime(beingPointer[i], &*hero, -1);

					if (beingPointer[i]->getEffect(j)->typeGet() == "Stun")
						stunned = true;

					if (beingPointer[i]->getEffect(j)->typeGet() == "Heal")
					{
						int heal = beingPointer[i]->getEffect(j)->valueGet() + (rand() % 3 - 1);

						if (beingPointer[i]->typeGet() == "Player")
						{
							mvprintw(hero->yPosGet(), 0, "You heal for %i health, from your %s. ", heal, beingPointer[i]->getEffect(j)->nameGet().c_str()); hero->yPosAdd(2);
						}
						else
						{
							mvprintw(hero->yPosGet(), 0, "%s is healed for %i health, from his %s. ", beingPointer[i]->nameGet().c_str(), heal, beingPointer[i]->getEffect(j)->nameGet().c_str()); hero->yPosAdd(2);
						}

						beingPointer[i]->healthMod(heal);
						HealthOutput(hero, beingPointer[i]);
						SleepC(1500);
					}
					if (beingPointer[i]->getEffect(j)->typeGet() == "Damage")
					{
						int damage = -beingPointer[i]->getEffect(j)->valueGet() + (rand() % 3 - 1);

						if (beingPointer[i]->typeGet() == "Player")
						{
							mvprintw(hero->yPosGet(), 0, "You take %i points of damage, from %s. ", -damage, beingPointer[i]->getEffect(j)->nameGet().c_str()); hero->yPosAdd(2);
						}
						else
						{
							mvprintw(hero->yPosGet(), 0, "%s takes %i points of damage, from %s. ", beingPointer[i]->nameGet().c_str(), -damage, beingPointer[i]->getEffect(j)->nameGet().c_str()); hero->yPosAdd(2);
							hero->killCheck(&*hero, beingPointer[i]);
						}

						beingPointer[i]->healthMod(damage);
						HealthOutput(hero, beingPointer[i]);
						SleepC(1500);
					}
				}

				if (!stunned)
				{
					beingPointer[i]->Attack(hero);
					beingPointer[i]->Stealthed = false;
					SleepC(1500);
				}

				if (hero->healthGet() <= 0)
				{
					if (battleType == 0 || battleType == 3)
					{
						mvprintw(hero->yPosGet(), 0, "Everything goes dark as all sensations slowly fades away..."); hero->yPosAdd(1);
						mvprintw(hero->yPosGet(), 0, "Game over! Try again.\n");
						Pause(); Clear(&*hero);
					}
					else
					{
						mvprintw(hero->yPosGet(), 0, "You are knocked unconcious!"); hero->yPosAdd(2);
						Pause(); Clear(&*hero);
					}

					for (int i = 0; i < ENEMY_LIMIT; i++)
						hero->Opponent[i].Reset();
					hero->yPosReset();
					
					return false; //Perma death, for now?
				}

				for (int j = 0; j < FOLLOWER_LIMIT; j++)
				{
					if (hero->Party[j].nameGet() != "NULL")
					{
						if (hero->Party[j].healthGet() <= 0 && hero->Party[j].nameGet() == "Gerald" && !hero->Party[j].Unconscious)
						{
							hero->Party[j].Unconscious = true;
							hero->Party[j].healthSet(0);
							mvprintw(hero->yPosGet(), 0, "Gerald is knocked unconscious!\n"); hero->yPosAdd(2);
							SleepC(1500);
						}
						else if (hero->Party[j].healthGet() <= 0 && !hero->Party[j].Unconscious)
						{
							mvprintw(hero->yPosGet(), 0, "%s falls in battle...", hero->Party[j].nameGet().c_str()); hero->yPosAdd(2);
							SleepC(1500);
							hero->Party[j].Reset();
						}
					}
				}
				if (CombatOver(hero))
				{
					if (hero->classGet() == "Monk")
						hero->manaSet(hero->maxManaGet());
					hero->yResetSet(0);
					hero->yPosReset();
					return true;
				}
			}
		}
		SleepC(1500);
	}
}

void TournamentDefeat(Player* hero, int rounds)
{
	if (hero->stageGet(1) && !hero->stageGet(2))
	{
		printw("\nDefeat!\nYou finished %i rounds\n", rounds);
		printw("%i gold was collected in prices!\n\n", rounds*5);
		Pause(); clear();
		hero->stageSet(2, false);
		hero->varSet(1, rounds);
		hero->goldMod(rounds * 5);
		hero->healthSet(1);
		return;
	}
	else if (hero->stageGet(2) && !hero->stageGet(3))
	{
		//clear();
		printw("Defeat!\nYou finished %i rounds.\n", rounds);
		if (rounds > hero->varGet(1))
		{
			printw("\nNew record!!\n");
			int gold = (rounds - hero->varGet(1)) * 5;
			hero->varSet(1, rounds);
			hero->goldMod(gold);
			printw("%i gold was collected in prices!\n\n", gold);
		}
		Paragraph(&*hero, "\n\nWant to try again? The tournament is still ongoing.", false, true, true, 0);
		hero->healthSet(1);
		return;
	}
}

void SortInitiative(int initiative[15], Being* being[15])
{
	Being* placeholder;
	int intholder; 

	for (int i = 0; i < 14; i++)
	{
		for (int j = i + 1; j < 15; j++)
		{
			if (initiative[i] < initiative[j] && being[j]->healthGet() > 0 && being[j]->nameGet() != "NULL"
				|| being[i]->nameGet() == "NULL" && being[j]->nameGet() != "NULL")
			{
				placeholder = being[i];
				being[i] = being[j];
				being[j] = placeholder; 

				intholder = initiative[i];
				initiative[i] = initiative[j];
				initiative[j] = intholder;
			}
		}
	}

}