////============================================================================
//// Name        : MapLoaderDriver.cpp
//// Author      : Marjolaine Roy
//// Description : Map Loader Driver c++ class.
////============================================================================
//
//
//#include "MapLoader.h";
//#include <iostream>
//#include <iostream>
//#include <string>
//#include "Map.h"
//
//using namespace std;
//
//bool main() {
//
//	Map map = Map();
//	MapLoader mapLoader = MapLoader();
//	string path = {};
//
//	cout << "Enter a file" << endl;
//	cin >> path;
//
//	//Check validity
//	bool isValid = mapLoader.CheckValidity(path);
//
//	if (isValid) {
//		std::cout << "Map file is valid." << endl;
//
//		//Add continents
//		vector<string> continentList = {};
//		continentList = mapLoader.ReadMapFile(path, continentList);
//
//		//Add countries
//		vector<Territory*> countryList = {};
//		countryList = mapLoader.ReadMapFileForCountries(path, countryList);
//
//		//Add borders
//		vector<vector<Territory*>> bordersList = {};
//		bordersList = mapLoader.ReadMapFileForBorders(path, bordersList, countryList);
//
//		////Create the map
//		//if (!continentList.empty() && !countryList.empty() && !bordersList.empty() ) {
//		//	map = mapLoader.CombineInfosConquest(continentList, countryList, bordersList);
//		//}
//	}
//	else {
//		cout << "\nMap file is invalid. Cannot create map." << endl;
//	}
//
//	return 0;
//}