#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
/*using std::ostream;
using std::istream;
using std::list;*/
using namespace std;

class Order
{
protected:
	std::string description;
	bool isvalid = false;
public:
	std::string name;
	bool executed = false;
	virtual bool validate() = 0;
	virtual void execute() = 0;
	//To print the orders in sequence, and index each order, this takes an int value to print the index of that order. This has been overloaded for all child classes.
	Order(std::string name, std::string desc);//The constructor called by all the child classes' default constructor
	//friend ostream& operator<<(ostream&, const Order& o);
	Order();
	void setValidity(bool s);//We can use this to set validity outside the Order classes.
	Order(const Order& o);//Copy constructor providing deep copy.
	//Similar to clone in Java, this creates a new object of the calling order and returns a pointer to it, being independent (deep copy) of the calling object. This has been overloaded for all child classes.
	friend ostream& operator << (ostream& out, Order& o);
};

class Deploy : public Order
{
public:
	bool validate();
	void execute();
	void print();
	int numArmies; Territory* t; Player* p;
	Deploy(int numArmies, Territory* t, Player* p);
	Deploy(const Deploy& d);
	Deploy* getNew();
};

class Advance : public Order
{
public:
	Territory* source; Territory* target; int numArmies; Player* p; Deck* d;
	bool validate();
	void execute();
	void print();
	Advance(Territory* source, Territory* target, int numArmies, Player* p, Deck* d);
	Advance(const Advance& a);
	Advance* getNew();
};

class Bomb : public Order
{

public:
	Territory* target; Player* p;
	bool validate();
	void execute();
	void print();
	Bomb(Territory* target, Player* p);
	Bomb(const Bomb& b);
	Bomb* getNew();
};

class Blockade : public Order
{
public:
	Territory* target; Player* p; Player* neutral;
	bool validate();
	void execute();
	void print();
	Blockade(Territory* target, Player* p, Player* neutral);
	Blockade(const Blockade& bl);
	Blockade* getNew();
};

class Airlift : public Order
{
public:
	Territory* source; Territory* target; int numArmies; Player* p;
	bool validate();
	void execute();
	void print();
	Airlift(Territory* source, Territory* target, int numArmies, Player* p);
	Airlift(const Airlift& a);
	Airlift* getNew();
};

class Negotiate : public Order
{
public:
	Player* source; Player* target;
	bool validate();
	void execute();
	Negotiate(Player* source, Player* targer);
	Negotiate(const Negotiate& n);
	Negotiate* getNew();
};

class OrderList
{
private:
	//This is the core of the class, the list of Orders being stored.
public:
	OrderList(std::list<Order*>);
	std::list <Order*> orders;
	OrderList();
	~OrderList();
	void move(int movefrom, int moveto); //Moves the order at the movefrom position, and places it in the position of the moveto position
	void add(Order* passed);//adds a new Order to the list, appending it to the back of the list (since orders are placed sequentially by default
	void printlist();
	void executeOrders();
	void remove(int n);//Removes the order at the nth position.
	OrderList(const OrderList& ol);//Copy constructor of OrderList returning deep copy of the OrderList.
	friend ostream& operator<<(ostream& os, OrderList& olist);//Prints out all the orders in the list
	OrderList& operator=(OrderList& olist);//Returns a pointer to a deep copy of the order on the R.H.S of the = sign.
	std::list<Order*> getOrders();
};

