//============================================================================
// Name        : Player.h
// Author      : Jeremiah Tiongson (40055477)
// Description : Player header class.
//============================================================================

#pragma once
#include "GameObservers.h"

class Territory; //forward declaration to avoid compilation errors

#include "Territory.h"
#include "Order.h"
#include "Cards.h"
#include <vector>
#include <ostream>

using std::vector;
using std::string;

class Player : public Observer
{
private:
	vector<Territory*> territories;
	Hand* hand;
	OrderList* orders;
	
public:
	Player() = default;
	Player(vector<Territory*> territories, Hand* hand, int id);
	vector<Territory> getTerritories();
	vector<Territory> toDefend();
	vector<Territory> toAttack();
	Hand getHand();
	void issueOrder();
	int playerId = 0;
	Player* operator = (Player& o);
	Player(const Player& o);
	virtual Player* getNew();
	friend ostream& operator << (ostream& out, const Player& p);

	//Observer pattern
	void notifyGame(int totalTerr) override;
	void notifyPhase(int phase) override;
};