#include "Dealership.h"

Dealership::Dealership() {
	Dealership::name = "Generic Dealership";
	Dealership::capacity = 0;
}

Dealership::Dealership(string name = "Generic Dealership", unsigned int capacity = 0) {
	Dealership::name = name;
	Dealership::capacity = capacity;
}

void Dealership::AddShowroom(Showroom s) {
	if ((unsigned int)ShowroomList.size() == capacity) {
		cout << "Dealership is full, can't add another showroom!" << endl;
	}
	else {
		ShowroomList.push_back(s);
	}
}

float Dealership::GetAveragePrice() {
	float totalprice = 0;
	float totalnumber = 0;
	if (ShowroomList.size() == 0) {
		return 0;
	}
	for (int i = 0; i < (int)ShowroomList.size(); i++) {
		for (int j = 0; j < (int)ShowroomList[i].GetVehicleList().size(); j++) {
			totalprice += ShowroomList[i].GetVehicleList()[j].GetPrice();
			totalnumber++;
		}
	}
	return totalprice / totalnumber;
}

void Dealership::ShowInventory() {
	if (ShowroomList.size() == 0) {
		cout << name << " is empty!" << endl;
	}
	else {
		for (int i = 0; i < (int)ShowroomList.size(); i++) {
			ShowroomList[i].ShowInventory();
			cout << endl;
		}
	}
	cout << "Average car price: $" << this->GetAveragePrice();
}
