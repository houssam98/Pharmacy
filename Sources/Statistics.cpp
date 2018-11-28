//
// Created by houss on 4/25/2017.
//

#include "../Headers/Statistics.hpp"
#include "../Headers/DBMS.hpp"

using namespace std;

const std::string Statistics::getAllTransactionsByDate = "GET_ALL_TRANSACTIONS_BY_DATE";
const std::string Statistics::getTotalIncomeToday = "GET_TOTAL_INCOME_TODAY";
const std::string Statistics::getAllTransactionsBy2Dates = "GET_ALL_TRANSACTIONS_BY_2_DATES";
const std::string Statistics::getTotalIncomeFromTransactions = "GET_TOTAL_INCOME_FROM_TRANSACTIONS";
const std::string Statistics::getTotalIncomeBy2Dates = "GET_TOTAL_INCOME_BY_2_DATES";
const std::string Statistics::getOrdersExpensesBy2Dates = "GET_ORDERS_EXPENSES_BY_2_DATES";
const std::string Statistics::getTotalExpenseOnSalary = "GET_TOTAL_EXPENSES_ON_SALARY";
const std::string Statistics::getTotalWorthOfStockProducts = "GET_TOTAL_WORTH_OF_STOCK_PRODUCTS";
const std::string Statistics::getFinancialStatus = "GET_FINANCIAL_STATUS";
const std::string Statistics::getFinancialStatusBy2Dates = "GET_FINANCIAL_STATUS_BY_2_DATES";
const std::string Statistics::getCustomerCountriesByBills = "GET_CUSTOMER_COUNTRIES_BY_BILLS";
const std::string Statistics::getNumberOrdersByEachUser = "GET_NUMBER_ORDERS_BY_EASY_USER";
const std::string Statistics::getProductWithMinQuantity = "GET_PRODUCT_WITH_MIN_QUANTITY";

void Statistics::InitPreparedStatements() {

    if(!S.getPreparedStatement(getAllTransactionsByDate)){
        stringstream query;
        query << "SELECT * FROM transactions WHERE date = $1;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsByDate, query.str());
    }

    if(!S.getPreparedStatement(getTotalIncomeToday)){
        stringstream query;
        query << "SELECT SUM(productprice) AS \"Total income today\" FROM transactions WHERE date = $1;" << endl;
        S.requestNewPreparedStatement(getTotalIncomeToday, query.str());
    }

    if(!S.getPreparedStatement(getAllTransactionsBy2Dates)){
        stringstream query;
        query << "SELECT * FROM transactions WHERE transactions.date BETWEEN $1 AND $2;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsBy2Dates, query.str());
    }

    if(!S.getPreparedStatement(getTotalIncomeFromTransactions)){
        stringstream query;
        query << "SELECT SUM(productprice*productquantity) AS \"Total income from transactions\" FROM transactions;" << endl;
        S.requestNewPreparedStatement(getTotalIncomeFromTransactions, query.str());
    }

    if(!S.getPreparedStatement(getTotalIncomeBy2Dates)){
        stringstream query;
        query << "SELECT SUM(productprice) AS \"Total income between\" FROM transactions WHERE transactions.date BETWEEN $1 AND $2;" << endl;
        S.requestNewPreparedStatement(getTotalIncomeBy2Dates, query.str());
    }

    if(!S.getPreparedStatement(getOrdersExpensesBy2Dates)){
        stringstream query;
        query << "SELECT SUM (Price*productQuantity) AS \"Total Price\"  FROM Products JOIN orders USING (productId) WHERE orders.date BETWEEN $1 AND $2;" << endl;
        S.requestNewPreparedStatement(getOrdersExpensesBy2Dates, query.str());
    }

    if(!S.getPreparedStatement(getTotalExpenseOnSalary)){
        stringstream query;
        query << "SELECT SUM(salary) AS \"Total salaries\" FROM users;" << endl;
        S.requestNewPreparedStatement(getTotalExpenseOnSalary, query.str());
    }

    if(!S.getPreparedStatement(getTotalWorthOfStockProducts)){
        stringstream query;
        query << "SELECT SUM(quantity*price) AS \"Products worth\" FROM products;" << endl;
        S.requestNewPreparedStatement(getTotalWorthOfStockProducts, query.str());
    }

    if(!S.getPreparedStatement(getFinancialStatus)){
        stringstream query;
        query << "SELECT SUM((SELECT SUM(productprice*productquantity) FROM transactions)-(SELECT SUM(salary) FROM users)-(SELECT SUM (Price*productQuantity) FROM Products JOIN orders USING (productId))) AS \"Total\"" << endl;
        S.requestNewPreparedStatement(getFinancialStatus, query.str());
    }

    if(!S.getPreparedStatement(getFinancialStatusBy2Dates)){
        stringstream query;
        query << "SELECT SUM((SELECT SUM(productprice*productquantity) FROM transactions WHERE transactions.date BETWEEN $1 AND $2)-(SELECT SUM(salary) FROM users)-(SELECT SUM (Price*productQuantity) FROM Products JOIN orders USING (productId) WHERE orders.date BETWEEN $1 AND $2)) AS \"Total\" " << endl;
        S.requestNewPreparedStatement(getFinancialStatusBy2Dates, query.str());
    }

    if(!S.getPreparedStatement(getCustomerCountriesByBills)){
        stringstream query;
        query << "SELECT DISTINCT country FROM bill; " << endl;
        S.requestNewPreparedStatement(getCustomerCountriesByBills, query.str());
    }

    if(!S.getPreparedStatement(getNumberOrdersByEachUser)){
        stringstream query;
        query << "SELECT userid, COUNT(orderid) FROM orders GROUP BY userid " << endl;
        S.requestNewPreparedStatement(getNumberOrdersByEachUser, query.str());
    }

    if(!S.getPreparedStatement(getProductWithMinQuantity)){
        stringstream query;
        query << "SELECT productId, productname, quantity FROM products WHERE quantity = (SELECT min(quantity) FROM products);" << endl;
        S.requestNewPreparedStatement(getProductWithMinQuantity, query.str());
    }
}