#include "../include/Being.h"

SpellTome::SpellTome()
{
	ID = 0;
	SpellID = 0;
	Name = "NULL";
	Type = tome;
	SubType = "NULL";
	Description = "NULL";
	Value = 0;
}
SpellTome::SpellTome(int id, int sid, string name, string type, string desc, int value)
{
	ID = id;
	SpellID = sid;
	Name = name;
	Type = tome;
	SubType = type;
	Description = desc;
	Value = value;
}
void SpellTome::Transform(SpellTome tome)
{
	ID = tome.idGet();
	SpellID = tome.spellIDGet();
	Name = tome.nameGet();
	SubType = tome.typeGet();
	Description = tome.descGet();
	Value = tome.valueGet();
}
SpellTome::~SpellTome(){}

void SpellTome::Use(Player* hero)
{
	int number = hero->learnSpell(SpellID);

	if (number >= 0)
	{
		for (int i = 0; i < MAX_SPELLS; i++)
		{
			if (hero->getSpell(i)->nameGet() == hero->getSpell(number)->nameGet())
			{
				if (i != number) 
				{
					PausedString("You already know this spell.");
					hero->getSpell(number)->Reset();
					return;
				}
			}
		}
		if (hero->intGet() < hero->getSpell(number)->intReqGet() || hero->classGet() != "Channeler")
		{
			PausedString("You study the pages for awhile, but must eventually admit that you cannot fully comprehend its contents.");
			hero->getSpell(number)->Reset();
		}
		else
		{
			Paragraph(&*hero, "You read the ancient spell tome, pondering its contents and absorbing all the knowledge you can. You have learned the spell \"" + hero->getSpell(number)->nameGet() + "\"!\n", true, false, true, 39);
		}
	}
}
bool SpellTome::Status(Being* hero, bool vendor)
{
	if (!vendor)
		clear();
	printw("%s\n\n", Name.c_str());
	printw("%s\n\n", Description.c_str());
	if (!vendor)
	{
		printw("Value: %i\n\n", Value);
		return Question(&*hero, "Use it?");
	}
	return false;
}

int SpellTome::spellIDGet(){ 
	return SpellID;
}
void SpellTome::idTransform(int id)
{
	//int id, int spellid, string name, string type, string desc, int value 
	SpellTome Sparks(9, 1, "Harvesting Electricity", "Thunder", "An old tome.\nYou can feel a faint tingling when touching its covers.", 30);
	SpellTome Fireball(10, 2, "The Aspect of Fire", "Fire", "An old tome.\nYou can feel a faint heat radiating from its covers.", 40);
	SpellTome Heal(11, 3, "The Flow of Life", "Life", "An old tome.\nYou can feel a faint warmth radiating from its covers.", 50);
	SpellTome Regeneration(12, 4, "Balancing Lifeflow", "Life", "An old tome.\nYou can feel a faint warmth radiating from its covers.", 70);
	SpellTome Dispel(13, 5, "Reversing Channeled Flows", "Life", "An old tome.\nYou can feel a faint warmth radiating from its covers.", 50);
	SpellTome Corruption(14, 6, "The Weakness of Flesh", "Shadow", "An old tome.\nIts presence makes you feel uneasy.", 60);
	SpellTome DrainLife(15, 7, "Siphoning Techniques", "Shadow", "An old tome.\nHolding this book makes you feel slightly drained of energy.", 100);
	SpellTome Storm(16, 8, "Secrets of the Storm", "Thunder", "An old tome.\nThe book seems to be slightly shaking, as if eager to be opened.", 150);
	SpellTome Haze(17, 9, "Warm Winds", "Fire", "An old tome.\nYou can feel a faint heat radiating from its covers.", 50);
	SpellTome GolemT(18, 10, "Channeling Rock", "Conjuring", "Conjure minions from the very ground, have the earth itself on your side!", 200);
	SpellTome BarrierT(37, 14, "Defensive Mana Techniques", "Life", "Learn how to harden and shape mana to create protective shielding.", 100);

	if (id == 9)
		Transform(Sparks);
	if (id == 10)
		Transform(Fireball);
	if (id == 11)
		Transform(Heal);
	if (id == 12)
		Transform(Regeneration);
	if (id == 13)
		Transform(Dispel);
	if (id == 14)
		Transform(Corruption);
	if (id == 15)
		Transform(DrainLife);
	if (id == 16)
		Transform(Storm);
	if (id == 17)
		Transform(DrainLife);
	if (id == 18)
		Transform(GolemT);
	if(id == 37)
		Transform(BarrierT);
}