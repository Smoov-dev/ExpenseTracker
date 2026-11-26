#pragma once

#include "models/Transaction.h"
#include <vector>
#include <chrono>

class TransactionService
{

private:
	std::vector<Transaction> transactions;
	std::chrono::year_month_day dateConvertion(const std::string& date) const;

public:
	TransactionService(std::vector<Transaction> transactions = {});
	void addTransaction(const Transaction& transaction);
	void listTransactions() const;
	Transaction& getTransactionByID(int id);
	Transaction& editTransactionByID(int id, TransactionType newType, const std::string& newDescription, double newAmount, const std::string& newCategory, const std::string& newDate);
	void deleteTransactionByID(int id);
	std::vector<Transaction> getTransactionsByType(TransactionType type) const;
	std::vector<Transaction> getTransactionsByCategory(const std::string& category) const;
	std::vector<Transaction> getTransactionsByTypeAndCategory(TransactionType type, const std::string& category) const;
	std::vector<Transaction> getTransactionsByAmountRange(double minRange, double maxRange) const;
	std::vector<Transaction> getTransactionsByDateRange(const std::string& dateStartStr, const std::string& dateEndStr) const;
	std::vector<Transaction> getTransactionsByDescription(const std::string& description) const;
	void sortByAmount();
	void sortByAmountDescending();
	void sortTransactionsByDate();
	std::vector<Transaction> getAllTransactions() const;
	std::vector<Transaction> searchTransactions(std::optional<TransactionType> type, const std::optional<std::string>& category, std::optional<double> minAmount, std::optional<double> maxAmount) const;
};