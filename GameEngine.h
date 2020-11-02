#pragma once
#include "Cards.h"
#include "Map.h"

class Player;

class GameEngine{
public:
	Map* map;
	vector<Player*> players;

	void Start();
	string queryDirectory(string directory);
	Map* createMap(string path);
	int queryPlayerCount();
	vector<Player*> createPlayers(int playerCount);
};