#include "../include/Being.h"
//Access and Mutator functions

Being::Being() 
{
	Name = "NULL";
	Type = "NULL";
	Title = "NULL";
	Health = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Gold = 0;
	Strength = 0;
	Intelligence = 0;
	Agility = 0;
	Level = 0;
	Experience = 0;

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	EquippedWeapon.Reset();
	for (int i = 0; i < 7; i++)
		EquippedArmor[i].Reset();
	for (int i = 0; i < MAX_EFFECTS; i++)
		Effect[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		wInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		aInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		pInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		sInventory[i].Reset();

	for (int i = 0; i < 9; i++)
		wPointer[i] = &wInventory[i];
	for (int i = 0; i < 9; i++)
		aPointer[i] = &aInventory[i];
	for (int i = 0; i < 9; i++)
		wPointer[i] = &wInventory[i];
	for (int i = 0; i < 9; i++)
		pPointer[i] = &pInventory[i];
	for (int i = 0; i < 9; i++)
		sPointer[i] = &sInventory[i];
	for (int i = 0; i < 9; i++)
		tPointer[i] = &tInventory[i];
	for (int i = 0; i < 9; i++)
		iPointer[i] = &Inventory[i];

}
Being::Being(string name, string title, string type, int level, int health, int mana, int strength, int intelligence, int agility, int exp, int gold) 
{
	Name = name;
	Type = type;
	Title = title;
	Type = type;
	Level = level;
	Health = health;
	MaxHealth = health;
	Mana = mana;
	MaxMana = mana;
	Strength = strength;
	Intelligence = intelligence;
	Agility = agility;
	Experience = exp;
	Gold = gold;
	EquippedWeapon.Reset();

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	for (int i = 0; i < 7; i++)
		EquippedArmor[i].Reset();
	for (int i = 0; i < MAX_EFFECTS; i++)
		Effect[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		wInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		aInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		pInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		sInventory[i].Reset();

	for (int i = 0; i < 9; i++)
		wPointer[i] = &wInventory[i];
	for (int i = 0; i < 9; i++)
		aPointer[i] = &aInventory[i];
	for (int i = 0; i < 9; i++)
		wPointer[i] = &wInventory[i];
	for (int i = 0; i < 9; i++)
		pPointer[i] = &pInventory[i];
	for (int i = 0; i < 9; i++)
		sPointer[i] = &sInventory[i];
	for (int i = 0; i < 9; i++)
		tPointer[i] = &tInventory[i];
	for (int i = 0; i < 9; i++)
		iPointer[i] = &Inventory[i];
}
void Being::Reset()
{
	Name = "NULL";
	Type = "NULL";
	Health = 0;
	MaxHealth = 0;
	Mana = 0;
	MaxMana = 0;
	Strength = 0;
	Intelligence = 0;
	Agility = 0;
	Level = 0;
	Experience = 0;
	Gold = 0;

	ypos = 0;
	xpos = 0;
	yReset = 0;
	xReset = 0;

	EquippedWeapon.Reset();
	for (int i = 0; i < 7; i++)
		EquippedArmor[i].Reset();
	for (int i = 0; i < MAX_EFFECTS; i++) 
		Effect[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		wInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		aInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		pInventory[i].Reset();
	for (int i = 0; i < INVENTORY_SIZE; i++)
		sInventory[i].Reset();

	InCombat = false;
	Stealthed = false;
}
Being::~Being() {}


//Defining Access Functions
#pragma region ACCESS FUNCTIONS

string Being::nameGet(){
	return Name;
}
string Being::typeGet(){
	return Type;
}
string Being::titleGet() {
	return Title;
}
int Being::strengthGet(){
	return Strength;
}
int Being::intGet(){
	return Intelligence;
}
int Being::agilityGet(){
	return Agility;
}
int Being::healthGet(){
	return Health;
}
int Being::maxHealthGet(){
	return MaxHealth;
}
int Being::manaGet(){
	return Mana;
}
int Being::maxManaGet(){
	return MaxMana;
}
int Being::goldGet(){
	return Gold;
}
int Being::levelGet(){
	return Level;
}
int Being::levelReqGet() {
	return LevelReq;
}
int Being::expGet(){
	return Experience;
}
int Being::yPosGet(){
	return ypos;
}
int Being::xPosGet(){
	return xpos;
}
int Being::essenceGet()
{
	int essence = getWeapon()->magicGet();

	for (int i = 0; i < 7; i++)
		essence += getArmor(i)->magicGet();

	return essence;
}
Companion Being::getCompanion(int i)
{
	Companion frank;
	return frank;
}

#pragma endregion

#pragma region MUTATOR FUNCTIONS

void Being::nameSet(string newName) {
	Name = newName;
}
void Being::typeSet(string newType){
	Type = newType;
}
void Being::titleSet(string newType) {
	Title = newType;
}
void Being::healthSet(int var){
	Health = var;
}
void Being::healthMod(int var) 
{
	Health += var;
	if (Health > MaxHealth){
		Health = MaxHealth;
	}
	if (Health < 0){
		Health = 0;
	}
	
	if (Type == "Player" && InCombat) 
	{ 
		mvprintw(0, 18, "%i/%i", Health, MaxHealth);
		if(Health < 10)
			mvprintw(0, 22, " ");
		ColoredString(" HP", HealthColorCode(&*this));
		move(ypos, xpos);
	}
}
void Being::maxHealthSet(int var){
	MaxHealth = var;
}
void Being::manaSet(int var){
	Mana = var;
}
void Being::manaMod(int var)
{
	Mana += var;
	if (Mana > MaxMana){
		Mana = MaxMana;
	}
	
	if (Type == "Player" && InCombat) 
	{ 
		mvprintw(1, 18, "%i/%i", Mana, MaxMana);
		if(Mana < 10)
			mvprintw(1, 22, " ");
		ColoredString(" MP", ManaColorCode(&*this));
		move(ypos, xpos);
	}
}
void Being::maxManaSet(int var){
	MaxMana = var;
}
void Being::strSet(int var){
	Strength = var;
}
void Being::strMod(int var){
	Strength += var;
	MaxHealth += (var * 5);
}
void Being::intSet(int var){
	Intelligence = var;
}
void Being::intMod(int var){
	Intelligence += var;
	MaxMana += (var * 5);

	if (Mana > MaxMana)
		Mana = MaxMana;
}
void Being::agiSet(int var){
	Agility = var;
}
void Being::agiMod(int var){
	Agility += var;
}
void Being::goldSet(int var){
	Gold = var;
}
void Being::goldMod(int var){
	Gold += var;
}
void Being::levelSet(int level){
	Level = level;
}
void Being::expSet(int var){
	Experience = var;
}
void Being::expGive(int var){
	//Experience += var;
}
void Being::addCompanion(int i){

}
void Being::yPosAdd(int y)
{
	ypos += y;
	if (ypos > MaxX() - 2)
	{
		SleepC(1000);
		for(int i = ypos; i >= yReset; i--)
		{
			move(i, 0);
			deleteln();
		}
		ypos = yReset;
	}
} 
void Being::yPosReset()
{
	ypos = yReset;
	for(int i = yReset; i < MaxY(); i++)
	{
		move(i, xpos);
		clrtoeol();
	}
}
void Being::yPosSet(int i){
	ypos = i;
}
void Being::xPosAdd(int x, int xReset)
{
	xpos += x;
	if (xpos > MaxX() - 2)
	{
		SleepC(2000);
		for(int i = ypos; i >= 0; i--)
		{
			move(i, xReset);
			clrtoeol();
		}
		xpos = xReset;
	}
}
void Being::xPosReset()
{
	xpos = xReset;
	for(int i = ypos; i >= 0; i--)
	{
		move(i, xpos);
		clrtoeol();
	}
}
void Being::xPosSet(int i){
	xpos = i;
}
void Being::yResetSet(int y){
	yReset = y;
}
void Being::xResetSet(int x){
	xReset = x;
}

#pragma endregion


void Being::Talk(Being* hero, string words, bool cls1, bool cls2, bool pause, int speed)
{
	if (cls1)
	{
		hero->yPosReset();
		clear();
	}

	mvprintw(hero->yPosGet(), 0, "%s, the %s:", Name.c_str(), Title.c_str()); hero->yPosAdd(2);
	Paragraph(&*hero, words, false, cls2, pause, speed);
}
void Being::Attack(Player* hero)
{
}
bool Being::killCheck(Being* hero, Being* target)
{
	if (Type == "Player")
	{
		if (target->healthGet() <= 0)
		{
			mvprintw(hero->yPosGet(), 0, "The %s is defeated!", target->nameGet().c_str()); hero->yPosAdd(2);

			//Revise for flexibility, difficulty etc.
			if (rand() % 10 == 0)
			{ // 10% chance of loots
				int random = rand() % 10 + 1;
				if (random <= 5)
				{
					Potion potion;
					int potionRand = rand() % 100 + 1;
					if (potionRand <= 40)
						potion.idTransform(7);
					else if (potionRand > 40 && potionRand <= 80)
						potion.idTransform(8);
					else
						potion.idTransform(38);

					pickupPotion(potion, 1);
					mvprintw(hero->yPosGet(), 0, "You find a potion, a %s!", potion.nameGet().c_str()); hero->yPosAdd(2);
				}
				else if (random <= 8)
				{
					Scroll scroll;
					random = rand() % 11 + 19;
					scroll.idTransform(random);

					pickupScroll(scroll);
					mvprintw(hero->yPosGet(), 0, "You find a scroll, called %s!", scroll.nameGet().c_str()); hero->yPosAdd(2);
				}
				else
				{
					SpellTome tome;
					tome.idTransform(rand() % 10 + 9);
					pickupTome(tome);
					mvprintw(hero->yPosGet(), 0, "You find an old book, called \"%s\"!", tome.nameGet().c_str()); hero->yPosAdd(2);
				}
			}
			for (int i = 0; i < 10; i++)
			{
				if (target->dropGet(i) != 0)
				{
					if (rand() % target->dropGet(i) == 0)
					{
						Item item = pickupItem(target->lootGet(i));
						string name = item.nameGet().c_str();
						mvprintw(hero->yPosGet(), 0, "You find "); hero->yPosAdd(1);
						if (name[0] == 'E' || name[0] == 'Y' || name[0] == 'U' || name[0] == 'I' || name[0] == 'O' || name[0] == 'A')
							printw("an");
						else
							printw("a");
						printw(" \"%s\"!", item.nameGet().c_str());
					}
				}
			}
			SleepC(1500);
			return true;
		}
	}
	return false;
}

//Defining Item Functions

void Being::equipWeapon(Weapon* equip)
{ //Optimize
	if (EquippedWeapon.valueGet() > 0)
	{
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (wInventory[i].nameGet() == "NULL")
			{
				wInventory[i].Transform(EquippedWeapon);
				break;
			}
		}
	}
	EquippedWeapon.Transform(*equip);
	equip->Reset();
	SortWeaponInventory(this->wPointer);
}
void Being::equipWeapon(int id)
{

}
void Being::equipArmor(Armor* equip)
{
	for (int i = 0; i < 7; i++)
	{
		if (i == equip->slotGet())
		{
			if (EquippedArmor[i].valueGet() > 0)
			{
				for (int j = 0; j < INVENTORY_SIZE; j++)
				{
					if (aInventory[j].nameGet() == "NULL")
					{
						aInventory[j].Transform(EquippedArmor[i]);
						break;
					}
				}
			}
			EquippedArmor[i].Transform(*equip);
			equip->Reset();
			SortArmorInventory(this->aPointer);
		}
	}
}
Item Being::pickupItem(int id)
{
	Weapon IronMace(1, "Iron Mace", "1H Mace", "A solid mace made from iron. \nThe mace is quite old, and the spikes are dull.", 3, 0, 10);
	Weapon OakStaff(2, "Oak Staff", "Staff", "A staff made from oak, infused with magic essence", 1, 2, 10);
	Weapon Broadsword(3, "Broadsword", "2H Sword", "A wide sturdy blade forged in iron..", 4, 0, 30);
	Armor Leather(4, "Leather Cuirass", "Leather", Chest, "Made from animal hides, it's sturdy and of decent quality.", 2, 0, 0, 20);
	Armor Robes(5, "Tattered Robes", "Cloth", Chest, "These robes are quite worn out, but a previous wearer seem to have \nimprinted some magical essence into them.", 0, 2, 1, 20);
	Armor IronArmor(6, "Iron Armor", "Iron", Chest, "Standard armor made out of iron.", 3, 0, 0, 70);
	Potion smallHealthPotion(7, "Small Health Potion", "Health", "A standard magical potion contained in a small glass vial", 10, 5, 5);
	Potion smallManaPotion(8, "Small Mana Potion", "Mana", "A standard magical potion contained in a small glass vial", 10, 5, 10);
	SpellTome SparksT(9, 1, "Harvesting Electricity", "Thunder", "An old tome. You can feel a faint heat radiating from its covers.", 30);
	SpellTome FireballT(10, 2, "The Aspect of Fire", "Fire", "An old tome. You can feel a faint tingling when touching its covers.", 40);
	SpellTome HealT(11, 3, "The Flow of Life", "Life", "An old tome. You can feel a faint warmth radiating from its covers.", 50);
	SpellTome RegenerationT(12, 4, "Balancing Lifeflow", "Life", "An old tome. You can feel a faint warmth radiating from its covers.", 70);
	SpellTome DispelT(13, 5, "Reversing Channeled Flows", "Life", "An old tome. You can feel a faint warmth radiating from its covers.", 50);
	SpellTome CorruptionT(14, 6, "The Weakness of Flesh", "Shadow", "An old tome. Its presence makes you feel uneasy.", 60);
	SpellTome DrainLifeT(15, 7, "Siphoning Techniques", "Shadow", "An old tome. Holding this book makes you feel slightly drained of energy.", 100);
	SpellTome StormT(16, 8, "Secrets of the Storm", "Thunder", "An old tome. The book seems to be slightly shaking, as if eager to be opened.", 150);
	SpellTome HazeT(17, 9,  "Warm Winds", "Fire", "An old tome. You can feel a faint heat radiating from its covers.", 50);
	SpellTome GolemT(18, 10, "Channeling Rock", "Conjuring", "Conjure minions from the very ground, have the earth itself on your side!", 200);
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
	Armor LeatherCap(30, "Leather Cap", "Leather", Head, "Basic head protection, looks kinda silly though.", 1, 0, 0, 30);
	Armor LeatherGloves(31, "Leather Gloves", "Leather", Gloves, "Some standard leather gloves", 1, 0, 0, 40);
	Armor LeatherPads(32, "Leather Shoulder Pads", "Leather", Shoulders, "Bulky shoulder pads, to protect those important joints", 1, 0, 0, 45);
	Armor LeatherLeggings(33, "Leather Leggings", "Leather", Leggs, "Some standard leather leggings", 1, 0, 0, 50);
	Potion HealthPotion(34, "Health Potion", "Health", "A standard magical potion contained in a glass vial", 20, 5, 15);
	Potion ManaPotion(35, "Mana Potion", "Mana", "A standard magical potion contained in a glass vial", 20, 5, 20);
	Weapon Sword(36, "Short Sword", "1h Sword", "A short sword, a light, piercing melee weapon", 2, 0, 20);
	SpellTome BarrierT(37, 14, "Defensive Mana Techniques", "Life", "Learn how to harden and shape mana to create protective shielding.", 100);
	Potion StrengthElixir(38, "Elixir of Strength", "Strength", "Increases strength temporarily by +2", 2, 5, 20); 

	if (id == 1)
		IronMace.pickUp(this);
	if (id == 2)
		OakStaff.pickUp(this);


	if (id == 1)
	{
		pickupWeapon(IronMace);
		return IronMace;
	}
	if (id == 2)
	{
		pickupWeapon(OakStaff);
		return OakStaff;
	}
	if (id == 3)
	{
		pickupWeapon(Broadsword);
		return Broadsword;
	}
	if (id == 4)
	{
		pickupArmor(Leather);
		return Leather;
	}
	if (id == 5)
	{
		pickupArmor(Robes);
		return Robes;
	}
	if (id == 6)
	{
		pickupArmor(IronArmor);
		return IronArmor;
	}
	if (id == 7)
	{
		pickupPotion(smallHealthPotion, 1);
		return smallHealthPotion;
	}
	if (id == 8)
	{
		pickupPotion(smallManaPotion, 1);
		return smallManaPotion;
	}
	if (id == 9)
	{
		pickupTome(SparksT);
		return SparksT;
	}
	if (id == 10)
	{
		pickupTome(FireballT);
		return FireballT;
	}
	if (id == 11)
	{
		pickupTome(HealT);
		return HealT;
	}
	if (id == 12)
	{
		pickupTome(RegenerationT);
		return RegenerationT;
	}
	if (id == 13)
	{
		pickupTome(DispelT);
		return DispelT;
	}
	if (id == 14)
	{
		pickupTome(CorruptionT);
		return CorruptionT;
	}
	if (id == 15)
	{
		pickupTome(DrainLifeT);
		return DrainLifeT;
	}
	if (id == 16)
	{
		pickupTome(StormT);
		return StormT;
	}
	if (id == 17)
	{
		pickupTome(HazeT);
		return HazeT;
	}
	if (id == 18)
	{
		pickupTome(GolemT);
		return GolemT;
	}
	if (id == 19)
	{
		pickupScroll(Sparks);
		return Sparks;
	}
	if (id == 20)
	{
		pickupScroll(Fiery);
		return Fiery;
	}
	if (id == 21)
	{
		pickupScroll(Rejuvenation);
		return Rejuvenation;
	}
	if (id == 22)
	{
		pickupScroll(Regen);
		return Regen;
	}
	if (id == 23)
	{
		pickupScroll(Dispel);
		return Dispel;
	}
	if (id == 24)
	{
		pickupScroll(Corruption);
		return Corruption;
	}
	if (id == 25)
	{
		pickupScroll(DrainLife);
		return DrainLife;
	}
	if (id == 26)
	{
		pickupScroll(Storm);
		return Storm;
	}
	if (id == 27)
	{
		pickupScroll(Haze);
		return Haze;
	}
	if (id == 28)
	{
		pickupScroll(Golem);
		return Golem;
	}
	if (id == 29)
	{
		pickupScroll(Barrier);
		return Barrier;
	}
	if (id == 30)
	{
		pickupArmor(LeatherCap);
		return LeatherCap;
	}
	if (id == 31)
	{
		pickupArmor(LeatherGloves);
		return LeatherGloves;
	}
	if (id == 32)
	{
		pickupArmor(LeatherPads);
		return LeatherPads;
	}
	if (id == 33)
	{
		pickupArmor(LeatherLeggings);
		return LeatherLeggings;
	}
	if (id == 34)
	{
		pickupPotion(HealthPotion, 1);
		return HealthPotion;
	}
	if (id == 35)
	{
		pickupPotion(ManaPotion, 1);
		return ManaPotion;
	}
	if (id == 36)
	{
		pickupWeapon(Sword);
		return Sword;
	}
	if (id == 37)
	{
		pickupTome(BarrierT);
		return BarrierT;
	}
	if (id == 38)
	{
		pickupPotion(StrengthElixir, 1);
		return StrengthElixir;
	}


	Item item(0, "Something went wrong", other, "", "", 0);
	return item;
}
int Being::pickupWeapon(Weapon weapon)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (wInventory[i].nameGet() == "NULL")
		{
			wInventory[i].Transform(weapon);
			return i;
		}
	}
	int selection = ChooseWeapon("Your weapon inventory is full, choose a weapon to replace.", this, wInventory, false);
	if (selection != -1)
	{
		wInventory[selection].Transform(weapon);
		return selection;
	}
	return -1;
}
int Being::pickupArmor(Armor armor)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (aInventory[i].nameGet() == "NULL"){
			aInventory[i].Transform(armor);
			return i;
		}
	}
	int selection = ChooseArmor("Your armor inventory is full, choose some armor to replace.", this, aInventory, false);
	if (selection != -1)
	{
		aInventory[selection].Transform(armor);
		return selection;
	}
	return -1;
}
int Being::pickupPotion(Potion potion, int amount)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (pInventory[i].nameGet() == potion.nameGet())
		{
			if (pInventory[i].amountGet() + amount <= potion.stackSizeGet())
			{
				pInventory[i].amountMod(amount);
				amount = 0;
			}
			else
			{
				amount += pInventory[i].amountGet() - potion.stackSizeGet();
				pInventory[i].amountSet(potion.stackSizeGet());
			}
		}
		if (amount == 0)
			return 0;
	}
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (pInventory[i].nameGet() == "NULL" && amount != 0)
		{
			pInventory[i].Transform(potion);
			if (amount > potion.stackSizeGet())
			{
				pInventory[i].amountMod(potion.stackSizeGet());
				amount -= potion.stackSizeGet();
			}
			else
			{
				pInventory[i].amountMod(amount);
				amount = 0;
			}
		}
		if (amount == 0)
			return 0;
	}
	return -1;
}
int Being::pickupScroll(Scroll scroll)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (sInventory[i].nameGet() == scroll.nameGet())
		{
		}
		if (sInventory[i].nameGet() == "NULL")
		{
			sInventory[i].Transform(scroll);
			return i;
		}
	}
	int selection = ChooseScroll("Your scroll inventory is full, choose a scroll to replace.", this, sInventory, false);
	if (selection != -1)
	{
		sInventory[selection].Transform(scroll);
		return selection;
	}
	return -1;
}
int Being::pickupTome(SpellTome tome)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (tInventory[i].nameGet() == "NULL"){
			tInventory[i].Transform(tome);
			return i;
		}
	}
	int selection = ChooseTome("Your spell tome inventory is full, choose a tome to replace.", this, tInventory, false);
	if (selection != -1)
	{
		tInventory[selection].Transform(tome);
		return selection;
	}
	return -1;
}

void Being::addLoot(int i, int id, int drop){}
int Being::lootGet(int i){
	return 0;
}
int Being::dropGet(int i){
	return 0;
}

Weapon* Being::getWeapon(){
	return &EquippedWeapon;
}
Armor* Being::getArmor(int i){
	return &EquippedArmor[i];
}
Potion Being::getPotion(int i){
	return pInventory[i];
}
Scroll* Being::getScroll(int i){
	return &sInventory[i];
}
Status* Being::getEffect(int i){
	return &Effect[i];
}

bool Being::hasEffect(string name)
{
	for (int i = 0; i < MAX_EFFECTS; i++)
	{
		if (Effect[i].nameGet() == name)
			return true;
	}
	return false;
}

int Being::addEffect(int id)
{
	Status effect;
	effect.idTransform(id);

	for (int i = 0; i < MAX_EFFECTS; i++)
	{
		if (Effect[i].nameGet() == effect.nameGet())
		{
			Effect[i].modTime(&*this, &*this, effect.timeGet());
			return i;
		}

		if (Effect[i].nameGet() == "NULL")
		{
			Effect[i].idTransform(id);
			if (Effect[i].typeGet() == "Strength")
				this->strMod(Effect[i].valueGet());
			if (Effect[i].typeGet() == "Agility")
				this->agiMod(Effect[i].valueGet());
			if (Effect[i].typeGet() == "Intelligence")
				this->intMod(Effect[i].valueGet());
			return i;
		}
	}
	return 0;
}


Spell* Being::getSpell(int i){
	return &spell[i];
}
int Being::learnSpell(int id)
{
	int i;
	for (i = 0; i < MAX_SPELLS; i++)
	{
		if (spell[i].nameGet() == "NULL"){
			break;
		}
	}
	if (i == MAX_SPELLS)
	{
		int replace = ChooseSpell("You already know the max amount of spells, do you wish to replace one?", &*this, spell);
		i = replace;
	}
	if (i < MAX_SPELLS && i >= 0)
	{
		spell[i].idTransform(id);
	}
	return i;
}
