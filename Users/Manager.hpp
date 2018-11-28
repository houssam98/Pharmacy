//
// Created by houss on 4/26/2017.
//

#ifndef PHARMACY_MANAGER_HPP
#define PHARMACY_MANAGER_HPP

#include <iostream>
#include "Employee.hpp"

class Manager : public Employee {

protected:
//Products
    const static std::string insertProduct;
    const static std::string changeProductPriceByName;
    const static std::string changeProductPriceByID;
    const static std::string changeProductQuantityByName;
    const static std::string changeProductQuantityByID;
//Orders
    const static std::string getOrdersTotalPrice;
    const static std::string getEachOrderTotalPrice;
//Category
    const static std::string insertCategory;
//Transactions
    const static std::string getTotalNumberOfTransactions;
    const static std::string getTransactionOfSpecificProduct;
    const static std::string getTransactionsDoneByUserID;
    const static std::string getTransactionsDoneByUserName;


public:

    void static InitPreparedStatements();

    void static userManager();

    void static insertProductf();
    void static changeProductPriceByNamef();
    void static changeProductPriceByIDf();
    void static changeProductQuantityByNamef();
    void static changeProductQuantityByIDf();
//Orders
    void static getOrdersTotalPricef();
    void static getEachOrderTotalPricef();
//Category
    void static insertCategoryf();
//Transactions
    void static getTotalNumberOfTransactionsf();
    void static getTransactionOfSpecificProductf();
    void static getTransactionsDoneByUserIDf();
    void static getTransactionsDoneByUserNamef();
};


#endif //PHARMACY_MANAGER_HPP
