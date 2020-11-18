#pragma once

#include "GameObservers.h"
#include "Map.h"
#include "Cards.h"
#include "Territory.h"

class Player; //forward declaration

// Part 1: Game start  ?? might not need a class for this
class Startup
{
	
};

// Part 2: Game play (game startup phase)
// Game inherits from Subject as it needs to be observed
class Game : public Subject
{
public:
	Game(int playerCount, std::string& map);
	std::vector<Player>& getPlayerTurns();

private:
	static Map map;
	Deck gameDeck;
	std::vector<Player> players;
	static std::vector<Player> turns;
	int phase;
	int totalPlayers;
	void startupPhase();
	void setTurns();
	void setArmies();
	void setObservers();
	void setMap();
};
