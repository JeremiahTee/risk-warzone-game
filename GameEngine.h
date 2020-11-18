#pragma once
#include "Cards.h"
#include "Map.h"

class Player;

class GameEngine //: public Observer
{
public:
	Map* map;
	vector<Player*> players;
	vector<Player*> playersIssuingOrders;
	vector<Player*> playersExecutingOrders;
	GameEngine();
	~GameEngine();

	void startupPhase();
	string queryDirectory(string directory);
	Map* createMap(string path);
	int queryPlayerCount();
	vector<Player*> createPlayers(int playerCount);
	void assignTerritoriesToPlayers(vector<Player*> playerList, vector<Territory*> territoryList);
	void assignInitialArmies(vector<Player*> playerList);
	void mainGameLoop();
	void reinforcementPhase();
	void orderIssuingPhase();
	void orderExecutionPhase();
};