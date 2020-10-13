//============================================================================
// Name        : MapLoaderDriver.cpp
// Author      : Marjolaine Roy (40098364)
// Description : Map Loader Driver c++ class.
//============================================================================
/*
#include <iostream>
#include <string>
#include "Map.h"
#include "MapLoader.h"
#include "Territory.h"

using namespace std;

bool main() {

	Map map = Map();
	MapLoader mapLoader = MapLoader();

	string path = {};

	cout << "Enter a file" << endl;
	cin >> path;

	//Add continents
	vector<Territory> continentList = mapLoader.GetContinentList();
	continentList = mapLoader.ReadMapFile(path, continentList);

	//Add countries
	vector<Territory> countryList = mapLoader.GetCountryList();
	countryList = mapLoader.ReadMapFileForCountries(path, countryList);

	//Add borders
	vector<vector<Territory>> bordersList = mapLoader.GetBordersList();
	bordersList = mapLoader.ReadMapFileForBorders(path, bordersList, countryList);

	//Create the map
	map = mapLoader.CombineInfos(continentList, countryList, bordersList);
	
	return 0;
}*/