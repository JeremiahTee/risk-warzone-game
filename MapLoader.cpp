//============================================================================
// Name        : MapLoader.cpp
// Author      : Marjolaine, David, Jeremiah
// Description : Map Loader c++ class.
//============================================================================

#include "Map.h"
#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace helperMethods
{
	vector<string> splitByDelimiter(const string& input, char delimiter) {
		stringstream stream(input);
		string elements;
		vector<string> elements_list;
		while (getline(stream, elements, delimiter)) {
			elements_list.push_back(elements);
		}
		return elements_list;
	}
}

using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::string;
using std::ifstream;
using std::stringstream;
using std::stoi; //conversion string to integer
using std::distance;
using helperMethods::splitByDelimiter;

void MapLoader::ShowBorders(vector<vector<Territory*>> _bordersList) {
	Territory* singularBorder;
	vector<Territory*> currentBorders;
	vector<vector<Territory*>> bL = _bordersList;

	for (int i = 0; i < bL.size(); i++) {
		currentBorders = bL.at(i);

		for (int j = 0; j < bL.at(i).size(); j++)
		{
			singularBorder = currentBorders.at(j);
			cout << singularBorder->getName() << " - ";
		}
		cout << endl;
	}
}

void MapLoader::ShowContinents(vector<string> _continentList) {

	string currentContinent;
	vector<string> cL = _continentList;

	for (int i = 0; i < cL.size(); i++) {
		currentContinent = cL.at(i);
		cout << currentContinent << "\n";
	}
}

vector<string> MapLoader::GetContinentList()
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

vector<int> MapLoader::SetArmiesNb(vector<int> *bonusControlList)
{
	armiesNb = *bonusControlList;
	return armiesNb;
}

vector<int> MapLoader::GetArmiesNb()
{
	return armiesNb;
}

Map* MapLoader::CombineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList)
{
	Map* map = new Map();
	int currContinentNb;

	for (int i = 0; i < _countryList.size(); i++)
	{
		map->addTerritory(_countryList[i], _bordersList[i]);
		currContinentNb = continentNb[i] - 1;
		map->registerWithContinent(_continentList[currContinentNb], armiesNb[currContinentNb], _countryList[i]);
	}
	cout << "\n";
	cout << "\n";
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

vector<string> MapLoader::ReadMapFile(string _inputFileStream, vector<string> _continentList) {
	cout << "\nREGISTERING CONTINENTS" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int armies;
	string territoryName, continentName, color;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[continents]") {
		};

		//first line
		inputFileStream >> continentName >> armies >> color;
		string continent = string(continentName);
		armiesNb.push_back(armies);
		_continentList.push_back(continent);

		while (getline(inputFileStream, line) && line != "[continents]") {
			inputFileStream >> continentName >> armies >> color;

			if (continentName == "[countries]")
			{
				break;
			}
			string continent = string(continentName);
			armiesNb.push_back(armies);
			_continentList.push_back(continent);
		}

		inputFileStream.close();
		inputFileStream.clear();

		return _continentList;
	}

	cout << "File is not open " << "\n";
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

		while (getline(inputFileStream, line) && line != "[countries]") {

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
		cout << "Country list size: " << _countryList.size() << endl;
		return _countryList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}

vector<vector<Territory*>> MapLoader::ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList) {
	cout << "\nREGISTERING BORDERS" << endl;

	string line;
	ifstream inputFileStream(_inputFileStream);

	vector<Territory*> nList;
	int i_subs;
	string::size_type sz;
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
				Territory* current = _countryList[i_subs - 1];
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

		cout << "Borders list size: " << _bordersList.size() << endl;
		return _bordersList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}

//Adapter code
ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader fileReader)
{
	file_reader_ = fileReader;
}

bool ConquestFileReaderAdapter::CheckValidity(string _inputFileStream)
{
	return file_reader_.CheckValidityConquest(_inputFileStream);
}

vector<string> ConquestFileReaderAdapter::ReadMapFile(string _inputFileStream, vector<string> _continentList)
{
	return file_reader_.ReadMapFileConquest(_inputFileStream, _continentList);
}

vector<vector<Territory*>> ConquestFileReaderAdapter::ReadMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList)
{
	return file_reader_.ReadMapFileForBordersConquest(_inputFileStream, _bordersList, _countryList);
}

vector<Territory*> ConquestFileReaderAdapter::ReadMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList)
{
	return file_reader_.ReadMapFileForCountriesConquest(_inputFileStream, _countryList);
}

Map* ConquestFileReaderAdapter::CombineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList)
{
	return file_reader_.CombineInfosConquest(_continentList, _countryList, _bordersList);
}

//Conquest File Read methods
bool ConquestFileReader::CheckValidityConquest(string _inputFileStream)
{
	cout << "Checking VALIDITY of CONQUEST map...\n" << endl;

	string line;
	ifstream ifs(_inputFileStream);

	bool hasCountries = false;
	bool hasContinents = false;
	bool isValid;

	while (getline(ifs, line)) {
		if (line == "[Continents]") {
			hasContinents = true;
		}
		if (line == "[Territories]") {
			hasCountries = true;
		}
	}

	ifs.close();
	ifs.clear();

	if (hasContinents && hasCountries)
	{
		isValid = true;
		cout << "Valid map file :)" << endl;
	}else
	{
		cout << "Invalid map file. Make sure the [Continents] and [Territories] lines are present." << endl;
		isValid = false;
	}

	return isValid;
}

vector<string> ConquestFileReader::ReadMapFileConquest(string _inputFileStream, vector<string> _continentList)
{
	ifstream ifs(_inputFileStream);
	string currentLine;
	while (getline(ifs, currentLine) && currentLine != "[Continents]")
	{
		//While current line isn't equal to [Continents] skip 
	}
	//Read until empty line
	while (getline(ifs, currentLine) && !currentLine.empty())
	{
		const int equals_index = currentLine.find('=');
		auto continent = currentLine.substr(0, equals_index);
		auto control_bonus = stoi(currentLine.substr(equals_index + 1));
		_continentList.push_back(continent);
		bonusWithContinent.insert({ continent, control_bonus });
	}
	return _continentList;
}

vector<Territory*> ConquestFileReader::ReadMapFileForCountriesConquest(string _inputFileStream, vector<Territory*> _countryList)
{
	ifstream ifs(_inputFileStream);
	string currentLine;
	while (getline(ifs, currentLine) && currentLine != "[Territories]")
	{
		//Read until you reach [Territories]
	}
	//Read until empty line
	while (getline(ifs, currentLine) && !currentLine.empty())
	{
		const int comma_index = currentLine.find(',');
		auto territoryName = currentLine.substr(0, comma_index);
		Territory* country = new Territory(territoryName);
		_countryList.push_back(country);
	}
	
	return _countryList;
}

vector<vector<Territory*>> ConquestFileReader::ReadMapFileForBordersConquest(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList)
{
	ifstream ifs(_inputFileStream);
	string currentLine;
	vector<Territory*> neighbors;
	
	while (getline(ifs, currentLine) && currentLine != "[Territories]")
	{
		//Read until you reach [Territories]
	}
	//Read until empty line
	while (getline(ifs, currentLine) && !currentLine.empty())
	{
		neighbors.clear();
		const int first_comma_index = currentLine.find(',');
		auto territoryName = currentLine.substr(0, first_comma_index);
		const int second_comma_index = currentLine.find(',', first_comma_index + 1);
		const int third_comma_index = currentLine.find(',', second_comma_index + 1);
		const int fourth_comma_index = currentLine.find(',', third_comma_index + 1);
		//Get the continent name in between the 3rd comma and 4rth comma
		auto continentName = currentLine.substr(third_comma_index + 1, fourth_comma_index - third_comma_index - 1); 
		auto neighborsLine = currentLine.substr(fourth_comma_index + 1);
		
		Territory* country = new Territory(territoryName);

		territoryWithContinent.insert({country, continentName});
		
		//Split neighborsLine by the delimiter ","
		vector<string> neighborsName = splitByDelimiter(neighborsLine, ',');

		for(string territory_name: neighborsName)
		{
			neighbors.push_back(new Territory(territory_name));
		}

		_bordersList.push_back(neighbors);
	}

	return _bordersList;
}

Map* ConquestFileReader::CombineInfosConquest(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList)
{
	Map* map = new Map();
	
	for (int i = 0; i < _countryList.size(); i++)
	{
		string currentContinent;

		//Find corresponding territory to the continent
		for (auto& [key, value] : territoryWithContinent) {
			if (key->getName() == _countryList[i]->getName())
			{
				currentContinent = value;
			}
		}
		map->addTerritory(currentContinent, bonusWithContinent[currentContinent], _countryList[i], _bordersList[i]);
	}
	
	cout << "SUCCESS! Combined info from Conquest Map." << endl;
	cout << "\n";
	return map;
}