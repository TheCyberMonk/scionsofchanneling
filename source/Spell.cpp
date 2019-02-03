#include "../include/Being.h"

#pragma region Initializors/Mutators

Spell::Spell()
{
	ID = 0;
	Name = "NULL";
	Class = "NULL";
	ManaCost = 0;
	Aspect = "NULL";
	Type = "NULL";
	Combat = false;
	QuickAction = false;
	Chant = "NULL";
	Impact = 0;
	AspectMod = 0;
	AttributeMod = 0;
	EssenceMod = 0;
	EffectID = 0;
	ManaCost = 0;
	IntelligenceReq = 0;
}
Spell::Spell(int id, string name, string class_, string aspect, string type, bool combat, bool quick, string desc, string chant,
	int impact, double aspectmod, double attmod, double essencemod, int effectid, int cost, int intreq)
{
	ID = id;
	Name = name;
	Class = class_;
	Aspect = aspect;
	Type = type;
	Combat = combat;
	QuickAction = quick;
	Description = desc;
	Chant = chant;
	Impact = impact;
	AspectMod = aspectmod;
	AttributeMod = attmod;
	EssenceMod = essencemod;
	EffectID = effectid;
	ManaCost = cost;
	IntelligenceReq = intreq;
}
void Spell::spellSet(int id, string name, string class_, string aspect, string type, bool combat, bool quick, string desc, string chant,
	int impact, double aspectmod, double attmod, double essencemod, int effectid, int cost, int intreq)
{
	ID = id;
	Name = name;
	Class = class_;
	Aspect = aspect;
	Type = type;
	Combat = combat;
	QuickAction = quick;
	Description = desc;
	Chant = chant;
	Impact = impact;
	AspectMod = aspectmod;
	AttributeMod = attmod;
	EssenceMod = essencemod;
	EffectID = effectid;
	ManaCost = cost;
	IntelligenceReq = intreq;
}
void Spell::Mutate(Spell spell)
{
	ID = spell.idGet();
	Name = spell.nameGet();
	Class = spell.classGet();
	Aspect = spell.aspectGet();
	Type = spell.typeGet();
	Combat = spell.inCombat();
	QuickAction = spell.quickAction();
	Chant = spell.castGet();
	Impact = spell.impactGet();
	AspectMod = spell.aspectModGet();
	AttributeMod = spell.attModGet();
	EssenceMod = spell.essenceModGet();
	EffectID = spell.effectGet();
	ManaCost = spell.costGet();
	IntelligenceReq = spell.intReqGet();
}
void Spell::Reset()
{
	ID = 0;
	Name = "NULL";
	Class = "NULL";
	Aspect = "NULL";
	Type = "NULL";
	Combat = false;
	QuickAction = false;
	Chant = "NULL";
	Impact = 0;
	AspectMod = 0;
	AttributeMod = 0;
	EssenceMod = 0;
	EffectID = 0;
	ManaCost = 0;
	IntelligenceReq = 0;
}
Spell::~Spell(){}

#pragma endregion

#pragma region Accessors

int Spell::idGet(){
	return ID;
}
string Spell::nameGet(){
	return Name;
}
string Spell::classGet(){
	return Class;
}
string Spell::aspectGet(){
	return Aspect;
}
string Spell::typeGet(){
	return Type;
}
string Spell::castGet(){
	return Chant;
}
string Spell::descGet() {
	return Description;
}
int Spell::impactGet(){
	return Impact;
}
int Spell::effectGet(){
	return EffectID;
}
int Spell::costGet(){
	return ManaCost;
}
int Spell::intReqGet(){
	return IntelligenceReq;
}
double Spell::aspectModGet(){
	return AspectMod;
}
double Spell::attModGet(){
	return AttributeMod;
}
double Spell::essenceModGet(){
	return EssenceMod;
}
bool Spell::inCombat(){
	return Combat;
}
bool Spell::quickAction(){
	return QuickAction;
}

void Spell::nameSet(string name){
	Name = name;
}
void Spell::classSet(string class_){
	Class = class_;
}
void Spell::costSet(int cost){
	ManaCost = cost;
}

#pragma endregion


bool Spell::Cast(Player* hero, Being* caster, Being* target, bool Self, bool scroll) 
{
	if (caster->manaGet() < ManaCost && !scroll) 
	{
		mvprintw(hero->yPosGet(), 0, "You don't have enough mana to use that spell."); hero->yPosAdd(2);
		return false;
	}

	srand(time(NULL));
	FullImpact = Impact;
	int NewEffect = 0;
	bool Castable = false;

	if (caster->intGet() >= IntelligenceReq)
		Castable = true;
	if (Name == "Ambush" && caster->Stealthed == false)
	{
		mvprintw(hero->yPosGet(), 0, "You can't ambush the enemy, they are aware of you."); hero->yPosAdd(2);
		Castable = false;
	}
	else if (scroll && caster->intGet() < intReqGet())
	{
		mvprintw(hero->yPosGet(), 0, "This scroll is indecipherable to you."); hero->yPosAdd(1);
		mvprintw(hero->yPosGet(), 0, "Intelligence requirement: %i", IntelligenceReq); hero->yPosAdd(2);
		if(!hero->InCombat)
			SleepC(1500);
		return false;
	}
	if (Type == "+Effect" || Type == "SelfBuff")
	{
		if (target->hasEffect(Name))
		{
			if (target->typeGet() == "Player")
			{
				mvprintw(hero->yPosGet(), 0, "%s is already active!\n", Name.c_str()); hero->yPosAdd(2);
			}
			else
			{
				mvprintw(hero->yPosGet(), 0, "%s is already active on %s!\n", Name.c_str(), target->nameGet().c_str()); hero->yPosAdd(2);
			}
			if(!hero->InCombat)
				SleepC(1500);
			return false;
		}
	}
	if (EffectID > 0)
	{
		NewEffect = target->addEffect(EffectID);
		if (target->getEffect(NewEffect)->valueGet() > 0)	//AKA, not a stat modifier
			FullImpact = target->getEffect(NewEffect)->valueGet();
	}


	if (Castable && Type == "Conjuring" && caster->typeGet() == "Player")
	{
		for (int i = 0; i < FOLLOWER_LIMIT; i++)
		{
			if (caster->getCompanion(i).typeGet() == "Conjured")
			{
				mvprintw(hero->yPosGet(), 0, "You can only control one conjured creation at a time."); hero->yPosAdd(2);
				if(!hero->InCombat)
					SleepC(1500);
				return false;
			}
		}
		mvprintw(hero->yPosGet(), 0, "%s uses %s .", caster->nameGet().c_str(), caster->nameGet().c_str()); hero->yPosAdd(1);
		mvprintw(hero->yPosGet(), 0, "%s", Chant.c_str()); hero->yPosAdd(1);
		caster->addCompanion(EffectID); 
		caster->manaMod(-ManaCost);
		return true;
	}

	if (Castable && target->healthGet() > 0) 
	{
		if (Class == "Channeler" && caster->typeGet() == "Player")
			;// printw("You cast " << Name << "!\n");
		else if (caster->typeGet() == "Player")
			;// printw("You use " << Name << "!\n");
		else
			mvprintw(hero->yPosGet(), 0, "%s casts %s.", caster->nameGet().c_str(), Name.c_str()); hero->yPosAdd(2);

		if (Aspect == "Strength")
		{
			Castable = true;
			bool raged = false;
			for (int i = 0; i < MAX_EFFECTS; i++)
			{
				if (caster->getEffect(i)->nameGet() == "Rage")
					raged = true;
			}
			if (raged)
				FullImpact += (caster->strengthGet() * AttributeMod * 1.5) + (caster->getWeapon()->damageGet() * AspectMod);
			else
				FullImpact += (caster->strengthGet() * AttributeMod) + (caster->getWeapon()->damageGet() * AspectMod);

			for (int i = 0; i < MAX_EFFECTS; i++)
			{
				if (caster->getEffect(i)->typeGet() == "+Damage")
					FullImpact += (caster->getEffect(i)->valueGet() * AspectMod);
			}
		}
		else if (Aspect == "Agility")
		{
			Castable = true;
			FullImpact += (caster->agilityGet() * AttributeMod) + (caster->getWeapon()->damageGet() * AspectMod);
			for (int i = 0; i < MAX_EFFECTS; i++)
			{
				if (caster->getEffect(i)->typeGet() == "+Damage")
					FullImpact += (caster->getEffect(i)->valueGet() * AspectMod);
			}
		}
		else
		{
			FullImpact += (caster->intGet() * AttributeMod) + (caster->essenceGet() * EssenceMod);
			if (Type != "+Effect" && Type != "SelfBuff")
			{
				for (int i = 0; i < 7; i++)
					FullImpact -= target->getArmor(i)->magicDefenceGet();
			}
		}
		if (Type != "+Effect" && Type != "SelfBuff")
			FullImpact += (rand() % (int)(FullImpact / 3)) - (int)(FullImpact / 6);


		if (Name == "Execute")
		{
			Castable = false;

			for (int i = 0; i < MAX_EFFECTS; i++)
			{
				if (target->Effect[i].typeGet() == "Stun")
					Castable = true;
			}

			if (!Castable)
			{
				mvprintw(hero->yPosGet(), 0, "The enemy is not vulnerable..."); hero->yPosAdd(2);
				return false;
			}
		}

		if (Castable)
		{
			if (Type == "Dispel")
			{
				int input = 99;
				while (input != 0)
				{
					mvprintw(hero->yPosGet(), 0, "What effect do you wish to remove?"); hero->yPosAdd(1);
					for (int i = 0; i < MAX_EFFECTS; i++)
					{
						if (target->getEffect(i)->nameGet() != "NULL")
							printw("%i - %s\n", i+1, target->getEffect(i)->nameGet().c_str());
					}
					mvprintw(hero->yPosGet(), 0, "0. Cancel>"); hero->yPosAdd(1);
					mvprintw(hero->yPosGet(), 0, ">"); hero->yPosAdd(1);
					input = getch();

					if (input <= MAX_EFFECTS && input > 0)
					{
						if (target->getEffect(input - 49)->nameGet() != "NULL")
						{
							mvprintw(hero->yPosGet(), 0, "%s %s is Dispelled!\n", Chant.c_str(), target->getEffect(input - 49)->nameGet().c_str()); hero->yPosAdd(2);
							target->getEffect(input - 49)->Reset();
							break;
						}
					}
					if (input == 0)
						return false;
				}
			}
			else
			{
				hero->yPosAdd(-2);
				Paragraph(&*hero, Chant, false, false, false, 0);
				if (Type == "Damage" || Type == "AoE" || Type == "Weapon")
				{
					target->healthMod(-FullImpact);

					if (target->typeGet() == "Player")
					{
						mvprintw(hero->yPosGet(), 0, "You take %i damage. ", (int)FullImpact); hero->yPosAdd(2);
						HealthOutput(hero, target);
					}
					else
					{
						mvprintw(hero->yPosGet(), 0, "%s takes %i damage. ", target->nameGet().c_str(), (int)FullImpact); hero->yPosAdd(2);
						HealthOutput(hero, target);
					}
				}
				if (Type == "Drain")
				{
					target->healthMod(-FullImpact);
					caster->healthMod(FullImpact / 2);

					if (target->typeGet() == "Player")
					{
						mvprintw(hero->yPosGet(), 0, "You take %i damage. ", (int)FullImpact); hero->yPosAdd(1);
						HealthOutput(hero, target);
					}
					else
					{
						mvprintw(hero->yPosGet(), 0, "%s takes %i damage. ", target->nameGet().c_str(), (int)FullImpact); hero->yPosAdd(2);
						HealthOutput(hero, target);
					}

					if (caster->typeGet() == "Player")
					{
						mvprintw(hero->yPosGet(), 0, "You heal for %i health. ", (int)(FullImpact / 2)); hero->yPosAdd(1);
						HealthOutput(hero, caster);
					}
					else
					{
						mvprintw(hero->yPosGet(), 0, "%s heals for %i health. ", caster->nameGet().c_str(), (int)(FullImpact / 2)); hero->yPosAdd(2);
						HealthOutput(hero, caster);
					}

				}
				if (Type == "Healing")
				{
					if (Self == true)
					{
						caster->healthMod(FullImpact);
						if (caster->typeGet() == "Player")
						{
							mvprintw(hero->yPosGet(), 0, "You heal yourself for %i health.\n", (int)FullImpact); hero->yPosAdd(2);
						}
						else
						{
							mvprintw(hero->yPosGet(), 0, "%s heals for %i health.\n", caster->nameGet().c_str(), (int)FullImpact); hero->yPosAdd(2);
						}
					}
					else
					{
						target->healthMod(FullImpact);
						if (target->typeGet() == "Player")
						{
							mvprintw(hero->yPosGet(), 0, "You're healed for %i health.\n", (int)FullImpact); hero->yPosAdd(2);
						}
						else
						{
							mvprintw(hero->yPosGet(), 0, "%s is healed for %i health.\n", target->nameGet().c_str(), (int)FullImpact); hero->yPosAdd(2);
						}
					}
				}
				if (EffectID > 0)
				{
					if (Self == true)
					{
						caster->getEffect(NewEffect)->setValue(FullImpact);
						mvprintw(hero->yPosGet(), 0, "%s is affected by %s.\n", caster->nameGet().c_str(), caster->getEffect(NewEffect)->nameGet().c_str()); hero->yPosAdd(2);
					}
					else
					{
						target->getEffect(NewEffect)->setValue(FullImpact);
						mvprintw(hero->yPosGet(), 0, "%s is affected by %s.\n", target->nameGet().c_str(), target->getEffect(NewEffect)->nameGet().c_str()); hero->yPosAdd(2);
					}
				}
			}
			if(!hero->InCombat)
				SleepC(1500);

			if (caster->typeGet() == "Player")
				caster->killCheck(&*hero, target);

			if (Type != "AoE")
				caster->manaMod(-ManaCost);

			if (caster->typeGet() == "Player" && QuickAction)
			{
				hero->ExtraActionUsed = true;
				return false;
			}
			return true;
		}
	}
	return false;
}

void Spell::idTransform(int id)
{
	//ID, Name, Class, Aspect, Type, Combat Only?, Quick Action?,  Description, Chant, Impact, AspectMod, AttributeMod, EssenceMod, EffectID, Cost, IntelligenceRequirement
	if (id == 1)
		spellSet(1, "Sparks", "Channeler", "Thunder", "Damage", true, false,
		"A basic lightning based damage spell.",
		"A cacophony of sparks crackles from the casters fingertips and electrocutes the target.", 5, 1, 1, 1, 0, 2, 1);
	if (id == 2)
		spellSet(2, "Fireball", "Channeler", "Fire", "Damage", true, false,
		"A decent fire based damage spell that scales nicely as you power up.",
		"The caster amasses a huge fireball in their palms and hurl it at their target!", 8, 1, 1.5, 1.5, 0, 4, 1);
	if (id == 3)
		spellSet(3, "Heal", "Channeler", "Life", "Healing", false, false,
		"A basic healing spell.",
		"The caster focuses on the flow of life energies within them. And then channeling it where needed.", 4, 1, 1, 1, 0, 2, 1);
	if (id == 4)
		spellSet(4, "Regeneration", "Channeler", "Life", "+Effect", false, false,
		"Applies a buff to the target that heals a small amount every round, with a duration of 4 rounds.",
		"The caster focuses on the life energies within them, creating a sustained flow of positive energy.", 0, 1, 0.75, 0.5, 3, 3, 2);
	if (id == 5)
		spellSet(5, "Dispel", "Channeler", "Life", "Dispel", false, true,
		"A spell which can be used to remove any status effect from foe or friend alike. Quick action.",
		"The caster brings their attention to the effect, reading its magic. And then applying opposite forces to Dispel it.", 0, 0, 0, 0, 0, 1, 1);
	if (id == 6)
		spellSet(6, "Corruption", "Channeler", "Shadow", "-Effect", true, false,
		"Applies a debuff to an enemy and it takes damage each round, with a duration of 3 rounds.",
		"Ancient incantations of death and decay is muttered... The target is struck with a horrible affliction!", 1, 1, 0.75, 0.5, 4, 2, 1);
	if (id == 7)
		spellSet(7, "Drain Life", "Channeler", "Shadow", "Drain", true, false,
		"A spell that does damage to an enemy and heals the caster.",
		"The caster uses magic to latch onto the life essence of his enemy. Forcibly pulling it towards him.", 2, 1, 1, 1, 0, 3, 1);
	if (id == 8)
		spellSet(8, "Thunderstorm", "Channeler", "Thunder", "AoE", true, false,
		"A lightning based damage spell which damages all your enemies.",
		"The caster controls the clouds and unleashes a cacophony of lightning strikes at its foes!", 2, 1, 0.5, 0.5, 0, 7, 3);
	if (id == 9)
		spellSet(9, "Flame Haze", "Channeler", "Fire", "Damage", true, false,
		"A fire based damage spell. It also applies a debuff that reduces the accuracy of the target, with a duration of 2 rounds.",
		"Sand whirls all around.", 1, 1, 1, 1, 1, 2, 1);
	if (id == 10)
		spellSet(10, "Conjure Stone Golem", "Channeler", "Earth", "Conjuring", false, false,
		"A spell which summons a golem to fight beside you. You can only have one conjured companion active at any time, and it disappears at the end of combat.",
		"You focus your magic on the ground in front of you, and large stones fly out of the ground. They fuse together to form a bipedal shape and it joins the fight.", 0, 0, 0, 0, 2, 10, 6);
	if (id == 14)
		spellSet(14, "Mana Barrier", "Channeler", "Life", "+Effect", false, true,
		"Applies a buff that reduces all incoming damage based on your intelligence and magic essence. Quick action.",
		"The caster creates and sustains a barrier around themselves, increasing defences.", 0, 0, 0.5, 0.5, 6, 3, 1);

	if (id == 11)
		spellSet(11, "Whirlwind", "Berserker", "Strength", "AoE", true, false,
		"Deals a small amount of damage to all enemies.",
		"\nYou swing your weapon, keeping momentum while you slash through your enemies.", 1, 0.3, 0.5, 0, 0, 1, 1);
	if (id == 12)
		spellSet(12, "Charge", "Berserker", "Strength", "Damage", true, false,
		"Deals a small amount of damage to an enemy and stuns it for one round.",
		"The target is charged and knocked to the ground.", 0, 0, 1, 0, 5, 2, 0);
	if (id == 13)
		spellSet(13, "Execute", "Berserker", "Strength", "Damage", true, false,
		"Deals a large amount of damage to any incapacitated enemy.",
		"You swing at the weakened enemy, attempting to finish it.", 5, 1, 2, 0, 0, 0, 0);

	if (id == 15)
		spellSet(15, "Ambush", "Nightblade", "Agility", "Damage", true, false,
		"An agility based attack, it deals a large amount of damage to any enemy which have yet to take an action.",
		"You take the enemy unaware, striking a vital spot!", 5, 2, 2, 0, 0, 1, 0);
	if (id == 16)
		spellSet(16, "Poison Strike", "Nightblade", "Agility", "Damage", true, false,
		"An agility based attack, it deals damage to an enemy and applies a debuff that deals damage for 2 rounds.",
		"You throw a poisoned knife at the enemy.", 2, 0, 1, 0, 2, 2, 0);
	if (id == 17)
		spellSet(17, "Enchant Weapon", "Nightblade", "Enchanting", "+Effect", false, true,
		"Applies a buff to the caster, increasing melee damage by an amount based on your intelligence and magic essence. Quick action.",
		"You draw upon the strength of your own spirit and channel it, temporarily re-arranging the atoms of the weapon to make it razor sharp.", 1, 0, 1, 1, 7, 2, 2);
	if (id == 18)
		spellSet(18, "Devastating Strike", "Nightblade", "Strength", "Damage", true, false,
		"Deals a large amount of damage that is based on your strength.",
		"You channel unstable essence into your weapon. After plunging your weapon into your enemy, it shakes violently in your hand ripping the foe apart.", 6, 2, 2, 1, 0, 5, 2);

	if (id == 19)
		spellSet(19, "Quick Attack", "Monk", "Agility", "Damage", true, true,
		"A quick attack. Quick action.",
		"You land a quick resounding unarmed strike.", 3, 0, 1, 0, 0, 5, 1);
	if (id == 20)
		spellSet(20, "Dodge", "Monk", "Agility", "SelfBuff", true, true,
		"Applies a buff to yourself that greatly increases your avoidance to attacks for one round. Quick action.",
		"You focus on dodging any incoming attacks.", 0, 0, 0, 0, 8, 2, 1);
	if (id == 21)
		spellSet(21, "Stunning Strike", "Monk", "Agility", "Damage", true, false,
		"Deals a small amount of damage to an enemy and stuns it for one round.",
		"You form Ki in your palm and unleash it with a strike creating a concussive force.", 0, 1, 1, 0, 9, 3, 1);

	//ID, Name, Class, Aspect, Type, Combat Only?, Quick Action?, Description, Chant, Impact, AspectMod, AttributeMod, EssenceMod, EffectID, Cost, IntelligenceRequirement
	if (id == 22)
		spellSet(22, "Rage", "Berserker", "Strength", "SelfBuff", true, true,
			"Directs your unbound rage at your enemies, increasing damage done and decreases physical damage taken. Only usable once per rest. Quick action.",
			"You unleash your rage and direct it towards your enemies. AAAAHHHHRG, they're gonna get it now!", 0, 0, 0, 0, 11, 0, 0);
	if (id == 23) //Only implemented here so far
		spellSet(23, "Unleash Ki", "Monk", "Agility", "Damage", true, false,
			"Unleash your entire storage of Ki into a singular strike, the more Ki you have the more damaging this attack will be. It is also very straining for the body and you will take part of the damage dealt.",
			"You direct all of your inner Ki into your fist, making it hard as steel. Then land a devastating blow as it lands and the Ki coating explodes out towards your enemy.", 3, 1, 1.5, 0, 0, 0, 0);
}