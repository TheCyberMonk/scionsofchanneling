#include "../include/Being.h"

void Intro()
{
	Weapon StarterWeapon;
	Being Hadgar("Hadgar", "Commander", "NPC", 10, 80, 15, 25, 8, 15, 100, 500);
	Player hero("Farmer John", "Peasant", 15, 0, 0, 0, 0, 5);

	Clear(&hero);
	Paragraph(&hero, "You have been trekking through an arid desert for days, searching for the rumored city of Tyria. It is said to be the last stronghold for the civilization of Ayataria, and probably the last "
		"hope for mankind. If there exists a safe haven yet in this world, that would be it. The only place where one could hope to make a difference. A darkness has swept over this land for centuries. "
		"A corruption that turns beasts, men and all life into a wicked and tormented form of existence. The elders say it was all started by very powerful Channelers called The Dark Liches. If that "
		"is the case though it is already far out of their control. No one really knows however, it could simply be that the gods have grown tired of this mortal plane...\n\nPondering this question your "
		"feet starts to drag, you're closing your limit. But just as thoughts of giving up start entering your mind, you can make out tall stone walls in the distance. As you move closer the guards "
		"on top of the wall notices you. They all aim different ranged weaponry at you, all the way from bows to powerful ancient boomsticks. They watch intently as you approach. Eventually, they "
		" stand down. Most likely assessing that you have no mutations. After a while the gate opens and a tall muscular man with a long ornate cloak approach and address you.", false, false, false, 39);

	Paragraph(&hero, "\n\"Greetings, it is rare to see anyone wandering alone these days.\"\n\"What is your name?\"", false, false, false, 39);
	hero.nameSet(GetStringInput(&hero, "", false));

	Clear(&hero);
	Hadgar.Talk(&hero, "\"Welcome " + hero.nameGet() + " to Tyria! A bastion of humanity and a shining beacon of hope! I am Hadgar and I'm the military commander here. "
		"I'm glad you made the journey, not many do these days.\"\n", false, false, false, 39);
	Hadgar.Talk(&hero, "\"How did you make it if I may ask? What is your style of combat?\"", false, false, false, 39);

	int input = 0;
	hero.yResetSet(hero.yPosGet());
	while (input != '1' && input != '2' && input != '3' && input != '4')
	{
		hero.yPosReset();
		Paragraph(&hero, "1: Berserker\n2: Channeler\n3: Nightblade\n4: Monk\n>", false, false, false, 0);
		input = getch();

		if (input == '1')
		{
			Paragraph(&hero, "Berserkers use brute strength to smash their enemies to pieces!\n-Strength focus\n-+2 base attack\n-Can use all armor\n-Keybindings: \'q\'-Whirlwind, \'w\'-Charge, \'e\'-Execute, \'r\'-Rage\n", false, false, false, 0);
			if (Question(&hero, "Are you sure that you want to be a Berserker?"))
			{
				hero.classSet("Berserker");
				hero.strMod(3);
				hero.agiMod(2);
				hero.intMod(1);
				StarterWeapon.idTransform(1);
				hero.equipWeapon(&StarterWeapon);
				hero.learnSpell(11);
				hero.learnSpell(12);
				hero.learnSpell(13);
				hero.learnSpell(22);
				hero.Binding[113-97].setBinding(113, "Spell", 11);
				hero.Binding[119-97].setBinding(119, "Spell", 12);
				hero.Binding[101-97].setBinding(101, "Spell", 13);
				hero.Binding[114-97].setBinding(114, "Spell", 22);

				hero.yPosAdd(2);
				Hadgar.Talk(&hero, "The need for brutality has never been stronger, you'll fit right in.", false, false, true, 39);
			}
			else
				input = 0;
		}
		if (input == '2')
		{
			Paragraph(&hero, "Channelers call upon a strength from deep within to manipulate the chaotic energies of this world to their will.\n-Intelligence focus\n-Spell Casting!\n-Can only wear Cloth\n-Keybindings: \'q\'-Sparks, \'w\'-Heal, \'e\'-Mana Barrier, \'r\'-Drain Life\n", false, false, false, 0);
			if (Question(&hero, "Are you sure that you want to be a Channeler?"))
			{
				hero.classSet("Channeler");
				hero.intMod(3);
				hero.agiMod(2);
				hero.strMod(1);
				hero.learnSpell(1);
				hero.learnSpell(3);
				hero.learnSpell(14);
				hero.learnSpell(7);
				hero.Binding[113-97].setBinding(113, "Spell", 1);
				hero.Binding[119-97].setBinding(119, "Spell", 3);
				hero.Binding[101-97].setBinding(101, "Spell", 14);
				hero.Binding[114-97].setBinding(114, "Spell", 7);
				StarterWeapon.idTransform(2);
				hero.equipWeapon(&StarterWeapon);

				Hadgar.Talk(&hero, "You have mastered the channeling of essence? We have few Channelers among us, but they have proven themselves invaluable to the city. Be wary though, some are suspicious and not as appreciative of your arts. ", false, false, true, 39);
			}
			else
				input = 0;
		}
		if (input == '3')
		{
			Paragraph(&hero, "Nightblades prefer the shadows, often using channeling to enhance their attacks and enchant their blades.\n-No stat focus\n-Bonus to initiative\n-Can wear cloth and leather\n-Keybindings: \'q\'-Ambush, \'w\'-Poison Strike, \'e\'-Enchant Weapon, \'r\'-Devastating Strike\n", false, false, false, 0);
			if (Question(&hero, "Are you sure that you want to be a Nightblade?"))
			{
				hero.classSet("Nightblade");
				hero.strMod(2);
				hero.agiMod(2);
				hero.intMod(2);
				hero.learnSpell(15);
				hero.learnSpell(16);
				hero.learnSpell(17);
				hero.learnSpell(18);
				hero.Binding[113-97].setBinding(113, "Spell", 15);
				hero.Binding[119-97].setBinding(119, "Spell", 16);
				hero.Binding[101-97].setBinding(101, "Spell", 17);
				hero.Binding[114-97].setBinding(114, "Spell", 18);
				StarterWeapon.idTransform(36);
				hero.equipWeapon(&StarterWeapon);

				Hadgar.Talk(&hero, "So you prefer the shadows? The nights have grown long and full of terrors. I'm sure you will feel right at home. *He gives a short chuckle*", false, false, true, 39);
			}
			else
				input = 0;
		}
		if (input == '4')
		{
			Paragraph(&hero, "Monks study ancient martial techniques to master close quarter combat. \n-Agility focus\n-Quick actions\n-Ki(Mana regens between each fight)\n-Can wear cloth and leather\n-Keybindings: \'q\'-Quick Attack, \'w\'-Dodge, \'e\'-Stunning Strike\n", false, false, false, 0);
			if (Question(&hero, "Are you sure that you want to be a Monk?"))
			{
				hero.classSet("Monk");
				hero.agiMod(2);
				hero.strMod(2);
				hero.intMod(2);
				hero.learnSpell(19);
				hero.learnSpell(20);
				hero.learnSpell(21);
				hero.Binding[113-97].setBinding(113, "Spell", 19);
				hero.Binding[119-97].setBinding(119, "Spell", 20);
				hero.Binding[101-97].setBinding(101, "Spell", 21);
				StarterWeapon.idTransform(36);
				hero.equipWeapon(&StarterWeapon);
				
				Hadgar.Talk(&hero, "\nYou walk the nameless path? We are honored to welcome you within our walls.", false, false, true, 39);
			}
			else
				input = 0;
		}
	}
	Clear(&hero);
	Hadgar.Talk(&hero, "I wanted to welcome you personally, but I am currently re-organizing the city's defences so you will have to excuse me. Please explore the city freely, and then come speak to me if you want to "
		"contribute to our continued survival. In any case you are free to stay here as long as the city does, the barracks are open to you if you need lodgings. They lay just east of the castle, you can't miss it.   \n\n"
		"Hadgar gives you a smile and a nod, and then returns through the gate. You are left to your own devices. \n\nLarge stone walls encompass the entire city, as well as another smaller set of walls around the castle in the center. Almost everything towers in blinding white and the size of it all leaves you breathless. "
		"You've never seen anything like it before. It's not surprising that the city still stands.", false, false, false, 39);

	Paragraph(&hero, "\nThe amount of people is staggering, being a wanderer your whole life you have never seen more than a dozen people gathered, but here in the middle of the city there "
		"are hundreds of people going about their day. Thousands must live within these walls. After taking a moment, you gather yourself and decide to "
		"head out and see what other experiences this city has in store. \n\nWhat immediately grabs your attention is the fighting pits. It stands right in the middle of the town square. It's full of people fighting both mutants and each other. There even "
		"seems to be a system of retractable bar walls to section off the fighting pits so that multiple fights can happen at the same time. And they are currently making good "
		"use of it. It seems to be the perfect place to hone your skills.", false, false, true, 39);

	hero.healthMod(hero.maxHealthGet());
	hero.manaMod(hero.maxManaGet());
	Tyria(&hero);
}