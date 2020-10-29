#pragma once
#include <list>

//Observer making use of pure virtual function

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
	virtual void setCountriesCount(int totalCountries);
	Subject();
	~Subject();
private:
	std::list<Observer*>* _observers;
	int phase;
	int countries;
};