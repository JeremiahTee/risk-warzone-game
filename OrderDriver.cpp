//============================================================================
// Name        : OrderDriver.cpp
// Author      : Aryamann Mehra (40127106)
// Description : Order driver class.
//============================================================================
/*
#include "Order.h"
#include<iostream>

int main()
{
	Order* o1 = new Deploy();
	Order* o2 = new Advance();
	Order* o3 = new Bomb();
	Order* o4 = new Blockade();
	Order* o5 = new Airlift();
	Order* o6 = new Negotiate();
	// Created one of every type of order

	Bomb b = Bomb();
	b.setValidity(true);//Since orders have not been implemented, here we manually specify that the order is valid so that we can test the general program behaviour.

	Order* o7 = &b;
	// Created an independant order of type bomb (to show it can be casted to Order* type).
	o1->setValidity(true);
	o2->setValidity(true);
	o3->setValidity(true);
	o5->setValidity(true);
	//Sets more orders to valid

	OrderList* mo = new OrderList();//Creating the object of OrderList.
	mo->add(o1);
	mo->add(o2);
	mo->add(o3);
	mo->add(o4);
	mo->add(o5);
	mo->add(o6);
	mo->add(o7);

	OrderList mo2object = *mo;//Create a deep copy of OrderList mo and store in mo2object

	OrderList* mo2 = &mo2object;//Create a pointer to this new object to use in the driver class, to show the working of deep copy

	std::cout << *mo;//print the contents of the mo list

	std::cout << "\n\n";
	mo2->move(1, 4);//Move objects in the deep copy of the list
	std::cout << *mo2;// Shows the changes to the list
	std::cout << "\n\n";
	mo2->remove(6);
	mo2->printlist();//Here the 6th order is removed and the list is printed to show changes
	std::cout << "\n\n";
	mo2->executeOrders();//Execute all valid orders in the mo2 list.
	std::cout << "\n\nThe list will now be printed after executing the orders\n\n";
	mo2->printlist();
	std::cout << "\n\nNow showing the original list to show that the original object is unaffected by the changes to copy list.\n\n";
	std::cout << *mo;//Prints original list
	return 0;
};
*/