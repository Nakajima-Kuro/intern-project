#include<iostream>
#include<list>
#include"BaseObject.h"
#include"Car.h"
#include"Motorbike.h"
#include"Tree.h"
#include"House.h"

int main() {
		std::list<BaseObject*> listObject;

		listObject.push_back(new Car(0, "mustang gt", std::pair<int, int>(0, 0)));
		listObject.push_back(new Car(1, "Corvette Stingray", std::pair<int, int>(0, 0)));
		listObject.push_back(new Motorbike(2, "Ninja H2R", std::pair<int, int>(0, 0)));
		listObject.push_back(new Motorbike(2, "Panigale V4", std::pair<int, int>(0, 0)));
		listObject.push_back(new Tree(2, "Boring tree 1", std::pair<int, int>(6, 10)));
		listObject.push_back(new House(2, "Boring house 1", std::pair<int, int>(14, 20)));

		for (auto obj : listObject) {
			std::cout << obj->getName() << std::endl;
		}

		for (auto obj : listObject) {
			obj->move(std::pair<int, int>(2, 5));
		}

		for (auto obj : listObject) {
			obj->printPosition();
		}

		//Free Memory
		for (auto obj : listObject) {
			delete obj;
		}
		listObject.clear();
}