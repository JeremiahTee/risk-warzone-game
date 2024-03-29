//============================================================================
// Name        : Player.h
// Author      : Jeremiah Tiongson 
// Description : Player header class.
//============================================================================

#pragma once
#include "GameObservers.h"
#include "PlayerStrategies.h"
#include "Map.h"
#include "Order.h"
#include "Cards.h"
#include <vector>

using std::vector;
using std::string;

class Observer;
class Territory; //forward declaration to avoid compilation errors
class OrderList;
class PlayerStrategy;

class Player : public Observer
{
private:
	
	Hand* hand;
	
public:
	PlayerStrategy* playerStrategy;
	vector<Territory*> territories;
	Player* neutral;
	Deck* gameDeck;
	OrderList* orders;
	int roundwiseordercount;
	bool doneIssue;
	int numOfArmies;//Change to better name

	bool doneDefence;
	bool doneAttack;
	bool doneAdvance;
	bool donecard;

	Map* mapPlayed;
	vector<Player*> negotiated;
	vector<Territory*> attacks;
	vector<Territory*> defences;
	bool isNegotiated(Player*, Player*);
	string name; //left public intentionally just for testing purposes & to avoid setting up unnecessary getter
	int playerId = 0;
	int tempArmies;
	bool conqueredOne = false;
	bool orderFlag = false;
	map<Territory*, vector<Territory*>> neighbourMap;
	map<Territory*, vector<Territory*>> enemyneighbourMap;
	int attackArmies;

	Player() = default;
	Player(vector<Territory*> territories, Hand* hand, int id);
	Player(const Player& o);
	virtual ~Player();

	vector<Territory*>& getOwnedTerritories();
	void setOwnedTerritories(vector<Territory*>& list);

	Hand* getHand();
	OrderList* getOrderList();

	int getPlayerID() { return playerId; };
	int getNumberOfArmies() { return numOfArmies; };

	void setStratedy(PlayerStrategy*);

	virtual void updatePhase(int phaseNumber);
	virtual void updateGame(int totalTerritories, bool isPlayerBeingRemoved);

	friend ostream& operator << (ostream& out, const Player& p);
};