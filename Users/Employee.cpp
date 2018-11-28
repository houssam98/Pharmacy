//
// Created by houss on 4/26/2017.
//

#include "Employee.hpp"
#include "Customer.hpp"

#include "../Headers/DBMS.hpp"
#include <sstream>
#include <algorithm>

using namespace std;

//Orders
const std::string Employee::addOrder = "ADD_ORDER";
const std::string Employee::removeOrderByNameID = "REMOVE_ORDER_BY_NAME_ID";
const std::string Employee::updateOrderQuantity = "UPDATE_ORDER_QUANTITY";
//Transactions
const std::string Employee::insertTransaction = "INSERT_TRANSACTION";
const std::string Employee::getTransactionFromDate = "GET_TRANSACTION_FROM_DATE";
const std::string Employee::getAllTransactionsOfAProduct = "GET_ALL_TRANSACTIONS_OF_A_PRODUCT";
//Category
const std::string Employee::getAllCategories = "GET_ALL_CATEGORIES";
const std::string Employee::getProductsByCategoryID = "GET_PRODUCTS_BY_CATEGORY_ID";
//Bills
const std::string Employee::addBill = "ADD_BILL";
const std::string Employee::getBillByID = "GET_BILL_BY_ID";



void Employee::InitPreparedStatements() {


    if (!S.getPreparedStatement(addOrder)) {
        stringstream query;
        query << "INSERT INTO orders VALUES (DEFAULT, $1, $2, $3, $4);" << endl;
        S.requestNewPreparedStatement(addOrder, query.str());
    }

    if (!S.getPreparedStatement(removeOrderByNameID)) {
        stringstream query;
        query << "DELETE FROM orders WHERE productid = $1;" << endl;
        S.requestNewPreparedStatement(removeOrderByNameID, query.str());
    }

    if (!S.getPreparedStatement(updateOrderQuantity)) {
        stringstream query;
        query << "UPDATE orders SET productquantity = $1 WHERE productid = $2;" << endl;
        S.requestNewPreparedStatement(updateOrderQuantity, query.str());
    }

    if (!S.getPreparedStatement(insertTransaction)) {
        stringstream query;
        query << "INSERT INTO transactions VALUES ( default, $1, $2, $3, $4, $5 );" << endl;
        S.requestNewPreparedStatement(insertTransaction, query.str());
    }

    if (!S.getPreparedStatement(getTransactionFromDate)) {
        stringstream query;
        query << "SELECT * FROM transactions WHERE date = $1;" << endl;
        S.requestNewPreparedStatement(getTransactionFromDate, query.str());
    }

    if (!S.getPreparedStatement(getAllTransactionsOfAProduct)) {
        stringstream query;
        query << "SELECT * FROM transactions WHERE productname LIKE $1;" << endl;
        S.requestNewPreparedStatement(getAllTransactionsOfAProduct, query.str());
    }


    if (!S.getPreparedStatement(getAllCategories)) {
        stringstream query;
        query << "SELECT * FROM category;" << endl;
        S.requestNewPreparedStatement(getAllCategories, query.str());
    }

    if (!S.getPreparedStatement(getProductsByCategoryID)) {
        stringstream query;
        query
                << "SELECT productname,quantity FROM products JOIN category ON(product_category_Id = categoryid) WHERE categoryid = $1;"
                << endl;
        S.requestNewPreparedStatement(getProductsByCategoryID, query.str());
    }

    if (!S.getPreparedStatement(addBill)) {
        stringstream query;
        query << "INSERT INTO bill VALUES (default, $1, $2, $3, $4, $5, $6, $7, $8);" << endl;
        S.requestNewPreparedStatement(addBill, query.str());
    }

    if (!S.getPreparedStatement(getBillByID)) {
        stringstream query;
        query << "SELECT * FROM bill WHERE billid = $1;" << endl;
        S.requestNewPreparedStatement(getBillByID, query.str());
    }

}

void Employee::addOrderf() {
    int ID;
    std::string date;
    int userid;
    int quantity;
    cout << "Please enter the productid: ";
    cin >> ID;
    cout << "Please enter the order date: ";
    cin >> date;
    cout << "Please enter your user ID: ";
    cin >> userid;
    cout << "Please enter the product quantity: ";
    cin >> quantity;

    const PreparedStatement *ps = S.getPreparedStatement("ADD_ORDER");
    SQLResult sqlResult = ps->run({to_string(ID), date,to_string(userid), to_string(quantity)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nInsert: " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Employee::removeOrderByNameIDf() {
    int ID;
    cout << "Please enter the product ID: ";
    cin >> ID;

    const PreparedStatement *ps = S.getPreparedStatement("REMOVE_ORDER_BY_NAME_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n" << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Employee::updateOrderQuantityf() {
    int quantity;
    std::string name;
    cout << "Please enter the new order quantity: ";
    cin >> quantity;
    cout << "Please enter the product name: ";
    cin >> name;

    transform(name.begin(),name.end(),name.begin(),::toupper);

    const PreparedStatement *ps = S.getPreparedStatement("UPDATE_ORDER_QUANTITY");
    SQLResult sqlResult = ps->run({to_string(quantity), "%" + name + "%"});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n" << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Employee::insertTransactionf() {
    std::string productname;
    int userid;
    std::string date;
    double price;
    int quantity;
    cout << "Please enter the product price: ";
    cin >> price;
    cout << "Please enter the product quantity: ";
    cin >> quantity;
    cout << "Please enter your user ID: ";
    cin >> userid;
    cout << "Please enter the product name: ";
    cin >> productname;
    cout << "Please enter transaction date:";
    cin >> date;

    transform(productname.begin(),productname.end(),productname.begin(),::toupper);

    const PreparedStatement *ps = S.getPreparedStatement("INSERT_TRANSACTION");
    SQLResult sqlResult = ps->run({to_string(price), to_string(quantity),to_string(userid), productname, date});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\n " << sqlResultTable[i]->getString(0) << endl;
        }
    }
}

void Employee::getTransactionFromDatef() {

    std::string date;
    cout << "Please enter the transaction date: ";
    cin >> date;

    const PreparedStatement *ps = S.getPreparedStatement("GET_TRANSACTION_FROM_DATE");
    SQLResult sqlResult = ps->run({date});
    if (sqlResult.hasError()) {
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTransaction ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product price: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(2) << endl;
            cout << "User ID: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Date: " << sqlResultTable[i]->getString(5) << endl;
        }
    }
}

void Employee::getAllTransactionsOfAProductf() {

    std::string productname;
    cout << "Please enter the product name: ";
    cin >> productname;

    transform(productname.begin(),productname.end(),productname.begin(),::toupper);

    const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_TRANSACTIONS_OF_A_PRODUCT");
    SQLResult sqlResult = ps->run({"%"+productname+"%"});
    if (sqlResult.hasError()) {
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nTransaction ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product price: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(2) << endl;
            cout << "User ID: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Date: " << sqlResultTable[i]->getString(5) << endl;
        }
    }
}

void Employee::getAllCategoriesf() {
    const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_CATEGORIES");
    SQLResult sqlResult = ps->run({});
    if (sqlResult.hasError()) {
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nCategory ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Category name: " << sqlResultTable[i]->getString(1) << endl;
        }
    }
}

void Employee::getProductsByCategoryIDf() {
    int ID;
    cout << "Please enter the category ID: ";
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCTS_BY_CATEGORY_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasError()) {
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct Name: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product ID: " << sqlResultTable[i]->getString(1) << endl;
        }
    }
}

void Employee::addBillf() {

    std::string creditcard;
    unsigned long creditnumber;
    std::string firstname;
    std::string lastname;
    std::string date;
    std::string country;
    std::string adress;
    double amount;

    cout << "Please enter the Credit Card type: ";
    cin >> creditcard;
    cout << "Please enter the Credit Card number: ";
    cin >> creditnumber;
    cout << "Please enter the First Name: ";
    cin >> firstname;
    cout << "Please enter the Last Name: ";
    cin >> lastname;
    cout << "Please enter transaction date: ";
    cin >> date;
    cout << "Please enter the country: ";
    cin >> country;
    cout << "Please enter the address: ";
    cin >> adress;
    cout << "Please enter the amount: ";
    cin >> amount;

    const PreparedStatement *ps = S.getPreparedStatement("ADD_BILL");
    SQLResult sqlResult = ps->run({creditcard,to_string(creditnumber), firstname, lastname, date, country, adress, to_string(amount)});
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

void Employee::getBillByIDf() {
    int ID;
    cout << "Please enter the bill ID: ";
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_BILL_BY_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if(sqlResult.hasError()){
        cerr << sqlResult.getErrorMessage();
    }
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nBill ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Credit card type: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Credit card number: " << sqlResultTable[i]->getString(2) << endl;
            cout << "First name: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Last name: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Date: " << sqlResultTable[i]->getString(5) << endl;
            cout << "Country: " << sqlResultTable[i]->getString(6) << endl;
            cout << "Adress: " << sqlResultTable[i]->getString(7) << endl;
            cout << "Amount: " << sqlResultTable[i]->getString(8) << endl;
        }
    }
}

void Employee::getProductFromIDf() {
    int ID;
    cout << "Please enter the product ID: " << endl;
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_FROM_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        cout << "\nProduct ID: " << sqlResultTable[0]->getString(0) << endl;
        cout << "Product Name: " << sqlResultTable[0]->getString(1) << endl;
        cout << "Product Details: " << sqlResultTable[0]->getString(2) << endl;
        cout << "Product IMG: " << sqlResultTable[0]->getString(3) << endl;
        cout << "Product Quantity: " << sqlResultTable[0]->getString(4) << endl;
        cout << "Product Category ID: " << sqlResultTable[0]->getString(5) << endl;
        cout << "Product Price: " << sqlResultTable[0]->getString(6) << "\n" << endl;
    }
}



void Employee::userEmployeef() {

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
        default: "Error! Please enter a number from 1 to 25.";


    }
}