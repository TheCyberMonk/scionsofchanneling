#include "../include/Being.h"

Scroll::Scroll()
{
	ID = 0;
	SpellID = 0;
	Name = "NULL";
	Type = spellscroll;
	SubType = "NULL";
	Description = "NULL";
	Value = 0;
}
Scroll::Scroll(int id, int sid, string name, string type, string desc, int value)
{
	ID = id;
	SpellID = sid;
	Name = name; 
	Type = spellscroll;
	SubType = type;
	Description = desc;
	Value = value;
}
Scroll::~Scroll(){}

void Scroll::Transform(Scroll scroll)
{
	ID = scroll.idGet();
	SpellID = scroll.spellIDGet();
	Name = scroll.nameGet();
	SubType = scroll.typeGet();
	Description = scroll.descGet();
	Value = scroll.valueGet();
}

bool Scroll::Status(Being* hero, bool vendor)
{
	if (!vendor)
		clear();

	printw("%s\n", Name.c_str());
	printw("%s\n", Description.c_str());
	if (!vendor)
	{
		printw("Value: %i\n\n", Value);
		return Question(&*hero, "Use it?");
	}
	return false;
}

bool Scroll::Use(Player* hero, Being* caster, Being* target, Being* enemy[10])
{
	caster->scrollSpell.idTransform(SpellID); 

	bool SelfCast = false;
	if (target->typeGet() == "Player")
		SelfCast = true;

	if (SubType == "AoE")
	{
		if (!caster->InCombat)
		{
			PausedString("You have to be in combat to use this spell.");
			caster->scrollSpell.Reset();
			return false;
		}
		for (int i = 0; i < ENEMY_LIMIT; i++)
		{
			if (enemy[i]->healthGet() > 0)
				caster->scrollSpell.Cast(hero, caster, enemy[i], false, true);
		}

		caster->scrollSpell.Reset();
		Reset();

		return true;
	}

	if (caster->scrollSpell.Cast(hero, caster, target, SelfCast, true))
	{
		caster->manaMod(caster->scrollSpell.costGet());
		caster->scrollSpell.Reset();
		Reset();
		return true;
	}

	caster->scrollSpell.Reset();
	return false;
}
int Scroll::spellIDGet(){
	return SpellID;
}
void Scroll::idTransform(int id)
{
	Scroll Sparks(19, 1, "Scroll of Sparks", "Thunder", "A common scroll used to cast a basic thunder spell", 10);
	Scroll Fiery(20, 2, "Fiery Incantations", "Fire", "A common scroll used to cast a basic fire spell", 15);
	Scroll Rejuvenation(21, 3, "Secrets of Rejuvenation", "Healing", "A scroll used to cast a basic healing spell", 10);
	Scroll Regen(22, 4, "Regeneration Scroll", "Healing", "A scroll used to apply a healing effect", 20);
	Scroll Dispel(23, 5, "Dispel Scroll", "Healing", "A scroll used to remove an effect", 15);
	Scroll Corruption(24, 6, "Corruption Scroll", "Shadow", "A scroll used to cast a negative effect", 20);
	Scroll DrainLife(25, 7, "Drain Life Scroll", "Shadow", "A scroll used to drain life from your enemies", 30);
	Scroll Storm(26, 8, "Stormbringer", "AoE", "Calls forth a storm onto a group of enemies", 40);
	Scroll Haze(27, 9, "Flame Haze", "Fire", "Creates a small sandstorm to damage and blind an enemy", 20);
	Scroll Golem(28, 10, "Infusing the Earth", "Conjuring", "Conjure minions from the very ground, have the earth itself on your side!", 50);
	Scroll Barrier(29, 14, "Barrier Scroll", "+Effect", "Casts Mana Barrier, a spell that solidifies life essence to negate any attack.", 10);

	if (id == 19)
		Transform(Sparks);
	if (id == 20)
		Transform(Fiery);
	if (id == 21)
		Transform(Rejuvenation);
	if (id == 22)
		Transform(Regen);
	if (id == 23)
		Transform(Dispel);
	if (id == 24)
		Transform(Corruption);
	if (id == 25)
		Transform(DrainLife);
	if (id == 26)
		Transform(Storm);
	if (id == 27)
		Transform(Haze);
	if (id == 28)
		Transform(Golem);
	if (id == 29)
		Transform(Barrier);
}