//
// Created by houss on 4/26/2017.
//

#ifndef PHARMACY_EMPLOYEE_HPP
#define PHARMACY_EMPLOYEE_HPP

#include "Customer.hpp"


class Employee : public Customer{

protected:
//Orders
    const static std::string addOrder;
    const static std::string removeOrderByNameID;
    const static std::string updateOrderQuantity;
//Transactions
    const static std::string insertTransaction;
    const static std::string getTransactionFromDate;
    const static std::string getAllTransactionsOfAProduct;
//Category
    const static std::string getAllCategories;
    const static std::string getProductsByCategoryID;
//Bills
    const static std::string addBill;
    const static std::string getBillByID;

public:

    void static InitPreparedStatements();

    void static userEmployeef();
    //Orders
    void static addOrderf();
    void static removeOrderByNameIDf();
    void static updateOrderQuantityf();
//Transactions
    void static insertTransactionf();
    void static getTransactionFromDatef();
    void static getAllTransactionsOfAProductf();
//Category
    void static getAllCategoriesf();
    void static getProductsByCategoryIDf();
//Bills
    void static addBillf();
    void static getBillByIDf();


};


#endif //PHARMACY_EMPLOYEE_HPP
