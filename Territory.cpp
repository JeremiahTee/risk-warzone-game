//============================================================================
// Name        : Territory.cpp
// Author      : Maxime Johnson (40081684)
// Description : Territory c++ class.
//============================================================================

#include "Territory.h"
#include "Player.h"
#include <string>

using namespace std;

Territory::Territory(string n) {
	name = n;
	armyCount = 0;
	owner = NULL;
}
Territory::Territory(string n, Player* player, int armies) {
	name = n;
	owner = player;
	armyCount = armies;
}
Territory::Territory(const Territory& territory) {
	name = territory.name;
	owner = territory.owner;
	armyCount = territory.armyCount;
}

string Territory::getName() {
	return name;
}

Player* Territory::getOwner() {
	return owner;
}
void Territory::setOwner(Player* player) {
	owner = player;
}

int Territory::getArmyCount() {
	return armyCount;
}

void Territory::setArmyCount(int armies) {
	armyCount = armies;
}

Territory& Territory::operator=(const Territory& t) {
	name = t.name;
	owner = t.owner;
	armyCount = t.armyCount;

	return *this;
}

ostream& operator <<(ostream& out, Territory& t) {
	out << "Territory Name: " + t.name;
	return out;
}