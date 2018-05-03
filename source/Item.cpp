#include "../include/Being.h"

Item::Item()
{
	ID = 0;
	Name = "NULL";
	Type = other;
	SubType = "NULL";
	Description = "NULL";
	Value = 0;
}
void Item::Reset()
{
	ID = 0;
	Name = "NULL";
	Type = other;
	SubType = "NULL";
	Description = "NULL";
	Value = 0;
}
Item::Item(int id, string name, ItemType type, string subtype, string desc, int value)
{
	ID = id;
	Name = name;
	Type = type;
	SubType = subtype;
	Description = desc;
	Value = value;
}
void Item::Transform(Item item) 
{
	ID = item.idGet();
	Name = item.nameGet();
	//Type = typeget;
	SubType = item.typeGet();
	Description = item.descGet();
	Value = item.valueGet();
}
Item::~Item(){} 

int Item::pickUp(Being* being) {
	return -1;
}
void Item::Use(Being* being) {

}

int Item::idGet(){
	return ID;
}
string Item::nameGet(){
	return Name;
}
string Item::descGet(){
	return Description;
}
string Item::typeGet(){
	return SubType;
}
int Item::valueGet(){
	return Value;
}

void Item::idSet(int id){
	ID = id;
}
void Item::nameSet(string name){
	Name = name;
}
void Item::descSet(string desc){
	Description = desc;
}
void Item::typeSet(string type){
	SubType = type; 
}
void Item::valueSet(int value){
	Value = value;
}

void Item::Status(Being* being)
{
	printw("%s\n", Name.c_str());
	printw("%i\n\n", Type);
	printw("%s\n\n", Description.c_str());
	printw("Worth %i gold.", Value);
	Pause(); clear();
}
void Item::Use(void){}