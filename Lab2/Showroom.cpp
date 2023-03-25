#include "Showroom.h"

Showroom::Showroom() {
	Showroom::name = "Unnamed Showroom";
	Showroom::capacity = 0;
}

Showroom::Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0) {
	Showroom::name = name;
	Showroom::capacity = capacity;
}

vector<Vehicle> Showroom::GetVehicleList() {
	return VehicleList;
}

void Showroom::AddVehicle(Vehicle v) {
	if ((unsigned int)VehicleList.size() == capacity) {
		cout << "Showroom is full! Cannot add ";
		cout << v.GetYearMakeModel() << endl;
	}
	else {
		VehicleList.push_back(v);
	}
}

void Showroom::ShowInventory() {
	if (VehicleList.size() == 0) {
		cout << "Unnamed Showroom is empty!" << endl;
	}
	else {
		cout << "Vehicles in " << name << endl;
		for (int i = 0; i < (int)VehicleList.size(); i++) {
			VehicleList[i].Display();
		}
	}
}

float Showroom::GetInventoryValue() {
	float total = 0;
	for (int i = 0; i < (int)VehicleList.size(); i++) {
		total += VehicleList[i].GetPrice();
	}
	return total;
}
