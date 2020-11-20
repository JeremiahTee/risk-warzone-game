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
		createPlayers(playerCount);

		deck = new Deck(10, 10, 10, 10, 10, 10);

		attachObservers(players);
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
		assignTerritoriesToPlayers(players, map->getTerritories());

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

void GameEngine::createPlayers(int playerCount) {
	for (int i = 1; i < playerCount + 1; i++) {
		vector<Territory*> list;
		players.push_back(new Player(list, new Hand(0, 0, 0, 0, 0, 0), i));
	}
}

void GameEngine::assignTerritoriesToPlayers(vector<Player*> playerList, vector<Territory*> territoryList) {
	int playerIndex = 0;
	int territoryIndex = 0;

	if (!playerList.empty()) {
		while (territoryIndex < territoryList.size()) {
			Map::assignTerritory(playerList.at(playerIndex), territoryList.at(territoryIndex));

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

	cout << armyCount;
	cout << " armies are being assigned to each player..." << endl;

	for (auto player : playerList) {
		player->mapPlayed = map;
		Hand* playerHand = player->getHand();
		player->numOfArmies = armyCount;
		player->gameDeck = deck;
	}
}

void GameEngine::mainGameLoop()
{
	while (!map->checkWinner(players))
	{
		
		reinforcementPhase();
		
		playersIssuingOrders = players;
		orderIssuingPhase();
		playersExecutingOrders = players;
		orderExecutionPhase();
		for(auto it:players)
		{
			std::cout << it->getOwnedTerritories().size() << endl;
			it->neighbourmap.clear();
			it->attacks.clear();
			it->getOrderList()->orders.clear();
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
		int continentbonus = 4;//need to get this property from map/maploader for each continent
		
		for (auto& it  :map->getContinentMap())
		{
			owns = map->checkContinentOwnership(p, it.second);
			if (owns)
			{
				p->numOfArmies += continentbonus;
			}
		}
		if (p->numOfArmies < 3)
		{
			p->numOfArmies +=3;
		}
		p->tempArmies = p->numOfArmies;
	}
}
void GameEngine::orderIssuingPhase()
{
	phase = 2;
	setPhase(phase);
	notifyGame();
	notifyPhase();
	orderattempts = 0;
	bool allDone = false;
	while((!allDone)&&(orderattempts<100))
	{
		
		allDone = true;
		
		for(auto it:playersIssuingOrders)
		{
			if(it->doneIssue==false)
			{
				it->issueOrder();
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
		it->doneIssue = false;
		it->roundwiseordercount = 0;
		it->tempArmies = it->numOfArmies;
	}
}

void GameEngine::eraseLosers()
{
	vector<int> loserPlayerIndex;

	//Store all the indices of players without territories
	for(int j = 0; j < players.size(); j++)
	{
		auto player = players[j];
		if(player->getOwnedTerritories().empty())
		{
			loserPlayerIndex.push_back(j);
		}
	}

	setIsPlayerBeingRemoved(true);

	//Erase the players without territories from the player list
	for(int j: loserPlayerIndex)
	{
		players.erase(players.begin() + j);
		notifyGame();
		detach(players[j]); //detach the observer as well
	}

	setIsPlayerBeingRemoved(false);
}

void GameEngine::orderExecutionPhase()
{
	phase = 3;
	setPhase(phase);
	notifyGame();
	notifyPhase();
	bool allDone = false;
	while (!allDone)
	{
		std::cout << players.back()->getTerritories2().size() << endl;

		allDone = true;
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
						std::cout << "Deploy Executed" << endl;
						break;
					}
				}
				else if ((orderit->name == "Airlift") && !(orderit->executed))
				{
					if (!orderit->executed)
					{
						orderit->execute();
						allDone = false;
						break;
					}
				}
				else if ((orderit->name == "Blockade") && (!orderit->executed))
				{
					if (!orderit->executed)
					{
						orderit->execute();
						allDone = false;
						break;
					}
				}
				else
				{
					if (!orderit->executed)
					{
						orderit->execute();
						allDone = false;
						break;
					}
				}
			}
		}
	}
	
	eraseLosers();
}