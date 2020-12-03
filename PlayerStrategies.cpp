#include "PlayerStrategies.h"

using std::cout;

PlayerStrategy::PlayerStrategy(Player* player) {
	this->player = player;
}
PlayerStrategy::PlayerStrategy(PlayerStrategy& PS)
{
	this->player = PS.player;
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
ostream& operator << (ostream& out, PlayerStrategy& ps)
{
	out << "Base Strategy of player " << ps.player->getPlayerID() << endl;
	
	return out;
}


HumanPlayerStrategy::HumanPlayerStrategy(Player* player, vector<Player*>players) : PlayerStrategy(player) { gameplayers = players; };
void HumanPlayerStrategy::issueOrder() {

	if(player->tempArmies>0)
	{
		cout << "Hey Player " << player->getPlayerID() << ". You still have armies left to deploy. You have " << player->tempArmies<< " armies left. Deploy them before you can issue other orders.\nYour Territories:"<< endl;
		for(auto it: player->getOwnedTerritories())
		{
			cout << it->getName() << "\tArmies on this territory: " << it->getArmyCount() << endl;
		}
		cout << "How many armies?" << endl;
		int numarmies;
		cin >> numarmies;
		cout << "And on which territories?" << endl;
		string name;
		cin >> name;
		bool flag = false;
		for (auto it : player->getOwnedTerritories())
		{
			if (it->getName()==name)
			{
				player->getOrderList()->add(new Deploy(numarmies, it, player));
				flag = true;
			}
		}
		if(!flag)
		{
			cout << "You entered an incorrect name." << endl;
		}
	}
	else 
	{
		cout << "What type of order do you want to issue? Enter \"done\" when finished.\n Options are: Advance orders (type \"advance\") or Cards (type \"cards\")."<<endl;
		string choice;
		cin >> choice;
		if(choice=="done")
		{
			player->doneIssue = true;
			return;
		}
		else if (choice=="advance")
		{
			cout << "You have chosen Advance. Your territories are ordered below and you can move armies from here to any other territory that own or to an enemy neighbours territory." << endl;
			cout << "To see a neighbour of your territories enter the name or press skip if you're ready to place the order." << endl;
			string neighbourname;
			cin >> neighbourname;
			if (neighbourname=="skip")
			{
				cout << "You chose to skip" << endl;
			}
			else {
				Territory* thisterr=player->mapPlayed->getTerritory(neighbourname);
				if (thisterr->getName()!="N/A")
				{
					cout << "Displaying names of neighbours: "<<endl;
					for (auto it:player->mapPlayed->getTerritoryNeighbors(neighbourname))
					{
						cout << it->getName()<<"\t"<<it->getArmyCount()<<endl;
					}
				}
				else
				{
					cout << "Wrong name entered" << endl;
				}
			}
			cout << "Enter the source then press enter then target then press enter then number of armies then enter." << endl;
			string source, target;
			int num;
			cout << endl << "Source: ";
			cin >> source;
			cout << endl << "Target: ";
			cin >> target;
			cout << endl << "Number of armies: ";
			cin >> num;
			Territory* sourcet;
			Territory* targett;
			sourcet = player->mapPlayed->getTerritory(source);
			targett = player->mapPlayed->getTerritory(target);
			if(sourcet->getName()==("N/A")||targett->getName()=="N/A")
			{
				cout << "You have entered a wrong territory name. Try again next turn haha";
			}
			else
			{
				player->getOrderList()->add(new Advance(sourcet, targett, num,player,player->gameDeck));
			}
		}
		else if(choice == "cards")
		{
			cout << "Here is your hand of cards" << endl;
			cout << "airlift\t" << player->getHand()->getAirlift() << endl;
			cout << "bomb\t" << player->getHand()->getBomb() << endl;
			cout << "blockade\t" << player->getHand()->getBlockade() << endl;
			cout << "negotiate\t" << player->getHand()->getDiplomacy() << endl;
			cout << "Which card do you wanna play?" << endl;
			string cardtype;
			cin >> cardtype;
			if(cardtype=="airlift")
			{
				cout << "Enter source followed by target followed by number of armies..." << endl;
				string source, target;
				int num;
				cout << endl << "Source: ";
				cin >> source;
				cout << endl << "Target: ";
				cin >> target;
				cout << endl << "Number of armies: ";
				cin >> num;
				Territory* sourcet;
				Territory* targett;
				sourcet = player->mapPlayed->getTerritory(source);
				targett = player->mapPlayed->getTerritory(target);
				if (sourcet->getName() == ("N/A") || targett->getName() == "N/A")
				{
					cout << "You have entered a wrong territory name. Try again next turn haha";
				}
				else
				{
					player->getOrderList()->add(new Airlift(sourcet, targett, num, player));
				}
			}
			else if (cardtype == "bomb")
			{
				cout << "enter target territory: " << endl;
				string  target;
				cin >> target;
				Territory* sourcet;
				Territory* targett;
				targett = player->mapPlayed->getTerritory(target);
				if ( targett->getName() == "N/A")
				{
					cout << endl << "You have entered a wrong territory name. Try again next turn haha" << endl;
				}
				else
				{
					player->getOrderList()->add(new Bomb(targett,player));
				}
			}
			else if (cardtype == "blockade")
			{
				cout << "Enter target territory: " << endl;
				string  target;
				cin >> target;
				Territory* targett;
				targett = player->mapPlayed->getTerritory(target);
				if (targett->getName() == "N/A")
				{
					cout << endl << "You have entered a wrong territory name. Try again next turn haha" << endl;
				}
				else
				{
					player->getOrderList()->add(new Blockade(targett, player, player->neutral));
				}
			}
			else if (cardtype == "negotiate")
			{
				
				cout << "Showing player names:" << endl;
				for(auto it:gameplayers)
				{
					cout << it->getPlayerID();
				}
				cout << "Enter the target player ID:" << endl;
				int playerid;
				cin >> playerid;
				if(playerid<=gameplayers.size())
				{
					player->getOrderList()->add(new Negotiate(player, gameplayers[playerid]));
				}
			}
			else 
			{
				cout << "invalid input try again next turn and maybe learn to read properly";
			}
		}
		else
		{
			cout << "Wrong entry, try again next turn ;)";
		}
		
	}
		
}
vector<Territory*> HumanPlayerStrategy::toDefend() {
	vector<Territory*> list;

	return list;
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
	vector<Territory*> list;
	return list;
}
HumanPlayerStrategy& HumanPlayerStrategy::operator=(HumanPlayerStrategy& o)
{
	HumanPlayerStrategy p = HumanPlayerStrategy(o);
	return  p;
};
void HumanPlayerStrategy::reset() {}

HumanPlayerStrategy::HumanPlayerStrategy(HumanPlayerStrategy& hps) : PlayerStrategy( hps)
{
	this->players = hps.players;
	this->gameplayers = hps.gameplayers;
}
ostream& operator << (ostream& out, HumanPlayerStrategy& hps)
{

	out << "Human Strategy of player " << hps.player->getPlayerID() << endl;
	out << "The players in the game hosting this strategy are " <<  endl;
	for(auto it: hps.gameplayers)
	{
		out << it->getPlayerID() << endl;
	}

	return out;
}

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
		player->attackArmies=0;
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
		cout << mainTerritory->getName() << "\t" << mainTerritory->getOwner()->getPlayerID() << "\t"<<player->getPlayerID();
		exit(0);
	}
	return getEnemyNeighbors(mainTerritory);
}
void AggressivePlayerStrategy::reset() {}
AggressivePlayerStrategy::AggressivePlayerStrategy(AggressivePlayerStrategy& hps) : PlayerStrategy(hps)
{
	this->mainTerritory = hps.mainTerritory;
}
ostream& operator << (ostream& out, AggressivePlayerStrategy& aps)
{

	out << "Aggressive Strategy of player " << aps.player->getPlayerID() << endl;
	out << "The main territory in the game hosting this strategy are " << aps.mainTerritory->getName() <<endl;

	return out;
}
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(AggressivePlayerStrategy& o)
{
	AggressivePlayerStrategy p = AggressivePlayerStrategy(o);
	return  p;
};
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
	int defenceCount = ceil(list.size()*.5);

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
BenevolentPlayerStrategy::BenevolentPlayerStrategy(BenevolentPlayerStrategy& bps):PlayerStrategy(bps)
{
	benevolentIndex = bps.benevolentIndex;
}
ostream& operator << (ostream& out, BenevolentPlayerStrategy& bps)
{
	out << "Benevolent Strategy of player " << bps.player->getPlayerID() << endl;
	out << "The benevolent index currently in the game hosting this strategy are " << bps.benevolentIndex << endl;

	return out;
}
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(BenevolentPlayerStrategy& o)
{
	BenevolentPlayerStrategy p = BenevolentPlayerStrategy(o);
	return  p;
};

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}
void NeutralPlayerStrategy::issueOrder() {
	//This does nothing.
	player->doneIssue = true;
}
NeutralPlayerStrategy::NeutralPlayerStrategy(NeutralPlayerStrategy& nps):PlayerStrategy(nps)
{
	
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
ostream& operator << (ostream& out, NeutralPlayerStrategy& bps)
{
	out << "Neutral Strategy of player " << bps.player->getPlayerID() << endl;
	return out;
}
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(NeutralPlayerStrategy& o)
{
	NeutralPlayerStrategy p = NeutralPlayerStrategy(o);
	return  p;
};