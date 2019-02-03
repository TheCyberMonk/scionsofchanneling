#include "../include/Being.h"

#pragma region Text Managment

// int kbhit()
// {
// 	int ch = getch();

// 	if (ch != ERR) {
// 		ungetch(ch);
// 		return 1;
// 	}
// 	else {
// 		return 0;
// 	}
// }
int kbhit(void)    /* comment */
{
    int ch, r;

    // turn off getch() blocking and echo
    nodelay(stdscr, TRUE);
    noecho();

    // check for input
    ch = getch();
    if( ch == ERR)      // no input
            r = FALSE;
    else                // input
    {
            r = TRUE;
            ungetch(ch);
    }

    // restore block and echo
    echo();
    nodelay(stdscr, FALSE);
    return(r);
}
void Pause()
{
	//flushinp(); //Clears input buffer so player doesn't accidentally skip
	while (kbhit())
		getch();

	printw("Press ENTER to continue...");
	getch();
	refresh();
}
void Pause(Being* hero)
{
	while (kbhit())
		getch();

	mvprintw(hero->yPosGet(), 0, "Press ENTER to continue...");
	getch();
	refresh();
}
void Clear(Being* hero)
{
	clear();
	hero->yResetSet(0);
	hero->xResetSet(0);
	hero->yPosReset();
	hero->xPosReset();
}
void SleepC(int x)
{
	refresh();
	std::chrono::milliseconds timespan(x);
	std::this_thread::sleep_for(timespan);
}

void PausedString(string output)
{
	clear();
	printw("%s\n\n", output.c_str());
	Pause(); clear();
}

void ClearX(int y, int x)
{
	for(int i = y; i >= 0; i--)
	{
		move(i, x);
		clrtoeol();
	}
}
void ClearY(int y, int x)
{
	for(int i = y; i < MaxY(); i++)
	{
		move(i, x);
		clrtoeol();
	}
}
int CurrentY()
{
	int y, x;
	getyx(stdscr, x, y);
	return y;
}
int CurrentX()
{
	int y, x;
	getyx(stdscr, x, y);
	return x;
}
int MaxY()
{
	int y, x;
	getmaxyx(stdscr, x, y);
	return y;
}
int MaxX()
{
	int y, x;
	getmaxyx(stdscr, x, y);
	return x;
}
void CenterText(string text)
{
	int space = (80 - text.length()) / 2;
	for (int i = 0; i < space; i++)
		printw(" ");

	printw("%s\n", text.c_str());
}
void CenterText(string text, char spacing)
{
	int space = (80 - text.length()) / 2;

	for (int i = 0; i < space; i++)
		printw("%c", spacing);

	printw("%s", text.c_str());

	for (int i = 0; i < space; i++)
		printw("%c", spacing);

	if (space % 2 == 0)
		printw("%c", spacing);
}
void Paragraph(Being* hero, string text, bool cls1, bool cls2, bool pause, int speed)
{
	bool newline = false;
	int maxY, maxX;
	int x = 0;

	getmaxyx(stdscr, maxY, maxX);

	if (cls1)
		Clear(hero);

	for (unsigned int i = 0; i < text.length(); i++)
	{
		mvprintw(hero->yPosGet(), x, "%c", text[i]);
		x++;

		if (kbhit())
		{
			speed = 1;
		}

		if (x % (maxX-10) == 0 && i != 0)
			newline = true;

		if (text[i] == '\n')
		{
			x = 0;
			hero->yPosAdd(1);
		}

		if (newline && text[i] == ' ')
		{
			refresh();
			hero->yPosAdd(1);
			newline = false;
			x = 0;
		}
		SleepC(speed);
	}
	hero->yPosAdd(1);

	if (pause)
	{
		printw("\n\n"); hero->yPosAdd(3);
		Pause();
	}
	if (cls2)
	{
		clear();
		hero->yPosReset();
	}

	while (kbhit()) 
		getch();
}

void ColoredString(string text, int color)
{
	attron(COLOR_PAIR(color));
	printw("%s", text.c_str());
	attroff(COLOR_PAIR(color));
}
void PausedColoredString(string text, int color)
{
	attron(COLOR_PAIR(color));
	clear(); 
	printw("%s\n\n", text.c_str()); 
	Pause();
	attroff(COLOR_PAIR(color));
}
int HealthColorCode(Being* being)
{
	if (being->healthGet() <= being->maxHealthGet() / 3)
		return 1;
	else if (being->healthGet() <= (being->maxHealthGet() / 4) * 3)
		return 2;
	else
		return 3;
}
int ManaColorCode(Being* being)
{
	if (being->manaGet() >= being->maxManaGet() / 4)
		return 4;
	else
		return 5;
}
int KiColorCode(Being* being)
{
	if (being->manaGet() >= being->maxManaGet() / 3)
		return 5;
	else
		return 6;
}
void HealthOutput(Player* hero, Being* being)
{
	printw("(%i/%i", being->healthGet(), being->maxHealthGet());
	ColoredString(" hp", HealthColorCode(being));
	printw(")\n");
}

#pragma endregion

#pragma region Input Managment

int GetInt(int y, int x, string prompt, bool cls)
{
	if(y == -1)
	{
		y = CurrentY();
	}
	if(x == -1)
	{
		x = CurrentX();
	}
	keypad(stdscr, TRUE); 
	noecho();

	if (cls)
		clear();

	mvprintw(y, x, "%s", prompt.c_str());
	mvprintw(y+1, x, ">");
	
	int ch = 0, pos = 0;
	std::ostringstream ostream;
	ostream.str(""); ostream.clear();
	while (ch != 10 || ostream.str() == "")
	{
		getyx(stdscr, y, x);
		ch = getch();
		if(ch == 8 || ch == 127)
		{
			mvdelch(y, x-1);
			ostream << '\b';
		}
		if(ch > 47 && ch < 58) 
		{
			printw("%c", (char)ch);
			ostream << (char)ch;
		}
	}
	int input = 0, temp = 0, skips = 0;
	int length = 0;
	length = ostream.str().length();
	bool skip[100];
	for(int i = 0; i < length; i++)
		skip[i] = false;

	for(int i = 0; i < length; i++)
	{
		if(ostream.str()[length - i - 1] == '\b')
		{
			skip[i] = true;
			skip[i+1] = true;

			if(i > 0)
				skip[i+1] = true;
			skips += 2;
		}
	}
	for(int i = 0; i < length; i++)
	{
		if(!skip[i])
		{
			temp = 1;
			for(int j = 0; j < (i - skips); j++)
			{
				temp *= 10;
			}
			input += ((int)ostream.str()[length - 1 - i] - 48) * temp;
			//printw("\n%i * %i", input, temp);
		}
	}
	keypad(stdscr, FALSE); 
	echo();
	return input;
}
string GetStringInput(Being* hero, string prompt, bool cls)
{
	keypad(stdscr, TRUE); 
	noecho();

	if (cls)
		clear();

	printw("%s\n>", prompt.c_str());
	
	int ch = 0, pos = 0;
	int y, x = 0;
	std::ostringstream ostream;
	ostream.str(""); ostream.clear();
	while (ch != 10 || ostream.str() == "")
	{
		getyx(stdscr, y, x);
		ch = getch();
		if(ch == 8 || ch == 127)
		{
			mvdelch(y, x-1);
			ostream << '\b';
		}
		if(ch > 64 && ch < 91 || ch > 96 && ch < 123) 
		{
			printw("%c", (char)ch);
			ostream << (char)ch;
		}
	}
	string input = ostream.str();

	keypad(stdscr, FALSE); 
	echo();

	return input;
}
bool Question(int y, int x, string question, bool clearr)
{
	if(y == -1)
	{
		y = CurrentY();
	}
	if(x == -1)
	{
		x = CurrentX();
	}

	if(clearr)
		clear();

	int answer = ' ';
	while (answer != 'y' && answer != 'Y' && answer != '+' && answer != 'n' && answer != 'N' && answer != '-' && answer != 43)
	{
		mvprintw(y, x, "%s(y/n|+/-)", question.c_str());
		mvprintw(y+1, x, ">");
		answer = getch();
	}

	if (answer == 'Y' || answer == 'y' || answer == '+' || answer == 43)
		return true;
	if (answer == 'N' || answer == 'n' || answer == '-')
		return false;
}
bool Question(Being* hero, string question)
{
	int answer = ' ';
	while (answer != 'y' && answer != 'Y' && answer != '+' && answer != 'n' && answer != 'N' && answer != '-' && answer != 43)
	{
		mvprintw(hero->yPosGet(), 0, "%s(y/n|+/-)", question.c_str());
		mvprintw(hero->yPosGet() + 1, 0, ">");
		answer = getch();
	}
	hero->yPosAdd(2);
	if (answer == 'Y' || answer == 'y' || answer == '+' && answer != 43)
		return true;
	if (answer == 'N' || answer == 'n' || answer == '-')
		return false;
}

#pragma endregion


static int increment = 0;
void Menu(Player* hero)
{
	int choice = 99;

	while (choice != '0')
	{
		Clear(&*hero);
		printw("1. Display status\n");
		printw("2. Use item\n");
		printw("3. Use ability\n");
		printw("4. Journal\n");
		printw("5. Keybindings\n");
		printw("6. Game Tips\n");
		printw("7. Save Game\n");
		printw("8. Load Game\n");
		printw("9. New Game\n");
		printw("0. Cancel\n>");
		choice = getch();
		refresh();

		if (choice == '1')
			hero->viewStatus();
		if (choice == '2')
			hero->inventoryDisplay(); // In combat = false
		if (choice == '3')
			hero->spellDisplay();
		if (choice == '4')
			Journal(hero);
		if (choice == '5')
			hero->setBinding();
		if (choice == '7')
			Save(hero, false);
		if (choice == '8')
		{
			Clear(&*hero);
			Paragraph(&*hero, "You will loose any unsaved progress.\nAnd will be returned to Tyria upon loading.", false, false, false, 0);
			if (Question(&*hero, "Are you sure?"))
			{
				hero->Reset();	//Is this needed and working correctly?
				Load(hero);
			}
		}
		if (choice == '9')
		{
			Paragraph(&*hero, "You will lose any unsaved progress.", true, false, false, 0);
			if (Question(&*hero, "Are you sure you wish to start a new game?"))
			{
				hero->Reset();
				Intro();
			}
		}
		if (choice == '6')
		{
			increment++;

			if (increment == 11)
				increment = 1;

			if (increment == 1)
			{
				Paragraph(&*hero, "Save often! Death is permanent.", true, true, true, 0);
			}
			if (increment == 2)
			{
				Paragraph(&*hero, "If you're looking for shops to gear up, make sure to explore the town.", true, true, true, 0);
			}
			if (increment == 3)
			{
				Paragraph(&*hero, "It's not a bad idea to train some in the fighting pits before embarking on a difficult mission.", true, true, true, 0);
			}
			if (increment == 4)
			{
				Paragraph(&*hero, "You can apply status effects (like mana barrier) to yourself and your companions before initiating combat.", true, true, true, 0);
			}
			if (increment == 5)
			{
				Paragraph(&*hero, "All status effects are dropped after resting and combat.", true, true, true, 0);
			}
			if (increment == 6)
			{
				Paragraph(&*hero, "You can bind almost any action to a letter key by going to Key Bindings in the menu. This works both inside and outside of combat. Mana Barrier for Channelers and Enchant Blade for Nighblades is already bound to 'e' for quick use before combat.", true, true, true, 0);
			}
			if (increment == 7)
			{
				Paragraph(&*hero, "Retreat is often an option and might be a good idea in a dire situation, especially if you've forgotten to save.", true, true, true, 0);
			}
			if (increment == 8)
			{
				Paragraph(&*hero, "Skilled channelers can infuse inanimate objects to give them life and fight for you, though you can only maintain control of them for one fight.", true, true, true, 0);
			}
			if (increment == 9)
			{
				Paragraph(&*hero, "Strength affects health and the amount of melee damage you do. \nAgility affects ranged attacks, stealth attacks and your turn in combat. \nIntellect affects mana and the impact of your spells.", true, true, true, 0);
			}
			if (increment == 10)
			{
				Paragraph(&*hero, "You might find playing with the numpad prefferable. You can use + and - to answer y/n questions", true, true, true, 0);
			}
			if (increment == 11)
			{
				Paragraph(&*hero, "Nightblades have skills that uses both Agility and Strength. \"Devastating Strike\" uses strength and \"Poison Strike\" and \"Ambush\" utilises Agility.", true, true, true, 0);
			}
		}
	}
}

int ChooseOption(string text, Player* hero, string choice[9], bool clearr)
{
	int input = 99;
	while (true)
	{
		if (clearr)
			Clear(&*hero);
		Paragraph(&*hero, text, false, false, false, 0);
		for (int i = 0; i < 9; i++)
		{
			if (choice[i] != "NULL")
			{
				mvprintw(hero->yPosGet(), 0, "%i: %s", i+1, choice[i].c_str()); 
				hero->yPosAdd(1);
			}
		}
		mvprintw(hero->yPosGet(), 0, "0: Menu"); hero->yPosAdd(1);
		mvprintw(hero->yPosGet(), 0, ">");
		input = mvgetch(hero->yPosGet(), 1); hero->yPosAdd(1);

		hero->keyBindingCheck(input);

		if (input <= '9' && input > '0')
		{
			if (choice[input - 49] != "NULL")
				return input;
		}
		if (input == '0')
			Menu(hero);

		//CHEATS
		if(input == '|')
		{
			input = GetInt(-1, -1, "Enter cheat code: ", true);
			if (input == 894)
			{
				hero->healthMod(hero->maxHealthGet());
				hero->manaMod(hero->maxManaGet());
				for (int i = 0; i < 5; i++)
				{
					if (hero->Party[i].nameGet() != "NULL")
					{
						hero->Party[i].healthMod(hero->Party[i].maxHealthGet());
						hero->Party[i].manaMod(hero->Party[i].maxManaGet());
					}
				}
			}
			if (input == 895)
			{
				int amount = GetInt(-1, -1, "Add gold:", true);
				hero->goldMod(amount);
			}
			if (input == 896)
			{
				int amount = GetInt(-1, -1, "Add exp:", true);
				hero->expGive(amount);
			}
			if (input == 897)
			{
				int id = GetInt(-1, -1, "Spell id:", true);
				hero->learnSpell(id);
			}
			if (input == 898)
			{
				int id = GetInt(-1, -1, "Companion id:", true);
				int amount = GetInt(-1, -1, "How many?", true);
				for (int i = 0; i < amount; i++)
					hero->addCompanion(id);
			}
			if (input == 899)
			{
				int id = GetInt(-1, -1, "Stage id:", true);
				hero->stageFlip(id);
			}
			if (input == 900)
			{
				for (int i = 1; i <= 10; i++)
				{
					if (hero->stageGet(i))
					{
						printw("1 ");
					}
					else
					{
						printw("0 ");
					}
				}
				printw("\n");
				Pause();
			}
			if (input == 901)
			{
				int i = 0;
				cin >> i;
				if (!BattleGroup(hero, i, 3, 1))
					return false;
				else
					return true;
			}
			if (input == 902)
			{
				int id = GetInt(-1, -1, "Item id:", true);
				hero->pickupItem(id);
			}
			if (input == 903)
			{
				int i = GetInt(-1, -1, "Add Strength:", true);
				hero->strMod(i);
			}
			if (input == 904)
			{
				int i = GetInt(-1, -1, "Add Intellect:", true);
				hero->intMod(i);
			}
			if (input == 905)
			{
				int i = GetInt(-1, -1, "Add Agility:", true);
				hero->agiMod(i);
			}
			if (input == 906)
			{
				BattleGroup(hero, 0, 100, 0);
			}
			if (input == 907)
			{
				int exp = GetInt(-1, -1, "Add Companion Exp:", true);
				for (int i = 0; i < 5 - 1; i++)
				{
					if (hero->getCompanion(i).healthGet() > 0)
						hero->getCompanion(i).expGive(exp);
				}
			}
		}
		clear();
	}
}
int ChooseEnemy(string prompt, Player* hero, int position)
{
	int target = 99;
	int aliveCount = 0;
	int y = 0, x = 0;
	Enemy e;
	while (target != '0')
	{
		//clear();

		//Sort enemy order
		for (int i = 1; i < ENEMY_LIMIT; i++)
		{
			if (hero->Opponent[i].healthGet() > 0 && hero->Opponent[i - 1].healthGet() <= 0)
			{
				e.Mutate(hero->Opponent[i - 1]);
				hero->Opponent[i - 1].Mutate(hero->Opponent[i]);
				hero->Opponent[i].Mutate(e);
			}
		}

		for (int i = 0; i < ENEMY_LIMIT; i++)
		{
			if (hero->Opponent[i].healthGet() > 0)
				aliveCount++;
		}
		if (aliveCount == 1)
		{
			for (int i = 0; i < ENEMY_LIMIT; i++)
			{
				if (hero->Opponent[i].healthGet() > 0)
				{
					return i;
				}
			}
		}
		y = 0; x = 0;
		if(position == 1)
		{
			y = 0;
			x = 50;
		}
		if(position == 2)
		{
			y = 0;
			x = 50;
		}
		mvprintw(y, x, "%s\n", prompt.c_str()); y++;

		for (int i = 0; i < ENEMY_LIMIT; i++)
		{
			if (hero->Opponent[i].healthGet() > 0)
			{
				mvprintw(y, x, "%i. %s - %i/%i", i+1, hero->Opponent[i].nameGet().c_str(), hero->Opponent[i].healthGet(), hero->Opponent[i].maxHealthGet());
				ColoredString(" HP\n", HealthColorCode(&hero->Opponent[i]));
				y++;
			}
		}
		mvprintw(y, x, "0. Cancel"); y++;
		mvprintw(y, x, ">");
		move(y, x+1);
		target = getch();

		if (target > 48 && target <= 48 + ENEMY_LIMIT)
		{
			if (hero->Opponent[target - 49].nameGet() != "NULL")
				break;
		}
	}
	ClearX(y, 50);
	return (target - 49);
}
int ChooseBeing(string prompt, Player* hero, Being* being[10])
{
	int target = 99;
	int groupSize = 0;
	int y = 0;
	while (true)
	{
		//clear();
		printw("%s\n", prompt.c_str());

		for (int i = 0; i < ENEMY_LIMIT; i++)
		{
			if (being[i]->healthGet() > 0)
			{
				printw("%i. %s - %i/%i HP\n", i+1, being[i]->nameGet().c_str(), being[i]->healthGet(), being[i]->maxHealthGet());
				groupSize++;
				y = i;
			}
		}

		if (groupSize == 1)
			return y;

		printw("0. Cancel\n>");
		target = getch();

		if (target > 48 && target <= 48 + ENEMY_LIMIT)
		{
			if (being[target - 49]->nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	return (target - 49);
}
int ChooseCompanion(int y, int x, string prompt, Player* hero, Companion* party[5])
{
	if(y == -1)
		y = CurrentY();
	if(x == -1)
		x = CurrentX();

	int target = 99;
	while (true)
	{
		y = 0, x = 0;
		if(hero->InCombat)
			x = 50;
		else
		{
			x = 0;
			y = hero->yPosGet();
		}
		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (party[i]->nameGet() != "NULL")
				hero->hasCompanion = true;
		}
		if (!hero->hasCompanion)
			return -1;

		//clear();
		mvprintw(y, x, "%s", prompt.c_str()); y++;
		mvprintw(y, x, "1. Yourself - %i/%i", hero->healthGet(), hero->maxHealthGet());
		ColoredString(" HP", HealthColorCode(hero));
		printw("   %i/%i", hero->manaGet(),hero->maxManaGet());
		ColoredString(" MP", ManaColorCode(hero)); y++;

		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (party[i]->healthGet() > 0)
			{
				mvprintw(y, x, "%i. %s - %i/%i" , i+2, party[i]->nameGet().c_str(), party[i]->healthGet(), party[i]->maxHealthGet());
				ColoredString(" HP", HealthColorCode(party[i]));
				printw("   %i/%i", party[i]->manaGet(), party[i]->maxManaGet());
				ColoredString(" MP", ManaColorCode(party[i])); y++;
			}
		}
		mvprintw(y, x, "0. Cancel"); y++;
		mvprintw(y, x, ">"); y++;
		target = getch();

		if (target >= 50 && target <= 50 + FOLLOWER_LIMIT)
		{
			if (party[target - 50]->nameGet() != "NULL")
				break;
		}
		if (target == '0' || target == '1')
			break;
	}
	if(hero->InCombat)
		ClearX(y, x);
	return (target - 50);
}
Being* ChooseTarget(string prompt, Player* hero, Companion* party[FOLLOWER_LIMIT], Being* being[ENEMY_LIMIT])
{
	Being dummy;
	Being* dummyPointer = &dummy;

	Being* beingPointer[15];
	beingPointer[0] = hero;

	int pos = 0;
	for (int i = 0; i < FOLLOWER_LIMIT; i++)
	{
		if (party[i]->nameGet() != "NULL")
		{
			pos++;
			beingPointer[pos] = party[i];
		}
	}
	for (int i = 0; i < ENEMY_LIMIT; i++)
	{
		if (being[i]->nameGet() != "NULL")
		{
			pos++;
			beingPointer[pos] = being[i];
		}
	}

	int target;
	int y = 0;
	while (true)
	{
		//clear();
		printw("%s\n", prompt.c_str());

		for (int i = 0; i <= pos; i++)
		{
			if (beingPointer[i]->healthGet() > 0)
			{
				printw("%i. %s - %i/%i HP\n", i + 1, beingPointer[i]->nameGet().c_str(), beingPointer[i]->healthGet(), beingPointer[i]->maxHealthGet());
				y = i;
			}
		}

		printw("0. Cancel\n>");
		target = getch();

		if (target > 48 && target <= 48 + 15)
		{
			if (beingPointer[target - 49]->nameGet() != "NULL")
				return beingPointer[target - 49];
		}
		if (target == 0)
			return dummyPointer;
	}
}
int ChooseSpell(string prompt, Being* hero, Spell spell[MAX_SPELLS])
{
	int target = 99;
	int y = 0;
	while (true)
	{
		y = 0;
		mvprintw(y, 50, "%s\n", prompt.c_str()); y++;

		for (int i = 0; i < MAX_SPELLS; i++)
		{
			if (spell[i].idGet() > 0)
			{
				mvprintw(i+1, 50, "%i. %s - %i MP\n", i+1, spell[i].nameGet().c_str(), spell[i].costGet()); y++;

			}
		}
		mvprintw(y, 50, "0. Cancel"); y++;
		mvprintw(y, 50, ">");
		target = getch();

		if (target > 48 && target <= 48 + MAX_SPELLS)
		{
			if (spell[target - 49].nameGet() != "NULL")
				break;
		}
		if (target == '0')
			break;
	}
	ClearX(y, 50);
	return (target - 49);
}
int ChooseItem(string prompt, Player* hero, Item* item[INVENTORY_SIZE], bool vendor)
{ 
	int target = 99;
	while (true)
	{
		int number = 0;
		//clear();
		printw("%s\n", prompt.c_str());

		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (item[i]->idGet() > 0)
			{
				printw("%i. %s", i+1, item[i]->nameGet().c_str());
				if (vendor)
				{ 
					printw(" | %i Gold", item[i]->valueGet()); 
				}
				printw("\n");
				number++;
			}
		}
		printw("0. Cancel\n>");
		target = getch();

		if (target > 48 && target <= 48 + INVENTORY_SIZE)
		{
			if (item[target - 49]->nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	return (target - 49);
}
int ChooseWeapon(string prompt, Being* hero, Weapon weapon[INVENTORY_SIZE], bool vendor)
{
	int target = 99;
	while (true)
	{
		int number = 0;
		mvprintw(hero->yPosGet(), 0, "%s", prompt.c_str()); hero->yPosAdd(1);

		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (weapon[i].idGet() > 0)
			{
				mvprintw(hero->yPosGet(), 0, "%i. %s", i+1, weapon[i].nameGet().c_str());
				if (vendor)
				{ 
					printw(" | %i Damage | ", weapon[i].damageGet());
					if (weapon[i].magicGet() > 0)
						printw("%i Magic | ", weapon[i].magicGet());
					printw("%i Gold", weapon[i].valueGet());
				}
				hero->yPosAdd(1);
				number++;
			}
		}
		if (!vendor)
		{ 
			printw("%i/%i in inventory\n\n", number, INVENTORY_SIZE); hero->yPosAdd(2); 
		}
		mvprintw(hero->yPosGet(), 0, "0. Cancel\n>"); hero->yPosAdd(2);
		target = getch();

		if (target > 48 && target <= 48 + INVENTORY_SIZE)
		{
			if (weapon[target - 49].nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	return (target - 49);
}
int ChooseArmor(string prompt, Being* hero, Armor armor[INVENTORY_SIZE], bool vendor)
{
	int y = 0; int x = 0;
	int target = 99;
	while (true)
	{
		y = 0, x = 0;
		if(hero->InCombat)
			x = 75;
		else
		{
			x = 0;
			y = hero->yPosGet();
		}

		int number = 0;
		mvprintw(y, x, "%s", prompt.c_str()); y++;

		if (!vendor)
		{ 
			mvprintw(y, x, "%i/%i in inventory", number, INVENTORY_SIZE); 
			y += 2;
		}
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (armor[i].idGet() > 0)
			{
				mvprintw(y, x, "%i. %s", i+1, armor[i].nameGet().c_str()); y++;

				if (vendor) 
				{ 
					printw(" | ");
					if (armor[i].defenceGet() > 0)
						printw("%i Defence | ", armor[i].defenceGet());
					if (armor[i].magicDefenceGet() > 0)
						printw("%i Magic Defence | ", armor[i].magicDefenceGet());
					if (armor[i].magicGet() > 0)
						printw("%i Magic Essence | ", armor[i].magicGet());
					printw("%i Gold", armor[i].valueGet());
				}
				number++;
			}
		}
		mvprintw(y, x, "0. Cancel"); y++;
		mvprintw(y, x, ">");
		target = getch();

		if (target > 48 && target <= 48 + INVENTORY_SIZE)
		{
			if (armor[target - 49].nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	if(hero->InCombat)
		ClearX(y, x);
	else
		hero->yPosSet(y+1);
	return (target - 49);
}
int ChooseScroll(string prompt, Being* hero, Scroll scroll[INVENTORY_SIZE], bool vendor)
{
	int y = 0; int x = 0;
	int target = 99;
	while (true)
	{
		y = 0, x = 0;
		if(hero->InCombat)
			x = 75;
		else
			x = 20;

		int number = 0;
		mvprintw(y, x, "%s", prompt.c_str()); y++;
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (scroll[i].idGet() > 0)
			{
				mvprintw(y, x, "%i. %s", i+1, scroll[i].nameGet().c_str()); y++;
				if (vendor)
				{ 
					printw(" | %i Gold", scroll[i].valueGet()); 
				}
				number++;
			}
		}
		if (!vendor)
		{ 
			mvprintw(y, x, "%i/%i in inventory", number, INVENTORY_SIZE); 
			y += 2;
		}
		mvprintw(y, x, "0. Cancel"); y++;
		mvprintw(y, x, ">");
		target = getch();

		if (target > 48 && target <= 48 + INVENTORY_SIZE)
		{
			if (scroll[target - 49].nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	ClearX(y, x);
	return (target - 49);
}
int ChoosePotion(string prompt, Being* hero, Potion potion[INVENTORY_SIZE], bool vendor)
{
	int y = 0; int x = 0;
	int target = 99;
	while (true)
	{
		y = 0, x = 0;
		if(hero->InCombat)
			x = 75;
		else
			x = 20;

		int number = 0;
		//clear();
		mvprintw(y, x, "%s", prompt.c_str()); y++;

		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (potion[i].idGet() > 0)
			{
				mvprintw(y, x, "%i. %s", i+1, potion[i].nameGet().c_str()); y++;
				if (vendor)
				{ 
					printw(" | %i Gold", potion[i].valueGet()); 
				}
				else
				{ 
					printw(" x%i", potion[i].amountGet() ); 
				}
				number++;
			}
		}
		if (!vendor)
		{ 
			mvprintw(y, x, "%i/%i in inventory", number, INVENTORY_SIZE); 
			y += 2;
		}
		mvprintw(y, x, "0. Cancel"); y++;
		mvprintw(y, x, ">");
		target = getch();

		if (target > 48 && target <= 48 + INVENTORY_SIZE)
		{
			if (potion[target - 49].nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	ClearX(y, x);
	return (target - 49);
}
int ChooseTome(string prompt, Being* hero, SpellTome tome[INVENTORY_SIZE], bool vendor)
{
	int y = 0; int x = 0;
	int target = 99;
	while (true)
	{
		y = 0, x = 20;

		int number = 0;
		mvprintw(y, x, "%s", prompt.c_str()); y++;

		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (tome[i].idGet() > 0)
			{
				mvprintw(y, x, "%i. %s", i+1, tome[i].nameGet().c_str()); y++;
				if (vendor)
				{ 
					printw(" | %i Gold", tome[i].valueGet()); 
				}
				number++;
			}
		}
		if (!vendor)
		{ 
			mvprintw(y, x, "%i/%i in inventory", number, INVENTORY_SIZE); y += 2;
		}
		mvprintw(y, x, "0. Cancel"); y++;
		mvprintw(y, x, ">");
		target = getch();

		if (target > 48 && target <= 48 + INVENTORY_SIZE)
		{
			if (tome[target - 49].nameGet() != "NULL")
				break;
		}
		if (target == 48)
			break;
	}
	ClearX(y, x);
	return (target - 49);
}
void SortWeaponInventory(Weapon* weapon[INVENTORY_SIZE])
{
	for (int i = 1; i < INVENTORY_SIZE; i++)
	{
		if (weapon[i]->nameGet() != "NULL" && weapon[i - 1]->nameGet() == "NULL")
		{
			weapon[i - 1]->Transform(*weapon[i]);
			weapon[i]->Reset();
		}
	}
}
void SortArmorInventory(Armor* armor[INVENTORY_SIZE])
{
	for (int i = 1; i < INVENTORY_SIZE; i++)
	{
		if (armor[i]->nameGet() != "NULL" && armor[i - 1]->nameGet() == "NULL")
		{
			armor[i - 1]->Transform(*armor[i]);
			armor[i]->Reset();
		}
	}
}
void SortScrollInventory(Scroll* scroll[INVENTORY_SIZE])
{
	for (int i = 1; i < INVENTORY_SIZE; i++)
	{
		if (scroll[i]->nameGet() != "NULL" && scroll[i - 1]->nameGet() == "NULL")
		{
			scroll[i - 1]->Transform(*scroll[i]);
			scroll[i]->Reset();
		}
	}
}
void SortPotionInventory(Potion* potion[INVENTORY_SIZE])
{
	for (int i = 1; i < INVENTORY_SIZE; i++)
	{
		if (potion[i]->nameGet() != "NULL" && potion[i - 1]->nameGet() == "NULL")
		{
			potion[i - 1]->Transform(*potion[i]);
			potion[i]->Reset();
		}
	}
}
void SortTomeInventory(SpellTome* tome[INVENTORY_SIZE])
{
	for (int i = 1; i < INVENTORY_SIZE; i++)
	{
		if (tome[i]->nameGet() != "NULL" && tome[i - 1]->nameGet() == "NULL")
		{
			tome[i - 1]->Transform(*tome[i]);
			tome[i]->Reset();
		}
	}
}
void SortItemInventory(Item* item[INVENTORY_SIZE])
{
	for (int i = 1; i < INVENTORY_SIZE; i++)
	{
		if (item[i]->nameGet() != "NULL" && item[i - 1]->nameGet() == "NULL")
		{
			item[i - 1]->Transform(*item[i]);
			item[i]->Reset();
		}
	}
}
void SortEnemyOrder(Enemy* enemy[ENEMY_LIMIT])
{
	for (int i = 1; i < ENEMY_LIMIT; i++)
	{
		if (enemy[i]->nameGet() != "NULL" && enemy[i - 1]->nameGet() == "NULL")
		{
			enemy[i - 1]->Mutate(*enemy[i]);
			enemy[i]->Reset();
		}
	}
}

bool CombatOver(Player* hero)
{
	int slain = 0;
	int exp = 0;
	int playerExp = 0;
	int gold = 0;
	int partySize = 1;

	for (int i = 0; i < ENEMY_LIMIT; i++)
	{
		if (hero->Opponent[i].healthGet() <= 0)
		{
			slain++;
			if (hero->Opponent[i].nameGet() != "NULL")
			{
				gold += hero->Opponent[i].goldGet();
				exp += hero->Opponent[i].expGet();
			}
		}
	}
	if (slain == ENEMY_LIMIT)
	{
		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (hero->getCompanion(i).healthGet() > 0)
				partySize++;
		}
		exp /= partySize;
		if (partySize > 1)
			playerExp = exp * 1.5;
		else
			playerExp = exp;

		if (gold > 0 || exp > 0)
		{
			Paragraph(&*hero, "All of the enemies have been vanquished, victory!\n", false, false, false, 39);
			printw("You've earned %i gold, and %i experience!\n\n", gold, playerExp);
			Pause();
		}

		hero->goldMod(gold);
		hero->expGive(playerExp);
		for (int i = 0; i < FOLLOWER_LIMIT - 1; i++) 
		{
			if (hero->getCompanion(i).healthGet() > 0)
				hero->getCompanion(i).expGive(exp);		//TODO: Bug check, they don't actually get any experience / False, the experience resets somehow
		}
		hero->InCombat = false;
		hero->Stealthed = true;

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

		for (int i = 0; i < ENEMY_LIMIT; i++)
			hero->Opponent[i].Reset();

		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (hero->Party[i].typeGet() == "Conjured")
				hero->Party[i].Reset();

			for (int j = 0; j < MAX_EFFECTS; j++) 
				hero->Party[i].getEffect(j)->Reset();

			if (hero->Party[i].nameGet() == "Gerald" && hero->Party[i].Unconscious)
			{
				hero->Party[i].healthSet(1);
				hero->Party[i].Unconscious = false;
			}
		}

		return true;
	}
	else
		return false;
}

bool EnemiesDead(Player* hero)
{
	int slain = 0;
	int exp = 0;
	int gold = 0;

	for (int i = 0; i < ENEMY_LIMIT; i++)
	{
		if (hero->Opponent[i].healthGet() <= 0)
		{
			slain++;
			if (hero->Opponent[i].nameGet() != "NULL")
			{
				gold += hero->Opponent[i].goldGet();
				exp += hero->Opponent[i].expGet();
			}
		}
	}
	if (slain == ENEMY_LIMIT)
	{
		return true;
	}
	else
		return false;
}

void Journal(Player* hero)
{
	//THOUGHT: Add dates to the game, that progresses each time the player takes a rest, and use those dates to append each entry for at what day it happened.
	//BUT: That will require an addition to the save file system to remember it between saves.

	Clear(&*hero);
	if (!hero->stageGet(1))
	{
		Paragraph(&*hero, "I've just arrived here at Tyria, finally made it! I should take my time and explore a bit, there has to be many things to see in such a city. And after that I need to talk to Hadgar again at the Castle.\n", false, false, false, 10);
	}
	if (hero->stageGet(1))
	{
		Paragraph(&*hero, "I've arrived at Tyria! Finally found a home, and now a new purpose as I've accepted Hadgars call to join the cities defences. He said I should first attend the local tournament, so that he can gauge my skill in combat as well as it is a means for me to improve it.\n", false, false, false, 10);
	}
	if (hero->stageGet(2))
	{
		if (hero->varGet(1) == 10)
		{
			//Champion of the tournament
			Paragraph(&*hero, "I've proved myself worthy and arisen as the champion of the tournament! I now need to report back to Hadgar with my victory.\n", false, false, false, 10);
		}
		if (hero->varGet(1) < 10 && hero->varGet(1) >= 5)
		{
			Paragraph(&*hero, "The tournament was a challenge, but I believe I have proven myself to be a skilled combatant. I need to report back to Hadgar with the results.\n", false, false, false, 10);
		}
		if (hero->varGet(1) < 5)
		{
			Paragraph(&*hero, "The tournament was a challenge, and I got knocked out in the earlier rounds. I can give it another go or report back to Hadgar with the results.\n", false, false, false, 10);
		}
	}
	if (hero->stageGet(4)) //Finished the Defence of Tyria
	{
		Paragraph(&*hero, "The invasion of Tyria by invading mutant bandits have been fended off. I should take a well deserved rest and then yet again report back to Hadgar.\n", false, false, false, 10);
	}
	else if (hero->stageGet(3)) //About to head to defend Tyria
	{
		Paragraph(&*hero, "Hadgar has just told me about an invading force of Mutant bandits bearing down on the city! I must gather my wits and report to the barracks to help at once!\n", false, false, false, 10);
	}
	if (hero->stageGet(5))
	{
		Paragraph(&*hero, "I've been sent on a most vital mission, to purge a center of corruption for this seething blight. I've been directed to a location, where the desert meets the mountains.\n", false, false, false, 10);
	}
	if (hero->stageGet(6))
	{
		Paragraph(&*hero, "The journey has been rough, but I have finally made it to the congregation of these corrupted channelers.\n", false, false, false, 10);
	}
	if (hero->stageGet(7))
	{
		Paragraph(&*hero, "The channelers were nothing like what I thought, it seems we share a similar purpose. Even if they have very different means, we need to work together for now.\n", false, false, false, 10);
	}
	else if (hero->stageGet(8))
	{
		Paragraph(&*hero, "My mission has been complete, the deserts have been purged of this corrupted channeling and will hopefully in time recover. I was welcomed back as a hero, and I know in my heart I have found my true home.\n", false, false, false, 10);
	}
	if (hero->stageGet(10)) //Found the mysterious symbol
	{
		Paragraph(&*hero, "In the alleyways of Tyria I have found a mysterious symbol. It bares the symbol of life and seems to be calling for it. This needs further investigation, but I am wary of it.\n", false, false, false, 10);
	}
	if (hero->stageGet(11)) //Found the channelers hideout
	{
		Paragraph(&*hero, "I touched the mysterious symbol and some of my life was drained away, but just a little as if to sample it. The bricks of the alley folded backwards and revealed a hallway, where hooded figures greeted me to what they called \"The Channelers Hideout\"\n", false, false, false, 10);
	}
	if (hero->stageGet(15)) //Statue background lore unlocked
	{
		//Paragraph(&*hero, "Today I came upon a statue of Alissa the Swordsmaster, as a bystander informed me. He also told me of great deeds she did to lead her people here and to defend the city. It seems I owe a lot to this person.\n", false, false, false, 10);
	}
	hero->yPosAdd(1);
	Pause(&*hero);
}