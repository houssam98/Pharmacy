//
// Created by houss on 4/26/2017.
//

#ifndef PHARMACY_ADMIN_HPP
#define PHARMACY_ADMIN_HPP

#include <iostream>
#include "Customer.hpp"
#include "Employee.hpp"
#include "Manager.hpp"

class Admin : public Manager{

//STATISTICS
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
//Users
    const static std::string insertUser;
    const static std::string changeSalaryByUserID;
    const static std::string getContactDetailsByName;
    const static std::string changeUserPassword;

public:

    void static InitPreparedStatements();

    void static userAdmin();

    void static getAllTransactionsByDatef();
    void static getTotalIncomeTodayf();
    void static getAllTransactionsBy2Datesf();
    void static getTotalIncomeFromTransactionsf();
    void static getTotalIncomeBy2Datesf();
    void static getOrdersExpensesBy2Datesf();
    void static getTotalExpenseOnSalaryf();
    void static getTotalWorthOfStockProductsf();
    void static getFinancialStatusf();
    void static getFinancialStatusBy2Datesf();
    void static getCustomerCountriesByBillsf();
    void static getNumberOrdersByEachUserf();
    void static getProductWithMinQuantityf();
//Users
    void static insertUserf();
    void static changeSalaryByUserIDf();
    void static getContactDetailsByNamef();
    void static changeUserPasswordf();

};


#endif //PHARMACY_ADMIN_HPP
