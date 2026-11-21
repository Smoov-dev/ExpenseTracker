#include "models/Transaction.h"
#include <iostream>

using namespace std;

Transaction::Transaction(int id, TransactionType type, const std::string& description, double amount, const std::string& category, const std::string& date) :
	ID(id),
	type(type),
	description(description),
	amount(amount),
	category(category),
	date(date)
{}

//Getters
int Transaction::getID() const { return ID; }
TransactionType Transaction::getType() const { return type; }
std::string Transaction::getDescription() const { return description; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getDate() const { return date; }
	
std::string transactionTypeToString(TransactionType type)
{
	switch (type)
	{
	case TransactionType::Income:
		return "Income";

	case TransactionType::Expense:
		return "Expense";

	default:
		return "Unknown";
	}
}

//Setters
void Transaction::setType(TransactionType newType) { type = newType; }
void Transaction::setDescription(const std::string& newDescription) { description = newDescription; }
void Transaction::setAmount(double newAmount) { 
	if (newAmount < 1) {
		cout << "Amount must be greater than 0. Transaction amount not updated." << endl;
	} else {
		amount = newAmount; 
	} 
}
void Transaction::setCategory(const std::string& newCategory) { category = newCategory; }
void Transaction::setDate(const std::string& newDate) { date = newDate; }
