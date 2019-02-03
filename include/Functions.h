#include <iostream>
#include <string>
using namespace std;

class Being;
class Player;
class Enemy;
class Companion;
class Item;
class Weapon;
class Armor;
class Spell;
class Scroll;
class Potion;
class SpellTome;

#define INVENTORY_SIZE 9
#define ENEMY_LIMIT 9
#define FOLLOWER_LIMIT 5
#define MAX_SPELLS 9
#define MAX_EFFECTS 9

bool BattleGroup(Player* hero, int number, int difficulty, int battleType);
void TournamentDefeat(Player* hero, int rounds);
bool CombatOver(Player*);
bool EnemiesDead(Player*);
void SortInitiative(int initiative[15], Being* being[15]);

int ChooseBeing(string, Being*[ENEMY_LIMIT]);
int ChooseEnemy(string, Player*, int);
int ChooseCompanion(int y, int x, string, Player*, Companion*[FOLLOWER_LIMIT]);
Being* ChooseTarget(string prompt, Player* hero, Companion* party[FOLLOWER_LIMIT], Being* being[ENEMY_LIMIT]);
int ChooseSpell(string, Being*, Spell[MAX_SPELLS]);
int ChooseItem(string, Player*, Item*[INVENTORY_SIZE], bool);
int ChooseWeapon(string, Being*, Weapon[INVENTORY_SIZE], bool);
int ChooseArmor(string, Being*, Armor[INVENTORY_SIZE], bool);
int ChooseScroll(string, Being*, Scroll[INVENTORY_SIZE], bool);
int ChoosePotion(string, Being*, Potion[INVENTORY_SIZE], bool);
int ChooseTome(string, Being*, SpellTome[INVENTORY_SIZE], bool);
int ChooseOption(string, Player*, string[9], bool);
void SortWeaponInventory(Weapon* weapon[INVENTORY_SIZE]);
void SortArmorInventory(Armor* armor[INVENTORY_SIZE]);
void SortScrollInventory(Scroll* scroll[INVENTORY_SIZE]);
void SortPotionInventory(Potion* potion[INVENTORY_SIZE]);
void SortTomeInventory(SpellTome* tome[INVENTORY_SIZE]);
void SortItemInventory(Item* item[INVENTORY_SIZE]);
void SortEnemyOrder(Enemy* enemy[ENEMY_LIMIT]);
bool Question(int y, int x, string, bool);
bool Question(Being* hero, string question);
int GetInt(int y, int x, string prompt, bool cls);
string GetStringInput(Being* hero, string prompt, bool cls);

int kbhit();
void Pause();
void Pause(Being* hero);
void Clear(Being* being);
void SleepC(int x);
void ClearX(int y, int x);
void ClearY(int y, int x);
int CurrentY();
int CurrentX();
int MaxY();
int MaxX();
void CenterText(string);
void CenterText(string, char);
void Paragraph(Being* hero, string text, bool clsbefore, bool clsafter, bool pause, int speed);
void PausedString(string output); 
void ColoredString(string text, int color);
void PausedColoredString(string text, int color); 
int HealthColorCode(Being* being);
int ManaColorCode(Being* being);
int KiColorCode(Being* being);
void HealthOutput(Player* hero, Being* being);
void Save(Player* save, bool autosave);
bool Load(Player* load);
void Menu(Player* hero);
void Journal(Player* hero);

