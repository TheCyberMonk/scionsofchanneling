#include "../include/Being.h"
std::ostringstream oss;

void Tyria(Player* hero)
{
	refresh();
	string Choices[9] = { "Explore", "Barracks", "Fighting Pits", "NULL", "NULL", "NULL", "NULL", "Castle", "Leave Town" };

	while (true)
	{
		if (hero->stageGet(10))
			Choices[6] = "Mysterious Symbol";
		if (hero->stageGet(11))
			Choices[6] = "Channelers Hideout";
		if (hero->stageGet(12))
			Choices[4] = "Blacksmith";
		if (hero->stageGet(13))
			Choices[3] = "General Goods Store";
		if (hero->stageGet(14))
			Choices[5] = "Tavern";
		int input = 99;
		
		Clear(&*hero);
		input = ChooseOption("All around you people are going about their daily chores. "
							 "Almost all of the villagers carry arms, ready to defend their home at any time. "
							 "There are plenty of stores and services all around.\n", hero, Choices, true);

		if (input == '1')
		{
			if (!Explore(&*hero))
				return;
		}
			
		if (input == '2')
		{
			if (!Barracks(&*hero))
				return;
		}
		if (input == '3')
		{
			if (!Pits(&*hero))
				return;
		}
		if (input == '4')
			Store(&*hero);
		if (input == '5')
			Blacksmith(&*hero);
		if (input == '6')
			Tavern(&*hero);
		if (input == '7')
		{
			if (hero->stageGet(10))
				Channeler(&*hero);
		}
		if (input == '8')
			Castle(&*hero);
		if (input == '9')
		{
			if (hero->stageGet(0))
			{
				if (!Desert(&*hero))
					return;
			}
			else
				Paragraph(&*hero, "You are too tired after walking the desert for days to embark again so soon.\n", true, true, true, 39);

		}
	}
}

void Blacksmith(Player* hero)
{
	Clear(&*hero);
	static Being Blacksmith("Leon", "Blacksmith", "NPC", 3, 12, 1, 6, 1, 2, 5, 50);
	Blacksmith.Talk(&*hero, "Have a look at my wares, if there's anything you want to try out let me know.", true, true, true, 39);
	string Choices[9] = { "Buy Weapons", "Buy Armor", "Sell Weapons", "Sell Armor", "NULL", "NULL", "NULL", "NULL", "Leave" };

	Weapon weapon;
	Blacksmith.wInventory[0].idTransform(2);
	Blacksmith.wInventory[1].idTransform(1);
	if (hero->levelGet() >= 3)
		Blacksmith.wInventory[2].idTransform(3);

	Armor armor;
	Blacksmith.aInventory[1].idTransform(5);	//Robes

	if (hero->classGet() != "Channeler")
	{
		Blacksmith.aInventory[0].idTransform(4);
		if (hero->levelGet() >= 3)
			Blacksmith.aInventory[2].idTransform(30);
		if (hero->levelGet() >= 4)
		{
			Blacksmith.aInventory[3].idTransform(31);

			if (hero->classGet() == "Berserker")
				Blacksmith.aInventory[4].idTransform(6);
		}
		if (hero->levelGet() >= 5)
			Blacksmith.aInventory[5].idTransform(32);
	}

	int input = 0;
	int selection = 0;

	while (input != '9')
	{
		oss.str(""); oss.clear();
		oss << "Vendor Gold: " << Blacksmith.goldGet() << endl << 
			   "Your Gold: " << hero->goldGet() << "\n";

		input = 0;
		hero->yPosReset();
		input = ChooseOption(oss.str(), hero, Choices, true);

		if (input == '1') 
		{
			selection = ChooseWeapon("Have a look at my wares!", &*hero, Blacksmith.wInventory, true);

			if (selection >= 0)
			{
				weapon.idTransform(Blacksmith.wInventory[selection].idGet());
				mvprintw(hero->yPosGet(), 0, "Buying %s for %i Gold", weapon.nameGet().c_str(), weapon.valueGet()); hero->yPosAdd(1);
				bool confirmation = Question(&*hero, "Are you sure?");

				if (!confirmation)
					input = 0;
				else if (hero->goldGet() < weapon.valueGet() && selection != -1 && confirmation)
					Blacksmith.Talk(&*hero, "Seems you can't afford this weapon right now.\nCome back later!", true, true, true, 39);
				else if (weapon.valueGet() > 0 && confirmation)
				{
					hero->goldMod(-weapon.valueGet());
					Blacksmith.goldMod(weapon.valueGet());
					int wpn = hero->pickupWeapon(weapon);
					hero->wInventory[wpn].Use(hero);
					printw("\"Thank you for your purchase, anything else?\"");
				}
			}
		}
		if (input == '2')
		{
			selection = ChooseArmor("Have a look at my wares!", &*hero, Blacksmith.aInventory, true);

			if (selection >= 0)
			{
				armor.idTransform(Blacksmith.aInventory[selection].idGet());

				mvprintw(hero->yPosGet(), 0, "Buying %s for %i Gold", armor.nameGet().c_str(), armor.valueGet()); hero->yPosAdd(1);
				bool confirmation = Question(&*hero, "Are you sure?"); 

				if (!confirmation)
					input = 0;
				else if (hero->goldGet() < armor.valueGet() && input != 0 && confirmation)
					Blacksmith.Talk(&*hero, "Seems you can't afford this armor right now.\nCome back later!", true, true, true, 39);
				else if (armor.valueGet() > 0 && confirmation)
				{
					hero->goldMod(-armor.valueGet());
					Blacksmith.goldMod(armor.valueGet());
					armor.Use(&*hero);
					printw("\"Thank you for your purchase, anything else?\"");
				}
			}
		}
		if (input == '3')
		{
			selection = ChooseWeapon("What do you have for me?", &*hero, hero->wInventory, true);

			if (selection >= 0)
			{
				int value = hero->wInventory[selection].valueGet() / 2;

				printw("\n\nSelling %s for %i Gold\n", hero->wInventory[selection].nameGet().c_str(), value);
				bool confirmation = Question(&*hero, "Are you sure?");

				if (Blacksmith.goldGet() < value && selection >= 0 && confirmation)
					Blacksmith.Talk(&*hero, "I can't afford that.", true, true, true, 39);
				else if (value > 0 && selection >= 0 && confirmation)
				{
					hero->goldMod(value);
					Blacksmith.goldMod(-value);
					printw("\n%s sold ", hero->wInventory[selection].nameGet().c_str());
					printw("for %i gold.\n\n", value);
					hero->wInventory[selection].Reset();
					SortWeaponInventory(hero->wPointer);
					SleepC(2000);
				}
			}
		}
		if (input == '4')
		{
			selection = ChooseArmor("What do you have for me?", &*hero, hero->aInventory, true);

			if (selection >= 0)
			{
				int value = hero->aInventory[selection].valueGet() / 2;

				if (Blacksmith.goldGet() < value && selection >= 0)
					Blacksmith.Talk(&*hero, "I can't afford that.", true, true, true, 39);
				else if (value > 0 && selection >= 0)
				{
					printw("\n\nSelling %s for %i Gold\n", hero->aInventory[selection].nameGet().c_str(), value);
					bool confirmation = Question(&*hero, "Are you sure?");

					if (Blacksmith.goldGet() < value && selection >= 0 && confirmation)
						Blacksmith.Talk(&*hero, "I can't afford that.", true, true, true, 39);
					else if (value > 0 && selection >= 0 && confirmation)
					{
						hero->goldMod(value);
						Blacksmith.goldMod(-value);
						printw("\n%s sold ", hero->aInventory[selection].nameGet().c_str());
						printw("for %i gold.\n\n", value);
						hero->aInventory[selection].Reset();
						SortArmorInventory(hero->aPointer);
						SleepC(2000);
					}
				}
			}
		}
	}
}

void Store(Player* hero)
{
	Clear(&*hero);
	Being Clerk("Troy", "Clerk", "NPC", 1, 8, 4, 1, 2, 1, 2, 50);
	Clerk.Talk(&*hero, "Welcome, everything is for sale! Please have a look around.\n", false, false, true, 39);
	string Choices[9] = { "Buy Potions", "Buy Scrolls", "NULL", "Sell Potions", "Sell Scrolls", "NULL", "NULL", "NULL", "Leave" };
	if (hero->classGet() == "Channeler") {
		Choices[2] = "Buy Spell Tomes";
		Choices[5] = "Sell Spell Tomes";
	}

	Scroll scroll;
	Clerk.sInventory[0].idTransform(19);
	Clerk.sInventory[1].idTransform(20);
	Clerk.sInventory[2].idTransform(21);
	Clerk.sInventory[3].idTransform(29);

	Potion potion;
	Clerk.pInventory[0].idTransform(7);
	Clerk.pInventory[1].idTransform(8);
	Clerk.pInventory[2].idTransform(34);
	Clerk.pInventory[3].idTransform(35);

	SpellTome tome;
	Clerk.tInventory[0].idTransform(9);
	Clerk.tInventory[1].idTransform(10);
	Clerk.tInventory[2].idTransform(11);
	Clerk.tInventory[3].idTransform(12);
	Clerk.tInventory[4].idTransform(13);
	Clerk.tInventory[5].idTransform(37);

	if (hero->levelGet() >= 2)
		Clerk.tInventory[6].idTransform(14);

	if (hero->levelGet() >= 3)
	{
		Clerk.tInventory[7].idTransform(15);
		Clerk.tInventory[8].idTransform(16);
	}

	int input = 0;
	int selection = 0;
	int amount = -1;
	while (input != '9')
	{
		oss.str(""); oss.clear();
		oss << "Vendor Gold: " << Clerk.goldGet() << endl <<
			   "Your Gold: " << hero->goldGet() << "\n";

		input = 0;
		input = ChooseOption(oss.str(), hero, Choices, true);
		printw("\n");

		if (input == '1')
		{
			selection = ChoosePotion("This is my selection of potions.", &*hero, Clerk.pInventory, true);

			if (selection >= 0)
			{
				potion.idTransform(Clerk.pInventory[selection].idGet());

				amount = -1;
				while (amount <= 0 && amount < 10)
				{
					amount = GetInt(0, 55, "How many would you like?", false);
				}
				if (amount != 0)
				{
					mvprintw(2, 55, "Buying %i %s for %i Gold\n", amount, potion.nameGet().c_str(), potion.valueGet()*amount);
					if (Question(3, 55, "Are you sure?", false))
					{
						if(hero->goldGet() < (potion.valueGet() * amount))
							Clerk.Talk(&*hero, "Seems you can't afford this right now.\nCome back later!", true, true, true, 39);
						else
						{
							hero->goldMod(-potion.valueGet() * amount);
							Clerk.goldMod(potion.valueGet() * amount);
							hero->pickupPotion(potion, amount);
							mvprintw(6, 55, "\"Thank you for your purchase, anything else?\"");
							SleepC(2000);
							amount = -1;
						}
					}
				}
			}
		}
		if (input == '2')
		{
			selection = ChooseScroll("Interested in the magical arts?", &*hero, Clerk.sInventory, true);

			if (selection >= 0)
			{
				scroll.idTransform(Clerk.sInventory[selection].idGet());

				clear();
				scroll.Status(&*hero, true);
				printw("Buying for  Gold\n", scroll.valueGet());
				bool confirmation = Question(&*hero, "Are you sure?");

				if (hero->goldGet() < scroll.valueGet() && input != 0 && confirmation)
					Clerk.Talk(&*hero, "Seems you can't afford this right now.\nCome back later!", true, true, true, 39);
				else if (scroll.valueGet() > 0 && confirmation)
				{
					hero->goldMod(-scroll.valueGet());
					Clerk.goldMod(scroll.valueGet());
					hero->pickupScroll(scroll);

					Clerk.Talk(&*hero, "Thank you for your purchase, anything else?", true, true, true, 39);
				}
			}
		}
		if (input == '3' && hero->classGet() == "Channeler")
		{
			selection = ChooseTome("Interested in the magical arts?", &*hero, Clerk.tInventory, true);

			if (selection >= 0)
			{
				tome.idTransform(Clerk.tInventory[selection].idGet());

				clear();
				tome.Status(&*hero, true);
				printw("Buying for %i Gold\n", tome.valueGet());
				bool confirmation = Question(&*hero, "Are you sure?");

				if (hero->goldGet() < tome.valueGet() && input != 0 && confirmation)
					Clerk.Talk(&*hero, "Seems you can't afford this right now.\nCome back later!", true, true, true, 39);
				else if (tome.valueGet() > 0 && confirmation)
				{
					hero->goldMod(-tome.valueGet());
					Clerk.goldMod(tome.valueGet());
					hero->pickupTome(tome);

					Clerk.Talk(&*hero, "Thank you for your purchase, anything else?", true, true, true, 39);
				}
			}
		}
		if (input == '4')
		{
			int y = 0;
			selection = ChoosePotion("You wish to sell?", &*hero, hero->pInventory, false);
			if (selection >= 0)
			{
				int value = hero->pInventory[selection].valueGet() / 2;
				if (hero->pInventory[selection].amountGet() != 1)
				{
					amount = -1;
					while (amount < 0)
					{
						amount = GetInt(y, 55, "How many would you like to sell?", false); y += 2;

						if (amount > hero->pInventory[selection].amountGet())
							amount = -1;
					}
				}
				else
					amount = 1;

				if (amount > 0)
				{
					//clear();
					mvprintw(y, 55, "Selling %i %s for %i gold", amount, hero->pInventory[selection].nameGet().c_str(), value*amount); y++;
					bool confirmation = Question(y, 55, "Are you sure?", false); y++;

					if (value * amount <= Clerk.goldGet() && confirmation)
					{
						hero->goldMod(value * amount);
						Clerk.goldMod(-(value * amount));

						mvprintw(y, 55, "%s sold ", hero->pInventory[selection].nameGet().c_str());
						printw("for %i gold.\n\n", value*amount); y++;
						hero->pInventory[selection].amountMod(-amount);
						SortTomeInventory(hero->tPointer);
						amount = -1;
					}
					else if (confirmation)
						mvprintw(y, 55, "\"Sorry, I cannot afford that at this time.\""); y++;
				}

			}
		}
		if (input == '5')
		{
			selection = ChooseScroll("You wish to sell?", &*hero, hero->sInventory, true);
			if (selection >= 0)
			{
				int value = hero->sInventory[selection].valueGet() / 2;

				clear();
				printw("Selling %s for %i gold.\n", hero->sInventory[selection].nameGet().c_str(), value);
				bool confirmation = Question(&*hero, "Are you sure?");

				if (value <= Clerk.goldGet() && confirmation)
				{
					hero->goldMod(value);
					Clerk.goldMod(-value);

					clear();
					printw("%s sold ", hero->sInventory[selection].nameGet().c_str());
					printw("for %i gold.\n\n", value);
					hero->sInventory[selection].Reset();
					SortScrollInventory(hero->sPointer);
					Pause(); clear();
				}
				else if (confirmation)
					Clerk.Talk(&*hero, "Sorry, I cannot afford that at this time.", true, true, true, 39);
			}
		}
		if (input == '6' && hero->classGet() == "Channeler")
		{
			selection = ChooseTome("You wish to sell?", &*hero, hero->tInventory, true);
			if (selection >= 0)
			{
				int value = hero->tInventory[selection].valueGet() / 2;

				clear();
				printw("Selling %s for %i gold.\n", hero->tInventory[selection].nameGet().c_str(), value);
				bool confirmation = Question(&*hero, "Are you sure?");

				if (value <= Clerk.goldGet() && confirmation)
				{
					hero->goldMod(value);
					Clerk.goldMod(-value);

					clear();
					printw("%s sold ", hero->tInventory[selection].nameGet().c_str());
					printw("for %i gold.\n\n", value);
					hero->tInventory[selection].Reset();
					SortTomeInventory(hero->tPointer);
					Pause(); clear();
				}
				else if (confirmation)
					Clerk.Talk(&*hero, "Sorry, I cannot afford that at this time.", true, true, true, 39);
			}
		}
	}
}
bool Barracks(Player* hero)
{
	Companion Gerald(3, "Gerald", "Squad Commander", "NPC", 3, 25, 5, 5, 2, 4, 5);
	if (hero->stageGet(3) && !hero->stageGet(4))
	{
		bool clearr = false;
		int input = 0;
		while (input != '2')
		{
			if (clearr)
				clear();
			else
			{
				clearr = true;
				printw("\n");
			}
			printw("1. Report for duty\n");
			printw("2. Rest\n");
			printw("9. Leave\n>");
			input = getch();
			hero->keyBindingCheck(input);

			if (input == '1')
			{
				Clear(&*hero);
				Gerald.Talk(&*hero, "You here to join the defence? \nMy squad and I were just about to join the fray.\n\n", false, false, false, 39);
				if (Question(&*hero, "Join the fight? (This is a good time to save)"))
				{
					Paragraph(&*hero, "You follow Gerald through the gates out of the city. And what you see is complete chaos, the fight has obviously gone on for some time and devolved into a skirmish.\n\n\n", true, false, false, 39);
					Paragraph(&*hero, "Gerald, The Squad Commander:\n", false, false, false, 0);
					Paragraph(&*hero, "CHAAAARGEEEE!!", false, false, false, 200);
					Paragraph(&*hero, "\n\nYou take a deep breath and then charge alongside your squad.", false, true, true, 39);
					hero->addCompanion(3);
					for (int i = 0; i < 4; i++)
						hero->addCompanion(1);

					if (!BattleGroup(hero, 9, 2, 3))
						return false;

					for (int i = 0; i < FOLLOWER_LIMIT; i++)
						hero->Party[i].Reset();

					//Paragraph(&*hero, "After the last of the abominations fall to the ground, Gerald approaches you.", true, false, true, 45);
					Gerald.Talk(&*hero, "That was a fine scrap, thanks for the help. \nI'll let Hadgar know you did a damn good job.", true, true, true, 39);
					hero->stageSet(4, false);
					return true;
				}
			}
			if (input == '9')
				return true;
		}
	}

	Paragraph(&*hero, "You find the bed assigned to you and go to sleep.\nYou had a good nights rest\nHealth and mana fully restored!", false, true, true, 0);
	hero->healthMod(hero->maxHealthGet());
	hero->manaMod(hero->maxManaGet());
	
	for (int i = 0; i < FOLLOWER_LIMIT; i++)
	{
		if (hero->Party[i].nameGet() != "NULL")
		{
			hero->Party[i].healthMod(hero->Party[i].maxHealthGet());
			hero->Party[i].manaMod(hero->Party[i].maxManaGet());

			for (int j = 0; j < MAX_EFFECTS; j++)
				hero->Party[i].getEffect(j)->Reset();
		}
		if (hero->Party[i].typeGet() == "Conjured")
			hero->Party[i].Reset();
	}
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
	hero->RageUsed = false;

	if (hero->stageGet(0) == false)
	{
		//Talk with Hadgar again and get your first quest
		hero->stageSet(0, false);
	}
	return true;
}
void Tavern(Player* hero)
{
	string Choices[9] = { "Talk to the locals", "Buy a beer", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Leave" };
	int input = 0;
	while (input != '9')
	{
		input = ChooseOption(oss.str(), hero, Choices, true);

		if (input == '2')
		{
			if (hero->goldGet() > 0)
			{
				bool drunk = false;
				for (int i = 0; i < MAX_EFFECTS; i++)
				{
					if (hero->getEffect(i)->nameGet() == "Drunk")
						drunk = true;
				}
				if (true)
				{
					Paragraph(&*hero, "You spend a gold, and knock down a few drinks. You feel uninhibited but dizzy(+1 Strength, -1 Intelligence).\n", true, true, true, 39);

					hero->goldMod(-1);
					hero->addEffect(12);
					hero->addEffect(13);
				}
				else
				{
					Paragraph(&*hero, "You feel like you had enough, you've got adventuring to do after all!\n", true, true, true, 39);
				}
			}
			else
				Paragraph(&*hero, "You don't have the money you poor fuck.", true, true, true, 0); // maybe rewrite before release
		}
		if (input == '1')
		{
			Paragraph(&*hero, "You spend some time relaxing and talking to the locals.\n", true, true, true, 0);

			int random = rand() % 100 + 1;
			random = 40;

			if (random < 20)
			{
				Paragraph(&*hero, "", true, true, true, 39);

				if (hero->varGet(99) == 0)
				{
					hero->varSet(99, 1);
					Paragraph(&*hero, "", true, true, true, 39);
				}
				else if (hero->varGet(99) == 1)
				{
					hero->varSet(99, 2);
					Paragraph(&*hero, "", true, true, true, 39);
				}
				else if (hero->varGet(99) == 2)
				{
					hero->varSet(99, 0);
					Paragraph(&*hero, "", true, true, true, 39);
				}
			}
			else if (random >= 20 && random < 40)
			{
				Paragraph(&*hero, "", true, true, true, 39);
				//Useful information

				if (hero->varGet(98) == 0)
				{
					hero->varSet(98, 1);
					Paragraph(&*hero, "", true, true, true, 39);
				}
				else if (hero->varGet(98) == 1)
				{
					hero->varSet(98, 2);
					Paragraph(&*hero, "", true, true, true, 39);
				}
				else if (hero->varGet(98) == 2)
				{
					hero->varSet(98, 0);
					Paragraph(&*hero, "", true, true, true, 39);
				}
			}
			else if (random >= 40 && random < 80)
			{
				Paragraph(&*hero, "The talk of the tavern today is of myths, gods, and days long since passed.", true, true, true, 39);

				if (random >= 40 && random < 50)
				{
					if (hero->varGet(97) == 0)
					{
						hero->varSet(97, 1);
						Paragraph(&*hero, "There are two types of deities in this world.\nThe Ayans, the immortals and The Davas, the creators. "
							"\n\nAyans are said to be beings from another plane of existance. \nTrancending their mortal bodies a long time "
							"ago. There are very few of them left, most gave up their immortality to be able to directly interact with the "
							"mortal world and became part of The Davas. A guard also jokingly added a comment about boredom. They are omnipresent "
							"beings. Unable to act directly, they instead pull the threads of fate to their will. In old times powerful channelers "
							"found a way to communicate with The Ayans, but the means to do so has been lost. "
							"\n\nThe Davas created this world tens of thousands of years ago. \nOnce Ayans, they gave up their immortality for "
							"the power to create and take physical form. It is not known if any of the worldbuilders still live, few live beyond "
							"a thousand years. Most of them have vastly different ideology, so strife between Davas is not an uncommon occurence.\n", true, true, true, 39);
					}
					else if (hero->varGet(97) == 1)
					{
						hero->varSet(97, 2);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(97) == 2)
					{
						hero->varSet(97, 0);
						//You learn of Morgana, the lady of the night.
						Paragraph(&*hero, "", true, true, true, 39);
					}
				}
				else if (random >= 50 && random < 60)
				{
					Paragraph(&*hero, "You learn of ancient civilizations.", true, true, true, 39);

					if (hero->varGet(96) == 0)
					{
						hero->varSet(96, 1);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(96) == 1)
					{
						hero->varSet(96, 2);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(96) == 2)
					{
						hero->varSet(96, 0);
						Paragraph(&*hero, "", true, true, true, 39);
					}
				}
				else if (random >= 60 && random < 70)
				{
					Paragraph(&*hero, "You learn of the myths surrounding the origins of the blight", true, true, true, 39);

					if (hero->varGet(95) == 0)
					{
						hero->varSet(95, 1);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(95) == 1)
					{
						hero->varSet(95, 2);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(95) == 2)
					{
						hero->varSet(95, 0);
						Paragraph(&*hero, "", true, true, true, 39);
					}
				}
				else if (random >= 70 && random < 80)
				{
					Paragraph(&*hero, "", true, true, true, 39);

					if (hero->varGet(94) == 0)
					{
						hero->varSet(94, 1);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(94) == 1)
					{
						hero->varSet(94, 2);
						Paragraph(&*hero, "", true, true, true, 39);
					}
					else if (hero->varGet(94) == 2)
					{
						hero->varSet(94, 0);
						Paragraph(&*hero, "", true, true, true, 39);
					}
				}
			}
			else
			{
				Paragraph(&*hero, "You have a good time, but you don't really learn anything new", true, true, true, 39);
			}
		}
	}
}
bool Pits(Player* hero)
{
	Enemy opponent;

	bool clearr = false;
	int input = -1;
	if ((hero->stageGet(1) || hero->stageGet(2)) && !hero->stageGet(3))
	{
		while (input != '1' && input != '2')
		{
			if (clearr)
				clear();
			else
			{
				clearr = true;
				printw("\n");
			}

			printw("1. Join the tournament\n");
			printw("2. Fight mutants\n");
			printw("9. Leave\n>");
			input = getch();

			if (input == '9')
				return true;
		}
		if (input == '1')
		{
			//Tournament
			int round = 0;
			while (round < 10)
			{
				input = 99;
				clear();
				printw("%s\n", hero->nameGet().c_str());
				printw("%i/%i HP\n", hero->healthGet(), hero->maxHealthGet());
				if (hero->maxManaGet() > 0) 
				{
					printw("%i/%i MP\n", hero->manaGet(), hero->maxManaGet());
				}
				printw("\nRound: %i/10\n", round+1);
				printw("1: Enter the pit\n");
				printw("2: Use Item\n");
				printw("3: Use Spell\n");
				printw("9: Leave the tournament\n>");
				input = getch();
				hero->keyBindingCheck(input);

				if (input == '1')
				{
					if (round == 0 || round == 1)
					{
						if (BattleGroup(hero, 2, 0, 1))
							round++;
						else
						{
							TournamentDefeat(hero, round);
							return true;
						}
					}
					else if (round == 2 || round == 3)
					{
						if (BattleGroup(hero, 3, 0, 1))
							round++;
						else
						{
							TournamentDefeat(hero, round);
							return true;
						}
					}
					else if (round == 4 || round == 5)
					{
						if (BattleGroup(hero, 2, 1, 1))
							round++;
						else
						{
							TournamentDefeat(hero, round);
							return true;
						}
					}
					else if (round == 6 ||  round == 7)
					{
						if (BattleGroup(hero, 3, 1, 1))
							round++;
						else
						{
							TournamentDefeat(hero, round);
							return true;
						}
					}
					else if (round == 8 || round == 9)
					{
						if (BattleGroup(hero, 2, 2, 1))
							round++;
						else
						{
							TournamentDefeat(hero, round);
							return true;
						}
					}
					if (round == 10)
					{
						//Do more here
						if (hero->varGet(1) != 10)
						{
							int gold = 100 - hero->varGet(1);
							hero->stageSet(2, false);
							hero->varSet(1, 10);
							hero->goldMod(gold);
							Paragraph(&*hero, "You won the tournament!\n" + to_string(gold) + " gold collected in prizes!", true, true, true, 39);
							return true;
						}
						else
						{
							Paragraph(&*hero, "You won the tournament!", true, true, true, 39);
							return true;
						}
					}
				}
				if (input == '2')
					hero->inventoryDisplay();
				if (input == '3')
					hero->spellDisplay();
				if (input == '9')
				{
					Clear(&*hero);
					mvprintw(hero->yPosGet(), 0, "If you leave the tournament now, you will have to start over."); hero->yPosAdd(1);
					if (Question(&*hero, "Are you sure?"))
						return true;
				}
				if (hero->healthGet() <= 0)
				{
					hero->healthSet(1);
					return true;
				}
			}
		}
	}
	clearr = false;
	while (true)
	{
		Paragraph(&*hero, "How many enemies do you wish to fight?(0-9)", false, false, false, 0);
		input = getch();

		if (input == '0')
			return true;
		else if (input > 48 && input < 58)
		{
			if (BattleGroup(hero, input - 48, 1, 0))
				return true;
			else
				return false;
		}
	}
}
void Channeler(Player* hero)
{
	printw("\n\n");
	if (hero->stageGet(10))	//If they've been here before without unlocking the door.
	{
		Paragraph(&*hero, "You return to the mysterious symbol, contemplating if you should try to activate it. "
			"You study it again, and it confirms what you recall. "
			"The spell to activate the symbol requires life essence to be channeled into it. "
			"But you can only guess at what might happen then...\n\n", false, false, false, 39);
		if (Question(&*hero, "Go ahead?"))
		{
			if (hero->levelGet() >= 4)
			{
				//Get access to the Channelers Hideout
				hero->stageSet(11, false);
			}
			else
			{
				//Revise?
				Paragraph(&*hero, "\nImmediatly as you begin channeling, you realize something is wrong. "
					" The life force you were channeling slips away from you, and you collapse to your knees. "
					"After a few moments you collect yourself, but you still feel drained. "
					"While walking away you wonder what that was all about...", false, true, true, 39);
				hero->healthMod(-1);
			}
		}
		else
		{
			Paragraph(&*hero, "\nYou decide against activating the symbol. "
				"Some things are better left unanswered.", false, false, true, 39);
		}
		return;
	}
	if (!hero->stageGet(10))
	{
		hero->stageSet(10, false);
		Paragraph(&*hero, "As you search the large city you come upon an etching on one of the stone walls. "
			"The etching is compromised of numerous geometrical shapes interwining in intricate patterns. "
			"You have no idea what it's supposed to mean.\n\n", false, false, false, 39);
	}
	if (!hero->stageGet(11))
	{
		Paragraph(&*hero, "You recognize part of the etching as the symbol of life essence that is used in channeling magic. "
			"If you channeled some of your own essence into the symbol it would activate the spell. "
			"But you can only guess at what might happen then...\n\n", false, false, false, 39);
		if (Question(&*hero, "Go ahead?"))
		{
			if (hero->levelGet() >= 4)
			{
				//Get access to the Channelers Hideout
				hero->stageSet(11, false);
			}
			else
			{
				//Revise?
				Paragraph(&*hero, "\nImmediatly as you begin channeling, you realize something is wrong. "
				" The life force you were channeling slips away from you, and you collapse to your knees. "
				"After a few moments you collect yourself, but you still feel drained. "
				"While walking away you wonder what that was all about...", false, true, true, 39);
				hero->healthMod(-1);
			}
		}
		else
		{
			Paragraph(&*hero, "\nYou find the prospect of tempering with unkown magic quite hazardous. "
				"And atleast for now, you decide to leave it alone.", false, false, true, 39);
		}
	}
}
bool Explore(Player* hero)
{
	srand(time(NULL));
	Paragraph(&*hero, "You take some time exploring the various streets and alleys for anything interesting.\n", false, false, false, 39);
	for (int i = 0; i < 2; i++)
	{
		int chance = rand() % 100 + 1;

		if (chance <= 5)
		{
			int goldFound = rand() % 30 + 15;
			Paragraph(&*hero, "You find a bag of gold simply laying on the ground, lucky find! \nIt contains " + to_string(goldFound) + " gold.", false, true, true, 0);
			hero->goldMod(goldFound);
			return true;
		}
		else if (chance > 5 && chance <= 10 && !hero->stageGet(11) && !hero->stageGet(10))
		{
			Channeler(hero);
			return true;
		}
		else if (chance > 5 && chance <= 10 && hero->stageGet(10))
		{
			Paragraph(&*hero, "For some reason you find yourself back at the mysterious sign. It almost seems to be drawing you to it.", false, true, true, 39);
			Channeler(hero);
			return true;
		}
		else if (chance > 10 && chance <= 20 && !hero->stageGet(12))
		{
			Paragraph(&*hero, "You walk the streets, and come upon a building with a sign that depicts an anvil. The shop seems to be very popular and people are constantly coming and leaving. "
				"You do get quite a few looks as you enter, and the guy behind the counter greets you heartily. \n\n\"A new face! It's been too long, let me know if there's anything I can help you with."
				" I'm Leon, the blacksmith. Nice to meet ya.\"", false, true, true, 39);
			hero->stageSet(12, false);

			Blacksmith(hero);
			return true;
		}
		else if (chance > 20 && chance <= 35 && !hero->stageGet(13))
		{
			Paragraph(&*hero, "Not too far off the town square where the fighting pits are, there is a large three story wooden building with the sign of a pouch by the door. The owner seems a bit suprised "
				"as you enter, but greets you just the same.\n", false, false, false, 39);
			hero->stageSet(13, false);

			Store(hero);
			return true;
		}
		else if (chance > 35 && chance <= 45 && !hero->stageGet(14))
		{
			hero->stageSet(14, false);
			Paragraph(&*hero, "You hear some loud ruckus and the sweet tunes of a panflute coming from a nearby building, you can assume that it's the local tavern. Suddenly the music cuts out and you can hear "
				"lots of crashing noices coming from the tavern.\n", false, false, false, 39);
			if (Question(&*hero, "Join the brawl?"))
			{
				if (!BattleGroup(hero, 3, 0, 1))
				{
					Paragraph(&*hero, "You come too to a tavern bustling with energy, everyone seems to have been invigorated by the friendly brawl.", true, true, true, 39);
					Tavern(hero);
					return true;
				}
				Paragraph(&*hero, "After a fine scrap you are the last person standing! Weirdly enough the people you just knocked the lights out of now "
					"treat you as their best friend.", true, true, true, 39);
				Tavern(hero);
				return true;
			}
			else
			{
				Paragraph(&*hero, "You decide to not get involved, you make note of the location however and decide to maybe come back some other time.", true, true, true, 39);
			}
			return true;
		}
		else if (chance > 45 && chance <= 55)
		{
			Paragraph(&*hero, "You come across a vendor stall seller currently being shook down for gold by a rough looking individual with a knife and a scar across his face.\n", false, false, false, 39);
			if (Question(&*hero, "Help out the vendor?"))
			{
				Paragraph(&*hero, "You stand in front of the vendor to try and talk the robber down, but he is very on edge and jumps at you!", false, false, true, 39);
				if (!BattleGroup(hero, 1, 101, 3))
					return false;
				Paragraph(&*hero, "The vendor is overjoyed by you saving his livelyhood and offers as much gold as he can spare as compensation. You receive 20 gold!", false, false, true, 39);	//Add option to decline?
				hero->goldMod(20);
			}
			else
				Paragraph(&*hero, "\nYou decide that it's none of your business and move about yours. In the corner of your eye you see the Ruffian making off with a bag of gold.", false, true, true, 39);
			return true;
		}
		else if (chance > 55 && chance <= 65 && !hero->stageGet(15))
		{
			Paragraph(&*hero, "Walking around you spot a beautiful statue of a middle aged woman wielding a pristine curved sword. A man with a brimmed hat is leaning against it's base carving on a piece "
				"of wood. \n\nHe senses you, looks up and says. \"You look new, I imagine you haven't heard about Alissa the Swordmaster. " //Temporary title?
				"It's quite a story, would you like me to tell it?\"\n", false, false, false, 39); 

			if (Question(&*hero, "Listen to the forthcoming man?"))
			{
				Clear(&*hero);
				Paragraph(&*hero, "\"They say her magical sword could cut through air itself, sending a wave of destruction towards her foe. She is the one who led the first refugees to the city, and "
					"claimed it for the people. Everything we have here today, is all thanks to her. She gave her life defending it, and we will continue to do so in her name.\" \n\nYou thank him "
					"for the story, and find a new appreciation for the opportunities this city bring for you and humanity, and the person who made it possible.", false, true, true, 39);

			}
			else
			{
				Clear(&*hero);
				Paragraph(&*hero, "Not really interested you turn him down and move on. While walking away you can hear the man say almost to himself, "
					"\"Well... You'll hear of her sooner or later anyways.\" ", false, true, true, 39);
			}

			hero->stageSet(15, false);
			return true;
		}
		else if (chance > 65 && chance <= 75)
		{
			Paragraph(&*hero, "\"CAWW CAWW\" you hear in the distance, followed by screams of the townsfolk, you follow the sound and find that they are being "
				"attacked by mutant crows which must have flown over the wall.", false, true, true, 0);
			if (!BattleGroup(hero, 1, 104, 3))
				return false;
			return true;
		}
		else if (chance > 75 && chance <= 85 && !hero->stageGet(17))
		{
			Paragraph(&*hero, "While walking your mind begins to meander. Through all the things you've experienced getting here. It hasn't been easy, and you weren't always alone. "
				"Hopefully this is a whole new start, where you can finally find your place and stop loosing everything you love. Continuing about your day, you feel more motivated than you been in a "
				"long while.", false, true, true, 39); 
			hero->stageSet(17, false);
			return true;
		}
		else if (chance > 85 && chance <= 95)
		{
			Paragraph(&*hero, "The sky turns pitch black and tar like rain falls from the sky. Some of the rain forms into beings that attack.", false, true, true, 39);
			if (!BattleGroup(hero, 1, 103, 3))
				return false;
			hero->stageSet(16, false);
			return true;
		}
		else if (chance > 95 && chance <= 100)
		{
			Paragraph(&*hero, "Turning around a corner you bump into two slim looking individuals, they half-heartedly apologize and move on. A moment later you realize "
				"that one of your gold pouches is missing.\n\n\n", false, false, false, 39);
			if (Question(-1, -1, "Chase after them?", false))
			{
				int d20 = rand() % 20 + 1 + hero->agilityGet();
				if (d20 >= 15)
				{
					Paragraph(&*hero, "\nYou quickly follow after them, they head down another alleyway and you can hear quick footsteps as they begin to sprint. "
						"They are incredibly fast but you're barely able to catch up with them. You tackle them down, and after such a move they're hardly "
						"in the mood for any sensible discourse.", false, true, true, 39);
					if (!BattleGroup(hero, 2, 102, 3))
						return false;
					Paragraph(&*hero, "You recover your gold, and leave them unconscious in the streets to sleep off their stupidity.", true, true, true, 39);
					return true;
				}
				else
					Paragraph(&*hero, "\nYou try to chase after them, but you're not able to keep up at all, they turn down an alleyway and almost dissapears in their haste.", false, false, false, 39);
			}
			else
				Paragraph(&*hero, "\nYou decide a little money is no reason to kick up a fuss, they probably need it more than you anyway.", false, false, false, 39);

			int goldLost = rand() % 30 + 10;
			if (hero->goldGet() < goldLost)
				goldLost = hero->goldGet();
			hero->goldMod(-goldLost);

			Paragraph(&*hero, "\n\nYou count your gold and it seems you're missing " + to_string(goldLost) + " coins.", false, true, true, 39);
			return true;
		}
	}
	Paragraph(&*hero, "You find nothing new nor does aything really happen, you just have a nice little walk around the city. Greeting a few familiar faces as you do.", false, true, true, 39);
	return true;
}
bool Castle(Player* hero)
{
	Being Hadgar("Hadgar", "Commander", "NPC", 10, 80, 15, 25, 8, 15, 100, 500);
	Being Guard("Steve", "Royal Guard", "NPC", 5, 25, 5, 9, 2, 4, 10, 100);

	string Choices[9] = { "Speak with the King", "Find Hadgar", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Leave the Castle" };

	int input = 0;
	while (input != '9')
	{
		input = ChooseOption("The castle is connected by a massive hallway right in the middle.\n"
							 "It extends all the way to the throne room, which you can barely make out.\n"
							 "Decorations of various kinds fill the hallways, from fancy paintings to \n"
							 "bones of dragons\n", hero, Choices, true);

		if (input == '1')
		{
			Guard.Talk(&*hero, "The King does not currently recieve any audiences from the common people. No admittance!", false, false, true, 39);
		}
		if (input == '2')
		{
			Clear(&*hero);
			if (!hero->stageGet(1))
			{
				Paragraph(&*hero, "After asking some guards you learn that Hadgar is currently in his quarters and they point you in the right direction. "
					"You knock on the door and wait, after a pregnant pause he calls you in. \n\nAs you enter you see Hadgar sitting by a large table, "
					"surrounded by books, notes and something that looks like a strategic battlemap. He hastily finishes scrawling a note and stands "
					"up to greet you.\n", false, false, false, 39);

				Hadgar.Talk(&*hero, "Ahh, you came. Have you decided to give us a helping hand?", false, false, false, 39);
				if (Question(&*hero, "Join the cause?"))
				{
					hero->stageSet(1, false);
					Hadgar.Talk(&*hero, "I'm glad to hear it! *He pauses for a moment* Unfortunately, I have an urgent problem to deal with. The mutant bandits have become "
						"rather ferocious in their attacks. So I can't see to you personally at this time. Tell you what, there's going to be a tournament held at the fighting pits. "
						"Why don't you join? It would be advantagous to know what your skills in combat are before sending you off on any missions, and it's a valuable experience. ", false, false, false, 39);
					Hadgar.Talk(&*hero, "You will need some better equipment. Here, buy some with this, 30 gold pieces should be enough. Take some time to train in the pits before you enter."
						" And talk to me again when the tournament is over. Then we can begin discussing your future.", false, false, true, 39);
					hero->goldMod(30);
				}
				else
				{
					Hadgar.Talk(&*hero, "I understand... This might be a lot to take in. If you ever do change your mind just come talk to me again, your help would be most welcome. "
						"You may of course stay as long as you like, but you are expected to earn your keep. You'll have to excuse me, I have a lot to deal with right now."
						"\n\n*He returns to his table and continues his work by pouring over old maps. You can tell he is worried about something*", false, false, true, 39);
				}
			}
			else if (hero->stageGet(2) && !hero->stageGet(3))
			{
				if (hero->varGet(1) == 10)
				{
					//Won the tournament
					Hadgar.Talk(&*hero, hero->nameGet() + "! If it isn't THE champion! I didn't quite expect you to win the whole tournament. That was extraordinary! I can't wait to witness further great feats from you in the coming days.\n", false, false, false, 39);
				}
				else if (hero->varGet(1) > 4)
				{
					//Did well
					Hadgar.Talk(&*hero, "*He gives you a respectful nod as you approach*\nNice fighting out there " + hero->nameGet() +"! I think you can help us out a fair bit.\n", false, false, false, 39);
				}
				else
				{
					//Did poorly
					Hadgar.Talk(&*hero, "Hey there " + hero->nameGet() + ", I saw your fight! Not too bad, but you have a lot to learn. "
						"Make sure you get plenty of training in the pits, I might also train you some myself if I find the time.\n", false, false, false, 39);
				}
				Hadgar.Talk(&*hero, "Regardless, there's bad news. A group of mutants are attacking the city. I need to stay here, but I want you to "
					"report to the barracks to aid in our defence. Good luck.", false, false, true, 39);
				hero->stageSet(3, false);
			}
			else if (hero->stageGet(4) && !hero->stageGet(5))
			{
				Hadgar.Talk(&*hero, hero->nameGet() + "! Good job on the defence, glad to see you're well. *a short pause* I hope this isn't too sudden, but I have a mission that's been waiting around for someone with your particular skills."
				"\n\nThere is a group of liches that have a base near the city. They are channelers that have been affected by the corruption."
				" They seem to be able to channel the corruption itself. And in doing so furthering the decay of the lands."
				"\n\nI want you to seek them out, stop them from tearing this world anymore apart than it already is. One of my own officers, Gerald, volunteered to join this mission, so he will be accompanying you."
				" Do this by any means you see fit, reason with them if you can, slay them if you must. From what I've seen and heard of you these past days I'm confident you are up to this task, and Gerald is a competent warrior."
				"\n\nOnce again, I wish you luck, and may the Nameless one show you the truth of your path.", false, false, true, 39);
				hero->addCompanion(3);
				hero->stageSet(5, false);
			}
			else if (!hero->stageGet(0))
				Paragraph(&*hero, "After asking some guards you learn that the military commander is very busy attending strategic meetings. But he should be available tomorrow morning.\n", false, false, true, 0);
			else
				Paragraph(&*hero, "After asking some guards you learn that the military commander is currently unavailible", false, false, true, 0);
		}
	}
	return true;
}