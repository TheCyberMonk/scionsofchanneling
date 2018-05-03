#include "../include/Being.h"

bool Desert(Player* hero)
{
	int input = 0;
	string Choices[9] = { "Explore", "Hunt Monsters", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Return to town" };

	if (hero->stageGet(6))
		Choices[2] = "Lich Hideout";
	else if (hero->stageGet(5))
		Choices[2] = "Lich Hideout[QUEST]";
	if (hero->levelGet() < 3)
		Choices[1] = "Hunt Monsters[DANGEROUS]";

	while (true)
	{
		hero->yPosReset();
		input = ChooseOption("The near endless plains of the desert stretch out in front of you as far as the"
							 "eye can see. Many places connect to this vast wasteland, "
							 "but learning their locations will be a challenge.", hero, Choices, true);

		if (input == '2') 
		{
			srand(time(NULL));
			int random = rand() % 3 + 1;

			if (!BattleGroup(hero, random, 2, 0))
				return false;
		}
		if (input == '3')
		{
			if (!LichHideout(&*hero))
				return false;
		}

		if (input == '9')
			return true;
	}
	return false;
}

bool Oasis(Player* hero)
{
	//A large tropical oasis to explore
	
	return true;
}