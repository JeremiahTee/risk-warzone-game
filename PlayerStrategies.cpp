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
	
}
vector<Territory*> AggressivePlayerStrategy::toDefend() {
	vector<Territory*> list;
	return list;
}
vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
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

