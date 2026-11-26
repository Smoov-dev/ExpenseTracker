#include "services/TransactionService.h"
#include "models/Transaction.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <chrono>
#include <sstream>


using namespace std;

TransactionService::TransactionService(std::vector<Transaction> transactions) : transactions(transactions) {}

void TransactionService::addTransaction(const Transaction& transaction)
{
	transactions.push_back(transaction);
}

void TransactionService::listTransactions() const
{
	if (transactions.empty())
	{
		cout << "No transactions found." << endl;
		return;
	}
	for (const Transaction& transaction : transactions)
	{
		cout << "ID: " << transaction.getID() << endl;
		cout << "Type: " << transactionTypeToString(transaction.getType()) << endl;
		cout << "Description: " << transaction.getDescription() << endl;
		cout << "Amount: $" << transaction.getAmount() << endl;
		cout << "Category: " << transaction.getCategory() << endl;
		cout << "Date: " << transaction.getDate() << endl;
		cout << "------------------------" << endl;
	}
}

Transaction& TransactionService::getTransactionByID(int id)
{
	auto it = std::find_if(
		transactions.begin(),
		transactions.end(),
		[id](const Transaction& transaction)
		{
			return transaction.getID() == id;
		}
	);

	if (it != transactions.end())
	{
		return *it;
	}
	else
	{
		throw std::runtime_error("Transaction not found.");
	}

	
}

Transaction& TransactionService::editTransactionByID(int id, TransactionType newType, const std::string& newDescription, double newAmount, const std::string& newCategory, const std::string& newDate)
{
	Transaction& transaction = getTransactionByID(id);
	transaction.setType(newType);
	transaction.setDescription(newDescription);
	transaction.setAmount(newAmount);
	transaction.setCategory(newCategory);
	transaction.setDate(newDate);
	return transaction;
}

void TransactionService::deleteTransactionByID(int id)
{
	auto it = std::find_if(
		transactions.begin(),
		transactions.end(),
		[id](const Transaction& transaction)
		{
			return transaction.getID() == id;
		}
	);
	if (it != transactions.end())
	{
		transactions.erase(it);
	}
	else
	{
		throw std::runtime_error("Transaction not found.");
	}
}

std::vector<Transaction> TransactionService::getTransactionsByType(TransactionType type) const
{
	std::vector <Transaction> filteredTransactions;
	std::copy_if(
		transactions.begin(), 
		transactions.end(), 
		std::back_inserter(filteredTransactions),
		[type](const Transaction& transaction)
		{
			return transaction.getType() == type;
		}
	);
	return filteredTransactions;
}

std::vector<Transaction> TransactionService::getTransactionsByCategory(const std::string& category) const
{
	std::vector <Transaction> filteredTransactions;
	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(filteredTransactions),
		[&category](const Transaction& transaction)
		{
			return transaction.getCategory() == category;
		}
	);
	return filteredTransactions;
}
 
std::vector<Transaction> TransactionService::getTransactionsByTypeAndCategory(TransactionType type, const std::string& category) const
{
	std::vector<Transaction> filteredTransactions;
	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(filteredTransactions),
		[&type, &category](const Transaction& transaction)
		{
			return transaction.getType() == type && transaction.getCategory() == category;
		}
	);
	return filteredTransactions;
}

std::vector<Transaction> TransactionService::getTransactionsByAmountRange(double minRange, double maxRange) const
{

	if (minRange > maxRange)
	{
		throw std::invalid_argument("Minimum amount can't exceed maximum amount.");
	}


	std::vector<Transaction> filteredTransactions;
	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(filteredTransactions),
		[&minRange, &maxRange](const Transaction& transaction)
		{
			return transaction.getAmount() >= minRange && transaction.getAmount() <= maxRange;
		}
	);
	return filteredTransactions;

	
}

std::chrono::year_month_day TransactionService::dateConvertion(const std::string& dateStr) const
{

	int year, month, day;
	char sep1, sep2;
	std::istringstream date(dateStr);

	if (!(date >> year >> sep1 >> month >> sep2 >> day))
		throw std::invalid_argument("Invalid date format.");

	if (sep1 != '-' || sep2 != '-')
		throw std::invalid_argument("Invalid date format.");

	date >> year >> sep1 >> month >> sep2 >> day;

	std::chrono::year_month_day parsedDate{
		std::chrono::year{ year },
		std::chrono::month{ static_cast<unsigned int>(month) },
		std::chrono::day{ static_cast<unsigned int>(day) }
	};
	
	if (!parsedDate.ok())
		throw std::invalid_argument("Invalid date.");

	return parsedDate;

}

std::vector<Transaction> TransactionService::getTransactionsByDateRange(const std::string& dateStartStr, const std::string& dateEndStr) const
{
	std::chrono::year_month_day dateStart = dateConvertion(dateStartStr);
	std::chrono::year_month_day dateEnd = dateConvertion(dateEndStr);

	std::vector<Transaction> filteredTransactions;
	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(filteredTransactions),
		[this, &dateStart, &dateEnd](const Transaction& transaction)
		{
			return dateConvertion(transaction.getDate()) >= dateStart && dateConvertion(transaction.getDate()) <= dateEnd;
		}
	);

	return filteredTransactions;
}


std::vector<Transaction> TransactionService::getTransactionsByDescription(const std::string& description) const
{
	std::vector<Transaction> filteredTransactions;

	std::copy_if(
		transactions.begin(),
		transactions.end(),
		std::back_inserter(filteredTransactions),
		[&description](const Transaction& transaction)
		{
			return transaction.getDescription().find(description) != std::string::npos;
		}
	);

	return filteredTransactions;
}

void TransactionService::sortByAmount() 
{
	std::sort(
		transactions.begin(), 
		transactions.end(), 
		[](const Transaction& a, const Transaction& b) 
		{ 
			return a.getAmount() < b.getAmount(); 
		});
	
}

void TransactionService::sortByAmountDescending()
{
	std::sort(
		transactions.begin(), 
		transactions.end(), 
		[](const Transaction& a, const Transaction& b) 
		{ 
			return a.getAmount() > b.getAmount(); 
		});
}

void TransactionService::sortTransactionsByDate()
{
	std::sort(
		transactions.begin(), 
		transactions.end(), 
		[this](const Transaction& a, const Transaction& b) 
		{ 
			std::chrono::year_month_day dateA = dateConvertion(a.getDate());
			std::chrono::year_month_day dateB = dateConvertion(b.getDate());
			return dateA < dateB;
		});
}

std::vector<Transaction> TransactionService::getAllTransactions() const
{
	return transactions;
}