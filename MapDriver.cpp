//============================================================================
// Name        : MapDriver.cpp
// Author      : Maxime Johnson (40081684)
// Description : Driver class to test out Map and Territory features.
//============================================================================
/*
#include "Territory.h"
#include "Map.h"
#include <iostream>

using namespace std;

int main() {

	Territory a = Territory("a");
	Territory b = Territory("b");
	Territory c = Territory("c");
	Territory d = Territory("d");

	Map map = Map();

	vector<Territory> list = {
		b
	};
	map.addTerritory("1", a, list);

	list = {
		c
	};
	map.addTerritory("1", b, list);

	list = {
		b,d
	};
	map.addTerritory("2", c, list);

	list = {
		c,
		a
	};
	map.addTerritory("2", d, list);

	if (map.validate()) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}

	return 0;
}*/