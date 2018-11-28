//
// Created by luisp on 2017.04.25..
//

#include "../Headers/Products.hpp"
#include "../Headers/DBMS.hpp"
#include <sstream>

using namespace std;

const std::string Products::insertProduct = "INSERT_PRODUCT";
const std::string Products::getProductFromID = "GET_PRODUCT_FROM_ID";
const std::string Products::getProductFromName = "GET_PRODUCT_FROM_NAME";
const std::string Products::getProductPriceByName = "GET_PRODUCT_PRICE_BY_NAME";
const std::string Products::getProductDetailsByName = "GET_PRODUCT_DETAILS_BY_NAME";
const std::string Products::getProductID = "GET_PRODUCT_ID";
const std::string Products::getProductName = "GET_PRODUCT_NAME";
const std::string Products::getNumberOfProducts = "GET_NUMBER_OF_PRODUCTS";
const std::string Products::getProductIMG = "GET_PRODUCT_IMG";
const std::string Products::getProductQuantityByName = "GET_PRODUCT_QUANTITY_BY_NAME";
const std::string Products::getProductCategoryID = "GET_PRODUCT_CATEGORY_ID";
const std::string Products::getProductPriceByID = "GET_PRODUCT_PRICE_BY_ID";
const std::string Products::getProductByDescription = "GET_PRODUCT_BY_DESCRIPTION";
const std::string Products::changeProductPriceByName = "CHANGE_PRODUCT_PRICE_BY_NAME";
const std::string Products::changeProductPriceByID = "CHANGE_PRODUCT_PRICE_BY_ID";
const std::string Products::changeProductQuantityByName = "CHANGE_PRODUCT_QUANTITY_BY_NAME";
const std::string Products::changeProductQuantityByID = "CHANGE_PRODUCT_QUANTITY_BY_ID";
const std::string Products::getAllProductsByCategoryID = "GET_ALL_PRODUCTS_BY_CATEGORY_ID";
const std::string Products::getAllProductsByCategoryName = "GET_ALL_PRODUCTS_BY_CATEGORY_NAME";

void Products::InitPreparedStatements() {

    if(!S.getPreparedStatement(insertProduct)){
        stringstream query;
        query << "INSERT INTO products" << endl;
        query << "VALUES (default, $1, $2, $3, $4, $5, $6)";
        S.requestNewPreparedStatement(insertProduct, query.str());
    }

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
        query << "SELECT productdetails FROM products WHERE productname LIKE $1;" << endl;
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
        query << "SELECT productname FROM products" << endl;
        query << "WHERE productname LIKE $1" << endl;
        S.requestNewPreparedStatement(getProductName, query.str());
    }

    if(!S.getPreparedStatement(getNumberOfProducts)){
        stringstream query;
        query << "SELECT COUNT(productid) FROM products;" << endl;
        S.requestNewPreparedStatement(getNumberOfProducts, query.str());
    }

    if(!S.getPreparedStatement(getProductIMG)){
        stringstream query;
        query << "SELECT productimg FROM products " << endl;
        query << "WHERE productname LIKE $1";
        S.requestNewPreparedStatement(getProductIMG, query.str());
    }

    if(!S.getPreparedStatement(getProductQuantityByName)){
        stringstream query;
        query << "SELECT productname, quantity FROM products WHERE productname LIKE $1 " << endl;
        S.requestNewPreparedStatement(getProductQuantityByName, query.str());
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
        query << "SELECT * FROM products " << endl;
        query << "WHERE productdetails LIKE $1" << endl;
        S.requestNewPreparedStatement(getProductByDescription, query.str());
    }


    if(!S.getPreparedStatement(changeProductPriceByName)){
        stringstream query;
        query << "UPDATE products SET price = $1 WHERE productname LIKE $2;" << endl;
        S.requestNewPreparedStatement(changeProductPriceByName, query.str());
    }

    if(!S.getPreparedStatement(changeProductPriceByID)){
        stringstream query;
        query << "UPDATE products SET price = $1 WHERE productid = $2;" << endl;
        S.requestNewPreparedStatement(changeProductPriceByID, query.str());
    }

    if(!S.getPreparedStatement(changeProductQuantityByName)){
        stringstream query;
        query << "UPDATE products SET quantity = $1 WHERE productname LIKE $2;" << endl;
        S.requestNewPreparedStatement(changeProductQuantityByName, query.str());
    }

    if(!S.getPreparedStatement(changeProductQuantityByID)){
        stringstream query;
        query << "UPDATE products SET quantity = $1 WHERE productid = $2;" << endl;
        S.requestNewPreparedStatement(changeProductQuantityByID, query.str());
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


