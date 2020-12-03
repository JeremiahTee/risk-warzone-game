//====================================================================================
// Name        : Cards.cpp
// Author      : David Kim 
// Description : Driver class to test out Cards, Hand and Deck features. 
//====================================================================================
//
//#include <iostream>
//#include "Cards.h"
//#include "Order.h"
//
//using namespace std;
//
//int main()
//{
//    OrderList* ol = new OrderList();
//    int spy(0);
//    int bomb(0);
//    int reinforcement(0);
//    int blockade(0);
//    int airlift(0);
//    int diplomacy(0);
//    int length(0);
//
//    cout << "Please enter the number of spy cards for the deck: ";
//    cin >> spy;
//    cout << "Please enter the number of bomb cards for the deck: ";
//    cin >> bomb;
//    cout << "Please enter the number of reinforcement cards for the deck: ";
//    cin >> reinforcement;
//    cout << "Please enter the number of blockade cards for the deck: ";
//    cin >> blockade;
//    cout << "Please enter the number of airlift cards for the deck: ";
//    cin >> airlift;
//    cout << "Please enter the number of diplomacy cards for the deck: ";
//    cin >> diplomacy;
//    length = length + spy + bomb + reinforcement + blockade + airlift + diplomacy;
//
//    Deck* dp = new Deck(spy, bomb, reinforcement, blockade, airlift, diplomacy); //deck pointer
//    Hand* hp = new Hand(0, 0, 0, 0, 0, 0); //hand pointer
//
//    for (int i = 0; i < length; i++)
//    {
//        int cardType(0);
//        cardType = dp->draw(dp);
//        hp->addToHand(cardType, hp);
//    }
//
//    if (hp->getSpy() > 0)
//    {
//        int count = hp->getSpy();
//        for (int i = 0; i < count; i++)
//        {
//            hp->play(0, hp);
//            dp->addToDeck(0, dp);
//        }
//    }
//
//    if (hp->getBomb() > 0)
//    {
//        int count = hp->getBomb();
//        for (int i = 0; i < count; i++)
//        {
//            hp->play(1, hp);
//            dp->addToDeck(1, dp);
//            Order* o = new Bomb();
//            ol->add(o);
//        }
//    }
//
//    if (hp->getReinforcement() > 0)
//    {
//        int count = hp->getReinforcement();
//        for (int i = 0; i < count; i++)
//        {
//            hp->play(2, hp);
//            dp->addToDeck(2, dp);
//        }
//    }
//
//    if (hp->getBlockade() > 0)
//    {
//        int count = hp->getBlockade();
//        for (int i = 0; i < count; i++)
//        {
//            hp->play(3, hp);
//            dp->addToDeck(3, dp);
//            Order* o = new Blockade();
//            ol->add(o);
//        }
//    }
//
//    if (hp->getAirlift() > 0)
//    {
//        int count = hp->getAirlift();
//        for (int i = 0; i < count; i++)
//        {
//            hp->play(4, hp);
//            dp->addToDeck(4, dp);
//            Order* o = new Airlift();
//            ol->add(o);
//        }
//    }
//
//    if (hp->getDiplomacy() > 0)
//    {
//        int count = hp->getDiplomacy();
//        for (int i = 0; i < count; i++)
//        {
//            hp->play(5, hp);
//            dp->addToDeck(5, dp);
//        }
//    }
//
//    cout << *dp;
//    cout << *hp;
//    cout << *ol;
//
//    delete ol;
//    delete dp;
//    delete hp;
//
//    return 0;
//}