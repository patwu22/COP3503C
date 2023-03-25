#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Showroom.h"
using namespace std;

class Dealership
{
	string name;
	vector<Showroom> ShowroomList;
	unsigned int capacity;

public:
	Dealership();
	Dealership(string name, unsigned int capacity);

	void AddShowroom(Showroom s);
	float GetAveragePrice();
	void ShowInventory();
};
