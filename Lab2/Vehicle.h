#pragma once
#include <string>
#include <iostream>
using namespace std;

class Vehicle
{
	string make;
	string model;
	unsigned int year;
	float price;
	unsigned int mileage;

public:
	Vehicle();
	Vehicle(string make, string model, int year, float price, int mileage);

	void Display();

	string GetYearMakeModel();

	float GetPrice();
};
