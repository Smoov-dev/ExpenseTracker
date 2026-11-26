#pragma once

#include <vector>
#include "models/Transaction.h"

class FinancialSummaryService
{
private:
    std::vector<Transaction> transactions;

public:
    FinancialSummaryService(std::vector<Transaction> transactions);

    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getBalance() const;
    double getAverageExpense() const;

    Transaction getLargestExpense() const;
    std::string getHighestSpendingCategory() const;
};