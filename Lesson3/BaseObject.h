#pragma once
#include<sstream>
#include<iostream>

class BaseObject
{
	private:
		int id;
		std::string name;
		std::pair <int, int> position;
	public:
		explicit BaseObject(int id, const char* name, std::pair <int, int> position);
		~BaseObject();
		int getId();
		void setId(int id);
		std::string getName();
		void setName(std::string name);
		std::pair <int, int> getPosition();
		void printPosition();
		void setPosition(std::pair <int, int> position);
		virtual void move(std::pair <int, int> velocity) = 0;
};

