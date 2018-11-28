//
// Created by houss on 4/26/2017.
//

#include <sstream>
#include "Admin.hpp"
#include "../Headers/DBMS.hpp"


using namespace std;

const std::string Admin::getAllTransactionsByDate = "GET_ALL_TRANSACTIONS_BY_DATE";
const std::string Admin::getTotalIncomeToday = "GET_TOTAL_INCOME_TODAY";
const std::string Admin::getAllTransactionsBy2Dates = "GET_ALL_TRANSACTIONS_BY_2_DATES";
const std::string Admin::getTotalIncomeFromTransactions = "GET_TOTAL_INCOME_FROM_TRANSACTIONS";
const std::string Admin::getTotalIncomeBy2Dates = "GET_TOTAL_INCOME_BY_2_DATES";
const std::string Admin::getOrdersExpensesBy2Dates = "GET_ORDERS_EXPENSES_BY_2_DATES";
const std::string Admin::getTotalExpenseOnSalary = "GET_TOTAL_EXPENSE_ON_SALARY";
const std::string Admin::getTotalWorthOfStockProducts = "GET_TOTAL_WORTH_OF_STOCK_PRODUCTS";
const std::string Admin::getFinancialStatus = "GET_FINANCIAL_STATUS";
const std::string Admin::getFinancialStatusBy2Dates = "GET_FINANCIAL_STATUS_BY_2_DATES";
const std::string Admin::getCustomerCountriesByBills = "GET_CUSTOMER_COUNTRIES_BY_BILLS";
const std::string Admin::getNumberOrdersByEachUser = "GET_NUMBER_ORDERS_BY_EASY_USER";
const std::string Admin::getProductWithMinQuantity = "GET_PRODUCT_WITH_MIN_QUANTITY";

const std::string Admin::insertUser = "INSERT_USER";
const std::string Admin::changeSalaryByUserID = "CHANGE_SALARY_BY_USER_ID";
const std::string Admin::getContactDetailsByName = "GET_CONTACT_DETAILS_BY_NAME";
const std::string Admin::changeUserPassword = "CHANGE_USER_PASSWORD";



void Admin::InitPreparedStatements() {

    if (!S.getPreparedStatement(getAllTransactionsByDate)) {
        stringstream query;
        query << "SELECT * FROM transactions WHERE date = $1;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsByDate, query.str());
    }

    if (!S.getPreparedStatement(getTotalIncomeToday)) {
        stringstream query;
        query << "SELECT SUM(productprice) AS \"Total income today\" FROM transactions WHERE date = $1;" << endl;
        S.requestNewPreparedStatement(getTotalIncomeToday, query.str());
    }

    if (!S.getPreparedStatement(getAllTransactionsBy2Dates)) {
        stringstream query;
        query << "SELECT * FROM transactions WHERE transactions.date BETWEEN $1 AND $2;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsBy2Dates, query.str());
    }

    if (!S.getPreparedStatement(getTotalIncomeFromTransactions)) {
        stringstream query;
        query << "SELECT SUM(productprice*productquantity) AS \"Total income from transactions\" FROM transactions;"
              << endl;
        S.requestNewPreparedStatement(getTotalIncomeFromTransactions, query.str());
    }

    if (!S.getPreparedStatement(getTotalIncomeBy2Dates)) {
        stringstream query;
        query
                << "SELECT SUM(productprice) AS \"Total income between\" FROM transactions WHERE transactions.date BETWEEN $1 AND $2;"
                << endl;
        S.requestNewPreparedStatement(getTotalIncomeBy2Dates, query.str());
    }

    if (!S.getPreparedStatement(getOrdersExpensesBy2Dates)) {
        stringstream query;
        query
                << "SELECT SUM (Price*productQuantity) AS \"Total Price\"  FROM Products JOIN orders USING (productId) WHERE orders.date BETWEEN $1 AND $2;"
                << endl;
        S.requestNewPreparedStatement(getOrdersExpensesBy2Dates, query.str());
    }

    if (!S.getPreparedStatement(getTotalExpenseOnSalary)) {
        stringstream query;
        query << "SELECT SUM(salary) AS \"Total salaries\" FROM users;" << endl;
        S.requestNewPreparedStatement(getTotalExpenseOnSalary, query.str());
    }

    if (!S.getPreparedStatement(getTotalWorthOfStockProducts)) {
        stringstream query;
        query << "SELECT SUM(quantity*price) AS \"Products worth\" FROM products;" << endl;
        S.requestNewPreparedStatement(getTotalWorthOfStockProducts, query.str());
    }

    if (!S.getPreparedStatement(getFinancialStatus)) {
        stringstream query;
        query
                << "SELECT SUM((SELECT SUM(productprice*productquantity) FROM transactions)-(SELECT SUM(salary) FROM users)-(SELECT SUM (Price*productQuantity) FROM Products JOIN orders USING (productId))) AS \"Total\""
                << endl;
        S.requestNewPreparedStatement(getFinancialStatus, query.str());
    }

    if (!S.getPreparedStatement(getFinancialStatusBy2Dates)) {
        stringstream query;
        query
                << "SELECT SUM((SELECT SUM(productprice*productquantity) FROM transactions WHERE transactions.date BETWEEN $1 AND $2)-(SELECT SUM(salary) FROM users)-(SELECT SUM (Price*productQuantity) FROM Products JOIN orders USING (productId) WHERE orders.date BETWEEN $1 AND $2)) AS \"Total\" "
                << endl;
        S.requestNewPreparedStatement(getFinancialStatusBy2Dates, query.str());
    }

    if (!S.getPreparedStatement(getCustomerCountriesByBills)) {
        stringstream query;
        query << "SELECT DISTINCT country FROM bill; " << endl;
        S.requestNewPreparedStatement(getCustomerCountriesByBills, query.str());
    }

    if (!S.getPreparedStatement(getNumberOrdersByEachUser)) {
        stringstream query;
        query << "SELECT userid, COUNT(orderid) FROM orders GROUP BY userid" << endl;
        S.requestNewPreparedStatement(getNumberOrdersByEachUser, query.str());
    }

    if (!S.getPreparedStatement(getProductWithMinQuantity)) {
        stringstream query;
        query
                << "SELECT productId, productname, quantity FROM products WHERE quantity = (SELECT min(quantity) FROM products);"
                << endl;
        S.requestNewPreparedStatement(getProductWithMinQuantity, query.str());
    }

    if (!S.getPreparedStatement(insertUser)) {
        stringstream query;
        query << "INSERT INTO users VALUES (default, $1, $2, $3, $4, $5, $6, $7);" << endl;
        S.requestNewPreparedStatement(insertUser, query.str());
    }

    if (!S.getPreparedStatement(changeSalaryByUserID)) {
        stringstream query;
        query << "UPDATE users SET salary = $1 WHERE userid = $2;" << endl;
        S.requestNewPreparedStatement(changeSalaryByUserID, query.str());
    }

    if (!S.getPreparedStatement(getContactDetailsByName)) {
        stringstream query;
        query << "SELECT fullname, email, mobilephone FROM users WHERE fullname LIKE $1;" << endl;
        S.requestNewPreparedStatement(getContactDetailsByName, query.str());
    }

    if (!S.getPreparedStatement(changeUserPassword)) {
        stringstream query;
        query << "UPDATE users SET passwordone = $1 WHERE userid = $2;" << endl;
        S.requestNewPreparedStatement(changeUserPassword, query.str());
    }
}

void Admin::getAllTransactionsByDatef() {

    std::string date;
    cout << "Please enter the date in the form yyyy/mm/dd: ";
    cin >> date;

    const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_TRANSACTIONS_BY_DATE");
    SQLResult sqlResult = ps->run({date});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTransaction ID: " << sqlResultTable[i]->getString(0)<< endl;
            cout << "Product price: " << sqlResultTable[i]->getString(1)<< "$" << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(2)<< endl;
            cout << "User ID: " << sqlResultTable[i]->getString(3)<< endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4)<< endl;
            cout << "Date: " << sqlResultTable[i]->getString(5)<<  endl;
        }
    }
}

void Admin::getTotalIncomeTodayf() {
    std::string date;
    cout << "Please enter the date in the form yyyy/mm/dd: ";
    cin >> date;

    const PreparedStatement *ps = S.getPreparedStatement("GET_TOTAL_INCOME_TODAY");
    SQLResult sqlResult = ps->run({date});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal income: " << sqlResultTable[i]->getString(0)<< "$" <<endl;

        }
    }
}

void Admin::getAllTransactionsBy2Datesf() {
    std::string date;
    cout << "Please enter the first date in the form yyyy/mm/dd: ";
    cin >> date;
    std::string date2;
    cout << "Please enter the second date in the form yyyy/mm/dd: ";
    cin >> date2;

    const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_TRANSACTIONS_BY_2_DATES");
    SQLResult sqlResult = ps->run({date,date2});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTransaction ID: " << sqlResultTable[i]->getString(0)<< endl;
            cout << "Product price: " << sqlResultTable[i]->getString(1)<< "$" << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(2)<< endl;
            cout << "User ID: " << sqlResultTable[i]->getString(3)<< endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4)<< endl;
            cout << "Date: " << sqlResultTable[i]->getString(5)<<  endl;

        }
    }
}

void Admin::getTotalIncomeFromTransactionsf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_TOTAL_INCOME_FROM_TRANSACTIONS");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal income from transactions: " << sqlResultTable[i]->getString(0)<< "$"<< endl;


        }
    }
}

void Admin::getTotalIncomeBy2Datesf() {
std::string date1;
    std::string date2;
    cout << "Please enter the first date: ";
    cin >> date1;
    cout << "Please enter the second date: ";
    cin >> date2;
    const PreparedStatement *ps = S.getPreparedStatement("GET_TOTAL_INCOME_BY_2_DATES");
    SQLResult sqlResult = ps->run({date1,date2});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal income from "+date1 << " to "+date2<<": " << sqlResultTable[i]->getString(0)<< "$" <<endl;


        }
    }
}

void Admin::getOrdersExpensesBy2Datesf() {
    std::string date1;
    std::string date2;
    cout << "Please enter the first date: ";
    cin >> date1;
    cout << "Please enter the second date: ";
    cin >> date2;
    const PreparedStatement *ps = S.getPreparedStatement("GET_ORDERS_EXPENSES_BY_2_DATES");
    SQLResult sqlResult = ps->run({date1,date2});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal expense on orders from "+date1 << " to "+date2<<": " << sqlResultTable[i]->getString(0)<< "$" << endl;


        }
    }
}

void Admin::getTotalExpenseOnSalaryf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_TOTAL_EXPENSE_ON_SALARY");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal expense on salary: " << sqlResultTable[i]->getString(0)<< "$" << endl;
        }
    }
}

void Admin::getTotalWorthOfStockProductsf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_TOTAL_WORTH_OF_STOCK_PRODUCTS");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal worth of products in our stock: " << sqlResultTable[i]->getString(0)<< "$" << endl;
        }
    }
}

void Admin::getFinancialStatusf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_FINANCIAL_STATUS");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nPharmacy's total income/expense - finanacial status: " << sqlResultTable[i]->getString(0)<< "$" << endl;
        }
    }
}

void Admin::getFinancialStatusBy2Datesf() {

    std::string date1;
    cout << "Please enter the first date: ";
    cin >> date1;
    std::string date2;
    cout << "Please enter the second date: ";
    cin >> date2;

    const PreparedStatement *ps = S.getPreparedStatement("GET_FINANCIAL_STATUS_BY_2_DATES");
    SQLResult sqlResult = ps->run({date1,date2});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nPharmacy's total income/expense - finanacial status from "+date1 << " to "+date2<< ": " << sqlResultTable[i]->getString(0)<< "$" << endl;
        }
    }
}

void Admin::getCustomerCountriesByBillsf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_CUSTOMER_COUNTRIES_BY_BILLS");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nCountry: " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Admin::getNumberOrdersByEachUserf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_NUMBER_ORDERS_BY_EASY_USER");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nUser ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Number of orders done: " << sqlResultTable[i]->getString(1) << endl;
        }
    }
}

void Admin::getProductWithMinQuantityf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_WITH_MIN_QUANTITY");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Quantity: " << sqlResultTable[i]->getString(2) << endl;
        }
    }
}

void Admin::insertUserf() {
    std::string username;
    std::string password;
    std::string usertype;
    int salary;
    std::string fullname;
    std::string email;
    unsigned long mobilephone;

    cout << "Please enter the username: ";
    cin >> username;
    cout << "Please enter the password ";
    cin >> password;
    cout << "Please enter the user type: ";
    cin >> usertype;
    cout << "Please enter the salary: ";
    cin >> salary;
    cout << "Please enter the fullname: ";
    cin >> fullname;
    cout << "Please enter the email: ";
    cin >> email;
    cout << "Please enter the mobilephone: ";
    cin >> mobilephone;

    const PreparedStatement *ps = S.getPreparedStatement("INSERT_USER");
    SQLResult sqlResult = ps->run({username, password,usertype,to_string(salary), fullname, email, to_string(mobilephone)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
    }
            cout << "\n The new user has been inserted! " << endl;
}


void Admin::changeSalaryByUserIDf() {

    int ID;
    int salary;

    cout << "Please enter the user ID: ";
    cin >> ID;
    cout << "Please enter the new salary: ";
    cin >> salary;


    const PreparedStatement *ps = S.getPreparedStatement("CHANGE_SALARY_BY_USER_ID");
    SQLResult sqlResult = ps->run({to_string(salary), to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
    }
            cout << "\n The salary has been changed! " << endl;
    }


void Admin::getContactDetailsByNamef() {

    std::string username;
    cout << "Please enter the username: ";
    cin >> username;

    const PreparedStatement *ps = S.getPreparedStatement("GET_CONTACT_DETAILS_BY_NAME");
    SQLResult sqlResult = ps->run({"%"+username+"%"});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nFull name: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Email: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Mobile phone: " << sqlResultTable[i]->getString(2) << endl;
        }

    }
}

void Admin::changeUserPasswordf() {

    int ID;
    cout << "Please enter the user ID: ";
    cin >> ID;
    std::string password;
    cout << "Please enter the new password: ";
    cin >> password;

    const PreparedStatement *ps = S.getPreparedStatement("CHANGE_USER_PASSWORD");
    SQLResult sqlResult = ps->run({password, to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
    }
            cout << "\nThe password has been changed!" << endl;
}

void Admin::userAdmin() {

    cout << "\n\n\t\t\t\tPlease select an option by number!\n\n" ;
    cout << "\t\t\t\t\t\t\t\tEmployee selections: \n\n" ;
    cout << "\t\t\t\t1- Get a product by the product ID." ;
    cout << "\t\t\t\t\t\t\t2- Get a product by the product name."<< endl;
    cout << "\t\t\t\t3- Get a product price by the product name." ;
    cout << "\t\t\t\t\t4- Get a product ID."<< endl;
    cout << "\t\t\t\t5- Get a product name" ;
    cout << "\t\t\t\t\t\t\t\t\t\t6- Get a product details by the product name."<< endl;
    cout << "\t\t\t\t7- Get a product IMG. " ;
    cout << "\t\t\t\t\t\t\t\t\t\t8- Get a product quantity by the product name."<< endl;
    cout << "\t\t\t\t9- Get a product quantity by the product ID." ;
    cout << "\t\t\t\t10- Get a product by the product category ID."<< endl;
    cout << "\t\t\t\t11- Get the number of products available." ;
    cout << "\t\t\t\t\t12- Get a product price by the product ID."<< endl;
    cout << "\t\t\t\t13- Get a product by the product description." ;
    cout << "\t\t\t\t14- Get all the products in a category by ID."<< endl;
    cout << "\t\t\t\t15- Get all the products in a category by name.\n\n" ;
    cout << "\t\t\t\tEmployee selections:"<<endl;
    cout << "\n\n16- Add Order" << endl;
    cout << "17- Remove order by order name ID." << endl;
    cout << "18- Update order quantity." << endl;
    cout << "19- Insert Transaction." << endl;
    cout << "20- Get transaction by transaction date." << endl;
    cout << "21- Get all transactions of a specific product." << endl;
    cout << "22- Get all Categories." << endl;
    cout << "23- Get products by category ID." << endl;
    cout << "24- Add Bill." << endl;
    cout << "25- Get Bill by ID.\n\n" << endl;
    cout << "\t\t\t\tManager selections:"<<endl;
    cout << "\n\n26- Insert a new Product." << endl;
    cout << "27- Change a product price by product name." << endl;
    cout << "28- Change a product price by product ID." << endl;
    cout << "29- Change a product quantity by product name." << endl;
    cout << "30- Change a product quantity by product ID." << endl;
    cout << "31- Get all orders total price." << endl;
    cout << "32- Get each order total price." << endl;
    cout << "33- Insert a new category." << endl;
    cout << "34- Get the total number of Transactions done." << endl;
    cout << "35- Get transaction of a specific product." << endl;
    cout << "36- Get all Transactions done by an Employee by Employee ID." << endl;
    cout << "37- Get Transactions done by an Employee by Employee name.\n\n" << endl;
    cout << "\t\t\t\tAdmin selections:"<<endl;
    cout << "38- Get All Transactions by date." << endl;
    cout << "39- Get total income today." << endl;
    cout << "40- Get all transactions between two dates." << endl;
    cout << "41- Get total income from transactions." << endl;
    cout << "42- Get total income between two dates." << endl;
    cout << "43- Get orders expenses between two dates." << endl;
    cout << "44- Get total expenses spent on salary." << endl;
    cout << "45- Get total worth of the products stock." << endl;
    cout << "46- Get the general financial status of the Pharmacy." << endl;
    cout << "47- Get the general financial status between two dates." << endl;
    cout << "48- Get total worth of the products stock." << endl;
    cout << "49- Get the general financial status of the Pharmacy." << endl;
    cout << "50- Get the general financial status between two dates." << endl;

    int choice;
    cout << "\n\t\t\t\tSelect: ";
    cin >> choice;
    cout << "\n\n";

    switch (choice)
    {
        case 1: getProductFromIDf();
        case 2: getProductFromNamef();
        case 3: getProductPriceByNamef();
        case 4: getProductIDf();
        case 5: getProductNamef();
        case 6: getProductDetailsByNamef();
        case 7: getProductIMGf();
        case 8: getProductQuantityByNamef();
        case 9: getProductQuantityByIDf();
        case 10: getProductCategoryIDf();
        case 11: getNumberOfProductsf();
        case 12: getProductPriceByIDf();
        case 13: getProductByDescriptionf();
        case 14: getAllProductsByCategoryIDf();
        case 15: getAllProductsByCategoryNamef();
        case 16: addOrderf();
        case 17: removeOrderByNameIDf();
        case 18: updateOrderQuantityf();
        case 19: insertTransactionf();
        case 20: getTransactionFromDatef();
        case 21: getAllTransactionsOfAProductf();
        case 22: getAllCategoriesf();
        case 23: getProductsByCategoryIDf();
        case 24: addBillf();
        case 25: getBillByIDf();
        case 26: insertProductf();
        case 27: changeProductPriceByNamef();
        case 28: changeProductPriceByIDf();
        case 29: changeProductQuantityByNamef();
        case 30: changeProductQuantityByIDf();
        case 31: getOrdersTotalPricef();
        case 32: getEachOrderTotalPricef();
        case 33: insertCategoryf();
        case 34: getTotalNumberOfTransactionsf();
        case 35: getTransactionOfSpecificProductf();
        case 36: getTransactionsDoneByUserIDf();
        case 37: getTransactionsDoneByUserNamef();
        case 38: getAllTransactionsBy2Datesf();
        case 39: getTotalIncomeTodayf();
        case 40: getAllTransactionsBy2Datesf();
        case 41: getTotalIncomeFromTransactionsf();
        case 42: getTotalIncomeBy2Datesf();
        case 43: getOrdersExpensesBy2Datesf();
        case 44: getTotalExpenseOnSalaryf();
        case 45: getTotalWorthOfStockProductsf();
        case 46: getFinancialStatusf();
        case 47: getFinancialStatusBy2Datesf();
        case 48: getCustomerCountriesByBillsf();
        case 49: getNumberOrdersByEachUserf();
        case 50: getProductWithMinQuantityf();
        default: "Error! Please enter a number from 1 to 50.";

    }
}
