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

using namespace std;

bool main() {

	ConquestFileReader* reader = new ConquestFileReader();
	ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*reader);

	adapter->CheckValidity("test");
	
	string path = {};

	cout << "Enter a file" << endl;
	cin >> path;

	//Check validity
	bool isValid = adapter->CheckValidity(path);

	if (isValid) {
		std::cout << "Map file is valid." << endl;

		//Add continents
		vector<string> continentList = {};
		continentList = adapter->ReadMapFile(path, continentList);

		//Add countries
		vector<Territory*> countryList = {};
		countryList = adapter->ReadMapFileForCountries(path, countryList);

		//Add borders
		vector<vector<Territory*>> bordersList = {};
		bordersList = adapter->ReadMapFileForBorders(path, bordersList, countryList);

		//Create the map
		if (!continentList.empty() && !countryList.empty() && !bordersList.empty()) {
		//	map = mapLoader.CombineInfos(continentList, countryList, bordersList);
		}
	}
	else {
		cout << "\nMap file is invalid. Cannot create map." << endl;
	}


	delete adapter;
	delete reader;
	
	return 0;
}