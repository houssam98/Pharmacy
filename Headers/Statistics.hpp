//
// Created by houss on 4/25/2017.
//

#ifndef PHARMACY_STATISTICS_HPP
#define PHARMACY_STATISTICS_HPP

#include <iostream>
#include <sstream>

class Statistics {

    const static std::string getAllTransactionsByDate;
    const static std::string getTotalIncomeToday;
    const static std::string getAllTransactionsBy2Dates;
    const static std::string getTotalIncomeFromTransactions;
    const static std::string getTotalIncomeBy2Dates;
    const static std::string getOrdersExpensesBy2Dates;
    const static std::string getTotalExpenseOnSalary;
    const static std::string getTotalWorthOfStockProducts;
    const static std::string getFinancialStatus;
    const static std::string getFinancialStatusBy2Dates;
    const static std::string getCustomerCountriesByBills;
    const static std::string getNumberOrdersByEachUser;
    const static std::string getProductWithMinQuantity;

public:

    void static InitPreparedStatements();

};


#endif //PHARMACY_STATISTICS_HPP
