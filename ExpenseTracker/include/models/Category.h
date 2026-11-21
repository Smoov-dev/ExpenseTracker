#pragma once

#include <string>

class Category
{
private:
	int ID;
	std::string name;
public:
	Category(int id, const std::string& name);
	
	//Getters
	int getID() const;
	std::string getName() const;
	
	//Setters
	void setName(const std::string& name);
};