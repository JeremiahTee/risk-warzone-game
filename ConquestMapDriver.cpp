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

	cout << "Printing out continentList" << endl;

	for(auto continent: continentList)
	{
		cout << continent << endl;
	}
	
	//Add countries
	vector<Territory*> countryList = {};
	countryList = adapter->ReadMapFileForCountries(path, countryList);

	for(int i = 0; i < countryList.size(); i++)
	{
		cout << countryList[i]->getName() <<  endl;
	}
	
	//Add borders
	vector<vector<Territory*>> bordersList = {};
	bordersList = adapter->ReadMapFileForBorders(path, bordersList, countryList);

	for (int i = 0; i < bordersList.size(); i++)
	{
		cout << "Country at [" << i << "] has " << bordersList[i].size() << " neighbors." << endl;
	}
	
	//Create the map
	if (!continentList.empty() && !countryList.empty() && !bordersList.empty()) {
		map = *adapter->CombineInfos(continentList, countryList, bordersList);
	}

	delete adapter;
	delete reader;

	return 0;
}