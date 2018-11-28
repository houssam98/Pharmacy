//
// Created by houss on 4/26/2017.
//

#include <sstream>
#include "Customer.hpp"
#include "../Headers/DBMS.hpp"
#include <algorithm>


using namespace std;

//Products
const std::string Customer::getProductFromID = "GET_PRODUCT_FROM_ID";
const std::string Customer::getProductFromName = "GET_PRODUCT_FROM_NAME";
const std::string Customer::getProductPriceByName = "GET_PRODUCT_PRICE_BY_NAME";
const std::string Customer::getProductPriceByID = "GET_PRODUCT_PRICE_BY_ID";
const std::string Customer::getProductDetailsByName = "GET_PRODUCT_DETAILS_BY_NAME";
const std::string Customer::getProductID = "GET_PRODUCT_ID";
const std::string Customer::getProductName = "GET_PRODUCT_NAME";
const std::string Customer::getNumberOfProducts = "GET_NUMBER_OF_PRODUCTS";
const std::string Customer::getProductIMG = "GET_PRODUCT_IMG";
const std::string Customer::getProductQuantityByName = "GET_PRODUCT_QUANTITY_BY_NAME";
const std::string Customer::getProductQuantityByID = "GET_PRODUCT_QUANTITY_BY_ID";
const std::string Customer::getProductCategoryID = "GET_PRODUCT_CATEGORY_ID";
const std::string Customer::getProductByDescription = "GET_PRODUCT_BY_DESCRIPTION";
const std::string Customer::getAllProductsByCategoryID = "GET_ALL_PRODUCTS_BY_CATEGORY_ID";
const std::string Customer::getAllProductsByCategoryName = "GET_ALL_PRODUCTS_BY_CATEGORY_NAME";


void Customer::InitPreparedStatements() {


    if(!S.getPreparedStatement(getProductFromID)){
        stringstream query;
        query << "SELECT * FROM products" << endl;
        query << "WHERE productid = $1" << endl;
        S.requestNewPreparedStatement(getProductFromID, query.str());
    }

    if(!S.getPreparedStatement(getProductFromName)){
        stringstream query;
        query << "SELECT * FROM products" << endl;
        query << "WHERE productname LIKE $1";
        S.requestNewPreparedStatement(getProductFromName, query.str());
    }

    if(!S.getPreparedStatement(getProductPriceByName)){
        stringstream query;
        query << "SELECT productname, price FROM products" << endl;
        query << "WHERE productname LIKE $1";
        S.requestNewPreparedStatement(getProductPriceByName, query.str());
    }

    if(!S.getPreparedStatement(getProductDetailsByName)){
        stringstream query;
        query << "SELECT productid, productname ,productdetails FROM products WHERE productname LIKE $1 ORDER BY productid " << endl;
        S.requestNewPreparedStatement(getProductDetailsByName, query.str());
    }

    if(!S.getPreparedStatement(getProductID)){
        stringstream query;
        query << "SELECT productid FROM products" << endl;
        query << "WHERE productname LIKE $1;" << endl;
        S.requestNewPreparedStatement(getProductID, query.str());
    }

    if(!S.getPreparedStatement(getProductName)){
        stringstream query;
        query << "SELECT productid,productname FROM products" << endl;
        query << "WHERE productid = $1" << endl;
        S.requestNewPreparedStatement(getProductName, query.str());
    }

    if(!S.getPreparedStatement(getNumberOfProducts)){
        stringstream query;
        query << "SELECT COUNT(productid) FROM products;" << endl;
        S.requestNewPreparedStatement(getNumberOfProducts, query.str());
    }

    if(!S.getPreparedStatement(getProductIMG)){
        stringstream query;
        query << "SELECT productname, productimg FROM products " << endl;
        query << "WHERE productname LIKE $1";
        S.requestNewPreparedStatement(getProductIMG, query.str());
    }

    if(!S.getPreparedStatement(getProductQuantityByName)){
        stringstream query;
        query << "SELECT productname, quantity FROM products " << endl;
        query << "WHERE productname LIKE  $1" << endl;
        S.requestNewPreparedStatement(getProductQuantityByName, query.str());
    }

    if(!S.getPreparedStatement(getProductQuantityByID)){
        stringstream query;
        query << "SELECT productname, quantity FROM products " << endl;
        query << "WHERE productid = $1" << endl;
        S.requestNewPreparedStatement(getProductQuantityByID, query.str());
    }

    if(!S.getPreparedStatement(getProductCategoryID)){
        stringstream query;
        query << "SELECT productname, product_category_id FROM products " << endl;
        query << "WHERE productname LIKE $1" << endl;
        S.requestNewPreparedStatement(getProductCategoryID, query.str());
    }

    if(!S.getPreparedStatement(getProductPriceByID)){
        stringstream query;
        query << "SELECT productname, price FROM products " << endl;
        query << "WHERE productid = $1" << endl;
        S.requestNewPreparedStatement(getProductPriceByID, query.str());
    }

    if(!S.getPreparedStatement(getProductByDescription)){
        stringstream query;
        query << "SELECT * FROM products WHERE productdetails LIKE $1" << endl;
        S.requestNewPreparedStatement(getProductByDescription, query.str());
    }

    if(!S.getPreparedStatement(getAllProductsByCategoryID)){
        stringstream query;
        query << "SELECT * FROM products JOIN category ON(product_category_Id = categoryid) WHERE product_category_Id = $1;" << endl;
        S.requestNewPreparedStatement(getAllProductsByCategoryID, query.str());
    }

    if(!S.getPreparedStatement(getAllProductsByCategoryName)){
        stringstream query;
        query << "SELECT * FROM products JOIN category ON(product_category_Id = categoryid) WHERE categoryname LIKE $1;" << endl;
        S.requestNewPreparedStatement(getAllProductsByCategoryName, query.str());
    }

}

void Customer::getProductFromIDf() {
    int ID;
    cout << "Please enter the product ID: " << endl;
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_FROM_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        cout << "Product Name: " << sqlResultTable[0]->getString(1) << endl;
        cout << "Product Details: " << sqlResultTable[0]->getString(2) << endl;
        cout << "Product IMG: " << sqlResultTable[0]->getString(3) << endl;
        cout << "Product Category ID: " << sqlResultTable[0]->getString(5) << endl;
        cout << "Product Price: " << sqlResultTable[0]->getString(6) << "\n" << endl;
    }
}

void Customer::getProductFromNamef() {
    std::string name;
    cout << "Please enter a product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_FROM_NAME");
    SQLResult sqlResult = ps->run({"%" + name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product details: " << sqlResultTable[i]->getString(2) << endl;
            cout << "Product IMG: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Product category ID: " << sqlResultTable[i]->getString(5) << endl;
            cout << "Product price: " << sqlResultTable[i]->getString(6) << "\n" << endl;
        }
    }
}

void Customer::getProductPriceByNamef() {
    std::string name;
    cout << "Please enter the product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_PRICE_BY_NAME");
    SQLResult sqlResult = ps->run({"%" + name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for(int i=0; i<tuple;i++){
        cout << "\nProduct name: " << sqlResultTable[i]->getString(0) << endl;
        cout << "Product price: " << sqlResultTable[i]->getString(1) << endl; }
    }
}

void Customer::getProductPriceByIDf() {
    int ID;
    cout << "Please enter the product ID:"<< endl;
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_PRICE_BY_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        cout << "\nProduct name: " << sqlResultTable[0]->getString(0) << endl;
        cout << "Product price: " << sqlResultTable[0]->getString(1) << endl;
    }
}

void Customer::getProductDetailsByNamef() {
    std::string name;
    cout << "Please enter the product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_DETAILS_BY_NAME");
    SQLResult sqlResult = ps->run({"%" + name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for(int i=0; i<tuple;i++){
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product details: " << sqlResultTable[i]->getString(2) << endl;
        }
    }
}

void Customer::getProductIDf() {
    std::string name;
    cout << "Please enter the product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_ID");
    SQLResult sqlResult = ps->run({"%" + name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(1) << endl;
        }
    }
}

void Customer::getProductNamef() {
    int ID;
    cout << "Please enter the product ID:"<< endl;
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_NAME");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product name: " << sqlResultTable[i]->getString(1) << endl;
        }
    }
}

void Customer::getNumberOfProductsf() {
    const PreparedStatement *ps = S.getPreparedStatement("GET_NUMBER_OF_PRODUCTS");
    SQLResult sqlResult = ps->run({});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
            cout << "\nNumber of products: " << sqlResultTable[0]->getString(0) << endl;
        }
}

void Customer::getProductIMGf() {
    std::string name;
    cout << "Please enter the product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_IMG");
    SQLResult sqlResult = ps->run({"%"+ name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct name: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product IMG: " << sqlResultTable[i]->getString(1) <<endl;
        }
    }
}

void Customer::getProductQuantityByNamef() {
    std::string name;
    cout << "Please enter the product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_QUANTITY_BY_NAME");
    SQLResult sqlResult = ps->run({"%"+ name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct name: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(1) <<endl;
        }
    }
}

void Customer::getProductQuantityByIDf() {
    int ID;
    cout << "Please enter the product ID: " << endl;
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_QUANTITY_BY_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct name: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product quantity: " << sqlResultTable[i]->getString(1) <<endl;
        }
    }
}

void Customer::getProductCategoryIDf() {
    std::string name;
    cout << "Please enter the product name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_CATEGORY_ID");
    SQLResult sqlResult = ps->run({"%"+ name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct name: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product category ID: " << sqlResultTable[i]->getString(1) <<endl;
        }
    }
}

void Customer::getProductByDescriptionf() {
    std::string description;
    cout << "Please enter the product description: " << endl;
    cin >> description;
    const PreparedStatement *ps = S.getPreparedStatement("GET_PRODUCT_BY_DESCRIPTION");
    SQLResult sqlResult = ps->run({"%"+ description + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product Name: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product Details: " << sqlResultTable[i]->getString(2) << endl;
            cout << "Product IMG: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product Quantity: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Product Category ID: " << sqlResultTable[i]->getString(5) << endl;
            cout << "Product Price: " << sqlResultTable[i]->getString(6) << "\n" << endl;
        }
    }
}

void Customer::getAllProductsByCategoryNamef() {
    std::string name;
    cout << "Please enter the category name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::toupper);
    const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_PRODUCTS_BY_CATEGORY_NAME");
    SQLResult sqlResult = ps->run({"%"+ name + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product Name: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product Details: " << sqlResultTable[i]->getString(2) << endl;
            cout << "Product IMG: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product Quantity: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Product Category ID: " << sqlResultTable[i]->getString(5) << endl;
            cout << "Product Price: " << sqlResultTable[i]->getString(6) << "\n" << endl;
        }
    }
}

void Customer::getAllProductsByCategoryIDf() {
    int ID;
    cout << "Please enter the category ID: " << endl;
    cin >> ID;
    const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_PRODUCTS_BY_CATEGORY_ID");
    SQLResult sqlResult = ps->run({to_string(ID)});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        //cout << sqlResult << endl;
        unsigned long tuple = sqlResultTable.getNumberOfTuples();
        for (int i = 0; i < tuple; i++) {
            cout << "\nProduct ID: " << sqlResultTable[i]->getString(0) << endl;
            cout << "Product Name: " << sqlResultTable[i]->getString(1) << endl;
            cout << "Product Details: " << sqlResultTable[i]->getString(2) << endl;
            cout << "Product IMG: " << sqlResultTable[i]->getString(3) << endl;
            cout << "Product Quantity: " << sqlResultTable[i]->getString(4) << endl;
            cout << "Product Category ID: " << sqlResultTable[i]->getString(5) << endl;
            cout << "Product Price: " << sqlResultTable[i]->getString(6) << "\n" << endl;
        }
    }
}

void Customer::userCustomerf() {

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
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tAdmin selections:\n\n"<<endl;
    cout << "\t\t\t\t38- Get All Transactions by date.";
    cout << "\t\t\t\t\t\t\t\t39- Get total income today." << endl;
    cout << "\t\t\t\t40- Get all transactions between two dates.";
    cout << "\t\t\t\t\t\t41- Get total income from transactions." << endl;
    cout << "\t\t\t\t42- Get total income between two dates.";
    cout << "\t\t\t\t\t\t\t43- Get orders expenses between two dates." << endl;
    cout << "\t\t\t\t44- Get total expenses spent on salary.";
    cout << "\t\t\t\t\t\t\t45- Get total worth of the products stock." << endl;
    cout << "\t\t\t\t46- Get the general financial status of the Pharmacy.";
    cout << "\t\t\t47- Get the general financial status between two dates." << endl;
    cout << "\t\t\t\t48- Get total worth of the products stock.";
    cout << "\t\t\t\t\t\t49- Get the general financial status of the Pharmacy." << endl;
    cout << "\t\t\t\t50- Get the general financial status between two dates.";

    int choice;
    cout << "\t\t\t\tSelect: ";
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
        default: "Error! Please enter a number from 1 to 15.";

    }
}