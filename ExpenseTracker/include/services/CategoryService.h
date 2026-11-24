#pragma once

#include "models/Category.h"
#include <vector>

class CategoryService
{
	private:
		std::vector<Category> categories;
		bool categoryExists(int id) const;
		int getNextCategoryID() const;

	public:
		CategoryService(std::vector<Category> categories = {});
		bool addCategory(const Category& category);
		void listCategories() const;
		Category& getCategoryByID(int id);
		Category& editCategoryByID(int id, std::string name);
		void deleteCategoryByID(int id);
		std::vector <Category> getCategoryByName(const std::string& name) const;
		
};