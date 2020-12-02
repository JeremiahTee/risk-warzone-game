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
	PlayerStrategy(PlayerStrategy&);

	
	virtual void issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;

	virtual void reset() = 0;

	vector<Territory*> sortTerritories(vector<Territory*> list);
	Territory* getWeakestTerritory(vector<Territory*> list);
	vector<Territory*> getEnemyNeighbors(Territory* territory);
	bool hasEnemyNeighbor(Territory* territory);
	friend ostream& operator << (ostream& out, PlayerStrategy& ps);
	
};

class HumanPlayerStrategy : public PlayerStrategy{
private:
	vector<Player*> players;
	vector<Player*> gameplayers;
public:
	HumanPlayerStrategy() = default;
	HumanPlayerStrategy(Player* player, vector<Player*> players);
	HumanPlayerStrategy(HumanPlayerStrategy&);
	friend ostream& operator << (ostream& out, HumanPlayerStrategy& hps);
	HumanPlayerStrategy& operator=(HumanPlayerStrategy& h);
	
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
	AggressivePlayerStrategy(AggressivePlayerStrategy&);
	AggressivePlayerStrategy& operator=(AggressivePlayerStrategy& h);
	
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void reset();
	friend ostream& operator << (ostream& out, AggressivePlayerStrategy& aps);
};


class BenevolentPlayerStrategy : public PlayerStrategy {
private:
	int benevolentIndex;
public:
	BenevolentPlayerStrategy() = default;
	BenevolentPlayerStrategy(Player* player);
	BenevolentPlayerStrategy(BenevolentPlayerStrategy&);
	BenevolentPlayerStrategy& operator=(BenevolentPlayerStrategy& h);
	
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void reset();
	friend ostream& operator << (ostream& out, BenevolentPlayerStrategy& bps);

};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy() = default;
	NeutralPlayerStrategy(Player* player);
	NeutralPlayerStrategy(NeutralPlayerStrategy&);
	NeutralPlayerStrategy& operator=(NeutralPlayerStrategy& h);
	
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void reset();
	friend ostream& operator << (ostream& out, NeutralPlayerStrategy& nps);
};
