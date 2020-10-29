#include "GameObservers.h"
#include <iostream>

Observer::Observer() {};

Observer::~Observer() {};

Subject::Subject()
{
	_observers = new list<Observer*>;
}
Subject::~Subject()
{
	delete _observers;
	_observers = nullptr;
}
void Subject::attach(Observer* o)
{
	_observers->push_back(o);
}
void Subject::detach(Observer* o)
{
	_observers->remove(o);
}

void Subject::updatePhase()
{
	std::list<Observer*>::iterator i = _observers->begin();

	for(; i != _observers->end(); ++i)
	{
		(*i)->notifyPhase(phase);
	}
}

void Subject::updateGame()
{
	std::list<Observer*>::iterator i = _observers->begin();
	std::cout << "Notifying game | Game Statistic Observer" << std::endl;

	for(; i != _observers->end(); ++i)
	{
		(*i)->notifyGame(countries);
	}
}

void Subject::setPhase(int& phase)
{
	this->phase = phase;
}

void Subject::setCountriesCount(int amount)
{
	this->countries = amount;
}



