//============================================================================
// Name        : Player.cpp
// Author      : Jeremiah Tiongson (40055477)
// Description : Observer & Subject class declarations
//============================================================================

#pragma once
#include <list>

using std::list;

class Observer
{
public:
	Observer();
	~Observer();
	virtual void updatePhase(int phaseInt) = 0;
	virtual void updateGame(int totalTerritories, bool isPlayerBeingRemoved) = 0;
};

class GamePhaseObserver
{
public:
	GamePhaseObserver();
	~GamePhaseObserver();
	virtual void updatePhase(int phaseInt) = 0;
};

class GameStatisticsObserver
{
public:
	GameStatisticsObserver();
	~GameStatisticsObserver();
	virtual void updateGame(int totalTerritories, bool isPlayerBeingRemoved) = 0;
};

class Subject
{
public:
	virtual void attachGamePhase(GamePhaseObserver* o);
	virtual void detachGamePhase(GamePhaseObserver* o);
	virtual void attachGameStats(GameStatisticsObserver* o);
	virtual void detachGameStats(GameStatisticsObserver* o);
	virtual void notifyPhase();
	virtual void notifyGame();
	virtual void setPhase(int& phase);
	virtual void setTerritoriesCount(int totalTerr);
	virtual void setIsPlayerBeingRemoved(bool isPlayerBeingRemoved);
	Subject();
	~Subject();
private:
	std::list<GamePhaseObserver*> *gamePhaseObsList;
	std::list<GameStatisticsObserver*> *gameStatsObsList;
	int phase;
	int totalTerritories;
	bool isPlayerBeingRemoved;
};