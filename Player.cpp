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

//assignment operator overloading
Player* Player:: operator = (Player& p)
{
	return p.getNew();
}

Player::~Player() {
	for (auto territory : territories) {
		territory->setOwner(NULL);
	}
	
	delete hand;
	delete orders;
}
vector<Territory*> Player::getTerritories2()
{
	return territories;
}
//Shuffles the player's territories and removes the last two if the size is greater than 2
vector<Territory*> Player::toDefend()
{
	vector<Territory*> terr_toDefend = getOwnedTerritories();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(terr_toDefend.begin(), terr_toDefend.end(), g);

	//Remove last two territories
	if (terr_toDefend.size() > 2)
	{
		terr_toDefend.pop_back();
		terr_toDefend.pop_back();
	}

	return terr_toDefend;
}

//Shuffles the player's territories and removes the last territory is size is greater than 1
vector<Territory*> Player::toAttack()
{
	vector<Territory*> terr_toAttack = getOwnedTerritories();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(terr_toAttack.begin(), terr_toAttack.end(), g);

	//Remove last two territories
	if (terr_toAttack.size() > 1)
	{
		terr_toAttack.pop_back();
	}

	return terr_toAttack;
}

//Issues a Bomb order and adds it to the Player's list of orders
/*void Player::issueOrder()
{
	Order* order = new Bomb();
	if (order != nullptr)
	{
		std::cout << "Bomb order successfully placed.\n\n";
		orders->add(order);
		//Print the list to verify that order is indeed in the list
		orders->printlist();
	}
}*/

//Returns the hand if it has a valid pointer to it
Hand* Player::getHand()
{
	return hand;
}

OrderList* Player::getOrderList() {
	return orders;
}

Player* Player::getNew()
{
	return new Player(*this);
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

vector<Territory*> Player::getOwnedTerritories() {
	return territories;
}

void Player::setOwnedTerritories(vector<Territory*> list) {
	territories = list;
}

void Player::notifyGame(int totalCountries)
{
	int currentTerritories = getOwnedTerritories().size();
	double percentage = 0.0;
	if (totalCountries > 0)
	{
		percentage = (currentTerritories / totalCountries) * 100;
	}

	if (percentage == 100.0)
	{
		std::cout << "Congratulations! Player " << playerId << " has " << percentage << "owns all territories." << std::endl;
	}
	else
	{
		std::cout << "Player " << playerId << " has " << percentage << "% of territories owned." << std::endl;
	}

}

void printPlayerTable(int phase)
{
	if (phase == 1) //Reinforcement phase
	{

	}
	else
	{

	}
}

void Player::notifyPhase(int phase)
{
	switch (phase)
	{
	case 1: std::cout << "Phase 1" << std::endl;
		break;
	case 2: std::cout << "Phase 2" << std::endl;
		break;
	case 3: std::cout << "Phase 3" << std::endl;
		break;
	}
}


//Setup Observer methods stuff here
//Update Player driver logic -> when creating player, give it random int as playerID