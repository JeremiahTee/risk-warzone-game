//============================================================================
// Name        : ConquestMapDriver.cpp
// Author      : Marjolaine, David, Jeremiah 
// Description : Adapter Driver c++ class.
//============================================================================

#include "Map.h"
#include "MapLoader.h";
#include <iostream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

bool main() {

	Map map = Map();
	ConquestFileReader* reader = new ConquestFileReader();
	ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*reader);

	string path = {};

	cout << "Enter a file" << endl;
	cin >> path;

	//Check validity
	adapter->CheckValidity(path);

	//Add continents
	vector<string> continentList = {};
	continentList = adapter->ReadMapFile(path, continentList);

	cout << "Printing out continents: \n" << endl;

	for(auto continent: continentList)
	{
		cout << continent << endl;
	}
	
	//Add countries
	vector<Territory*> countryList = {};
	countryList = adapter->ReadMapFileForCountries(path, countryList);

	cout << "Printing out territories: \n" << endl;
	
	for(int i = 0; i < countryList.size(); i++)
	{
		cout << countryList[i]->getName() <<  endl;
	}
	
	//Add borders
	vector<vector<Territory*>> bordersList = {};
	bordersList = adapter->ReadMapFileForBorders(path, bordersList, countryList);

	for (int i = 0; i < bordersList.size(); i++)
	{
		cout << "\nCountry at [" << i << "] has " << bordersList[i].size() << " neighbor(s)." << endl;
	}
	
	//Create the map
	if (!continentList.empty() && !countryList.empty() && !bordersList.empty()) {
		map = *adapter->CombineInfos(continentList, countryList, bordersList);
	}

	cout << "Map territories: \n" << endl;

	for(auto terr: map.getTerritories())
	{
		cout << *terr << endl;
	}

	cout << "Map continents: \n" << endl;

	for (auto cont : map.getContinents())
	{
		cout << cont << endl;
	}

	delete adapter;
	delete reader;

	return 0;
}