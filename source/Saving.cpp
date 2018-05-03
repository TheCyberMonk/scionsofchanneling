#include "../include/Being.h"

void Save2(Player* save)
{
	ofstream outfile("Save.DAT", ios::binary);
	Player hero = *save;
	outfile.write(reinterpret_cast<char*>(&hero), sizeof(hero));
}
void Save(Player* save, bool autosave)
{	//To be revised, easily modified by player.
	stringstream sstm;
	ofstream Save[9];
	ifstream Load[9];
	int input = 49;
	string name[9], clas[9];

	do
	{
		if(!autosave)
		{
			Clear(&*save);
			mvprintw(save->yPosGet(), 0, "Save to which slot?"); save->yPosAdd(1);
			for (int i = 0; i < 9; i++) 
			{
				sstm.str("");
				sstm << "Save" << i << ".DAT";
				Load[i].open(sstm.str(), ios::binary);
				Load[i] >> name[i] >> clas[i];
				if(i == 0)
					mvprintw(save->yPosGet(), 0, "%i - Autosave: ", i+1);
				else
					mvprintw(save->yPosGet(), 0, "%i - ", i+1);
				if (name[i] != ""){
					printw("%s, the %s", name[i].c_str(), clas[i].c_str()); save->yPosAdd(1);
				}
				else{
					printw("EMPTY"); save->yPosAdd(1);
				}
			}
			mvprintw(save->yPosGet(), 0, "0. Cancel"); save->yPosAdd(1);
			mvprintw(save->yPosGet(), 0, ">");
			input = getch();
		}
		if(autosave || input > 49)
		{
			input--;
			if(!autosave)
			{
				save->yPosAdd(1);
				mvprintw(save->yPosGet(), 0, "This will overwrite Save %i.\n", input-47); save->yPosAdd(1);
				mvprintw(save->yPosGet(), 0, "You will be returned to Tyria upon reload.\n"); save->yPosAdd(1);
			}
			if (autosave || Question(save->yPosGet(), 0, "Are you sure?", false))
			{
				sstm.str("");
				sstm << "Save" << input - 48 << ".DAT";
				Save[input - 48].open(sstm.str(), ios::binary);
				if (Save[input - 48].is_open())
				{
					Save[input - 48] << save->nameGet() << ' ' << save->classGet() << ' ';
					Save[input - 48] << save->strengthGet() << ' ' << save->intGet() << ' ' << save->agilityGet() << ' ';
					Save[input - 48] << save->healthGet() << ' ' << save->maxHealthGet() << ' ' << save->manaGet() << ' ' << save->maxManaGet() << ' ';
					Save[input - 48] << save->goldGet() << ' ' << save->levelGet() << ' ' << save->expGet() << ' ' << save->getWeapon()->idGet() << ' ';

					for (int i = 0; i < 7; i++)
						Save[input - 48] << save->getArmor(i)->idGet() << ' ';

					for (int i = 0; i < INVENTORY_SIZE; i++)
						Save[input - 48] << save->wInventory[i].idGet() << ' ';

					for (int i = 0; i < INVENTORY_SIZE; i++)
						Save[input - 48] << save->aInventory[i].idGet() << ' ';

					for (int i = 0; i < INVENTORY_SIZE; i++)
						Save[input - 48] << save->pInventory[i].idGet() << ' ' << save->pInventory[i].amountGet() << ' ';

					for (int i = 0; i < INVENTORY_SIZE; i++)
						Save[input - 48] << save->sInventory[i].idGet() << ' ';

					for (int i = 0; i < 20; i++)
						Save[input - 48] << save->stageGet(i) << ' ';

					for (int i = 0; i < 20; i++)
						Save[input - 48] << save->varGet(i) << ' ';

					for (int i = 0; i < MAX_SPELLS; i++)
						Save[input - 48] << save->getSpell(i)->idGet() << ' ';

					for (int i = 0; i < INVENTORY_SIZE; i++)
						Save[input - 48] << save->tInventory[i].idGet() << ' ';

					for (int i = 0; i < FOLLOWER_LIMIT; i++)
						Save[input - 48] << save->Party[i].idGet() << ' ';

					for (int i = 0; i < 25; i++)
						Save[input - 48] << save->Binding[i].keyGet() << ' ' << save->Binding[i].typeGet() << ' ' << save->Binding[i].idGet() << ' ';

					Save[input - 48] << save->TutorialState << ' ';
				}
				else
				{
					printw("Could not open file!\n");
					Pause();
				}
				for (int i = 0; i < 9; i++)
				{
					Save[i].close();
					Load[i].close();
				}
				if(!autosave)
				{
					printw("\nThe game has been saved!\n\n");
					Pause(); clear();
				}
			}
			else
				input = 0;
		}

	} while (input < 48 || input >= 58);
	return;
}

bool Load(Player* load)
{
	stringstream sstm;
	ifstream Load[9];
	ifstream Save1("Save.DAT", ios::binary);
	int input;
	string name[9], clas[9];
	int level[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};

	do
	{
		clear();
		printw("Load which save?\n");
		for (int i = 0; i < 9; i++)
		{
			sstm.str("");
			sstm << "Save" << i << ".DAT";
			Load[i].open(sstm.str(), ios::binary);
			Load[i] >> name[i] >> clas[i]; 
			Load[i].seekg(0);

			if (name[i] != "")
			{ 
				if(i == 0)
					printw("%i - Autosave: ", i+1);
				else
					printw("%i - ", i+1);
				printw("%s, the %s\n", name[i].c_str(), clas[i].c_str());
			}
		}
		printw("0. Cancel\n>");
		input = getch();
	} while (input < 48 || input > 58);
	if (input == 48)
		return false;
	input--;

	if (Load[input - 48].is_open())
	{
		string Name, Class;
		int Health, MaxHealth, Mana, MaxMana;
		int Strength, Intelligence, Agility;
		int Level, Experience, Gold;

		int Weapon; int weapons[INVENTORY_SIZE];
		int eArmor[7]; int iArmor[INVENTORY_SIZE];
		int potions[INVENTORY_SIZE]; int pAmount[INVENTORY_SIZE];
		int scrolls[INVENTORY_SIZE];
		int stages[100];
		int variables[100];
		int spells[MAX_SPELLS];
		int tomes[INVENTORY_SIZE];
		int party[FOLLOWER_LIMIT];

		int bindingNumber[25];
		string bindingType[25];
		int bindingID[25];

		int tutorialState;

		Load[input - 48] >> Name >> Class >> Strength >> Intelligence >> Agility >>
			Health >> MaxHealth >> Mana >> MaxMana >> Gold >> Level >> Experience >> Weapon;

		for (int i = 0; i < 7; i++)
			Load[input - 48] >> eArmor[i];
		for (int i = 0; i < INVENTORY_SIZE; i++)
			Load[input - 48] >> weapons[i];
		for (int i = 0; i < INVENTORY_SIZE; i++)
			Load[input - 48] >> iArmor[i];
		for (int i = 0; i < INVENTORY_SIZE; i++)
			Load[input - 48] >> potions[i] >> pAmount[i];
		for (int i = 0; i < INVENTORY_SIZE; i++)
			Load[input - 48] >> scrolls[i];
		for (int i = 0; i < 20; i++)
			Load[input - 48] >> stages[i];
		for (int i = 0; i < 20; i++)
			Load[input - 48] >> variables[i];
		for (int i = 0; i < MAX_SPELLS; i++)
			Load[input - 48] >> spells[i];
		for (int i = 0; i < INVENTORY_SIZE; i++)
			Load[input - 48] >> tomes[i];
		for (int i = 0; i < FOLLOWER_LIMIT; i++)
			Load[input - 48] >> party[i];
		for (int i = 0; i < 25; i++)
			Load[input - 48] >> bindingNumber[i] >> bindingType[i] >> bindingID[i];

		Load[input - 48] >> tutorialState;

		load->nameSet(Name);
		load->classSet(Class);
		load->strSet(Strength);
		load->intSet(Intelligence);
		load->agiSet(Agility);
		load->maxHealthSet(MaxHealth);
		load->healthSet(Health);
		load->manaSet(Mana);
		load->maxManaSet(MaxMana);
		load->goldSet(Gold);
		load->levelSet(Level);
		load->expSet(Experience);
		load->getWeapon()->idTransform(Weapon);

		for (int i = 0; i < 7; i++)
			load->getArmor(i)->idTransform(eArmor[i]);
		for (int i = 0; i < INVENTORY_SIZE; i++)
			load->wInventory[i].idTransform(weapons[i]);
		for (int i = 0; i < INVENTORY_SIZE; i++)
			load->aInventory[i].idTransform(iArmor[i]);
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			load->pInventory[i].idTransform(potions[i]);
			load->pInventory[i].amountSet(pAmount[i]);
		}
		for (int i = 0; i < INVENTORY_SIZE; i++)
			load->sInventory[i].idTransform(scrolls[i]);
		for (int i = 0; i < 20; i++)
		{
			if (stages[i] == 1)
				load->stageSet(i, true);
		}
		for (int i = 0; i < 20; i++)
				load->varSet(i, variables[i]);
		for (int i = 0; i < MAX_SPELLS; i++)
			load->spell[i].idTransform(spells[i]);
		for (int i = 0; i < INVENTORY_SIZE; i++)
			load->tInventory[i].idTransform(tomes[i]);
		for (int i = 0; i < FOLLOWER_LIMIT; i++)
			load->Party[i].idMutate(party[i]);
		for (int i = 0; i < 25; i++)
			load->Binding[i].setBinding(bindingNumber[i], bindingType[i], bindingID[i]);

		load->TutorialState = tutorialState;
	}
	else{
		printw("Could not open file!\n");
		Pause();
	}
	for (int i = 0; i < 9; i++)
		Load[i].close();

	return true;
}