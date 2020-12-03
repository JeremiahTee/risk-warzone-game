//============================================================================
// Name        : MapLoader.h
// Author      : Marjolaine, David, Jeremiah
// Description : Map Loader header class.
//============================================================================

#pragma once
#include <vector>
#include "Map.h"
#include <unordered_map>

using namespace std;

class MapLoader {
	private:
		vector<string> continentList; 
		vector<Territory*> countryList; 
		vector<vector<Territory*>> bordersList; //Vector of vector of territories to store borders lists
		vector<int> continentNb; //To store the index of each continent associated to each country
		vector<int> armiesNb; //To store the nb of armies for each continent

	public:
		MapLoader();
		MapLoader(MapLoader&);
		MapLoader& operator=(MapLoader& h);
	
		virtual bool CheckValidity(string _inputFileStream);
		virtual vector<string> ReadMapFile(string _inputFileStream, vector<string> _continentList); //reads file & return list of continents
		virtual vector<vector<Territory*>> ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList); //reads file & return list of borders for each country
		virtual vector<Territory*> ReadMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList); //reads file & return list of countries
		void ShowBorders(vector<vector<Territory*>> _bordersList); //shows all the borders stored in bordersList, used mainly to debug
		void ShowTerritories(vector<Territory*> _countryList); //shows all countries stored in countryList, used mainly to debug
		void ShowContinents(vector<string> _continentList); //shows all continents stored in continentList, used mainly to debug
		vector<string> GetContinentList(); 
		vector<Territory*> GetCountryList();
		vector<vector<Territory*>> GetBordersList();
		vector<int> GetContinentNb();
		vector<int> SetArmiesNb(vector<int> *bonusControlList);
		vector<int> GetArmiesNb();

		friend ostream& operator << (ostream& out, MapLoader& hps);
	
		virtual Map* CombineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList); //stores all information into map
};

class ConquestFileReader
{
private:
	vector<string> continentListConquest; //new continentList
	vector<Territory*> countryListConquest; //new countryList
	vector<vector<Territory*>> borderListConquest; //new borderListConquest
	unordered_map<Territory*, string> territoryWithContinent;
	unordered_map<string, int> bonusWithContinent;
	
public:
	bool CheckValidityConquest(string _inputFileStream);
	vector<string> ReadMapFileConquest(string _inputFileStream, vector<string> _continentList); //reads file & return list of continents from a ConquestMap
	vector<vector<Territory*>> ReadMapFileForBordersConquest(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList); //reads file & return list of borders for each country from a ConquestMap
	vector<Territory*> ReadMapFileForCountriesConquest(string _inputFileStream, vector<Territory*> _countryList); //reads file & return list of countries from a ConquestMap
	ConquestFileReader();
	ConquestFileReader(ConquestFileReader&);
	Map* CombineInfosConquest(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList); //stores all information into map
	ConquestFileReader& operator=(ConquestFileReader& h);
	friend ostream& operator << (ostream& out, ConquestFileReader& hps);
};

/*Adapter */
class ConquestFileReaderAdapter : MapLoader
{
private:
	ConquestFileReader file_reader_;
public:
	ConquestFileReaderAdapter(ConquestFileReader fileReader);
	bool CheckValidity(string _inputFileStream);
	vector<string> ReadMapFile(string _inputFileStream, vector<string> _continentList);
	vector<Territory*> ReadMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList);
	vector<vector<Territory*>> ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList);
	Map* CombineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList); //stores all information into map

	ConquestFileReaderAdapter(ConquestFileReaderAdapter&); //copy constructor
	ConquestFileReaderAdapter& operator=(ConquestFileReaderAdapter& cfr); //stream insertion operator
	friend ostream& operator<<(ostream& out, ConquestFileReaderAdapter& cfr); //stream insertion operator
};