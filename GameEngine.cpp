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
}

GameEngine::~GameEngine() {
	delete map;
}

void GameEngine::attachObservers(vector<Player*> players)
{
	for (auto player : players)
	{
		attach(player);
	}

	setTerritoriesCount(map->getTerritories().size());
	setIsPlayerBeingRemoved(false);
}

void GameEngine::gameStartPhase() {
	std::cout << "Initializing game engine..." << endl;
	bool mapType = queryMapType();
	string fileName = "";
	
	if (mapType) {
		fileName = queryDirectory("maps");

	}
	else{
		fileName = queryDirectory("conquest");
	}

	std::cout << "Loading " + fileName + " from file..." << endl;
	if(mapType)
	{
		createMap("maps\\" + fileName, mapType);
	}else
	{
		createMap("conquest\\" + fileName, mapType);
	}

	std::cout << "Checking map validity..." << endl;
	if (map->validate()) {
		std::cout << "Map is valid!" << endl;
	}
	else {
		std::cout << "Map is invalid, terminating program..." << endl;
		exit(0);
	}

	std::cout << "Creating players...";
	int playerCount = queryPlayerCount();
	std::cout << "Creating players..." << endl;
	createPlayers(playerCount);

	deck = new Deck(10, 10, 10, 10, 10, 10);

	attachObservers(players);
	std::cout << "\n";
}

void GameEngine::startupPhase() {

	std::cout << "Running startup phase..." << endl;

	//Shuffle elements in players.
	std::cout << "Shuffling player list..." << endl;
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(players), std::end(players), rng);

	//Assign all territories to players.
	std::cout << "Assigning territories to players..." << endl;
	assignTerritoriesToPlayers(players, map->getTerritories());

	//Assign initial army counts.
	std::cout << "Assigning initial armies..." << endl;
	assignInitialArmies(players);
}

bool GameEngine::queryMapType() {
	std::cout << "Would you like to use conquest or normal maps (input conquest or normal): " << endl;

	string type = "";
	cin >> type;

	if (type != "conquest" && type != "normal") {
		std::cout << "Invalid input, selecting normal option." << endl;
		type = "normal";
	}
	else {
		std::cout << "Rerouting to "<< type << " maps folder." << endl;
	}

	std::cout << "\n";
	if (type == "normal") {
		return true;
	}
	else {
		return false;
	}
}

string GameEngine::queryDirectory(string directory) {
	vector<string> namelist;
	std::cout << "Files names:" << endl;
	try
	{
		for (const auto& entry : fs::directory_iterator(directory)) {
			std::cout << entry.path().filename() << endl;
		}
	}
	catch (exception& e)
	{
		std::cout << "Unable to display file contents..." << endl;
	}

	std::cout << "\n";

	std::cout << "Enter the file path of a map file: ";

	string path = "";
	cin >> path;

	std::cout << "\n";

	return path;
}

void GameEngine::createMap(string path, bool normalMap) {
	MapLoader mapLoader = MapLoader();

	//Add continents
	vector<string> continentList = mapLoader.GetContinentList();

	//Add territories
	vector<Territory*> countryList = mapLoader.GetCountryList();

	//Add borders
	vector<vector<Territory*>> bordersList = mapLoader.GetBordersList();

	if (normalMap) {
		////Normal map version
		countryList = mapLoader.ReadMapFileForCountries(path, countryList);
		continentList = mapLoader.ReadMapFile(path, continentList);
		bordersList = mapLoader.ReadMapFileForBorders(path, bordersList, countryList);

		////Create the map
		map = mapLoader.CombineInfos(continentList, countryList, bordersList);
	}
	else {
		//Adapter for Conquest version
		ConquestFileReader* reader = new ConquestFileReader();
		ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*reader);
		continentList = adapter->ReadMapFile(path, continentList);
		countryList = adapter->ReadMapFileForCountries(path, countryList);

		cout << "Continent list size: " << continentList.size() << endl;
		cout << "Country list size: " << countryList.size() << endl;
		
		bordersList = adapter->ReadMapFileForBorders(path, bordersList, countryList);
		map = adapter->CombineInfos(continentList, countryList, bordersList);
	}
}

int GameEngine::queryPlayerCount() {
	std::cout << "Enter the number of players(2-5): ";

	int count;
	cin >> count;
	std::cout << "\n";

	if (count < 2) {
		std::cout << "Input too small, rounding player count up to 2." << endl;
		count = 2;
	}
	else if (count > 5) {
		std::cout << "Input too large, rounding player count down to 5." << endl;
		count = 5;
	}

	return count;
}

void GameEngine::createPlayers(int playerCount) {
	for (int i = 1; i < playerCount + 1; i++) {
		vector<Territory*> list;

		Player* player = new Player(list, new Hand(0, 0, 0, 0, 0, 0), i);
		players.push_back(player);
	}

	for (int i = 0; i < players.size(); i++) {
		if (i == 0) {
			players[i]->playerStrategy = new HumanPlayerStrategy(players[i],players);
		}
		else if (i == 1) {
			players[i]->playerStrategy = new NeutralPlayerStrategy(players[i]);
		}
		else if (i == 2) {
			players[i]->playerStrategy = new AggressivePlayerStrategy(players[i]);
		}
		else if (i == 3) {
			players[i]->playerStrategy = new BenevolentPlayerStrategy(players[i]);
		}
		else {
			players[i]->playerStrategy = new AggressivePlayerStrategy(players[i]);
		}
	}
}

void GameEngine::assignTerritoriesToPlayers(vector<Player*> playerList, vector<Territory*> territoryList) {
	int playerIndex = 0;
	int territoryIndex = 0;

	if (!playerList.empty()) {
		while (territoryIndex < territoryList.size()) {
			Map::assignTerritory(playerList.at(playerIndex), territoryList.at(territoryIndex));

			std::cout << "Territory (";
			std::cout << territoryIndex;
			std::cout << ") being assigned to Player (";
			std::cout << playerList.at(playerIndex)->getPlayerID();
			std::cout << ")." << endl;

			territoryIndex++;
			playerIndex++;

			if (playerIndex >= playerList.size()) {
				playerIndex = 0;
			}
		}
	}
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

	std::cout << armyCount;
	std::cout << " armies are being assigned to each player..." << endl;

	for (auto player : playerList) {
		player->mapPlayed = map;
		Hand* playerHand = player->getHand();
		player->numOfArmies = armyCount;
		player->gameDeck = deck;
		player->neutral = players[1];
	}
}

void GameEngine::mainGameLoop()
{
	while (!map->checkWinner(players))
	{

		reinforcementPhase();
		for (auto p : players) {
			p->attackArmies = p->numOfArmies;
		}

		playersIssuingOrders = players;
		issueOrdersPhase();
		playersExecutingOrders = players;
		executeOrdersPhase();
		for (auto it : players)
		{
			std::cout << it->getOwnedTerritories().size() << endl;
			it->neighbourmap.clear();
			it->enemyneighbourmap.clear();
			it->attacks.clear();
			it->orders->orders.clear();
			it->conqueredOne = false;
			it->playerStrategy->reset();
		}
	}
}
void GameEngine::reinforcementPhase()
{
	phase = 1;
	setPhase(phase);
	notifyGame();
	notifyPhase();
	for (auto p : players) {
		vector<Territory*> myvec = p->territories;
		p->numOfArmies += floor(myvec.size() / 3);
		bool owns;

		for (auto& it : map->getContinentMap())
		{
			owns = map->checkContinentOwnership(p, it.second);
			if (owns)
			{
				p->numOfArmies += map->getContinentArmies().at(it.first);
			}
		}

		if (p->numOfArmies < 3)
		{
			p->numOfArmies += 3;
		}
		p->tempArmies = p->numOfArmies;
	}
}
void GameEngine::issueOrdersPhase()
{
	phase = 2;
	setPhase(phase);
	notifyGame();
	notifyPhase();
	orderattempts = 0;
	bool allDone = false;
	while ((!allDone))
	{

		allDone = true;

		for (auto it : playersIssuingOrders)
		{
			if (it->doneIssue == false)
			{
				it->playerStrategy->issueOrder();
				allDone = false;

			}
		}

		orderattempts++;
	}
	for (auto it : players)
	{
		it->doneDefence = false;
		it->doneAdvance = false;
		it->doneAttack = false;
		it->donecard = false;
		it->doneIssue = false;
		it->roundwiseordercount = 0;
		it->tempArmies = it->numOfArmies;

	}
}

void GameEngine::eraseLosers()
{
	vector<int> loserPlayerIndex;

	//Store all the indices of players without territories
	for (int j = 0; j < players.size(); j++)
	{
		auto player = players[j];
		if (player->getOwnedTerritories().empty())
		{
			loserPlayerIndex.push_back(j);
		}
	}

	setIsPlayerBeingRemoved(true);

	//Erase the players without territories from the player list
	for (int j : loserPlayerIndex)
	{
		detach(players[j]); //detach the observer as well
		players.erase(players.begin() + j);
	}

	setIsPlayerBeingRemoved(false);
}

void GameEngine::executeOrdersPhase()
{
	phase = 3;
	setPhase(phase);
	notifyGame();
	notifyPhase();
	bool allDone = false;
	bool allDoneDeploy = false;
	bool allDoneAirlift = false;
	bool allDoneBlockade = false;
	bool allDoneElse = false;
	while (!allDone)
	{
		std::cout << players.back()->getOwnedTerritories().size() << endl;

		allDone = true;





		while (!allDoneDeploy) {
			allDoneDeploy = true;
			for (auto it : players)
			{
				for (auto orderit : it->getOrderList()->getOrders())
				{

					if ((orderit->name == "Deploy") && !(orderit->executed))
					{
						if (!orderit->executed)
						{
							orderit->execute();
							allDone = false;
							allDoneDeploy = false;
							std::cout << "Deploy Executed" << endl;
							break;
						}
					}

				}
			}
		}
		while (!allDoneAirlift) {
			allDoneAirlift = true;
			for (auto it : players)
			{
				for (auto orderit : it->getOrderList()->getOrders())
				{

					if ((orderit->name == "Airlift") && !(orderit->executed))
					{
						if (!orderit->executed)
						{
							orderit->execute();
							allDone = false;
							allDoneAirlift = false;
							std::cout << "Airlift Executed" << endl;
							break;
						}
					}

				}
			}
		}
		while (!allDoneBlockade) {
			allDoneBlockade = true;
			for (auto it : players)
			{
				for (auto orderit : it->getOrderList()->getOrders())
				{

					if ((orderit->name == "Blockade") && !(orderit->executed))
					{
						if (!orderit->executed)
						{
							orderit->execute();
							allDone = false;
							allDoneBlockade = false;
							std::cout << "Blockade Executed" << endl;
							break;
						}
					}

				}
			}
		}
		while (!allDoneElse) {
			allDoneElse = true;
			for (auto it : players)
			{
				for (auto orderit : it->getOrderList()->getOrders())
				{

					if (!(orderit->executed))

						if (!orderit->executed)
						{
							orderit->execute();
							allDone = false;
							allDoneElse = false;
							std::cout << orderit->name << " Executed" << endl;
							break;
						}
				}

			}
		}
	}
	eraseLosers();
}

ostream& operator <<(ostream& out, GameEngine& m) {
	out << "This is a game engine.";
	return out;
}