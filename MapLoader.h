//============================================================================
// Name        : MapLoader.h
// Author      : Marjolaine Roy (40098364)
// Description : Map Loader header class.
//============================================================================

#pragma once
#include <vector>
#include "Map.h"

using namespace std;

class MapLoader {

private:
	Map map = Map(); 
	vector<Territory> continentList; 
	vector<Territory> countryList; 
	vector<vector<Territory>> bordersList; // vector of vector of territories to store borders lists
	vector<int> continentNb; //stores the index of each continent associated to each country
	vector<int> armiesNb; //stores the nb of armies for each country

public:
	vector<Territory> ReadMapFile(string _inputFileStream, vector<Territory>& _continentList); // reads file & returns list of continents
	vector<vector<Territory>> ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory>>& _bordersList, vector<Territory>& _countryList); //reads file & returns list of borders for each country
	vector<Territory> ReadMapFileForCountries(string _inputFileStream, vector<Territory>& _countryList); //reads file & returns list of territories

	void ShowBorders(vector<vector<Territory>> _bordersList); // shows all the borders stored in bordersList, used mainly to debug
	void ShowTerritories(vector<Territory> _countryList); // shows all territories stored in countryList, used mainly to debug
	void ShowContinents(vector<Territory> _continentList); // shows all continents stored in continentList, used mainly to debug
	vector<Territory> GetContinentList();
	vector<Territory> GetCountryList();
	vector<vector<Territory>> GetBordersList();
	vector<int> GetContinentNb();
	vector<int> GetArmiesNb();
	
	Map CombineInfos(vector<Territory>& _continentList, vector<Territory>& _countryList, vector<vector<Territory>>& _bordersList); //stores all information into map
};