//============================================================================
// Name        : MapLoader.cpp
// Author      : Marjolaine Roy (40098364)
// Description : Map Loader c++ class.
//============================================================================

#include "MapLoader.h";
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void MapLoader::ShowBorders(vector<vector<Territory*>> _bordersList) {

	Territory* singularBorder;
	vector<Territory*> currentBorders;
	vector<vector<Territory*>> bL = _bordersList;

	for (int i = 0; i < bL.size(); i++) {
		currentBorders = bL.at(i);

		for (int j = 0; j < bL.at(i).size(); j++)
		{
			singularBorder = currentBorders.at(j);
			std::cout << singularBorder->getName() << " - " ;
		}
		std::cout << endl;
	}
}

void MapLoader::ShowContinents(vector<Territory*> _continentList) {

	Territory* currentContinent;
	vector<Territory*> cL = _continentList;

	for (int i = 0; i < cL.size(); i++) {
		currentContinent = cL.at(i);
		std::cout << currentContinent->getName() << "\n";
	}
}

vector<Territory*> MapLoader::GetContinentList()
{
	return continentList;
}

vector<Territory*> MapLoader::GetCountryList()
{
	return countryList;
}

vector<vector<Territory*>> MapLoader::GetBordersList()
{
	return bordersList;
}

vector<int> MapLoader::GetContinentNb()
{
	return continentNb;
}

vector<int> MapLoader::GetArmiesNb()
{
	return armiesNb;
}


Map* MapLoader::CombineInfos(vector<Territory*> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList)
{
	Map* map = new Map();
	int currContinentNb;

	for (int i = 0; i < _countryList.size(); i++)
	{
		map->addTerritory(_countryList[i], _bordersList[i]);
		currContinentNb = continentNb[i] - 1;
		map->registerWithContinent(_continentList[currContinentNb]->getName(), _countryList[i]->getArmyCount(), _countryList[i]); //This can be changed to something else.
	}

	cout << "!" << endl;
	return map;
}


void MapLoader::ShowTerritories(vector<Territory*> _countryList) {

	vector<Territory*> ts;
	Territory* current;
	ts = _countryList;

	for (int i = 0; i < ts.size(); i++) {
		current = ts.at(i);
		cout << current->getName() << "\n";
	}
}

bool MapLoader::CheckValidity(string _inputFileStream) {
	cout << "\nCHECKING VALIDITY" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	bool hasCountries = false;
	bool hasContinents = false;
	bool hasBorders = false;
	bool hasFiles = false;
	bool isValid;

	while (getline(inputFileStream, line)) {
		if (line == "[files]") {
			hasFiles = true;
		}
		if (line == "[continents]") {
			hasContinents = true;
		}
		if (line == "[countries]") {
			hasCountries = true;
		}
		if (line == "[borders]") {
			hasBorders = true;
		}

	
	}

	inputFileStream.close();
	inputFileStream.clear();

	if (hasContinents && hasBorders && hasCountries && hasFiles)
		isValid = true;
	else
		isValid = false;


	return isValid;
}

vector<Territory*> MapLoader::ReadMapFile(string _inputFileStream, vector<Territory*> _continentList) {
	cout << "\nREGISTERING CONTINENTS" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int index, continentNb, armies;
	string territoryName, continentName, color;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[continents]") {
		};

			//first line
			inputFileStream >> continentName >> armies >> color;
			Territory* continent = new Territory(continentName);
			armiesNb.push_back(armies);
			_continentList.push_back(continent);

			while (getline(inputFileStream, line) && line != "[continents]") {
				inputFileStream >> continentName >> armies >> color;
				
				if (continentName == "[countries]")
				{
					break;
				};
				Territory* continent = new Territory(continentName);
				armiesNb.push_back(armies);
				_continentList.push_back(continent);
 			}

		inputFileStream.close();
		inputFileStream.clear();

		std::cout << "Continents list size: " << _continentList.size() << endl;
		return _continentList;
	}
	else {
		cout << "File is not open " << "\n";
		exit(0);
	}
}

vector<Territory*> MapLoader::ReadMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList) {

	cout << "\nREGISTERING COUNTRIES" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int index, continent, x, y;
	string territoryName;


	if (inputFileStream.is_open()) {

		while (getline(inputFileStream, line) && line != "[countries]") {};

			//first line
			inputFileStream >> index >> territoryName >> continent >> x >> y;
			Territory* country = new Territory(territoryName);
			continentNb.push_back(continent);
			_countryList.push_back(country);

			while (getline(inputFileStream, line) && line != "[countries]" ) {

				inputFileStream >> index >> territoryName >> continent >> x >> y;
				if (territoryName == "[borders]" || territoryName == _countryList.at(_countryList.size() - 1)->getName())
				{
					break;
				}

				Territory* country = new Territory(territoryName);
				continentNb.push_back(continent);
				_countryList.push_back(country);
			}

		inputFileStream.close();
		inputFileStream.clear();
		std::cout << "Country list size: " << _countryList.size() << endl;
		return _countryList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}


vector<vector<Territory*>> MapLoader::ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList) {

	cout << "\nREGISTERING BORDERS" << endl;

	string line;
	ifstream inputFileStream(_inputFileStream);

	int territoryNb;
	vector<Territory*> nList;
	int i_subs;
	std::string::size_type sz;
	string subs;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[borders]") {}

		//first number
		inputFileStream >> line;
		i_subs = stoi(line, &sz);
		Territory* current = _countryList[i_subs - 1];
		nList.push_back(current);


			while (getline(inputFileStream, line) && line.find("[borders]") == std::string::npos) {
				nList = {};
				istringstream iss(line);

				do {
					iss >> subs;
					i_subs = stoi(subs, &sz);
					Territory* current = _countryList[i_subs-1];
					nList.push_back(current);

				} while (iss);


				if (nList.at(nList.size() - 1)->getName() == nList.at(nList.size() - 2)->getName())
				{
					nList.pop_back();
				}

				_bordersList.push_back(nList);
			}

		inputFileStream.close();
		inputFileStream.clear();

		std::cout << "Borders list size: " << _bordersList.size() << endl;
		return _bordersList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}

