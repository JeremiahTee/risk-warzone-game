//============================================================================
// Name        : Player.cpp
// Author      : Jeremiah Tiongson (40055477)
// Description : Player compilation unit class.
//============================================================================

#include "Player.h"
#include <iomanip>
#include "Order.h"
#include <ostream>
#include <vector>
#include <random>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::setfill;

//fully parametrized constructor
Player::Player(vector<Territory*> playerTerritories, Hand* playerHand, int id)
{
	territories = playerTerritories;
	hand = playerHand;
	playerId = id;
	this->orders = new OrderList();
}

//copy constructor
Player::Player(const Player& p)
{
	territories = p.territories;
	hand = p.hand;
	neighbourmap = p.neighbourmap;
	
}
bool Player::isNegotiated(Player* p1, Player* p2)
{
	vector<Player*> myvec = p1->negotiated;
	vector<Player*>::iterator it = myvec.begin();
	for (it = myvec.begin(); it != myvec.end(); ++it)
	{


		if (*it == p2)
		{
			return true;
		};
		

	};
	return false;
}

////assignment operator overloading
//Player* Player:: operator = (Player& p)
//{
//	return p.getNew();
//}

Player::~Player() {
	for (auto territory : territories) {
		territory->setOwner(NULL);
	}
	
	//delete hand;
	//delete orders;
}
 vector<Territory*> &Player::getTerritories2()
{
	return territories;
}

vector<Territory*> Player::toAttack()//vector<Territory*> &Player::toAttack()
{
		neighbourmap = mapPlayed->getTerritoryNeighbors(this);
		//map < Territory*, vector<Territory*>>::iterator mapit;
		for (auto mapit : neighbourmap)
		{
			vector <Territory*> theseNeighbors = mapit.second;
			vector <Territory*> theseEnemyNeighbors;
			for(auto it:theseNeighbors)
			{
				if (it->getOwner()!=this)
				{
						if (std::find(attacks.begin(), attacks.end(), it) == attacks.end()) {
							attacks.push_back(it);
							theseEnemyNeighbors.push_back(it);
						}
				}
			}
			mapit.second = theseEnemyNeighbors;
		}
	
	return attacks;
}
vector<Territory*> Player::toDefend()//&Player::toDefend()
{
	for (auto it : territories)
	{
		if((it->getArmyCount()<4))
		{
			if (std::find(defences.begin(),defences.end(),it)==defences.end()) {
				defences.push_back(it);
			}
		}
	}
	return defences;
}

void Player::issueOrder()
{
	toAttack();
	toDefend();
	if((tempArmies<=4)&&(tempArmies>0))
	{
		orders->add(new Deploy(tempArmies,defences.front(),this));
		tempArmies = -1;
		defences.pop_back();
		cout << "Dep1" << endl;
		roundwiseordercount++;
	}
	else if ((tempArmies != 0)&&(tempArmies>0))
	{
		orders->add(new Deploy(tempArmies / 4, defences.back(), this));
		
		defences.pop_back();
		cout << "Dep2" << endl;
		roundwiseordercount++;
	}
	else if(!(doneAdvance && doneAttack) && (getHighestArmyTerritory()->getArmyCount() != 0))
	{
		if(!doneDefence)
		{
				orders->add(new Advance(getHighestArmyTerritory(), getLowestArmyTerritory(), getHighestArmyTerritory()->getArmyCount() / 2, this, this->gameDeck));
				doneDefence = true;
				roundwiseordercount++;
				cout << "AdvDef" << endl;
		}
		else
		{
			Territory* guarded = getHighestArmyTerritory();
			Territory* targ = neighbourmap.at(guarded).back();
			if (targ == NULL)
			{
				cout << "Fuck C++ im out";
			}
			else
			{
				cout << guarded->getName()<<"   ->   "<<targ->getName();

			}
			orders->add(new Advance(guarded, targ, guarded->getArmyCount()/ 2, this ,this->gameDeck));
			doneAdvance = true;
			doneAttack = true;
			roundwiseordercount++;
			cout << "AdvAtt" << endl;
		}
		doneAdvance = true;
	}
	else if(roundwiseordercount<10 && (getHighestArmyTerritory()->getArmyCount() != 0))
	{
		if (hand->getAirlift() >3 )
		{
			hand->play(4);//to add back to deck
			orders->add(new Airlift(getHighestArmyTerritory(),getLowestArmyTerritory(),getHighestArmyTerritory()->getArmyCount()/2,this));
			roundwiseordercount++;
			gameDeck->addToDeck(4);
		}
		else if (hand->getBlockade() >3)
		{
			hand->play(3);
			orders->add(new Blockade(getLowestArmyTerritory(),this,neutral));
			roundwiseordercount++;
			gameDeck->addToDeck(3);
		}
		else if (hand->getBomb() >3)
		{
			hand->play(1);
			Territory* neighOfBomb = getLowestArmyTerritory();
			Territory* toBomb = neighbourmap.at(neighOfBomb).front();
			orders->add(new Bomb(toBomb, this));
			roundwiseordercount++;
			gameDeck->addToDeck(1);
		}
		else if (false)//hand->getAirlift() >3    //NEED TO ADD NEGOTIATE BEHAVIOUR
		{
			hand->setAirlift(hand->getAirlift() - 1);
			orders->add(new Airlift(getHighestArmyTerritory(), getLowestArmyTerritory(), getHighestArmyTerritory()->getArmyCount() / 2, this));
		}
	}
	else
	{
		doneIssue = true;
	}
}
Territory* Player::getLowestArmyTerritory()
{
	int lowcount = 0;
	int thiscount;
	Territory* toReturn=nullptr;
	for(auto it:territories)
	{
		thiscount = it->getArmyCount();
		if(thiscount<=lowcount)
		{
			lowcount = thiscount;
			toReturn = it;
		}
	}
	return toReturn;
}
Territory* Player::getHighestArmyTerritory()
{
	int highcount = 0;
	int thiscount;
	Territory* toReturn=nullptr;
	for (auto it : territories)
	{
		thiscount = it->getArmyCount();
		if (thiscount >= highcount)
		{
			highcount = thiscount;
			toReturn = it;
		}
	}
	return toReturn;
}

//Returns the hand if it has a valid pointer to it
Hand* Player::getHand()
{
	return hand;
}

OrderList* Player::getOrderList() {
	return orders;
}

//
//Player* Player::getNew()
//{
//	return new Player(*this);
//}

//ostream operator for Player prints number of territories and indicates whether the hand is valid or not
std::ostream& operator <<(ostream& out, const Player& p)
{
	if (p.hand != nullptr)
	{
		out << "\nPlayer: " << p.playerId << " has " << p.territories.size() << " territories and a valid Hand.\n";
	}
	else
	{
		out << "\nPlayer: " << p.playerId << " has " << p.territories.size() << " territories and an empty Hand.\n";
	}

	return out;
}

vector<Territory*> &Player::getOwnedTerritories() {
	return territories;
}

void Player::setOwnedTerritories(vector<Territory*> &list) {
	territories = list;
}

void Player::updatePhase(int phaseNumber)
{
	if (phaseNumber == 1) {
		cout << "[Player " << playerId << " at Reinforcement Phase (1)]" << endl;
		cout << "Armies: " << getNumberOfArmies() << ", Cards: " << getHand()->totalCards(getHand()) << ", Countries Owned: " << getOwnedTerritories().size() << endl;
		cout << "Territories\t\t\t\t# Armies" << endl; //each tab is 8 characters of space, 8*4 = 32
		cout << "**********************************************************" << endl;
		for (int i = 0; i < getOwnedTerritories().size(); i++) {
			cout << left << setw(32) << setfill(' ') << getOwnedTerritories().at(i)->getName() << left << setw(32) << setfill(' ') << getOwnedTerritories().at(i)->getArmyCount() << endl;
		}
		cout << endl;
	}
	else if (phaseNumber == 2) {
		std::cout << "[Player " << playerId << " at Order Phase (2)]" << endl;
		cout << "Territories\t\t\t\t# Armies" << endl;
		cout << "**********************************************************" << endl;
		for (int i = 0; i < getOwnedTerritories().size(); i++) {
			std::cout << std::left << setw(32) << setfill(' ') << getOwnedTerritories().at(i)->getName() << left << setw(32) << setfill(' ') << getOwnedTerritories().at(i)->getArmyCount() << endl;
		}
		cout << endl;
	}
	else{
		cout << "[Player " << playerId << " at Order Execution Phase (3)]" << endl;
		cout << "Territories\t\t\t\t # Armies" << endl;
		cout << "**********************************************************" << endl;
		for (int i = 0; i < getOwnedTerritories().size(); i++) {
			cout << left << setw(32) << setfill(' ') << getOwnedTerritories().at(i)->getName() << left << setw(32) << setfill(' ') << getOwnedTerritories().at(i)->getArmyCount() << endl;
		}
		cout << endl;
	}
}

//Outputs the statistics of the game 
void Player::updateGame(int totalTerritories)
{
	int currentTerritories = getOwnedTerritories().size();
	double percent = 0.0;
	if (totalTerritories > 0)
	{
		percent = (static_cast<double>(currentTerritories) / totalTerritories) * 100;
	}

	if (percent > 80.0)
	{
		std::cout << "Watch out! Player " << playerId << " owns " << percent << "% of the territories" << std::endl;
	}else if(percent == 100.0){
		std::cout << "Winner winner, chicken dinner ~ Player " << playerId << "has won the game by owning all territories." << std::endl;
	}
	else
	{
		std::cout << "Player " << playerId << " owns " << percent << "% of the territories" << std::endl;
	}
}
