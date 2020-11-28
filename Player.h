//============================================================================
// Name        : Player.h
// Author      : Jeremiah Tiongson (40055477)
// Description : Player header class.
//============================================================================

#pragma once
#include "GameObservers.h"
#include "PlayerStrategies.h"
#include "Map.h"
#include "Order.h"
#include "Cards.h"

#include <vector>
#include <ostream>

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
	OrderList* orders;
	PlayerStrategy* playerStrategy;

public:
	vector<Territory*> territories;
	Player* neutral;
	Deck* gameDeck;
	int roundwiseordercount;
	bool doneIssue;
	int numOfArmies;//Change to better name
	vector<Player*> negotiated;
	vector<Territory*> attacks;
	vector<Territory*> defences;
	bool isNegotiated(Player*, Player*);
	string name; //left public intentionally just for testing purposes & to avoid setting up unnecessary getter
	int playerId = 0;
	int tempArmies;
	bool conqueredOne = false;
	Player() = default;
	Map* mapPlayed;
	 vector <Territory*>& getTerritories2();
	Player(vector<Territory*> territories, Hand* hand, int id);
	Player(const Player& o);
	~Player();
	Hand* getHand();
	OrderList* getOrderList();
	vector<Territory*>& getOwnedTerritories();
	void setOwnedTerritories(vector<Territory*> &list);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();
	bool orderFlag = false;
	friend ostream& operator << (ostream& out, const Player& p);
	Territory* getLowestArmyTerritory();
	Territory* getHighestArmyTerritory();
	map<Territory*, vector<Territory*>> neighbourmap;
	map<Territory*, vector<Territory*>> enemyneighbourmap;
	bool doneDefence;
	bool doneAttack;
	bool doneAdvance;
	bool donecard;
	//Implements the Observer notify methods
	virtual void updatePhase(int phaseNumber);
	virtual void updateGame(int totalTerritories, bool isPlayerBeingRemoved);
	int getPlayerID() { return playerId; };
	int getNumberOfArmies() { return numOfArmies; };
};