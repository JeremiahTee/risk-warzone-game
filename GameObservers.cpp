//============================================================================
// Name        : Player.cpp
// Author      : Jeremiah Tiongson (40055477)
// Description : Observer & Subject implementations
//============================================================================

#include "GameObservers.h"
#include <iostream>

Observer::Observer() {};

Observer::~Observer() {};

Subject::Subject()
{
	observersList = new list<Observer*>;
}
Subject::~Subject()
{
	delete observersList;
	observersList = nullptr;
}
void Subject::attach(Observer* o)
{
	observersList->push_back(o);
}
void Subject::detach(Observer* o)
{
	observersList->remove(o);
}

void Subject::notifyPhase()
{
	std::list<Observer*>::iterator i = observersList->begin();

	for(; i != observersList->end(); ++i)
	{
		(*i)->updatePhase(phase);
	}
}

void Subject::notifyGame()
{
	std::list<Observer*>::iterator i = observersList->begin();
	std::cout << "Notifying game | Game Statistic Observer" << std::endl;

	for(; i != observersList->end(); ++i)
	{
		(*i)->updateGame(totalTerritories, isPlayerBeingRemoved);
	}
}

void Subject::setPhase(int& phase)
{
	this->phase = phase;
}

void Subject::setTerritoriesCount(int terrCount)
{
	this->totalTerritories = terrCount;
}

void Subject::setIsPlayerBeingRemoved(bool isPlayerBeingRemoved)
{
	this->isPlayerBeingRemoved = isPlayerBeingRemoved;
}