#include "Order.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector> 

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
Order::Order()
{
	name = "";
	description = "";
	executed = false;
	isvalid = false;
};
void Order::setValidity(bool s)
{
	isvalid = s;
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

//==================================================================================================================================================================

Deploy::Deploy(int numArmies1, Territory* t1, Player* p1) : Order("Deploy", "place some armies on one of the current player's territories. ")
{
	numArmies = numArmies1;//Change name to numArmiesAllocated throughout
	t = t1;
	p = p1;
	p->tempArmies -= numArmies1;
};
Deploy::Deploy(const Deploy& d) : Order((Order&)d)
{
	numArmies = d.numArmies;
	t = d.t;
	p = d.p;
};
bool Deploy::validate()
{
	if ((p->numOfArmies >= numArmies) && (p == t->getOwner()))
	{
		std::cout << "\nThe Deploy Order is valid.";
		setValidity(true);
		return true;
	}
	
	std::cout << "\nThe Deploy Order is invalid."<<endl;
	print();
	return false;
};
void Deploy::execute()
{
	if (validate() == true)
	{
		t->setArmyCount(t->getArmyCount() + numArmies);
		p->numOfArmies = p->numOfArmies - numArmies;
		executed = true;
		print();
	}
	else
	{
		executed = true;
	}
}
void Deploy::print()
{
	std::cout<< "\n--- DEPLOY: Player" << p->getPlayerID() <<" deploys "<< numArmies<<" armies to "<< t->getName() <<" ---" << endl;
}
void Advance::print()
{
	std::cout << "\n--- Advance: Player" << p->getPlayerID() << " advances " << numArmies << " armies to " << target->getName() << " ---" << endl;
}
;
Deploy* Deploy::getNew()
{
	return new Deploy(*this);
};

//==================================================================================================================================================================

Advance::Advance(Territory* source1, Territory* target1, int numArmies1, Player* p1, Deck* d1) : Order("Advance", "move some armies from one of the current player's territories (source) to an adjacent territory (target).If the target territory belongs to the current player, the armies are moved to the target territory.If the target territory belongs to another player, an attack happens between the two territories. ")
{
	source = source1;
	target = target1;
	
	numArmies = numArmies1;
	p = p1;
	d = d1;
};
bool Advance::validate()
{
	
	if ((source->getArmyCount() < numArmies) || (source->getOwner() != p) || (source->isNeighbor(source, target, 2)) || (p->isNegotiated(p, target->getOwner())))//third condition is adjacency of source & neighbour
	{
		if (p->isNegotiated(p, target->getOwner()))
		{
			std::cout << "Attack invalid due to active negotiate card.";
		}
		else 
		{
			std::cout << "\nThe Advance Order is invalid.";
			
		}
		return false;
	};
	std::cout << "\nThe Advance Order is valid.";
	setValidity(true);
	return true;
};
void Advance::execute()
{
	if (validate() == true)
	{
		print();
		if ((target->getOwner() == p))
		{
			source->setArmyCount(source->getArmyCount() - numArmies);
			target->setArmyCount(target->getArmyCount() + numArmies);
		}
		else
		{
			srand(time(NULL));
			int probattack;
			int probdefend;

			int attackingArmies = numArmies;
			int defendingArmies = target->getArmyCount();
			source->setArmyCount(source->getArmyCount() - numArmies);
			while ((attackingArmies != 0) && defendingArmies != 0)
			{
				probattack = rand() % 100 + 1;
				if ((probattack >= 1) && (probattack <= 60))
				{
					defendingArmies--;
				}
				if (defendingArmies == 0)
				{
					break;
				}
				probdefend = rand() % 100 + 1;
				if ((probdefend >= 1) && (probdefend <= 70))
				{
					attackingArmies--;
				}
			}
			if (attackingArmies == 0)
			{
				target->setArmyCount(defendingArmies);
				std::cout << "\nDefender Wins. ";
			}
			else
			{
				target->setArmyCount(attackingArmies);//Need to remove territory from Owner's vector & add to player vector.
				Player* defender = target->getOwner();

				int count = 0;
				vector<Territory*>::iterator looper;
				vector<Territory*> myvec = defender->getOwnedTerritories();
				for (looper = defender->getOwnedTerritories().begin(); looper != defender->getOwnedTerritories().end(); ++looper)
				{

					if (*looper == target)
					{

						break;
					};
					count++;
				};

				defender->territories.erase(looper);
				target->setOwner(p);
				p->territories.push_back(target);
				std::cout << "\nAttacker Wins. ";
				if (p->conqueredOne == false) 
				{
					int cardType(0);
					Hand* h = p->getHand();
					cardType = d->draw(d);
					p->getHand()->addToHand(cardType, h);//h.addtohand
					p->conqueredOne = true;
				}
			}
		}
		executed = true;
	}
	else
	{
		executed = true;
	}
};
Advance::Advance(const Advance& a) : Order((Order&)a)
{
	source = a.source;
	target = a.target;
	numArmies = a.numArmies;
	p = a.p;
	d = a.d;
};
Advance* Advance::getNew()
{
	return new Advance(*this);
};

//==================================================================================================================================================================

Bomb::Bomb(Territory* target1, Player* p1) //: Order("Bomb", "destroy half of the armies located on an opponent's territory that is adjacent to one of the current player’s territories.")
{
	target = target1;
	p = p1;
};
bool Bomb::validate()
{
	if ((target->getOwner() != p) && (!p->isNegotiated(p, target->getOwner())))
	{
		std::cout << "\nThe Bomb Order is valid.";
		setValidity(true);
		return true;
	};
	if (p->isNegotiated(p, target->getOwner()))
	{
		std::cout << "Attack invalid due to active negotiate card.";
	}
	
	return false;
};
void Bomb::print()
{
	std::cout << "\n--- Bomb: Player" << p->getPlayerID() << " bombs " << target->getName() << " ----get rekt" << endl;
}
void Bomb::execute()
{
	if (validate() == true)
	{
		target->setArmyCount(target->getArmyCount() / 2);
		executed = true;
	}
	else
	{
		executed = true;
	}
};
Bomb::Bomb(const Bomb& b) : Order((Order&)b)
{
	target = b.target;
	p = b.p;
};
Bomb* Bomb::getNew()
{
	return new Bomb(*this);
};

//==================================================================================================================================================================

Blockade::Blockade(Territory* target1, Player* p1, Player* neutral1) //: Order("Blockade", "triple the number of armies on one of the current player's territories and make it a neutral territory.")
{
	target = target1;
	p = p1;
	neutral = neutral1;
};
bool Blockade::validate()
{
	if ((target->getOwner() == p))
	{
		std::cout << "\nThe Blockade Order is valid.";
		setValidity(true);
		return true;
	};
	std::cout << "\nThe Blockade Order is invalid.";
	return false;
};
void Blockade::execute()
{
	if (validate() == true)
	{
		target->setArmyCount(target->getArmyCount() * 2);
		target->setOwner(neutral);
		int count = 0;
		auto looper = p->getOwnedTerritories().front();
		vector<Territory*>::iterator it = p->getOwnedTerritories().begin();
		vector<Territory*> myvec = p->getOwnedTerritories();
		for (it = myvec.begin(); it != myvec.end(); ++it)
		{
			if (*it == target)
			{
				break;
			};
			++count;
		};

		myvec.erase(myvec.begin() + count);//p->getTerritories2().begin()+count

		neutral->getOwnedTerritories().push_back(target);
	}
	else
	{
		executed = true;
	}
};
Blockade::Blockade(const Blockade& bl) : Order((Order&)bl)
{
	target = bl.target;
	p = bl.p;
	neutral = bl.neutral;
};
Blockade* Blockade::getNew()
{
	return new Blockade(*this);
};

//==================================================================================================================================================================

Airlift::Airlift(Territory* source1, Territory* target1, int numArmies1, Player* p1) {
	source = source1;
	target = target1;
	numArmies = numArmies1;
	p = p1;
};
bool Airlift::validate()
{
	if ((target->getOwner() == p) && (numArmies <= source->getArmyCount()) && (source->getOwner() == p))
	{
		std::cout << "\nThe Airlift Order is valid.";
		setValidity(true);
		return true;
	}
	std::cout << "\nThe Airlift Order is invalid.";
	return false;
};
void Airlift::execute()
{
	if (validate() == true)
	{
		source->setArmyCount(source->getArmyCount() - numArmies);
		target->setArmyCount(target->getArmyCount() + numArmies);
		print();
		executed = true;
	}
	else
	{
		cout << " invalid airlift " << endl;
		executed = true;
	}
};
void Airlift::print()
{
	std::cout << "\n--- Airlift: Player" << p->getPlayerID() << " airlifts " << numArmies << " armies from " << source->getName() <<" to " << target->getName() << endl;
}
Airlift::Airlift(const Airlift& a) : Order((Order&)a)
{
	source = a.source;
	target = a.target;
	numArmies = a.numArmies;
	p = a.p;
};
Airlift* Airlift::getNew()
{
	return new Airlift(*this);
};

//==================================================================================================================================================================

Negotiate::Negotiate(Player* source1, Player* target1) : Order("Negotiate", "prevent attacks between the current player and another player until the end of the turn")
{
	source = source1;
	target = target1;
};
Negotiate::Negotiate(const Negotiate& n) : Order((Order&)n)
{
	source = n.source;
	target = n.target;
};
bool Negotiate::validate()
{
	if (source != target)
	{
		std::cout << "The Negotiate Order is valid.\n";
		setValidity(true);
		return true;
	};
	std::cout << "The Negotiate Order is invalid.\n";
	return false;
};
void Negotiate::execute()
{
	if (validate() == true)
	{
		source->negotiated.push_back(target);
		target->negotiated.push_back(source);
		executed = true;
	}
	else
	{
		executed = true;
	}
};
Negotiate* Negotiate::getNew()
{
	return new Negotiate(*this);
};

//==================================================================================================================================================================

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
	};
};
OrderList::OrderList(const OrderList& ol)
{
	for (auto looper = ol.orders.begin(); looper != ol.orders.end(); ++looper)
	{
		Order* x = *looper;
		orders.push_back(x);
	};
};
OrderList::~OrderList() {
	for (auto order : orders) {
		delete order;
	}
}
OrderList& OrderList::operator=(OrderList& o)
{
	OrderList p = OrderList(o);
	return  p;
};
ostream& operator << (ostream& os, OrderList& olist)
{
	int count = 0;
	for (auto looper = olist.orders.begin(); looper != olist.orders.end(); ++looper)
	{
		os << ++count << " : " << **looper << "\n";
	};
	return os;
};

std::list<Order*> OrderList::getOrders()
{
	return orders;
}