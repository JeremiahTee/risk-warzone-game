#include "GameEngine.h"

#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

#include <process.h>
#include <iostream>
#include <filesystem>
#include <vector>

#include <algorithm>
#include <random>
#include <exception>

namespace fs = std::filesystem;
using namespace std;

GameEngine::GameEngine() {
	validExecution = true;
}

GameEngine::~GameEngine() {
	delete map;
	for (auto player : players) {
		delete player;
	}
}

void GameEngine::gameStartPhase() {
	cout << "Initializing game engine..." << endl;

	string fileName = queryDirectory("maps");
	cout << "Loading " + fileName + " from file..." << endl;
	createMap("maps\\"+fileName);

	cout << "Checking map validity..." << endl;
	if (map->validate()) {
		cout << "Map is valid!" << endl;
	}
	else {
		cout << "Map is invalid, terminating..." << endl;
		validExecution = false;
	}

	if (validExecution) {
		cout << "Creating players...";
		int playerCount = queryPlayerCount();
		cout << "Creating players..." << endl;
		players = createPlayers(playerCount);

		deck = new Deck(10, 10, 10, 10, 10, 10);

		//Enable/Disable Observers HERE, ask JT when it is go time.
	}
	cout << "\n";
}

void GameEngine::startupPhase() {
	if (!validExecution) {
		cout << "Execution invalid, cancelling startup phase..." << endl;
	}
	else {

		cout << "Running startup phase..." << endl;

		//Shuffle elements in players.
		cout << "Shuffling player list..." << endl;
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(players), std::end(players), rng);

		//Assign all territories to players.
		cout << "Assigning territories to players..." << endl;
		vector<Territory*> toAssign = map->getTerritories();
		assignTerritoriesToPlayers(players, toAssign);

		//Assign initial army counts.
		cout << "Assigning initial armies..." << endl;
		assignInitialArmies(players);
	}
}

string GameEngine::queryDirectory(string directory) {
	vector<string> namelist;
	cout << "Files names:" << endl;
	try
	{
		for (const auto& entry : fs::directory_iterator(directory)) {
			cout << entry.path().filename() << endl;
		}
	}
	catch (exception& e)
	{
		cout << "Unable to display file contents..." << endl;
	}

	cout << "\n";

	cout << "Enter the file path of a map file: ";

	string path = "";
	cin >> path;

	cout << "\n";

	return path;
}

void GameEngine::createMap(string path) {
	MapLoader mapLoader = MapLoader();
	
	//Add continents
	vector<string> continentList = mapLoader.GetContinentList();
	continentList = mapLoader.ReadMapFile(path, continentList);

	//Add territories
	vector<Territory*> countryList = mapLoader.GetCountryList();
	countryList = mapLoader.ReadMapFileForCountries(path, countryList);

	//Add borders
	vector<vector<Territory*>> bordersList = mapLoader.GetBordersList();
	bordersList = mapLoader.ReadMapFileForBorders(path, bordersList, countryList);

	//Create the map

	map = mapLoader.CombineInfos(continentList, countryList, bordersList);
}

int GameEngine::queryPlayerCount() {
	cout << "Enter the number of players(2-5): ";

	int count;
	cin >> count;
	cout << "\n";

	if (count < 2) {
		cout << "Input too small, rounding player count up to 2." << endl;
		count = 2;
	}
	else if(count > 5){
		cout << "Input too large, rounding player count down to 5." << endl;
		count = 5;
	}

	return count;
}

vector<Player*> GameEngine::createPlayers(int playerCount) {
	vector<Player*> players;
	for (int i = 0; i < playerCount; i++) {
		vector<Territory*> list;
		players.push_back(new Player(list, new Hand(0, 0, 0, 0, 0, 0), i));
	}
	return players;
}

void GameEngine::assignTerritoriesToPlayers(vector<Player*> playerList, vector<Territory*> territoryList) {
	int playerIndex = 0;
	int territoryIndex = 0;

	if (playerList.size() > 0) {
		while (territoryIndex < territoryList.size()) {
			Map::assignTerritory(playerList.at(playerIndex), territoryList.at(territoryIndex));

			cout << "Territory (";
			cout << territoryIndex;
			cout << ") being assigned to Player (";
			cout << playerIndex;
			cout << ")." << endl;

			territoryIndex++;
			playerIndex++;

			if (playerIndex >= playerList.size()) {
				playerIndex = 0;
			}
		}
	}
	cout << "\n";
}

void GameEngine::assignInitialArmies(vector<Player*> playerList) {
	int armyCount = 0;
	
	if (playerList.size() <= 2) {
		armyCount = 40;
	}
	else if (playerList.size() == 3) {
		armyCount = 35;
	}
	else if (playerList.size() == 4) {
		armyCount = 30;
	}
	else if (playerList.size() >= 5) {
		armyCount = 25;
	}

	cout << armyCount;
	cout << " armies are being assigned to each player..." << endl;

	for (auto player : playerList) {
		Hand* playerHand = player->getHand();
		playerHand->setReinforcement(armyCount);
	}
}
