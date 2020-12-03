////============================================================================
//// Name        : OrderDriver.cpp
//// Author      : Aryamann Mehra 
//// Description : Order driver class.
////============================================================================
//
//#include "Order.h"
//#include<iostream>
//#include "Map.h"
//int main()
//{
//	Player* p1;
//	Player* p2;
//
//	Territory* alabama = new Territory("Alabama");
//	Territory* boston = new Territory("Boston");
//	Territory* colorado = new Territory("Colorado");
//	Territory* delaware = new Territory("Delaware");
//
//	vector<Territory*> t1;
//	vector<Territory*> t2;
//
//	t1.push_back(alabama);
//	t1.push_back(boston);
//	t2.push_back(colorado);
//	t2.push_back(delaware);
//
//	Hand* hand_one = new Hand();
//	Hand* hand_two = new Hand();
//
//	p1 = new Player(t1, hand_one, 01);
//	p2 = new Player(t2, hand_two, 02);
//
//	boston->setArmyCount(5);
//	colorado->setArmyCount(5);
//	delaware->setArmyCount(5);
//	alabama->setOwner(p1);
//	boston->setOwner(p1);
//	colorado->setOwner(p2);
//	delaware->setOwner(p2);
//
//	vector<Territory*> p1_terr = p1->getOwnedTerritories();
//	vector<Territory*> p2_terr = p2->getOwnedTerritories();
//
//	int spy(2);
//	int bomb(2);
//	int reinforcement(2);
//	int blockade(2);
//	int airlift(2);
//	int diplomacy(2);
//
//	Deck* dp = new Deck(spy, bomb, reinforcement, blockade, airlift, diplomacy); //deck pointer
//
//	p1->numOfArmies = 5;
//	p2->numOfArmies = 5;
//
//	std::cout << "Player 1's territories:\n";
//	vector <Territory*> myvec = p1->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		std::cout << thisTer->getName() << std::endl;
//	}
//
//	std::cout << "\nPlayer 2's territories:\n";
//	myvec = p2->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		std::cout << thisTer->getName() << std::endl;
//	}
//
//	Order* o1 = new Deploy(4, alabama, p1);
//
//	/***		Showing Deploy			***/
//	std::cout << "\n--- DEPLOY: Player 1 deploys 4 armies to Alabama ---" << endl;
//	alabama->setArmyCount(5);
//	std::cout << "BEFORE: Player 1's reinforcement pool: " << p1->numOfArmies;
//	std::cout << "\nBEFORE: Alabama armies: " << alabama->getArmyCount();
//	o1->execute();
//	std::cout << "\nAFTER: Player 1's reinforcement pool: " << p1->numOfArmies;
//	std::cout << "\nAFTER: Alabama armies: " << alabama->getArmyCount() << endl;
//
//	/***		Showing Advance	(DEFENCE)		***/
//	std::cout << "\n--- ADVANCE: Player 1 advances 4 armies from Boston to Alabama (friendly) ---" << endl;
//	Order* o2 = new Advance(boston, alabama, 4, p1, dp);
//	std::cout << "BEFORE: Boston armies: " << boston->getArmyCount();
//	std::cout << "\nBEFORE: Alabama armies: " << alabama->getArmyCount();
//	o2->execute();
//	std::cout << "\nAFTER: Boston armies: " << boston->getArmyCount();
//	std::cout << "\nAFTER: Alabama armies: " << alabama->getArmyCount() << endl << endl;
//
//	/***		Showing Advance	(OFFENCE)		***/  
//	std::cout << "--- ADVANCE: Player 1 advances 6 armies from Alabama to Colorado (ememy) ---";
//	Order* o3 = new Advance(alabama, colorado, 6, p1, dp);
//	std::cout << "\nBEFORE: Alabama armies: " << alabama->getArmyCount();
//	std::cout << "\nBEFORE: Colorado armies: " << colorado->getArmyCount();
//	o3->execute();
//
//	std::cout << "Player " << colorado->getOwner()->playerId << " occupies Colorado." << "\nAFTER: Armies left in Colorado: " << colorado->getArmyCount() << "\n";
//	std::cout << "AFTER: Alabama armies: " << alabama->getArmyCount() << "\n";
//
//	std::cout << "\nPlayer 1's territories:\n";
//	myvec = p1->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		std::cout << thisTer->getName() << std::endl;
//	}
//
//	std::cout << "\nPlayer 2's territories:\n";
//	myvec = p2->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		std::cout << thisTer->getName() << std::endl;
//	}
//
//	/***		Showing Airlift			***/
//	std::cout << "\n--- AIRLIFT: Player 1 airlifts 4 armies from Boston to Alabama ---" << endl;
//	boston->setArmyCount(6);
//	Order* o4 = new Airlift(boston, alabama, 4, p1);
//
//	std::cout << "BEFORE: Boston armies: " << boston->getArmyCount();
//	std::cout << "\nBEFORE: Alabama armies: " << alabama->getArmyCount();
//	o4->execute();
//	std::cout << "\nAFTER: Boston armies: " << boston->getArmyCount();
//	std::cout << "\nAFTER: Alabama armies: " << alabama->getArmyCount();
//
//	/****		Showing Bomb			**/
//	std::cout << "\n\n--- BOMB: Player 2 bombs Player 1's Alabama ---";
//	Order* o5 = new Bomb(alabama, p2);
//	std::cout << "\nBEFORE: Alabama armies: " << alabama->getArmyCount();
//	o5->execute();
//	std::cout << "\nAFTER: Alabama armies: " << alabama->getArmyCount();
//
//	/****		Showing Blockade			**/
//	std::cout << "\n\n--- BLOCKADE: Player 2 bombs Player 1's Alabama ---";
//	vector<Territory*> t3;
//	Hand* hand_three = new Hand();
//	Player* neutral = new Player(t3, hand_three, -1);
//	Order* o6 = new Blockade(boston, p1, neutral);
//	std::cout << "\nBEFORE: Boston armies: " << boston->getArmyCount();
//	std::cout << "\nBEFORE: Boston owner: Player " << boston->getOwner()->playerId;
//	o6->execute();
//	std::cout << "\nAFTER: Boston armies: " << boston->getArmyCount();
//	std::cout << "\nAFTER: Boston owner: Player " << boston->getOwner()->playerId;
//
//	/****		Showing Negotiate		****/
//	std::cout << "\n\n--- NEGOTIATE: Player 1 negotiates with Player 2 ---\n";
//	Order* o7 = new Negotiate(p1, p2);
//	o7->execute();
//	Order* o8 = new Advance(boston, delaware, 1, p1, dp);
//	o8->execute();
//	std::cout << "\n";
//	Order* o9 = new Negotiate(p1, p1);
//	o9->execute();
//
//	/****		Deleting Pointers		****/
//	alabama = NULL;
//	boston = NULL;
//	colorado = NULL;
//	delaware = NULL;
//	p1 = NULL;
//	p2 = NULL;	
//	dp = NULL;
//	o1 = NULL;
//	o2 = NULL;
//	o3 = NULL;
//	o4 = NULL;
//	o5 = NULL;
//	o6 = NULL;
//	o7 = NULL;
//	o8 = NULL;
//	o9 = NULL;
//	neutral = NULL;
//	delete alabama;
//	delete boston;
//	delete colorado;
//	delete delaware;
//	delete p1;
//	delete p2;
//	delete dp;
//	delete o1;
//	delete o2;
//	delete o3;
//	delete o4;
//	delete o5;
//	delete o6;
//	delete o7;
//	delete o8;
//	delete o9;
//	delete neutral;
//
//	return 0;
//};