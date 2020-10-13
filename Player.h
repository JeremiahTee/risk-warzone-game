//============================================================================
// Name        : Player.h
// Author      : Jeremiah Tiongson (40055477)
// Description : Player header class.
//============================================================================

#pragma once

class Territory; //forward declaration to avoid compilation errors

#include "Territory.h"
#include "Order.h"
#include "Cards.h"
#include <vector>
#include <ostream>

using std::vector;
using std::string;

class Player
{
private:
	vector<Territory*> territories;
	Hand* hand;
	OrderList* orders;
	
public:
	string name; //left public intentionally just for testing purposes & to avoid setting up unnecessary getter
	Player() = default;
	Player(vector<Territory*> territories, Hand* hand, string playerName);
	vector<Territory> getTerritories();
	vector<Territory> toDefend();
	vector<Territory> toAttack();
	Hand getHand();
	void issueOrder();
	Player* operator = (Player& o);
	Player(const Player& o);
	virtual Player* getNew();
	friend ostream& operator << (ostream& out, const Player& p);
};