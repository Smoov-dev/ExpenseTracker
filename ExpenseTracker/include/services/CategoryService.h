#pragma once

#include "models/Category.h"

class CategoryService
{
	private:
		std::vector<Category> categories;

	public:
		CategoryService(std::vector<Category> categories = {});
		void addCategory(const Category& category);
};