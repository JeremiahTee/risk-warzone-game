//============================================================================
// Name        : Player.cpp
// Author      : Jeremiah Tiongson (40055477)
// Description : Observer & Subject implementations
//============================================================================

#include "GameObservers.h"
#include <iostream>

Observer::Observer() {};

Observer::~Observer() {};

GamePhaseObserver::GamePhaseObserver() {};

GamePhaseObserver::~GamePhaseObserver() {};

GameStatisticsObserver::GameStatisticsObserver() {};

GameStatisticsObserver::~GameStatisticsObserver() {};

Subject::Subject()
{
	gamePhaseObsList = new list<GamePhaseObserver*>;
	gameStatsObsList = new list<GameStatisticsObserver*>;
}

Subject::~Subject()
{
	delete gamePhaseObsList;
	gamePhaseObsList = nullptr;
	delete gameStatsObsList;
	gameStatsObsList = nullptr;
}

void Subject::attachGamePhase(GamePhaseObserver* o)
{
	gamePhaseObsList->push_back(o);
}

void Subject::detachGamePhase(GamePhaseObserver* o)
{
	gamePhaseObsList->remove(o);
}

void Subject::attachGameStats(GameStatisticsObserver* o)
{
	gameStatsObsList->push_back(o);
}

void Subject::detachGameStats(GameStatisticsObserver* o)
{
	gameStatsObsList->remove(o);
}

void Subject::notifyPhase()
{
	std::list<GamePhaseObserver*>::iterator i = gamePhaseObsList->begin();

	for(; i != gamePhaseObsList->end(); ++i)
	{
		(*i)->updatePhase(phase);
	}
}

void Subject::notifyGame()
{
	std::list<GameStatisticsObserver*>::iterator i = gameStatsObsList->begin();
	std::cout << "Notifying game | Game Statistics Observer" << std::endl;

	for(; i != gameStatsObsList->end(); ++i)
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