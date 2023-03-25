#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Vehicle.h"
using namespace std;

class Showroom
{
	string name;
	vector<Vehicle> VehicleList;
	unsigned int capacity;

public:
	Showroom();
	Showroom(string name, unsigned int capacity);

	vector<Vehicle> GetVehicleList();
	void AddVehicle(Vehicle v);
	void ShowInventory();
	float GetInventoryValue();
};
