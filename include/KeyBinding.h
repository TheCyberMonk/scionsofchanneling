#include <iostream>
#include <string>
using namespace std;

class Player;
class Spell;
class Scroll;
class Weapon;
class Armor;

class KeyBinding
{
private:
	int Number;
	string Type;
	int ID;

	Spell spell;
	Potion potion;
	Scroll scroll;
	Weapon weapon;
	Armor armor;
public:
	KeyBinding();
	KeyBinding(int, string, int);
	~KeyBinding();

	void Reset();

	int keyGet();
	string nameGet();
	string typeGet();
	int idGet();

	void numberSet(int);
	void typeSet(string);
	void idSet(int);

	void setBinding(int, string, int);
};