//============================================================================
// Name        : Map.h
// Author      : Maxime Johnson (40081684)
// Description : Map header class.
//============================================================================

#pragma once

class Territory; //forward declaration to avoid compilation errors

#include "Territory.h"
#include <vector>
#include <unordered_map>

using namespace std;

class Map
{
private:
	vector<Territory> territories;
	unordered_map<string, vector<Territory>> territoryNeighbors;
	unordered_map<string, vector<Territory>> continents;

public:
	Map() = default;
	Map(const Map& map);

	bool validate(); //Validates the three map conditions.
	bool validateTerritoryConnectivity(); //Validates territory connectivity.
	bool validateNodeConnectivity(Territory& startingNode); //Validates node connectivity given starting node.
	bool validateContinentConnectivity(); //Validates continent connectivity.
	bool validateContinentExclusivity(); //Validates territory to continent connectivity.

	Territory getTerritory(string territoryName); //Get territory given territory name.

	vector<Territory> getTerritories(); //Get list of all territories.
	vector<Territory> getTerritoryNeighbors(Territory& territory); //Get neighbors of a given territory.
	vector<Territory> getTerritoryNeighbors(string territoryName); //Get neighbors of a given territory name.

	void addTerritory(Territory& territory, vector<Territory> neighborList); //Add territory and its list of neighbors.
	void addTerritory(string continent, Territory& territory, vector<Territory> neighborList); //Add territory and its list of neighbors, whilst also assigning it a continent.

	unordered_map<string, vector<Territory>> getTerritoryNeighborMap(); //Get territory name to neighbor vector map.
	void setTerritoryNeighborsMap(unordered_map<string, vector<Territory>> map); //Set territory name to neighbor vector map.

	vector<string> getContinents(); //Get list of territory names.
	unordered_map<string, vector<Territory>> getContinentMap(); //Get continent map.
	void registerWithContinent(string continent, Territory& territory); //Register a territory with a continent.

	bool contains(vector<Territory> list, Territory& territory); //Check if list contains a territory.
	bool hasDuplicates(vector<Territory> list); //Check if list has any duplicate territories.

	Map& operator=(const Map& m); //assignment operator.
	friend ostream& operator <<(ostream& out, Map& m);//stream insertion operator.
};