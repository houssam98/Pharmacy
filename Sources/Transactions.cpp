//
// Created by houss on 4/25/2017.
//

#include "../Headers/Transactions.hpp"
#include "../Headers/DBMS.hpp"
#include <sstream>

using namespace std;

const std::string Transactions::insertTransaction = "INSERT_TRANSACTION";
const std::string Transactions::getTotalNumberOfTransactions = "GET_TOTAL_NUMBER_OF_TRANSACTIONS";
const std::string Transactions::getTransactionFromDate = "GET_TRANSACTION_FROM_DATE";
const std::string Transactions::getTransactionOfSpecificProduct = "GET_TRANSACTION_OF_SPECIFIC_PRODUCT";
const std::string Transactions::getTransactionsDoneByUserID = "GET_TRANSACTION_DONE_BY_USER_ID";
const std::string Transactions::getTransactionsDoneByUserName = "GET_TRANSACTION_DONE_BY_USER_NAME";
const std::string Transactions::getAllTransactionsOfAProduct = "GET_ALL_TRANSACTIONS_OF_A_PRODUCT";
const std::string Transactions::getAllTransactionsByDate = "GET_ALL_TRANSACTIONS_BY_DATE";

void Transactions::InitPreparedStatements() {

    if(!S.getPreparedStatement(insertTransaction)){
        stringstream query;
        query << "INSERT INTO transactions VALUES ( default, $1, $2, $3, $4, $5 );" << endl;
        S.requestNewPreparedStatement(insertTransaction, query.str());
    }

    if(!S.getPreparedStatement(getTotalNumberOfTransactions)){
        stringstream query;
        query << "SELECT COUNT(transactionid) FROM transactions;" << endl;
        S.requestNewPreparedStatement(getTotalNumberOfTransactions, query.str());
    }

    if(!S.getPreparedStatement(getTransactionFromDate)){
        stringstream query;
        query << "SELECT COUNT(transactionid) FROM transactions WHERE date = $1;" << endl;
        S.requestNewPreparedStatement(getTransactionFromDate, query.str());
    }

    if(!S.getPreparedStatement(getTransactionOfSpecificProduct)){
        stringstream query;
        query << "SELECT COUNT(transactionid) FROM transactions WHERE productname LIKE 1$;" << endl;
        S.requestNewPreparedStatement(getTransactionOfSpecificProduct, query.str());
    }

    if(!S.getPreparedStatement(getTransactionsDoneByUserID)){
        stringstream query;
        query << "SELECT COUNT(transactionid) FROM transactions WHERE userid = 1$;" << endl;
        S.requestNewPreparedStatement(getTransactionsDoneByUserID, query.str());
    }

    if(!S.getPreparedStatement(getTransactionsDoneByUserName)){
        stringstream query;
        query << "SELECT COUNT(transactionid) FROM transactions JOIN users USING(userid) WHERE users.username LIKE $1;" << endl;
        S.requestNewPreparedStatement(getTransactionsDoneByUserName, query.str());
    }

    if(!S.getPreparedStatement(getAllTransactionsOfAProduct)){
        stringstream query;
        query << "SELECT * FROM transactions WHERE productname LIKE $1;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsOfAProduct, query.str());
    }

    if(!S.getPreparedStatement(getAllTransactionsByDate)){
        stringstream query;
        query << "SELECT * FROM transactions WHERE date LIKE 1$;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsByDate, query.str());
    }

}