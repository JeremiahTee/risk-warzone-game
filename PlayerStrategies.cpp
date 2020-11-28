#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy(Player* player) {
	this->player = player;
}

vector<Territory*> PlayerStrategy::sortTerritories(vector<Territory*> list) {
	vector<Territory*> sortedList = list;

	for (int i = 0; i < sortedList.size() - 1; i++) {
		int smallestIndex = i;
		for (int j = i + 1; j < sortedList.size(); j++) {
			if (sortedList[smallestIndex]->getArmyCount() > sortedList[j]->getArmyCount()) {
				smallestIndex = j;
			}
		}
		if (smallestIndex != i) {
			Territory* temp = sortedList[i];
			sortedList[i] = sortedList[smallestIndex];
			sortedList[smallestIndex] = temp;
		}
	}

	cout << "Sorting the list:" << endl;
	for (auto t : sortedList) {
		cout << t->getArmyCount() << endl;
	}

	return sortedList;
}

Territory* PlayerStrategy::getWeakestTerritory(vector<Territory*> list) {
	Territory* weakest = list[0];
	for (auto t : list) {
		if (weakest->getArmyCount() > t->getArmyCount()) {
			weakest = t;
		}
	}
	return weakest;
}

vector<Territory*> PlayerStrategy::getEnemyNeighbors(Territory* territory) {
	vector<Territory*> toReturn;
	vector<Territory*> list = territory->getOwner()->mapPlayed->getTerritoryNeighbors(territory);
	for (auto t : list) {
		if (t->getOwner() != territory->getOwner()) {
			toReturn.push_back(t);
		}
	}
	return toReturn;
}

bool PlayerStrategy::hasEnemyNeighbor(Territory* territory) {
	vector<Territory*> list = territory->getOwner()->mapPlayed->getTerritoryNeighbors(territory);
	for (auto t : list) {
		if (t->getOwner() != territory->getOwner()) {
			return true;
		}
	}
	return false;
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
void HumanPlayerStrategy::reset() {}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {}
void AggressivePlayerStrategy::issueOrder() {
	vector<Territory*> defendList = toDefend();
	vector<Territory*> attackList = toAttack();
	
	if (player->tempArmies > 0) {
		player->getOrderList()->add(new Deploy(player->tempArmies, mainTerritory, player));
	}
	else if (player->attackArmies > 0) {
		Territory* weakest = getWeakestTerritory(attackList);
		player->getOrderList()->add(new Advance(mainTerritory, weakest, mainTerritory->getArmyCount(), player, player->gameDeck));
	}
	else {
		player->doneIssue = true;
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
void AggressivePlayerStrategy::reset() {}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {}
void BenevolentPlayerStrategy::issueOrder() {
	vector<Territory*> defendList = toDefend();
	vector<Territory*> attackList = toAttack();

	if (player->tempArmies > 0) {
		player->getOrderList()->add(new Deploy(1, defendList[benevolentIndex], player));
		benevolentIndex++;
		if (benevolentIndex >= defendList.size()) {
			benevolentIndex = 0;
		}
	}
	else {
		player->doneIssue = true;
	}
}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> list = sortTerritories(player->getOwnedTerritories());
	int defenceCount = ceil(list.size()*.25);

	vector<Territory*> toReturn;

	for (int i = 0; i < defenceCount; i++) {
		toReturn.push_back(list[i]);
	}
	return toReturn;
}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}
void BenevolentPlayerStrategy::reset() {
	benevolentIndex = 0;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}
void NeutralPlayerStrategy::issueOrder() {
	//This does nothing.
	player->doneIssue = true;
}
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	vector<Territory*> list;
	return list;
}
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}
void NeutralPlayerStrategy::reset() {}
