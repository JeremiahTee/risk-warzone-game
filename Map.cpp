//============================================================================
// Name        : Map.cpp
// Author      : Maxime Johnson (40081684)
// Description : Map c++ class.
//============================================================================

#include "Map.h"
#include <vector>
#include <unordered_map>
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

Map::Map(const Map& map) {
	territories = map.territories;
	territoryNeighbors = map.territoryNeighbors;
	continents = map.continents;
}

Map::~Map() {
	cout << "Destructing" << endl;
	/*
	for (auto territory : territories) {
		delete territory;
	}
	*/
}

bool Map::validate() {
	return validateTerritoryConnectivity() && validateContinentConnectivity() && validateContinentExclusivity();
}

bool Map::validateTerritoryConnectivity() {
	vector<Territory*> territoryList = getTerritories();

	//Checks that there exists a node that is able to reach all nodes.
	for (auto i : territoryList) {
		if (!validateNodeConnectivity(i)) {
			return false;
		}
	 }

	return true;
}

bool Map::validateNodeConnectivity(Territory* startingNode) {
	vector<Territory*> territoryList = getTerritories();

	vector<Territory*> toProcess;
	vector<Territory*> processed;

	if (territoryList.size() > 0) {
		toProcess.push_back(startingNode);
	}

	//Processes every territory connected to eachother that hasn't already been processed or is queued for processing.
	while (toProcess.size() > 0) {
		Territory* currentlyProcessing = toProcess[toProcess.size() - 1];
		toProcess.pop_back();
		processed.push_back(currentlyProcessing);

		vector<Territory*> neighbors = getTerritoryNeighbors(currentlyProcessing);
		for (auto i : neighbors) {
			if (!contains(processed, i) && !contains(toProcess, i)) {
				toProcess.push_back(i);
			}
		}
	}


	//Checks if all territories have been processed, if not there is a missing connection somewhere.
	for (auto i : territoryList) {
		if (!contains(processed, i)) {
			return false;
		}
	}

	return true;
}

bool Map::validateContinentConnectivity() {

	//Confirms all continents have atleast one territory within it.
	for (auto i : continents) {
		if (i.second.size() <= 0) {
			return false;
		}
	}

	//Confirms all territories belong to a continent.
	for (auto i : getTerritories()) {
		bool isOwned = false;
		for (auto j : continents) {
			if (contains(j.second, i)) {
				isOwned = true;
				break;
			}
		}
		if (!isOwned) {
			return false;
		}
	}

	return true; //If all territories are connected and all territories belong to a single continent, then this can be implied.
}

bool Map::validateContinentExclusivity() {
	vector<string> list = getContinents();

	//Confirms there are no duplicate territories in a continent.
	for (auto i : list) {
		if (hasDuplicates(continents[i])) {
			return false;
		}
	}

	//Confirms each territory belongs to only a single continent.
	for (auto i : continents) {
		for (auto j : continents) {
			if (i.first != j.first) {
				for (auto k : i.second) {
					if (contains(j.second, k)) {
						return false;
					}
				}
			}
		}
	}

	return true;
}

Territory* Map::getTerritory(string territoryName) {
  if (!territories.empty()) {
    for (auto i : territories) {
      if (i->getName() == territoryName) {
        return i;
      }
    }
  } else {
    return new Territory("N/A");
  }
}

vector<Territory*> Map::getTerritories() {
	return territories;
}

vector<Territory*> Map::getTerritoryNeighbors(Territory* territory) {
	return territoryNeighbors.at(territory->getName());
}

vector<Territory*> Map::getTerritoryNeighbors(string territoryName) {
	return territoryNeighbors.at(territoryName);
}



void Map::addTerritory(Territory* territory, vector<Territory*> neighborList) {
	territories.push_back(territory);
	territoryNeighbors[territory->getName()] = neighborList;
}

void Map::addTerritory(string continent, int bonusArmyCount, Territory* territory, vector<Territory*> neighborList) {
	addTerritory(territory, neighborList);
	registerWithContinent(continent, bonusArmyCount, territory);
}



unordered_map<string, vector<Territory*>> Map::getTerritoryNeighborMap() {
	return territoryNeighbors;
}

void Map::setTerritoryNeighborsMap(unordered_map<string, vector<Territory*>> map) {
	territoryNeighbors = map;
}
bool Territory::isNeighbor(Territory* t1, Territory* t2, int n)
{
	if (n == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


vector<string> Map::getContinents() {
	vector<string> toReturn;
	for (auto kv : continents) {
		toReturn.push_back(kv.first);
	}
	return toReturn;
}

unordered_map<string, vector<Territory*>> Map::getContinentMap() {
	return continents;
}

void Map::registerWithContinent(string continent, int bonusArmyCount, Territory* territory) {
	continents[continent].push_back(territory);
	continentArmies[continent] = bonusArmyCount;
}

void Map::assignTerritory(Player* player, Territory* territory) {
	territory->setOwner(player);
	vector<Territory*> list = player->getOwnedTerritories();
	list.push_back(territory);
	player->setOwnedTerritories(list);
}

Map* Map::getTestMap() {
	Territory* a = new Territory("a");
	Territory* b = new Territory("b");
	Territory* c = new Territory("c");
	Territory* d = new Territory("d");

	Map* map = new Map();

	vector<Territory*> list = {
		b
	};
	map->addTerritory("1", 1, a, list);

	list = {
		c
	};
	map->addTerritory("1", 1, b, list);

	list = {
		b,d
	};
	map->addTerritory("2", 1, c, list);

	list = {
		c,
		a
	};
	map->addTerritory("2", 1, d, list);

	return map;
}

bool Map::contains(vector<Territory*> list, Territory* territory) {
	for (auto i : list) {
		if (i->getName() == territory->getName()) {
			return true;
		}
	}
	return false;
}

bool Map::hasDuplicates(vector<Territory*> list) {
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (list[i]->getName() == list[j]->getName()) {
				return true;
			}
		}
	}
	return false;
}

Map& Map::operator=(const Map& m) {
	territories = m.territories;
	territoryNeighbors = m.territoryNeighbors;
	continents = m.continents;

	return *this;
}

/*
ostream& operator <<(ostream& out, Map& m) {
	for (auto c : m.getContinents()) {
		out << c;
	}
	return out;
}*/
