//============================================================================
// Name        : Order.h
// Author      : Aryamann Mehra (40127106)
// Description : Order header class.
//============================================================================

#pragma once

#include <string>
#include <iostream>
#include <list>

using std::ostream;
using std::istream;
using std::list;

class Order
{
protected:
	/*Since not much is known about the execution of every order, the name and description is what is stored every order, along with whether or not it has
	been executed. These properties are common to all orders and hence they're stored in the base class.*/
	std::string name;
	std::string description;
	bool executed;
	bool isvalid;//Since we do not know implementation details of individual orders, this value is included so that we can manually specify if an order is valid or not, for testing purposes.
public:
	virtual bool validate();//only relies on isvalid for now. This has been overloaded for all child classes.
	virtual void execute();//checks whether an order is valid or not, and executes it if it is. This has been overloaded for all child classes.
	virtual void execute(int n);//To print the orders in sequence, and index each order, this takes an int value to print the index of that order. This has been overloaded for all child classes.
	Order(std::string name, std::string desc);//The constructor called by all the child classes' default constructor
	friend ostream& operator<<(ostream&, Order& o);
	Order();
	void setValidity(bool s);//We can use this to set validity outside the Order classes.
	Order* operator = (Order& o);
	Order(const Order& o);//Copy constructor providing deep copy.
	virtual Order* getNew();//Similar to clone in Java, this creates a new object of the calling order and returns a pointer to it, being independent (deep copy) of the calling object. This has been overloaded for all child classes.


};
class Deploy : public Order
{

public:
	bool validate();
	void execute();
	void execute(int n);
	Deploy();
	Deploy(const Deploy& d);
	Deploy* getNew();
};
class Advance : public Order
{

public:
	bool validate();
	void execute();
	void execute(int n);
	Advance();
	Advance(const Advance& a);
	Advance* getNew();
};
class Bomb : public Order
{

public:
	bool validate();
	void execute();
	void execute(int n);
	Bomb();
	Bomb(const Bomb& b);
	Bomb* getNew();
};
class Blockade : public Order
{

public:
	bool validate();
	void execute();
	void execute(int n);
	Blockade();
	Blockade(const Blockade& bl);
	Blockade* getNew();
};
class Airlift : public Order
{

public:
	bool validate();
	void execute();
	void execute(int n);
	Airlift();
	Airlift(const Airlift& a);
	Airlift* getNew();
};
class Negotiate : public Order
{
public:
	bool validate();
	void execute();
	void execute(int n);
	Negotiate();
	Negotiate(const Negotiate& n);
	Negotiate* getNew();
};
class OrderList
{
private:
	std::list <Order*> orders;//This is the core of the class, the list of Orders being stored.
public:
	OrderList(std::list<Order*>);
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
};
