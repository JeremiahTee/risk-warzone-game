#include "PlayerStrategies.h"

using namespace std;

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

HumanPlayerStrategy::HumanPlayerStrategy(Player* player, vector<Player*>players) : PlayerStrategy(player) { gameplayers = players; };
void HumanPlayerStrategy::issueOrder() {

	if(player->tempArmies>0)
	{
		cout << "You have still got armies left to deploy. You have " << player->tempArmies<< " armies left. Deploy them before you can issue other orders.\nYour Territories:"<< endl;
		for(auto it: player->getOwnedTerritories())
		{
			cout << it->getName() << "\tArmies on this territory: " << it->getArmyCount() << endl;
		}
		cout << "How many armies?" << endl;
		int numarmies;
		std::cin >> numarmies;
		cout << "And on which territories?" << endl;
		string name;
		std::cin >> name;
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
		cout << "What type of order do you want to issue. If you're done enter \"done\" Options are: Advance orders (type \"advance\") or Cards (type \"cards\")."<<endl;
		string choice;
		std::cin >> choice;
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
			std::cin >> neighbourname;
			if (neighbourname=="skip")
			{
				cout << "You chose to skip";
			}
			else {
				/*for(auto it:player->getOwnedTerritories())
				{
					if(it->getName()==neighbourname)
					{
						for(auto name2 : player->mapPlayed->getTerritoryNeighbors(it))
						{
							
						}
					}
				}*/
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
					cout << "Wrong name entered";
				}
			}
			cout << "Enter the source then press enter then target then press enter then number of armies then enter.";
			string source, target;
			int num;
			std::cin >> source;
			std::cin >> target;
			std::cin >> num;
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
			cout << "Airlift\t" << player->getHand()->getAirlift() << endl;
			cout << "Bomb\t" << player->getHand()->getBomb() << endl;
			cout << "Blockade\t" << player->getHand()->getBlockade() << endl;
			cout << "Negotiate\t" << player->getHand()->getDiplomacy() << endl;
			cout << "Which card do you wanna play?" << endl;
			string cardtype;
			cin >> cardtype;
			if(cardtype=="airlift")
			{
				//Territory* source; Territory* target; int numArmies; Player* p;
				cout << "enter source followed by target followed by number of armies";
				string source, target;
				int num;
				cin >> source;
				cin >> target;
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
				cout << "enter target territory";
				string  target;
				cin >> target;
				Territory* sourcet;
				Territory* targett;
				targett = player->mapPlayed->getTerritory(target);
				if ( targett->getName() == "N/A")
				{
					cout << "You have entered a wrong territory name. Try again next turn haha";
				}
				else
				{
					player->getOrderList()->add(new Bomb(targett,player));
				}
			}
			else if (cardtype == "blockade")
			{
				cout << "enter target territory";
				string  target;
				cin >> target;
				Territory* targett;
				targett = player->mapPlayed->getTerritory(target);
				if (targett->getName() == "N/A")
				{
					cout << "You have entered a wrong territory name. Try again next turn haha";
				}
				else
				{
					player->getOrderList()->add(new Blockade(targett, player, player->neutral));
				}
			}
			else if (cardtype == "negotiate")
			{
				cout << "showing player names:" << endl;
				
			}
			else 
			{
				cout << "invalid input try again next turn and maybe read properly";
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

//Testcomment
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
