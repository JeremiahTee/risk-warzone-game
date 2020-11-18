//============================================================================
// Name        : Order.cpp
// Author      : Aryamann Mehra (40127106)
// Description : Order compilation unit class.
//============================================================================

#include "Order.h"
#include <iostream>

Order::Order(std::string nm, std::string desc)
{
	name = nm.c_str();//c_str is called to make sure the string is deep copied.
	description = desc.c_str();
	executed = false;//by default, this value is set to false, as each order has not been executed when it is created.
};
Order::Order(const Order& o)
{
	name = o.name.c_str();
	description = o.description.c_str();
	executed = o.executed;
	isvalid = o.isvalid;
};
Order* Order:: operator = (Order& o)
{
	return o.getNew();
};
void Order::execute()
{

};
void Order::execute(int n)
{

};
bool Order::validate()
{
	return false;
};
Order* Order::getNew()
{
	return new Order(*this);
};

Deploy::Deploy() : Order("Deploy", "place some armies on one of the current player's territories. ")
{

};
Deploy::Deploy(const Deploy& d) : Order((Order&)d)
{
	std::cout << "\nDeploy created!\n\n";
};


bool Deploy::validate()
{

	if (isvalid == true)
	{
		return true;
	};
	return false;
};
void Deploy::execute()
{
	if (validate() == true)
	{
		executed = true;
	}
};
void Deploy::execute(int n)
{
	if (validate() == true)
	{
		executed = true;
		std::cout << "Validated and executed order number " << n << ", Name: " << name << ".\n";
	}
};
Deploy* Deploy::getNew()
{
	return new Deploy(*this);
};
ostream& operator << (ostream& out, Order& o)
{

	out << "Order: " << o.name << " | Description: " << o.description;
	if (o.executed)
	{
		out << "\n\nThis order was executed successfully.\n";
	}
	else {
		out << "\n";
	};

	return out;
}
void Order::setValidity(bool s)
{
	isvalid = s;
};

Advance::Advance() : Order("Advance", "move some armies from one of the current player's territories (source) to an adjacent territory (target).If the target territory belongs to the current player, the armies are moved to the target territory.If the target territory belongs to another player, an attack happens between the two territories. ")
{

};
Advance::Advance(const Advance& a) : Order((Order&)a)
{

};
bool Advance::validate()
{

	if (isvalid == true)
	{
		return true;
	};
	return false;
};
void Advance::execute()
{
	if (validate() == true)
	{
		executed = true;

	}
};
void Advance::execute(int n)
{
	if (validate() == true)
	{
		executed = true;
		std::cout << "Validated and executed order number " << n << ", Name: " << name << ".\n";
	}
};
Advance* Advance::getNew()
{
	return new Advance(*this);
};


Bomb::Bomb() : Order("Bomb", "destroy half of the armies located on an opponent's territory that is adjacent to one of the current player’s territories.")
{

};

Bomb::Bomb(const Bomb& b) : Order((Order&)b)
{

};
bool Bomb::validate()
{

	if (isvalid == true)
	{
		return true;
	};
	return false;
};
void Bomb::execute()
{
	if (validate() == true)
	{
		executed = true;

	}
};
void Bomb::execute(int n)
{
	if (validate() == true)
	{
		executed = true;
		std::cout << "Validated and executed order number " << n << ", Name: " << name << ".\n";
	}
};
Bomb* Bomb::getNew()
{
	return new Bomb(*this);
};


Blockade::Blockade() : Order("Blockade", "triple the number of armies on one of the current player's territories and make it a neutral territory.")
{

};
Blockade::Blockade(const Blockade& bl) : Order(bl.name, bl.description)
{

};
bool Blockade::validate()
{

	if (isvalid == true)
	{
		return true;
	};
	return false;
};
void Blockade::execute()
{
	if (validate() == true)
	{
		executed = true;

	}
};
void Blockade::execute(int n)
{
	if (validate() == true)
	{
		executed = true;
		std::cout << "Validated and executed order number " << n << ", Name: " << name << ".\n";
	}
};
Blockade* Blockade::getNew()
{
	return new Blockade(*this);
};


Airlift::Airlift() : Order("Airlift", "advance some armies from one of the current player's territories to any another territory.")
{

};
Airlift::Airlift(const Airlift& al) : Order((Order&)al)
{

};
bool Airlift::validate()
{

	if (isvalid == true)
	{
		return true;
	}
	else {
		return false;
	};
};
void Airlift::execute()
{
	if (validate() == true)
	{
		executed = true;

	}
};
void Airlift::execute(int n)
{
	if (validate() == true)
	{
		executed = true;
		std::cout << "Validated and executed order number " << n << ", Name: " << name << ".\n";
	}
};
Airlift* Airlift::getNew()
{
	return new Airlift(*this);
};


Negotiate::Negotiate() : Order("Negotiate", "prevent attacks between the current player and another player until the end of the turn")
{


};

Negotiate::Negotiate(const Negotiate& n) : Order((Order&)n)
{

};
bool Negotiate::validate()
{

	if (isvalid == true)
	{
		return true;
	};
	return false;
};
void Negotiate::execute()
{
	if (validate() == true)
	{
		executed = true;

	}
};
void Negotiate::execute(int n)
{
	if (validate() == true)
	{
		executed = true;
		std::cout << "Validated and executed order number " << n << ", Name: " << name << ".\n";
	}
};
Negotiate* Negotiate::getNew()
{
	return new Negotiate(*this);
};



OrderList::OrderList()
{

};
void OrderList::add(Order* passed)
{
	orders.push_back(passed);
};
void OrderList::move(int movefrom, int moveto)
{
	int count = 0;
	Order* tomove;
	if (moveto == orders.size())
	{
		for (auto looper = orders.begin(); looper != orders.end(); ++looper)
		{
			++count;
			if (count == movefrom)
			{

				tomove = *looper;
				orders.remove(*looper);
				break;

			};
		};
		orders.push_back(tomove);
	}
	else {

		for (auto looper = orders.begin(); looper != orders.end(); ++looper)
		{
			++count;
			if (count == movefrom)
			{

				tomove = *looper;
				orders.remove(*looper);
				break;

			};
		};

		count = 0;
		for (auto looper = orders.begin(); looper != orders.end(); ++looper)
		{
			++count;

			if (count == moveto)
			{
				orders.insert(looper, 1, tomove);
			};

		};
	};
};
void OrderList::printlist()
{
	int count = 0;
	for (auto looper = orders.begin(); looper != orders.end(); ++looper)
	{
		std::cout << ++count << " : " << **looper << "\n";
	};
};
void OrderList::remove(int n)
{
	int count = 0;
	for (auto looper = orders.begin(); looper != orders.end(); ++looper)
	{
		++count;
		if (count == n)
		{
			Order* x = *looper;
			orders.erase(looper);
			delete x;
			break;
		};
	};
};
void OrderList::executeOrders()
{
	int count = 0;
	for (auto looper = orders.begin(); looper != orders.end(); ++looper)
	{
		++count;
		Order* x = *looper;


		x->execute(count);
	};
};
OrderList::OrderList(const OrderList& ol)
{

	for (auto looper = ol.orders.begin(); looper != ol.orders.end(); ++looper)
	{
		Order* x = *looper;
		orders.push_back(x->getNew());
	};
};
ostream& operator<<(ostream& os, OrderList& olist)
{
	int count = 0;
	for (auto looper = olist.orders.begin(); looper != olist.orders.end(); ++looper)
	{
		os << ++count << " : " << **looper << "\n";
	};
	return os;
};

OrderList& OrderList::operator=(OrderList& o)
{
	OrderList p = OrderList(o);
	return  p;
};