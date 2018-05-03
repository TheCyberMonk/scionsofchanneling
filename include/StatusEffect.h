#include <iostream>
#include <string>
using namespace std;

#define StatusEffect_H
#ifdef StatusEffect_H

class Status{
public:
	Status();
	Status(int id, string name, string type, int value, int intmod, int variance, int time);
	~Status();

	string nameGet();
	string typeGet();
	int valueGet(); 
	int intModGet();
	int varianceGet();
	int timeGet();
	int idGet();

	void modTime(Being* being, Being* hero, int value);
	void modValue(int var);
	void setValue(int value);

	void Transform(Status* status);
	void idTransform(int id);
	void Reset();
private:
	int ID;
	string Name;
	string Type;
	int IntelligenceModifier; //Adds extra impact depending on Intelligence, set to 0 if irrelevant or unwanted. 5 intmod / 5 int = 1 extra impact
	int Value; //Variable, base damage etc.
	int Variance; //How random the impact is from the default value
	int Time;
};

#endif StatusEffect_H