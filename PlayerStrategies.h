#pragma once

#include "Map.h";
#include "Player.h";

#include <vector>;

class Territory;
class Player;

using namespace std;

class PlayerStrategy {

private:
	Player* player;

public:
	PlayerStrategy() = default;
	PlayerStrategy(Player* player);

	virtual void issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;

};

class HumanPlayerStrategy : public PlayerStrategy{
public:
	HumanPlayerStrategy() = default;
	HumanPlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};


class AggressivePlayerStrategy : public PlayerStrategy {
private:
	Territory* mainTerritory;
public:
	AggressivePlayerStrategy() = default;
	AggressivePlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};


class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy() = default;
	BenevolentPlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy() = default;
	NeutralPlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};
