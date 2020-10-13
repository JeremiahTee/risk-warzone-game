//============================================================================
// Name        : MapLoader.cpp
// Author      : Marjolaine Roy (40098364)
// Description : Map Loader c++ class.
//============================================================================

#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void MapLoader::ShowBorders(vector<vector<Territory>> _bordersList) {

	Territory singularBorder;
	vector<Territory> currentBorders;
	vector<vector<Territory>> bL = _bordersList;

	for (int i = 0; i < bL.size(); i++) {
		currentBorders = bL.at(i);

		for (int j = 0; j < bL.at(i).size(); j++)
		{
			singularBorder = currentBorders.at(j);
			cout << singularBorder.getName() << " - ";
		}
		cout << endl;
	}
}

void MapLoader::ShowContinents(vector<Territory> _continentList) {

	Territory currentContinent;
	vector<Territory> cL = _continentList;

	for (int i = 0; i < cL.size(); i++) {
		currentContinent = cL.at(i);
		cout << currentContinent.getName() << "\n";
	}
}

vector<Territory> MapLoader::GetContinentList()
{
	return continentList;
}

vector<Territory> MapLoader::GetCountryList()
{
	return countryList;
}

vector<vector<Territory>> MapLoader::GetBordersList()
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


Map MapLoader::CombineInfos(vector<Territory>& _continentList, vector<Territory>& _countryList, vector<vector<Territory>>& _bordersList)
{

	Territory currentT;
	vector<Territory> currentBorders;
	int currContinentNb;

	for (int i = 0; i < _countryList.size(); i++)
	{
		map.addTerritory(_countryList[i], _bordersList[i]);
		currContinentNb = continentNb[i] - 1;
		Territory continentName = _continentList[currContinentNb];
		map.registerWithContinent(_continentList[currContinentNb].getName(), _countryList[i]);
	}

	bool validate = false;
	validate = map.validate();
	if (map.validate() == true)
		cout << "Map is valid " << endl;
	else {

		cout << "Map is not valid" << endl;
	}

	return map;
}


void MapLoader::ShowTerritories(vector<Territory> _countryList) {

	vector<Territory> ts;
	Territory current;
	ts = _countryList;

	for (int i = 0; i < ts.size(); i++) {
		current = ts.at(i);
		cout << current.getName() << "\n";
	}
}


vector<Territory> MapLoader::ReadMapFile(string _inputFileStream, vector<Territory>& _continentList) {
	cout << "REGISTERING CONTINENTS" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int index, continentNb, armies;
	string territoryName, continentName, color;

	if (inputFileStream.is_open()) {

		while (getline(inputFileStream, line) && line.find("[continents]") == std::string::npos) {};

		//first line
		inputFileStream >> continentName >> armies >> color;
		Territory continent = Territory(continentName);
		armiesNb.push_back(armies);
		_continentList.push_back(continent);

		while (getline(inputFileStream, line) && line.find("[countries]") == std::string::npos) {

			inputFileStream >> continentName >> armies >> color;
			if (continentName == "[countries]")
			{
				break;
			};
			Territory continent = Territory(continentName);
			armiesNb.push_back(armies);
			_continentList.push_back(continent);
		}


		inputFileStream.close();

		return _continentList;
	}
	else {
		cout << "File is not open " << "\n";
	}


}

vector<Territory> MapLoader::ReadMapFileForCountries(string _inputFileStream, vector<Territory>& _countryList) {

	cout << "REGISTERING COUNTRIES" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int index, continent, x, y;
	string territoryName;


	if (inputFileStream.is_open()) {

		while (getline(inputFileStream, line) && line.find("[countries]") == std::string::npos) {};

		//first line
		inputFileStream >> index >> territoryName >> continent >> x >> y;
		Territory country = Territory(territoryName, nullptr, armiesNb[continent - 1]);
		continentNb.push_back(continent);
		_countryList.push_back(country);

		while (getline(inputFileStream, line) && line.find("[countries]") == std::string::npos) {

			inputFileStream >> index >> territoryName >> continent >> x >> y;
			if (territoryName == "[borders]" || territoryName == _countryList.at(_countryList.size() - 1).getName())
			{
				break;
			};

			Territory country = Territory(territoryName, nullptr, armiesNb[continent - 1]);
			continentNb.push_back(continent);
			_countryList.push_back(country);
		}

		inputFileStream.close();

		return _countryList;
	}
	else {
		cout << "File is not open " << "\n";
	}
}


vector<vector<Territory>> MapLoader::ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory>>& _bordersList, vector<Territory>& _countryList) {

	cout << "REGISTERING BORDERS" << endl;

	string line;
	ifstream inputFileStream(_inputFileStream);

	int territoryNb;
	vector<Territory> nList;
	int i_subs;
	std::string::size_type sz;
	string subs;

	if (inputFileStream.is_open()) {

		while (getline(inputFileStream, line) && line.find("[borders]") == std::string::npos) {}

		//first line
		/*istringstream iss(line);
		do {
			string subs;
			iss >> subs;
			cout << "Substrings:" << subs << endl;


		} while (iss);*/

		inputFileStream >> line;

		while (getline(inputFileStream, line) && line.find("[borders]") == std::string::npos) {
			nList = {};
			istringstream iss(line);

			do {
				iss >> subs;
				i_subs = stoi(subs, &sz);
				Territory current = _countryList[i_subs - 1];
				nList.push_back(current);

			} while (iss);


			if (nList.at(nList.size() - 1).getName() == nList.at(nList.size() - 2).getName())
			{
				nList.pop_back();
			};

			_bordersList.push_back(nList);
		}

		inputFileStream.close();

		return _bordersList;
		cout << "END BORDERS" << "\n";
	}
	else {
		cout << "File is not open " << "\n";
	}
}