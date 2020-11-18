//============================================================================
// Name        : MapLoader.h
// Author      : Marjolaine Roy (40098364)
// Description : Map Loader header class.
//============================================================================

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;

class MapLoader {

	private:
		vector<Territory*> continentList; 
		vector<Territory*> countryList; 
		vector<vector<Territory*>> bordersList; //Vector of vector of terriroties to store borders lists
		vector<int> continentNb; //To store the index of each continent associated to each country
		vector<int> armiesNb; //To store the nb of armies for each country

		bool foundCountries;

	public:
		bool CheckValidity(string _inputFileStream);
		vector<Territory*> ReadMapFile(string _inputFileStream, vector<Territory*> _continentList); //reads file & return list of continents
		vector<vector<Territory*>> ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList); //reads file & return list of borders for each country
		vector<Territory*> ReadMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList); //reads file & return list of countries

		void ShowBorders(vector<vector<Territory*>> _bordersList); //shows all the borders stored in bordersList, used mainly to debug
		void ShowTerritories(vector<Territory*> _countryList); //shows all countries stored in countryList, used mainly to debug
		void ShowContinents(vector<Territory*> _continentList); //shows all continents stored in continentList, used mainly to debug
		vector<Territory*> GetContinentList();
		vector<Territory*> GetCountryList();
		vector<vector<Territory*>> GetBordersList();
		vector<int> GetContinentNb();
		vector<int> GetArmiesNb();

		Map CombineInfos(vector<Territory*> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList); //stores all information into map
};