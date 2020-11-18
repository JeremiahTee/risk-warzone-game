//============================================================================
// Name        : Map.h
// Author      : Maxime Johnson (40081684)
// Description : Map header class.
//============================================================================

#pragma once
#include <map>

class Map;
class Player; //forward declaration to avoid compilation errors

#include "Territory.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
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
	bool isNeighbor(Territory* t1, Territory* t2, int n);//Only till maploader fixed
	Player* getOwner(); //Get owner of territory.
	void setOwner(Player* player); //Set owner of territory.

	int getArmyCount(); //Get army count of territory.
	void setArmyCount(int armies); //Set army count of territory.

	Territory& operator=(const Territory& t); //assignment operator.
	friend ostream& operator <<(ostream& out, Territory& t);//stream insertion operator.
};

class Map
{
private:
	vector<Territory*> territories;
	unordered_map<string, vector<Territory*>> territoryNeighbors;
	unordered_map<string, vector<Territory*>> continents;
	unordered_map<string, int> continentArmies;

public:
	
	Map() = default;
	Map(const Map& map);
	~Map();
	Player* winner;
	map<Territory*, vector<Territory*>> getTerritoryNeighbors( Player*);
	bool checkWinner(vector<Player*> p);
	bool validate(); //Validates the three map conditions.
	bool validateTerritoryConnectivity(); //Validates territory connectivity.
	bool validateNodeConnectivity(Territory& startingNode); //Validates node connectivity given starting node.
	bool validateContinentConnectivity(); //Validates continent connectivity.
	bool validateContinentExclusivity(); //Validates territory to continent connectivity.

	Territory getTerritory(string territoryName); //Get territory given territory name.

	vector<Territory*> getTerritories(); //Get list of all territories.
	vector<Territory*> getTerritoryNeighbors(Territory* territory); //Get neighbors of a given territory.
	vector<Territory*> getTerritoryNeighbors(string territoryName); //Get neighbors of a given territory name.
	
	void addTerritory(Territory* territory, vector<Territory*> neighborList); //Add territory and its list of neighbors.
	void addTerritory(string continent, int bonusArmyCount, Territory* territory, vector<Territory*> neighborList); //Add territory and its list of neighbors, whilst also assigning it a continent.

	unordered_map<string, vector<Territory>> getTerritoryNeighborMap(); //Get territory name to neighbor vector map.
	void setTerritoryNeighborsMap(unordered_map<string, vector<Territory>> map); //Set territory name to neighbor vector map.

	vector<string> getContinents(); //Get list of territory names.

	
	unordered_map<string, vector<Territory*>> getContinentMap(); //Get continent map.
	void registerWithContinent(string continent, int bonusArmyCount, Territory* territory); //Register a territory with a continent.

	static void assignTerritory(Player* player, Territory* territory); //Makes a 2-way link between a Player/Territory pair.
	
	static Map* getTestMap(); //Creates a test map for testing purposes.

	bool contains(vector<Territory*> list, Territory* territory); //Check if list contains a territory.
	bool hasDuplicates(vector<Territory*> list); //Check if list has any duplicate territories.
	bool checkContinentOwnership(Player* p, vector<Territory*> cont);
	Map& operator=(const Map& m); //assignment operator.
	friend ostream& operator <<(ostream& out, Map& m);//stream insertion operator.
};
