#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy(Player* player) {
	this->player = player;
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}

