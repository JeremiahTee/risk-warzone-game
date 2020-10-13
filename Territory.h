//============================================================================
// Name        : Territory.h
// Author      : Maxime Johnson (40081684)
// Description : Territory header class.
//============================================================================

#pragma once

class Player; //forward declaration to avoid compilation errors

#include "Player.h"
#include <string>

using namespace std;

class Territory
{
private:
	string name;
	Player* owner;
	int armyCount;

public:
	Territory() = default; //default constructor.
	Territory(string n); //constructor with just a name.
	Territory(string n, Player* player, int armies); //constructor with name, owner, and an army count.
	Territory(const Territory& territory); //copy constructor.

	string getName(); //Get territory name.

	Player* getOwner(); //Get owner of territory.
	void setOwner(Player* player); //Set owner of territory.

	int getArmyCount(); //Get army count of territory.
	void setArmyCount(int armies); //Set army count of territory.

	Territory& operator=(const Territory& t); //assignment operator.
	friend ostream& operator <<(ostream& out, Territory& t);//stream insertion operator.
};
