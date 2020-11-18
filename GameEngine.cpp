#include "GameEngine.h"

#include <ctime>
#include <process.h>
#include <iostream>
#include <filesystem>
#include <vector>

using std::vector;

//Map initialization
Map Game::map = Map();
//Vector to hold turns
vector<Player> Game::turns = {};

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
	//map = Map::getTestMap(); //UNCOMMENT ABOVE WHEN MAPLOADER IS FIXED.

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
	vector<Territory*> continentList = mapLoader.GetContinentList();
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

void Game::startupPhase()
{
	
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
	}
}
void GameEngine::reinforcementPhase()
{
	for (auto p : players) {
		vector<Territory*> myvec = p->getTerritories2();
		int count = 0;
		p->numOfArmies = floor(myvec.size() / 3);
		bool owns;
		int continentbonus = 4;//need to get this property from map/maploader for each continent
		std::cout << "HI";
		for (auto& it  :map->getContinentMap())
		{
			std::cout << "HI2";
			owns = map->checkContinentOwnership(p, it.second);
			if (owns)
			{
				p->numOfArmies += continentbonus;
			}
		}
		if (p->numOfArmies < 3)
		{
			p->numOfArmies = 3;
		}
	}
}
void GameEngine::orderIssuingPhase()
{
	
	bool allDone = false;
	while(!allDone)
	{
		allDone = true;
		for(auto it:playersIssuingOrders)
		{
			if(it->doneIssue!=false)
			{
				it->issueOrder();
				allDone = false;
			}
		}
	}
	for (auto it : players)
	{
		it->doneDefence = false;
		it->doneAdvance = false;
		it->doneAttack = false;
		it->doneIssue = false;
		it->roundwiseordercount = 0;
		//TO DELETE PLAYER WHO HAS LOST
		/**/
	}
}
void GameEngine::orderExecutionPhase()
{
	bool allDone = false;
	while (!allDone)
	{
		allDone = true;
		for (auto it : players)
		{
			for(auto orderit:it->getOrderList()->getOrders())
			{
				if(orderit->name=="Deploy")
				{
					if (!orderit->executed)
					{
						orderit->execute();
						allDone = false;
						
						break;
					}
				}
				else if(orderit->name=="Airlift")
				{
					if (!orderit->executed)
					{
						orderit->execute();
						allDone = false;
						break;
					}
				}
				else if (orderit->name == "Blockade")
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
	for (auto it : players)
	{
		if (it->getOwnedTerritories().size() == 0)
		{
			std::vector<Player*>::iterator position = std::find(players.begin(), players.end(), it);
			if (position != players.end()) // == myVector.end() means the element was not found
			{
				players.erase(position);
			}

		}
	}
	
}

