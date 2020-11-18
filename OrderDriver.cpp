////============================================================================
//// Name        : OrderDriver.cpp
//// Author      : Aryamann Mehra (40127106)
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
//
//	vector<Territory*> t1;
//	vector<Territory*> t2;
//
//
//
//
//	t1.push_back(alabama);
//	t1.push_back(boston);
//	t2.push_back(colorado);
//	t2.push_back(delaware);
//
//
//
//	Hand* h1 =new Hand(); //empty hand, will test P2's hand for features
//	Hand* hand_one = h1;
//
//	Hand* hand_two = new Hand(1, 2, 3, 4, 5, 6); //valid hand pointer with actual values for P2
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
//	cout << "------------ GETTER: getTerritories() -------------- \n";
//	//cout << "Player 1's territories:\n";
//
//	/*for (auto it = p1_terr.begin(); it != p1_terr.end(); ++it)
//	{
//		Territory* thisTer = it;
//		cout << thisTer->getName() << std::endl;
//	}
//
//	cout << "\nPlayer 2's territories:\n";
//
//	for (auto it = p2_terr.begin(); it != p2_terr.end(); ++it)
//	{
//		Territory* thisTer = it;
//		cout << thisTer->getName() << std::endl;
//	}
//
//	vector<Territory*> p1_terr_to_attack = p1->toAttack();
//	vector<Territory*> p2_terr_to_defend = p2->toDefend();
//
//
//
//
//
//	cout << "\n------------ Creating Deck in order to test functionalities -------------- \n";
//
//	int spy(1);
//	int bomb(2);
//	int reinforcement(3);
//	int blockade(4);
//	int airlift(5);
//	int diplomacy(6);
//
//	Deck* dp = new Deck(spy, bomb, reinforcement, blockade, airlift, diplomacy); //deck pointer
//
//	for (int i = 0; i < 7; i++)
//	{
//		int cardType(0);
//		cardType = dp->draw(dp);
//		hand_two->addToHand(cardType, hand_two);
//	}
//
//	cout << "\n------------ Printing out Deck in order to test ostream functionality -------------- \n";
//
//	//cout << *dp;
//
//	cout << "\n------------ Printing out Hand in order to test ostream functionality -------------- \n";
//
//	//cout << *hand_two;
//
//	cout << "\n------------ Printing out Player 2 to show ostream functionality -------------- \n";
//
//	*/
//
//
//	p1->numOfArmies = 5;
//	p2->numOfArmies = 5;
//
//
//	Order* o1 = new Deploy(4, alabama, p1);
//
//	/****		Showing Deploy			**/
//	alabama->setArmyCount(5);
//	std::cout << "Player1 armies before: " << p1->numOfArmies;
//	std::cout << "\nTerritory armies before: " << alabama->getArmyCount();
//	o1->execute();
//	std::cout << "\nPlayer1 armies after: " << p1->numOfArmies;
//	std::cout << "\nTerritory armies after : " << alabama->getArmyCount();
//	/****		Showing Deploy			**/
//	std::cout << "\n\n\n";
//	/****		Showing Advance	(DEFENCE)		**/
//	Order* o6 = new Advance(boston,alabama,4,p1);
//	std::cout << "\nBoston armies before: " << boston->getArmyCount();
//	std::cout << "\nAlabama armies before: " << alabama->getArmyCount();
//	o6->execute();
//	std::cout << "\nBoston armies before: " << boston->getArmyCount();
//	std::cout << "\nAlabama armies before: " << alabama->getArmyCount();
//	/****		Showing Advance			**/
//	std::cout << "\n\n\n";
//	cout << "Player 1's territories:\n";
//
//
//
//	vector <Territory*> myvec = p1->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		cout << thisTer->getName() << std::endl;
//	}
//
//	cout << "\nPlayer 2's territories:\n";
//	 myvec = p2->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		cout << thisTer->getName() << std::endl;
//	}
//	std::cout << "\n\n\n";
//
//
//	/****		Showing Advance	(OFFENCE)		**/
//	Order* o7 = new Advance(alabama, colorado, 6, p1);
//	std::cout << "\nAlabama armies before: " << alabama->getArmyCount();
//	std::cout << "\nColorado armies before: " << colorado->getArmyCount()<<endl;
//	o7->execute();
//	std::cout <<" "<<colorado->getOwner()->playerId << "\nArmies left after: " << colorado->getArmyCount() << "\n\n";
//	
//	std::cout << "\Alabama armies after: " << alabama->getArmyCount()<<"\n\n";
//
//
//	myvec = p1->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		cout << thisTer->getName() << std::endl;
//	}
//
//	cout << "\nPlayer 2's territories:\n";
//	myvec = p2->getTerritories2();
//	for (auto it = myvec.begin(); it != myvec.end(); ++it)
//	{
//		Territory* thisTer = *it;
//		cout << thisTer->getName() << std::endl;
//	}
//	/****		Showing Advance			**/
//	std::cout << "\n\n\n";
//
//	/****		Showing Airlift			**/
//
//	//NOTE: Ask nora whether Airlift can be used to attack.
//
//	boston->setArmyCount(6);
//
//	Order* o2 = new Airlift(boston, alabama, 4, p1);
//
//	std::cout << "\nBoston armies before: " << boston->getArmyCount();
//	std::cout << "\nAlabama armies before: " << alabama->getArmyCount();
//
//	o2->execute();
//
//
//	std::cout << "\nBoston armies after : " << boston->getArmyCount();
//	std::cout << "\nAlabama armies after : " << alabama->getArmyCount();
//	/****		Showing Airlift			**/
//
//	std::cout << "\n\n\n";
//
//	/****		Showing Bomb			**/
//	Order* o3 = new Bomb(alabama, p2);
//	std::cout << "\nAlabama armies before: " << alabama->getArmyCount();
//
//
//	o3->execute();
//
//	std::cout << "\nAlabama armies after : " << alabama->getArmyCount();
//
//
//	/****		Showing Bomb			**/
//
//	std::cout << "\n\n\n";
//
//	/****		Showing Blockade			**/
//	vector<Territory*> t3;
//	Hand* hand_three = new Hand(1, 2, 3, 4, 5, 6);
//	Player* neutral = new Player(t3, hand_three, -1);
//
//	Order* o4 = new Blockade(boston, p1, neutral);
//	std::cout << "\nBoston armies before: " << boston->getArmyCount();
//	std::cout << "\nBoston owner before: " << boston->getOwner()->name;
//	o4->execute();
//	std::cout << "\nBoston armies before: " << boston->getArmyCount();
//	std::cout << "\nBoston owner before: " << boston->getOwner()->name;
//	/****		Showing Blockade			**/
//
//	std::cout << "\n\n\n";
//
//	/****		Showing Negotiate		****/
//	Order* o5 = new Negotiate(p1, p2);
//	o5->execute();
//	Order* o8 = new Advance(boston, delaware, 1, p1);
//	o8->execute();
//	/****		Showing Negotiate		****/
//
//	delete alabama;
//	delete boston;
//	delete colorado;
//	delete delaware;
//
//
//
//	return 0;
//};