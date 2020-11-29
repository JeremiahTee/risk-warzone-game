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

//Returns the hand if it has a valid pointer to it
Hand* Player::getHand()
{
	return hand;
}

OrderList* Player::getOrderList() {
	return orders;
}

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
void Player::updateGame(int totalTerritories, bool isPlayerBeingRemoved)
{
	//First check is a player has been removed
	if (!isPlayerBeingRemoved)
	{
		int currentTerritories = getOwnedTerritories().size();
		double percent = 0.0;
		if (totalTerritories > 0)
		{
			percent = (static_cast<double>(currentTerritories) / totalTerritories) * 100;
		}

		if (percent > 80.0)
		{
			cout << "Watch out! Player " << playerId << " owns " << percent << "% of the territories" << endl;
		}
		else if (percent == 100.0) { //Announce when a player has won
			cout << "Winner winner, chicken dinner ~ Player " << playerId << "has won the game by owning all territories." << endl;
		}
		else
		{
			cout << "Player " << playerId << " owns " << percent << "% of the territories" << endl;
		}
	}else //Announce when a player has been removed 
	{
		cout << "Player " << playerId << " has been removed.";
	}
}
