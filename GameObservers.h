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
	~Observer();
	virtual void notifyPhase(int) = 0;
	virtual void notifyGame(int) = 0;
protected:
	Observer();
};

class Subject
{
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void updatePhase();
	virtual void updateGame();
	virtual void setPhase(int& phase);
	virtual void setTerritoriesCount(int totalTerr);
	Subject();
	~Subject();
private:
	std::list<Observer*>* _observers;
	int phase;
	int territories;
};