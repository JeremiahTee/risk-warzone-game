#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy(Player* player) {
	this->player = player;
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {}
void HumanPlayerStrategy::issueOrder() {

}
vector<Territory*> HumanPlayerStrategy::toDefend() {
	vector<Territory*> list;
	return list;
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {}
void AggressivePlayerStrategy::issueOrder() {
	vector<Territory*> defendList = toDefend();
	vector<Territory*> attackList = toAttack();
	
	if (player->tempArmies > 0) {
		player->getOrderList()->add(new Deploy(player->tempArmies, mainTerritory, player));
	}
	else if (player->attackArmies != 0) {
		Territory* weakest = getWeakestTerritory(attackList);
		player->getOrderList()->add(new Advance(mainTerritory, weakest, mainTerritory->getArmyCount(), player, player->gameDeck));
	}
	//Add card use if we have time.
}
vector<Territory*> AggressivePlayerStrategy::toDefend() {
	vector<Territory*> list;

	if (player->getOwnedTerritories().size() > 0) {
		Territory* maxArmyTerritory = nullptr;
		for (auto t : player->getOwnedTerritories()) {
			if (hasEnemyNeighbor(t)) {
				maxArmyTerritory = t;
				break;
			}
		}

		if (maxArmyTerritory == nullptr) {
			cout << "ERROR: Game should be over.";
			return list;
		}

		for (auto t : player->getOwnedTerritories()) {
			if (maxArmyTerritory->getArmyCount() < t->getArmyCount() && hasEnemyNeighbor(t)) {
				maxArmyTerritory = t;
			}
		}

		mainTerritory = maxArmyTerritory;
		list.push_back(maxArmyTerritory);
	}
	return list;
}
vector<Territory*> AggressivePlayerStrategy::toAttack() {
	if (mainTerritory == nullptr || mainTerritory->getOwner() != player) {
		cout << "Main territory is null or not owned by player." << endl;
		exit(0);
	}
	return getEnemyNeighbors(mainTerritory);
}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {}
void BenevolentPlayerStrategy::issueOrder() {

}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> list;
	return list;
}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}
void NeutralPlayerStrategy::issueOrder() {

}
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	vector<Territory*> list;
	return list;
}
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}


Territory* getWeakestTerritory(vector<Territory*> list) {
	Territory* weakest = list[0];
	for (auto t : list) {
		if (weakest->getArmyCount() > t->getArmyCount()) {
			weakest = t;
		}
	}
	return weakest;
}

vector<Territory*> getEnemyNeighbors(Territory* territory) {
	vector<Territory*> toReturn;
	vector<Territory*> list = territory->getOwner()->mapPlayed->getTerritoryNeighbors(territory);
	for (auto t : list) {
		if (t->getOwner() != territory->getOwner()) {
			toReturn.push_back(t);
		}
	}
	return toReturn;
}

bool hasEnemyNeighbor(Territory* territory) {
	vector<Territory*> list = territory->getOwner()->mapPlayed->getTerritoryNeighbors(territory);
	for (auto t : list) {
		if (t->getOwner() != territory->getOwner()) {
			return true;
		}
	}
	return false;
}