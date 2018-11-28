//
// Created by houss on 4/25/2017.
//

#ifndef PHARMACY_TRANSACTIONS_HPP
#define PHARMACY_TRANSACTIONS_HPP

#include <iostream>
#include <sstream>

class Transactions {

    const static std::string insertTransaction;
    const static std::string getTotalNumberOfTransactions;
    const static std::string getTransactionFromDate;
    const static std::string getTransactionOfSpecificProduct;
    const static std::string getTransactionsDoneByUserID;
    const static std::string getTransactionsDoneByUserName;
    const static std::string getAllTransactionsOfAProduct;
    const static std::string getAllTransactionsByDate;

public:

    void static InitPreparedStatements();

};


#endif //PHARMACY_TRANSACTIONS_HPP
