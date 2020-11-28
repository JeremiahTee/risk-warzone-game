#pragma once

#include "Map.h";
#include "Player.h";

#include <vector>;
#include <iostream>;

class Territory;
class Player;

using namespace std;

class PlayerStrategy {

protected:
	Player* player;

public:
	PlayerStrategy() = default;
	PlayerStrategy(Player* player);

	virtual void issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;

	virtual void reset() = 0;

	vector<Territory*> sortTerritories(vector<Territory*> list);
	Territory* getWeakestTerritory(vector<Territory*> list);
	vector<Territory*> getEnemyNeighbors(Territory* territory);
	bool hasEnemyNeighbor(Territory* territory);
};

class HumanPlayerStrategy : public PlayerStrategy{
private:
	vector<Player*> players;
public:
	HumanPlayerStrategy() = default;
	vector<Player*> gameplayers;
	HumanPlayerStrategy(Player* player, vector<Player*> players);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void reset();
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
	void reset();
};


class BenevolentPlayerStrategy : public PlayerStrategy {
private:
	int benevolentIndex;
public:
	BenevolentPlayerStrategy() = default;
	BenevolentPlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void reset();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy() = default;
	NeutralPlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void reset();
};
