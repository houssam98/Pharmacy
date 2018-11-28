//
// Created by houss on 4/26/2017.
//

#include "Manager.hpp"
#include "../Headers/DBMS.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

//Products
const std::string Manager::insertProduct = "INSERT_PRODUCT";
const std::string Manager::changeProductPriceByName = "CHANGE_PRODUCT_PRICE_BY_NAME";
const std::string Manager::changeProductPriceByID = "CHANGE_PRODUCT_PRICE_BY_ID";
const std::string Manager::changeProductQuantityByName = "CHANGE_PRODUCT_QUANTITY_BY_NAME";
const std::string Manager::changeProductQuantityByID = "CHANGE_PRODUCT_QUANTITY_BY_ID";

const std::string Manager::getOrdersTotalPrice = "GET_ORDERS_TOTAL_PRICE";
const std::string Manager::getEachOrderTotalPrice = "GET_EACH_ORDER_TOTAL_PRICE";

const std::string Manager::insertCategory = "INSERT_CATEGORY";

const std::string Manager::getTotalNumberOfTransactions = "GET_TOTAL_NUMBER_OF_TRANSACTIONS";
const std::string Manager::getTransactionOfSpecificProduct = "GET_TRANSACTION_OF_SPECIFIC_PRODUCT";
const std::string Manager::getTransactionsDoneByUserID = "GET_TRANSACTIONS_DONE_BY_USER_ID";
const std::string Manager::getTransactionsDoneByUserName = "GET_TRANSACTIONS_DONE_BY_USER_NAME";



void Manager::InitPreparedStatements() {

    if (!S.getPreparedStatement(getOrdersTotalPrice)) {
        stringstream query;
        query << "SELECT SUM (Price*productQuantity) FROM Products JOIN orders USING (productid)" << endl;
        S.requestNewPreparedStatement(getOrdersTotalPrice, query.str());
    }

    if (!S.getPreparedStatement(getEachOrderTotalPrice)) {
        stringstream query;
        query
                << "SELECT orderID, SUM (Price*productQuantity) FROM Products JOIN orders USING (productid) GROUP BY orderID ORDER BY orderid"
                << endl;
        S.requestNewPreparedStatement(getEachOrderTotalPrice, query.str());
    }

    if (!S.getPreparedStatement(changeProductQuantityByID)) {
        stringstream query;
        query << "UPDATE products SET quantity = $1 WHERE productid = $2;" << endl;
        S.requestNewPreparedStatement(changeProductQuantityByID, query.str());
    }

    if (!S.getPreparedStatement(insertProduct)) {
        stringstream query;
        query << "INSERT INTO products" << endl;
        query << "VALUES (default, $1, $2, $3, $4, $5, $6)";
        S.requestNewPreparedStatement(insertProduct, query.str());
    }

    if (!S.getPreparedStatement(changeProductPriceByName)) {
        stringstream query;
        query << "UPDATE products SET price = $1 WHERE productname LIKE $2;" << endl;
        S.requestNewPreparedStatement(changeProductPriceByName, query.str());
    }

    if (!S.getPreparedStatement(changeProductPriceByID)) {
        stringstream query;
        query << "UPDATE products SET price = $1 WHERE productid = $2;" << endl;
        S.requestNewPreparedStatement(changeProductPriceByID, query.str());
    }

    if (!S.getPreparedStatement(changeProductQuantityByName)) {
        stringstream query;
        query << "UPDATE products SET quantity = $1 WHERE productname LIKE $2;" << endl;
        S.requestNewPreparedStatement(changeProductQuantityByName, query.str());
    }

    if (!S.getPreparedStatement(insertCategory)) {
        stringstream query;
        query << "INSERT INTO category VALUES ( default, $1);" << endl;
        S.requestNewPreparedStatement(insertCategory, query.str());
    }

    if (!S.getPreparedStatement(getTotalNumberOfTransactions)) {
        stringstream query;
        query << "SELECT COUNT(transactionid) FROM transactions;" << endl;
        S.requestNewPreparedStatement(getTotalNumberOfTransactions, query.str());
    }

    if (!S.getPreparedStatement(getTransactionOfSpecificProduct)) {
        stringstream query;
        query << "SELECT * FROM transactions WHERE productname LIKE $1 ORDER BY transactionid;" << endl;
        S.requestNewPreparedStatement(getTransactionOfSpecificProduct, query.str());
    }

    if (!S.getPreparedStatement(getTransactionsDoneByUserID)) {
        stringstream query;
        query << "SELECT * FROM transactions WHERE userid = $1;" << endl;
        S.requestNewPreparedStatement(getTransactionsDoneByUserID, query.str());
    }

    if (!S.getPreparedStatement(getTransactionsDoneByUserName)) {
        stringstream query;
        query << "SELECT * FROM transactions JOIN users USING(userid) WHERE users.username LIKE $1;"
              << endl;
        S.requestNewPreparedStatement(getTransactionsDoneByUserName, query.str());
    }
}

    void Manager::insertProductf() {

        std::string productname;
        std::string productdetails;
        std::string productIMG;
        int quantity;
        int categoryID;
        double price;

        cout << "Please enter the product name: ";
        cin >> productname;
        cout << "Please enter the product details: ";
        cin >> productdetails;
        cout << "Please enter the product IMG: ";
        cin >> productIMG;
        cout << "Please enter the product quantity: ";
        cin >> quantity;
        cout << "Please enter product category ID: ";
        cin >> categoryID;
        cout << "Please enter the product price: ";
        cin >> price;

        transform(productname.begin(),productname.end(),productname.begin(),::toupper);

        const PreparedStatement *ps = S.getPreparedStatement("INSERT_PRODUCT");
        SQLResult sqlResult = ps->run({productname, productdetails, productIMG, to_string(quantity), to_string(categoryID), to_string(price)});
        if(sqlResult.hasError()){
            cerr << sqlResult.getErrorMessage();
        }
        if (sqlResult.hasTableResult()) {
            const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
            //cout << sqlResult << endl;
            unsigned long tuple = sqlResultTable.getNumberOfTuples();
            for (int i = 0; i < tuple; i++) {
                cout << "\n " << sqlResultTable[i]->getString(0) << endl;
            }
        }
    }

void Manager::changeProductPriceByNamef() {

    std::string productname;
    double price;
    cout << "Please enter the product name: ";
    cin >> productname;
    cout << "Please enter the new product price: ";
    cin >> price;

    transform(productname.begin(),productname.end(),productname.begin(),::toupper);

    const PreparedStatement *ps = S.getPreparedStatement("CHANGE_PRODUCT_PRICE_BY_NAME");
    SQLResult sqlResult = ps->run({to_string(price), "%"+productname+"%"});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Manager::changeProductPriceByIDf() {

    int ID;
    double price;
    cout << "Please enter the product ID: ";
    cin >> ID;
    cout << "Please enter the new product price: ";
    cin >> price;


    const PreparedStatement *ps = S.getPreparedStatement("CHANGE_PRODUCT_PRICE_BY_ID");
    SQLResult sqlResult = ps->run({to_string(price), to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Manager::changeProductQuantityByNamef() {

    std::string productname;
    int quantity;
    cout << "Please enter the product name: ";
    cin >>productname;
    cout << "Please enter the product quantity: ";
    cin >> quantity;

    transform(productname.begin(),productname.end(),productname.begin(),::toupper);

    const PreparedStatement *ps = S.getPreparedStatement("CHANGE_PRODUCT_QUANTITY_BY_NAME");
    SQLResult sqlResult = ps->run({to_string(quantity), "%"+productname+"%"});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Manager::changeProductQuantityByIDf() {

    int ID;
    int quantity;
    cout << "Please enter the product ID: ";
    cin >> ID;
    cout << "Please enter the product quantity: ";
    cin >> quantity;

    const PreparedStatement *ps = S.getPreparedStatement("CHANGE_PRODUCT_QUANTITY_BY_ID");
    SQLResult sqlResult = ps->run({to_string(quantity), to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Manager::getOrdersTotalPricef() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_ORDERS_TOTAL_PRICE");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "All orders total price: " << sqlResultTable[i]->getString(0)<< "$" << endl;
        }
    }
}

void Manager::getEachOrderTotalPricef() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_EACH_ORDER_TOTAL_PRICE");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nOrder ID: " << sqlResultTable[i]->getString(0)<< endl;
            cout << "Total price: " << sqlResultTable[i]->getString(1)<< "$" << endl;
        }
    }
}

void Manager::insertCategoryf() {

    std::string categoryname;
    cout << " Please enter the category name: ";
    cin >> categoryname;

    const PreparedStatement *ps = S.getPreparedStatement("INSERT_CATEGORY");
    SQLResult sqlResult = ps->run({categoryname});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n" << sqlResultTable[i]->getString(0)<< endl;

        }
    }
}


void Manager::getTotalNumberOfTransactionsf() {

    const PreparedStatement *ps = S.getPreparedStatement("GET_TOTAL_NUMBER_OF_TRANSACTIONS");
    SQLResult sqlResult = ps->run({});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTotal number of Transactions: " << sqlResultTable[i]->getString(0)<< endl;
        }
    }
}



void Manager::getTransactionOfSpecificProductf() {

    std::string productname;
    cout << "Please enter the product name: ";
    cin >> productname;

    transform(productname.begin(),productname.end(),productname.begin(),::toupper);

    const PreparedStatement *ps = S.getPreparedStatement("GET_TRANSACTION_OF_SPECIFIC_PRODUCT");
    SQLResult sqlResult = ps->run({"%"+productname+"%"});
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
            cout << "Total quantity " << sqlResultTable[i]->getString(2)<< endl;
            cout << "User ID: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Date: " << sqlResultTable[i]->getString(5)<< endl;
        }
    }
}

void Manager::getTransactionsDoneByUserIDf() {

    int ID;
    cout << "Please enter the product ID: ";
    cin >> ID;

    const PreparedStatement *ps = S.getPreparedStatement("GET_TRANSACTIONS_DONE_BY_USER_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nUser ID: " << sqlResultTable[i]->getString(0)<< endl;
            cout << "Transaction ID: " << sqlResultTable[i]->getString(1)<< endl;
            cout << "Product price: " << sqlResultTable[i]->getString(2)<< "$" << endl;
            cout << "Product quantity " << sqlResultTable[i]->getString(3)<< endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4)<< endl;
            cout << "Date: " << sqlResultTable[i]->getString(5)<<  endl;
        }
    }
}

void Manager::getTransactionsDoneByUserNamef() {

    std::string username;
    cout << "Please enter the user name: ";
    cin >> username;

    const PreparedStatement *ps = S.getPreparedStatement("GET_TRANSACTIONS_DONE_BY_USER_NAME");
    SQLResult sqlResult = ps->run({"%"+username+"%"});
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
            cout << "Product quantity " << sqlResultTable[i]->getString(2)<< endl;
            cout << "User ID: " << sqlResultTable[i]->getString(3)<< endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4)<< endl;
            cout << "Date: " << sqlResultTable[i]->getString(5)<<  endl;
        }
    }
}

void Manager::userManager() {

    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tCustomer selections: \n\n" ;
    cout << "\t\t\t\t1- Get a product by the product ID." ;
    cout << "\t\t\t\t\t\t\t\t2- Get a product by the product name."<< endl;
    cout << "\t\t\t\t3- Get a product price by the product name." ;
    cout << "\t\t\t\t\t\t4- Get a product ID."<< endl;
    cout << "\t\t\t\t5- Get a product name" ;
    cout << "\t\t\t\t\t\t\t\t\t\t\t6- Get a product details by the product name."<< endl;
    cout << "\t\t\t\t7- Get a product IMG. " ;
    cout << "\t\t\t\t\t\t\t\t\t\t\t8- Get a product quantity by the product name."<< endl;
    cout << "\t\t\t\t9- Get a product quantity by the product ID." ;
    cout << "\t\t\t\t\t10- Get a product by the product category ID."<< endl;
    cout << "\t\t\t\t11- Get the number of products available." ;
    cout << "\t\t\t\t\t\t12- Get a product price by the product ID."<< endl;
    cout << "\t\t\t\t13- Get a product by the product description." ;
    cout << "\t\t\t\t\t14- Get all the products in a category by ID."<< endl;
    cout << "\t\t\t\t15- Get all the products in a category by name.\n\n\n" ;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tEmployee selections:\n\n"<<endl;
    cout << "\t\t\t\t16- Add Order";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t17- Remove order by order name ID." << endl;
    cout << "\t\t\t\t18- Update order quantity.";
    cout << "\t\t\t\t\t\t\t\t\t\t19- Insert Transaction." << endl;
    cout << "\t\t\t\t20- Get transaction by transaction date.";
    cout << "\t\t\t\t\t\t21- Get all transactions of a specific product." << endl;
    cout << "\t\t\t\t22- Get all Categories.";
    cout << "\t\t\t\t\t\t\t\t\t\t\t23- Get products by category ID." << endl;
    cout << "\t\t\t\t24- Add Bill.";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t25- Get Bill by ID.\n\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tManager selections: \n\n"<<endl;
    cout << "\t\t\t\t26- Insert a new Product.";
    cout << "\t\t\t\t\t\t\t\t\t\t27- Change a product price by product name." << endl;
    cout << "\t\t\t\t28- Change a product price by product ID.";
    cout << "\t\t\t\t\t\t29- Change a product quantity by product name." << endl;
    cout << "\t\t\t\t30- Change a product quantity by product ID.";
    cout << "\t\t\t\t\t31- Get all orders total price." << endl;
    cout << "\t\t\t\t32- Get each order total price.";
    cout << "\t\t\t\t\t\t\t\t\t33- Insert a new category." << endl;
    cout << "\t\t\t\t34- Get the total number of Transactions done.";
    cout << "\t\t\t\t\t35- Get transaction of a specific product." << endl;
    cout << "\t\t\t\t36- Get all Transactions done by an Employee by Employee ID.";
    cout << "\t37- Get Transactions done by an Employee by Employee name.\n\n" << endl;

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
        default: "Error! Please enter a number from 1 to 37.";

    }
}
