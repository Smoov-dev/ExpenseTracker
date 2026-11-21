#pragma once

#include <string>

enum class TransactionType
{
    Income,
    Expense
};

std::string transactionTypeToString(TransactionType type);

class Transaction
{
	private:
		int ID;
		TransactionType type;
		std::string description;
		double amount;
		std::string category;
		std::string date;
	public:
		Transaction(int id, TransactionType type, const std::string& description, double amount, const std::string& category, const std::string& date);

		//Getters
		int getID() const;
		TransactionType getType() const;
		std::string getDescription() const;
		double getAmount() const;
		std::string getCategory() const;
		std::string getDate() const;

		//Setters
		void setType(TransactionType type);
		void setDescription(const std::string& description);
		void setAmount(double amount);
		void setCategory(const std::string& category);
		void setDate(const std::string& date);
};