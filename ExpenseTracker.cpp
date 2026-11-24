#include "models/Transaction.h"
#include "models/Category.h"
#include "services/TransactionService.h"
#include "services/CategoryService.h"
#include <iostream>

using namespace std;

int main()
{
    TransactionService service;

    Transaction t1(1, TransactionType::Income, "Salary", 1500, "Work", "2026-11-01");
    Transaction t2(2, TransactionType::Expense, "Groceries", 75.50, "Food", "2026-11-02");
	Transaction t3(3, TransactionType::Expense, "Boat Fuel", 50, "Transport", "2026-11-03");
	Transaction t4(4, TransactionType::Expense, "Car Fuel", 50, "Food", "2026-11-03");

    service.addTransaction(t1);
    service.addTransaction(t2);
    service.addTransaction(t3);
	service.addTransaction(t4);

    service.listTransactions();
	std::vector<Transaction> expenses = service.getTransactionsByType(TransactionType::Expense);
	std::cout << "Expenses:" << std::endl;
	for (const Transaction& expense : expenses)
	{
		cout << "ID: " << expense.getID() << endl;
		cout << "Type: " << transactionTypeToString(expense.getType()) << endl;
		cout << "Description: " << expense.getDescription() << endl;
		cout << "Amount: $" << expense.getAmount() << endl;
		cout << "Category: " << expense.getCategory() << endl;
		cout << "Date: " << expense.getDate() << endl;
		cout << "------------------------" << endl;
	}

	std::vector<Transaction> foodExpenses = service.getTransactionsByCategory("Food");
	std::cout << "Food Expenses:" << std::endl;
	for (const Transaction& expense : foodExpenses)
	{
		cout << "ID: " << expense.getID() << endl;
		cout << "Type: " << transactionTypeToString(expense.getType()) << endl;
		cout << "Description: " << expense.getDescription() << endl;
		cout << "Amount: $" << expense.getAmount() << endl;
		cout << "Category: " << expense.getCategory() << endl;
		cout << "Date: " << expense.getDate() << endl;
		cout << "------------------------" << endl;
	}
	cout << "Filtering by type and category of Expense and food:" << endl;
	auto results = service.getTransactionsByTypeAndCategory(
		TransactionType::Expense,
		"Food"
	);

	for (const Transaction& typeCategory : results)
	{
		cout << "ID: " << typeCategory.getID() << endl;
		cout << "Type: " << transactionTypeToString(typeCategory.getType()) << endl;
		cout << "Description: " << typeCategory.getDescription() << endl;
		cout << "Amount: $" << typeCategory.getAmount() << endl;
		cout << "Category: " << typeCategory.getCategory() << endl;
		cout << "Date: " << typeCategory.getDate() << endl;
		cout << "------------------------" << endl;
	}

	cout << "Filtering by amount between 51 and 100:" << endl;
	auto resultsMoney = service.getTransactionsByAmountRange(51.00, 100.00);

	for (const Transaction& amountRange : resultsMoney)
	{
		cout << "ID: " << amountRange.getID() << endl;
		cout << "Type: " << transactionTypeToString(amountRange.getType()) << endl;
		cout << "Description: " << amountRange.getDescription() << endl;
		cout << "Amount: $" << amountRange.getAmount() << endl;
		cout << "Category: " << amountRange.getCategory() << endl;
		cout << "Date: " << amountRange.getDate() << endl;
		cout << "------------------------" << endl;
	}

	cout << "Filtering by amount between 100 and 51:" << endl;try
	{
		auto resultsMoneyError = service.getTransactionsByAmountRange(100.00, 51.00);
	}
	catch (const std::invalid_argument& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	


	cout << "Filtering by dates between 2026-11-01 and 2026-11-02:" << endl;
	auto resultsDate = service.getTransactionsByDateRange("2026-11-01", "2026-11-02");

	for (const Transaction& dateRange : resultsDate)
	{
		cout << "ID: " << dateRange.getID() << endl;
		cout << "Type: " << transactionTypeToString(dateRange.getType()) << endl;
		cout << "Description: " << dateRange.getDescription() << endl;
		cout << "Amount: $" << dateRange.getAmount() << endl;
		cout << "Category: " << dateRange.getCategory() << endl;
		cout << "Date: " << dateRange.getDate() << endl;
		cout << "------------------------" << endl;
	}

	cout << "Filtering by description Fuel:" << endl;
	auto resultsDes = service.getTransactionsByDescription("Fuel");

	for (const Transaction& des : resultsDes)
	{
		cout << "ID: " << des.getID() << endl;
		cout << "Type: " << transactionTypeToString(des.getType()) << endl;
		cout << "Description: " << des.getDescription() << endl;
		cout << "Amount: $" << des.getAmount() << endl;
		cout << "Category: " << des.getCategory() << endl;
		cout << "Date: " << des.getDate() << endl;
		cout << "------------------------" << endl;
	}

	cout << "Sorting transactions by amount ascending:" << endl;
	service.sortByAmount();
	service.listTransactions();

	cout << "Sorting transactions by amount descending:" << endl;
	service.sortByAmountDescending();
	service.listTransactions();

	cout << "Sorting transactions by date:" << endl;
	service.sortTransactionsByDate();
	service.listTransactions();

	cout << "Listing categories:" << endl;

	CategoryService catService;
	Category c1 (1, "Games");
	Category c2 (2, "Movies");

	catService.addCategory(c1);
	catService.addCategory(c2);
	catService.listCategories();

	cout << "Getting category with id 2:" << endl;
	Category& test = catService.getCategoryByID(2);

	cout << "ID: " << test.getID() << endl;
	cout << "Name: " << test.getName() << endl;
	cout << "------------------------" << endl;

	cout << "Editing category with id 2 name to Music:" << endl;
	catService.editCategoryByID(2, "Music");
	cout << "ID: " << test.getID() << endl;
	cout << "Name: " << test.getName() << endl;
	cout << "------------------------" << endl;
	
	cout << "Deleting category with id 2:" << endl;
	catService.deleteCategoryByID(2);
	catService.listCategories();

	catService.addCategory(c2);

	cout << "Getting category with the name Movies:" << endl;
	std::vector <Category> testName = catService.getCategoryByName("Movies");
	for ( const Category& name : testName) 
	{
		cout << "ID: " << name.getID() << endl;
		cout << "Name: " << name.getName() << endl;
		cout << "------------------------" << endl;
	}
	

	return 0;
}
