#include "Vehicle.h"

Vehicle::Vehicle() {
	Vehicle::make = "COP3503";
	Vehicle::model = "Rust Bucket";
	Vehicle::year = 1900;
	Vehicle::price = 0;
	Vehicle::mileage = 0;
}

Vehicle::Vehicle(string make, string model, int year, float price, int mileage) {
	Vehicle::make = make;
	Vehicle::model = model;
	Vehicle::year = year;
	Vehicle::price = price;
	Vehicle::mileage = mileage;
}

void Vehicle::Display() {
	cout << year << ' ';
	cout << make << ' ';
	cout << model << ' ';
	cout << '$' << price << ' ';
	cout << mileage << endl;
}

string Vehicle::GetYearMakeModel() {
	return to_string(year) + " " + make + " " + model;
}

float Vehicle::GetPrice() {
	return price;
}
