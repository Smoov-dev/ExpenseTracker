#include "services/FinancialSummaryService.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <unordered_map>

using namespace std;

FinancialSummaryService::FinancialSummaryService(std::vector<Transaction> transactions) : transactions(transactions){}

double FinancialSummaryService::getTotalIncome() const
{
	double totalIncome = 0;

	for (const Transaction& income : transactions)
	{
		if (income.getType() == TransactionType::Income) {
			totalIncome += income.getAmount();
		}

	}

	return totalIncome;
}

double FinancialSummaryService::getTotalExpenses() const
{
	double totalExpense = 0;

	for (const Transaction& expense : transactions)
	{
		if (expense.getType() == TransactionType::Expense) {
			totalExpense += expense.getAmount();
		}

	}

	return totalExpense;
}

double FinancialSummaryService::getBalance() const
{
	double totalIncome = getTotalIncome();
	double totalExpense = getTotalExpenses();

	return totalIncome - totalExpense;
}

double FinancialSummaryService::getAverageExpense() const
{
	double totalExpense = getTotalExpenses();
	int div = 0;

	for (const Transaction& expense : transactions)
	{
		if (expense.getType() == TransactionType::Expense) {
			div++;
		}

	}

	return totalExpense / div;
}

Transaction FinancialSummaryService::getLargestExpense() const
{
	std::vector<Transaction> expenses;

	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(expenses),
		[](const Transaction& transaction)
		{
			return transaction.getType() == TransactionType::Expense;
		}
	);

	if (expenses.empty())
	{
		throw std::runtime_error("No expenses found.");
	}

	auto largest = std::max_element(
		expenses.begin(),
		expenses.end(),
		[](const Transaction& a, const Transaction& b)
		{
			return a.getAmount() < b.getAmount();
		}
	);

	return *largest;
}

std::string FinancialSummaryService::getHighestSpendingCategory() const
{
	std::vector<Transaction> expenses;

	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(expenses),
		[](const Transaction& transaction)
		{
			return transaction.getType() == TransactionType::Expense;
		}
	);

	if (expenses.empty())
	{
		throw std::runtime_error("No expenses found.");
	}

	std::unordered_map<std::string, double> categoryTotals;

	for (const Transaction& expense : expenses)
	{
		categoryTotals[expense.getCategory()] += expense.getAmount();
	}

	auto highestSpender = std::max_element(
		categoryTotals.begin(),
		categoryTotals.end(),
		[](const auto& a, const auto& b)
		{
			return a.second < b.second;
		}
	);

	return highestSpender->first;

}