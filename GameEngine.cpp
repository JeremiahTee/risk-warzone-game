#include "GameEngine.h"

#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

#include <process.h>
#include <iostream>
#include <filesystem>
#include <vector>;

namespace fs = std::filesystem;
using namespace std;

void GameEngine::Start() {
	string fileName = queryDirectory("");
	Map* map = createMap(fileName);

	int playerCount = queryPlayerCount();
	vector<Player*> players = createPlayers(playerCount);

	//Enable/Disable Observers HERE, ask JT when it is go time.
}

string GameEngine::queryDirectory(string directory) {
	vector<string> namelist;
	cout << "Directories:" << endl;
	for (const auto& entry : fs::directory_iterator(directory)) {
		cout << entry.path() << endl;
	}

	cout << "\n";
	cout << "Enter the file name of the map file: ";

	string path = "";
	cin >> path;

	cout << "\n";

	return path;
}

Map* GameEngine::createMap(string path) {
	//Add continents
	MapLoader mapLoader = MapLoader();

	vector<Territory> continentList = mapLoader.GetContinentList();
	continentList = mapLoader.ReadMapFile(path, continentList);

	//Add territories
	vector<Territory> countryList = mapLoader.GetCountryList();
	countryList = mapLoader.ReadMapFileForCountries(path, countryList);

	//Add borders
	vector<vector<Territory>> bordersList = mapLoader.GetBordersList();
	bordersList = mapLoader.ReadMapFileForBorders(path, bordersList, countryList);

	//Create the map
	return &mapLoader.CombineInfos(continentList, countryList, bordersList);;
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