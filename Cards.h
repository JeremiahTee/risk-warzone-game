﻿//====================================================================================
// Name        : Cards.h
// Author      : David Kim 
// Description : Cards header class containing definition for Deck and Hand classes.
//====================================================================================

#pragma once
using namespace std;

class Deck
{
private:
    int spy;                //Card Type 0
    int bomb;               //Card Type 1
    int reinforcement;      //Card Type 2
    int blockade;           //Card Type 3
    int airlift;            //Card Type 4
    int diplomacy;          //Card Type 5
public:
    Deck* operator= (Deck& d);
    Deck(const Deck& deck);
    Deck(int, int, int, int, int, int);
    int draw(Deck* d);
    int totalCards(Deck* d);
    void addToDeck(int);
    int getSpy();
    void setSpy(int);
    int getBomb();
    void setBomb(int);
    int getReinforcement();
    void setReinforcement(int);
    int getBlockade();
    void setBlockade(int);
    int getAirlift();
    void setAirlift(int);
    int getDiplomacy();
    void setDiplomacy(int);
};

class Hand
{
private:
    int spy;            // Card Type 0
    int bomb;           // Card Type 1
    int reinforcement;  // Card Type 2
    int blockade;       // Card Type 3
    int airlift;        // Card Type 4
    int diplomacy;      // Card Type 5
public:
    Hand* operator= (Hand& h);
    Hand() = default;
    Hand(const Hand& deck);
    Hand(int, int, int, int, int, int);
    void play(int);
    void addToHand(int, Hand* h);
    int totalCards(Hand* h);
    int getSpy();
    void setSpy(int);
    int getBomb();
    void setBomb(int);
    int getReinforcement();
    void setReinforcement(int);
    int getBlockade();
    void setBlockade(int);
    int getAirlift();
    void setAirlift(int);
    int getDiplomacy();
    void setDiplomacy(int);
};