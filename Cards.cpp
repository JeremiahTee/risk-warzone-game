//====================================================================================
// Name        : Cards.cpp
// Author      : David Kim (27151543)
// Description : Cards complation class.
//====================================================================================

#include <iostream>
#include <cstdlib>
#include <array>
#include "Cards.h"
using namespace std;

//ostream operator overloading
ostream& operator<< (ostream& os, Deck& d)
{
    os << "The deck has " << d.getSpy() << " spy cards, " << d.getBomb() << " bomb cards, " << d.getReinforcement() << " reinforcement cards, " << d.getBlockade() << " blockade cards, " << d.getAirlift() << " airlift cards and " << d.getDiplomacy() << " diplomacy cards." << endl;
    return os;
};

//assignment operator overloading
Deck* Deck::operator= (Deck& d)
{
    return new Deck(d);
}

//copy constructor
Deck::Deck(const Deck& deck)
{
    spy = deck.spy;
    bomb = deck.bomb;
    reinforcement = deck.reinforcement;
    blockade = deck.blockade;
    airlift = deck.airlift;
    diplomacy = deck.diplomacy;
};

//parameterized constructor
Deck::Deck(int s, int bo, int r, int bl, int a, int d)
{
    spy = s;
    bomb = bo;
    reinforcement = r;
    blockade = bl;
    airlift = a;
    diplomacy = d;
};

//randomly picks a card from Deck, remove it and return the type of card 
int Deck::draw(Deck* d)
{
    int nbOfCards(0);
    int randomNumber(0);
    int cardArray[6];
    int cardType(0);

    nbOfCards = d->totalCards(d);
    randomNumber = rand() % nbOfCards + 1;

    cardArray[0] = d->getSpy();
    cardArray[1] = d->getBomb();
    cardArray[2] = d->getReinforcement();
    cardArray[3] = d->getBlockade();
    cardArray[4] = d->getAirlift();
    cardArray[5] = d->getDiplomacy();

    for (int i = 0; i < sizeof(cardArray) / sizeof(cardArray[0]); i++)
    {
        randomNumber -= cardArray[i];
        if (randomNumber > 0)
        {
            continue;
        }
        else
        {
            cardType = i;
            break;
        }
    }

    switch (cardType)
    {
    case 0:
        cout << "The player drew a Spy card." << endl;
        d->setSpy(d->getSpy() - 1);
        break;
    case 1:
        cout << "The player drew a Bomb card." << endl;
        d->setBomb(d->getBomb() - 1);
        break;
    case 2:
        cout << "The player drew a Reinforcement card." << endl;
        d->setReinforcement(d->getReinforcement() - 1);
        break;
    case 3:
        cout << "The player drew a Blockade card." << endl;
        d->setBlockade(d->getBlockade() - 1);
        break;
    case 4:
        cout << "The player drew a Airlift card." << endl;
        d->setAirlift(d->getAirlift() - 1);
        break;
    case 5:
        cout << "The player drew a Diplomacy card." << endl;
        d->setDiplomacy(d->getDiplomacy() - 1);
        break;
    }

    return cardType;
};

//add card to the deck
void Deck::addToDeck(int i)
{
    if (i == 0)
    {
        setSpy(getSpy() + 1);
    }
    else if (i == 1)
    {
       setBomb(getBomb() + 1);
    }
    else if (i == 2)
    {
        setReinforcement(getReinforcement() + 1);
    }
    else if (i == 3)
    {
        setBlockade(getBlockade() + 1);
    }
    else if (i == 4)
    {
        setAirlift(getAirlift() + 1);
    }
    else if (i == 5)
    {
        setDiplomacy(getDiplomacy() + 1);
    }
};

//returns total amount of cards in the current deck
int Deck::totalCards(Deck* d)
{
    int sum(0);
    sum += d->getSpy();
    sum += d->getBomb();
    sum += d->getReinforcement();
    sum += d->getBlockade();
    sum += d->getAirlift();
    sum += d->getDiplomacy();
    return sum;
};

int Deck::getSpy()
{
    return spy;
};

void Deck::setSpy(int nb)
{
    spy = nb;
};

int Deck::getBomb()
{
    return bomb;
};

void Deck::setBomb(int nb)
{
    bomb = nb;
};

int Deck::getReinforcement()
{
    return reinforcement;
};

void Deck::setReinforcement(int nb)
{
    reinforcement = nb;
};

int Deck::getBlockade()
{
    return blockade;
};

void Deck::setBlockade(int nb)
{
    blockade = nb;
};

int Deck::getAirlift()
{
    return airlift;
};

void Deck::setAirlift(int nb)
{
    airlift = nb;
};

int Deck::getDiplomacy()
{
    return diplomacy;
};

void Deck::setDiplomacy(int nb)
{
    diplomacy = nb;
};

//ostream operator overloading
ostream& operator<< (ostream& os, Hand& h)
{
    os << "The hand has " << h.getSpy() << " spy cards, " << h.getBomb() << " bomb cards, " << h.getReinforcement() << " reinforcement cards, " << h.getBlockade() << " blockade cards, " << h.getAirlift() << " airlift cards and " << h.getDiplomacy() << " diplomacy cards." << endl;
    return os;
};

//assignment operator overloading
Hand* Hand::operator= (Hand& h)
{
    return new Hand(h);
}

//copy constructor
Hand::Hand(const Hand& hand)
{
    spy = hand.spy;
    bomb = hand.bomb;
    reinforcement = hand.reinforcement;
    blockade = hand.blockade;
    airlift = hand.airlift;
    diplomacy = hand.diplomacy;
};

//parameterized constructor
Hand::Hand(int s, int bo, int r, int bl, int a, int d)
{
    spy = s;
    bomb = bo;
    reinforcement = r;
    blockade = bl;
    airlift = a;
    diplomacy = d;
};

//Create Order of card type, add order to orderlist and remove card from hand
void Hand::play(int cardType)
{
    switch (cardType)
    {
    case 0:
       setSpy(getSpy() - 1);
        cout << "A Spy card has been played and removed from your hand." << endl;
        break;
    case 1:
        setBomb(getBomb() - 1);
        cout << "A Bomb card has been played and removed from your hand." << endl;
        break;
    case 2:
        setReinforcement(getReinforcement() - 1);
        cout << "A Reinforcement card has been played and removed from your hand." << endl;
        break;
    case 3:
        setBlockade(getBlockade() - 1);
        cout << "A Blockade card has been played and removed from your hand." << endl;
        break;
    case 4:
       setAirlift(getAirlift() - 1);
        cout << "A Airlift card has been played and removed from your hand." << endl;
        break;
    case 5:
        setDiplomacy(getDiplomacy() - 1);
        cout << "A Diplomacy card has been played and removed from your hand." << endl;
        break;
    }
};

//Adds card to hand
void Hand::addToHand(int i, Hand* h)
{
    if (i == 0)
    {
        h->setSpy(h->getSpy() + 1);
    }
    else if (i == 1)
    {
        h->setBomb(h->getBomb() + 1);
    }
    else if (i == 2)
    {
        h->setReinforcement(h->getReinforcement() + 1);
    }
    else if (i == 3)
    {
        h->setBlockade(h->getBlockade() + 1);
    }
    else if (i == 4)
    {
        h->setAirlift(h->getAirlift() + 1);
    }
    else if (i == 5)
    {
        h->setDiplomacy(h->getDiplomacy() + 1);
    }
};

int Hand::getSpy()
{
    return spy;
};

void Hand::setSpy(int nb)
{
    spy = nb;
};

int Hand::getBomb()
{
    return bomb;
};

void Hand::setBomb(int nb)
{
    bomb = nb;
};

int Hand::getReinforcement()
{
    return reinforcement;
};

void Hand::setReinforcement(int nb)
{
    reinforcement = nb;
};

int Hand::getBlockade()
{
    return blockade;
};

void Hand::setBlockade(int nb)
{
    blockade = nb;
};

int Hand::getAirlift()
{
    return airlift;
};

void Hand::setAirlift(int nb)
{
    airlift = nb;
};

int Hand::getDiplomacy()
{
    return diplomacy;
};

void Hand::setDiplomacy(int nb)
{
    diplomacy = nb;
};

int Hand::totalCards(Hand* h)
{
    int sum(0);
    sum += h->getSpy();
    sum += h->getBomb();
    sum += h->getReinforcement();
    sum += h->getBlockade();
    sum += h->getAirlift();
    sum += h->getDiplomacy();
    return sum;
}