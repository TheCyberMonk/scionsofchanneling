#include "../include/Being.h"
//std::ostringstream oss;

bool LichHideout(Player* hero)
{
	if (hero->stageGet(5) && !hero->stageGet(6))
	{
		int progress = 0;
		int difficulty = 2;
		string Choices[9] = { "Carry on", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Return" };

		Paragraph(&*hero, "Your companion lead you towards the suspected location. The journey will be rough, traveling under the schorching sun, constantly being ambushed by mutants.\n\n", true, false, false, 39);
		while (progress < 8)
		{
			srand(time(NULL));
			int random = (rand() % 4) + 1; 

			if (progress == 4)
			{
				difficulty = 3;
				Paragraph(&*hero, "Night time is approaching, and you try to find cover. But the desert is sorely lacking in that department. You eventually set up between a couple of tall sand dunes, hoping to remain somewhat unnoticed. You take the first watch.", true, true, true, 0);

				random = (rand() % 2) + 1;
				if (random == 1)
				{
					Paragraph(&*hero, "You remain vigilant, and after awhile you do spot some enemies in the distance. You wake your companion and ready yourself.", false, true, true, 0);
					if (!BattleGroup(hero, 2, 2, 0))
						return false;
				}

				Paragraph(&*hero, "You sleep as well as can be expected out in the deserts.\n50% of mana and health restored.", false, true, true, 0);
				hero->healthMod(hero->maxHealthGet() / 2);
				hero->manaMod(hero->maxManaGet() / 2);
				hero->RageUsed = false; 

				for (int i = 0; i < 5; i++)
				{
					if (hero->Party[i].nameGet() != "NULL")
					{
						hero->Party[i].healthMod(hero->Party[i].maxHealthGet() / 2);
						hero->Party[i].manaMod(hero->Party[i].maxManaGet() / 2);
					}
				}
			}

			int choice = ChooseOption("You take a moment, what's next?\n", hero, Choices, false);

			random = (rand() % 4) + 1;
			if (choice == '1')
			{
				if (random != 4)
				{
					if (random == 1)
					{
						Paragraph(&*hero, "\nNot surprisingly you encounter a group of mutants, ready yourself!", false, true, true, 0);
						if (!BattleGroup(hero, (8 - difficulty), difficulty, 3))
							return false;
					}
					if (random == 2)
					{
						PausedString("You suddenly notice some mutants behind you in a frenzied pursuit.\nYou have no chance to outrun them, so you take your stand.");
						if (!BattleGroup(hero, (7 - difficulty), difficulty, 3))
							return false;
					}
					if (random == 3)
					{
						PausedString("Walking out of a canyon a few mutants instantly spot you!");
						if (!BattleGroup(hero, (6 - difficulty), difficulty, 3))
							return false;
					}
				}
				else
				{
					PausedString("You carry on, and for a while you encounter no danger.");
				}
				progress++;
			}
			if (choice == '9')
			{
				return true;
			}
		}
		hero->stageSet(6, false);
	}
	if (hero->stageGet(6) && !hero->stageGet(7))
	{
		string Choices[9] = { "Attack!", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Return" };

		int choice = ChooseOption("The channeler camp comes into view, you are at the edge of the \nsouthern mountains and they've apparently inhabited a cave. \nYou can see a few camp tents, "
			"but suspect most of the \nactivity is happening inside the mountain.\n", hero, Choices, true);
		if (choice == '1')
		{
			if (!BattleGroup(hero, 2, 3, 0))
				return false;

			Paragraph(&*hero, "Suddenly all of the mutants and channelers stop in their tracks. This action is unnervingly synchroniced, so much so that you pause as well. Before you continue "
				"your attack every one of them lower their weapons and staffs to the ground. One of the Channelers speaks to you in a deep raspy voice.\n\n"
				"Channeler:\nI am Achalio, among the last of the Scions of Channeling. I am using this faithful follower as a vessel to communicate with you. Why are you killing my people?", true, true, true, 45);

			string Choices1[9] = { "Why are you using evil arts to desecrate the dead?", "Why are you corrupting this land?", "I need not explain myself to you, just die!", "NULL", "NULL", "NULL", "NULL", "NULL", "Leave" };
			while (Choices1[0] != "NULL" || Choices1[1] != "NULL")
			{
				int choice1 = ChooseOption("How do you respond?\n", hero, Choices1, false);
				if (choice1 == '1')
				{
					Paragraph(&*hero, "Achalio, Scion of Channeling:\n\n", true, false, false, 0);
					Paragraph(&*hero, "The dead are just so, dead... I do not see evil in what I do. There is death, and there is survival. I do not feel guilty by using every means at our disposal. Our goal is the same, an end to this eternal night. We do not have to be enemies.", false, true, true, 45);
					Choices1[0] = "NULL";
				}
				if (choice1 == '2')
				{
					Paragraph(&*hero, "Achalio, Scion of Channeling:\n\n", true, false, false, 0);
					Paragraph(&*hero, "Is that what you've been told? Or perhaps even merely surmized? We are doing everything we can to reverse the corruption. Our methods, as grim as they are, do not have any detrimental effect upon it. We channel just the same way you do, by drawing from our inner strength.", false, true, true, 45);
					Choices1[1] = "NULL";
				}
				if (choice1 == '3')
				{
					if (!BattleGroup(hero, 6, 100, 3))
						return false;
					Paragraph(&*hero, "You stand triumphant! Corpses of the channelers lay littered before you, the mission is acomplished. Returning to Tyria you are welcomed as A HERO. And for once the town is buzzing with life and hope as the celebration continues well into the next day.", true, true, true, 45);
					Paragraph(&*hero, "End of current game development.\nThanks for playing!", true, true, true, 0);
					return true;
				}
				if (choice1 == '9')
					return true;
				if (Choices1[0] == "NULL" || Choices1[1] == "NULL")
					Choices[2] = "Enough talk! Release your grip upon these lands!";
			}
			Paragraph(&*hero, "Achalio, Scion of Channeling:\n\n", true, false, false, 0);
			Paragraph(&*hero, "In your own way you have answered my question. You have killed many of my followers, human life in this day and age is extremely precious. Which is why I will not seek retribution. And because you might actually be able to help us finally end this seething blight.", false, true, true, 45);
			Paragraph(&*hero, "Achalio, Scion of Channeling:\n\n", true, false, false, 0);
			Paragraph(&*hero, "I think I have found a way to reverse the corruption. But we no longer have nearly enough resources to carry it out. But if we combine our deep knowledge of channeling and your manpower, this world might yet be saved. If you allow it, I will follow you in this vessel back to the city and make my plea to your superiors.", false, true, true, 45);

			Paragraph(&*hero, "You decide to take the risk, if he is speaking the truth the benefit is too great.\n\nAchalios Vessel joins the party.", true, true, true, 0);
			Paragraph(&*hero, "End of current game development.\nThanks for playing!", true, true, true, 0);
			hero->addCompanion(4);
			hero->stageSet(7, false);
		}
		if (choice == '9')
			return true;
	}
	return true;
}