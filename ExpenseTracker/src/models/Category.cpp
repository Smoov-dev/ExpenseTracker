#include "models/Category.h"
#include <iostream>

Category::Category(int id, const std::string& name) : ID(id), name(name) {}

//Getters
int Category::getID() const { return ID; }
std::string Category::getName() const { return name; }

//Setters
void Category::setName(const std::string& newName) { name = newName; }