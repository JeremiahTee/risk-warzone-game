//============================================================================
// Name        : Player.cpp
// Author      : Jeremiah Tiongson
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

class Subject
{
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notifyPhase();
	virtual void notifyGame();
	virtual void setPhase(int& phase);
	virtual void setTerritoriesCount(int totalTerr);
	virtual void setIsPlayerBeingRemoved(bool isPlayerBeingRemoved);
	Subject();
	~Subject();
private:
	std::list<Observer*>* observersList;
	int phase;
	int totalTerritories;
	bool isPlayerBeingRemoved;
};