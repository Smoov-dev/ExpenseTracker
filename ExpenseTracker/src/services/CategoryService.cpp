#include "services/CategoryService.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <chrono>
#include <sstream>

using namespace std;

CategoryService::CategoryService(std::vector<Category> categories) : categories(categories) {}

bool CategoryService::addCategory(const Category& category)
{
	if (categoryExists(category.getID()))
	{
		cout << "Error: Category ID already exists." << endl;
		return false;
	}

	categories.push_back(category);
	return true;
}

void CategoryService::listCategories() const
{
	if (categories.empty())
	{
		cout << "No categories found." << endl;
		return;
	}
	for (const Category& category : categories)
	{
		cout << "ID: " << category.getID() << endl;
		cout << "Name: " << category.getName() << endl;
		cout << "------------------------" << endl;
	}
}

Category& CategoryService::getCategoryByID(int id)
{
	auto it = std::find_if(
		categories.begin(),
		categories.end(),
		[id](const Category& category)
		{
			return category.getID() == id;
		});

		if (it != categories.end())
		{
			return *it;
		}
		else
		{
			throw std::runtime_error("Category not found.");
		}
}

Category& CategoryService::editCategoryByID(int id, std::string name)
{
	Category& category = getCategoryByID(id);
	category.setName(name);

	return category;
}

void CategoryService::deleteCategoryByID(int id)
{
	auto it = std::find_if(
		categories.begin(),
		categories.end(),
		[id](const Category& category)
		{
			return category.getID() == id;
		}
	);

	if (it != categories.end())
	{
		categories.erase(it);
	}
	else
	{
		throw std::runtime_error("Category not found.");
	}
}

std::vector <Category> CategoryService::getCategoryByName(const std::string& name) const
{
	std::vector <Category> filteredCategories;
	std::copy_if(
		categories.begin(),
		categories.end(),
		std::back_inserter(filteredCategories),
		[&name](const Category& category)
		{
			return category.getName() == name;
		}
	);

	return filteredCategories;
}

bool CategoryService::categoryExists(int id) const
{

	auto it = std::find_if(
		categories.begin(),
		categories.end(),
		[id](const Category& category)
		{
			return category.getID() == id;
		}
	);

	return it != categories.end();
}

int CategoryService::getNextCategoryID() const
{
	auto maxID = std::max_element(
		categories.begin(),
		categories.end(),
		[](const Category& a, const Category& b)
		{
			return a.getID() < b.getID();
		}
	);

	if (maxID != categories.end())
	{
		return (*maxID).getID() + 1;
	}
	else
	{
		return 1;
	}

}


