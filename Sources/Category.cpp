//
// Created by houss on 4/25/2017.
//

#include "../Headers/Category.hpp"
#include "../Headers/DBMS.hpp"
#include <sstream>

using namespace std;

const std::string Category::insertCategory = "INSERT_CATEGORY";
const std::string Category::getProductsByCategoryID = "GET_PRODUCTS_BY_CATEGORY_ID";
const std::string Category::getAllCategories = "GET_ALL_CATEGORIES";


void Category::InitPreparedStatements() {

    if (!S.getPreparedStatement(insertCategory)) {
        stringstream query;
        query << "INSERT INTO category VALUES ( default, $1);" << endl;
        S.requestNewPreparedStatement(insertCategory, query.str());
    }

    if(!S.getPreparedStatement(getProductsByCategoryID)){
        stringstream query;
        query << "SELECT productname,quantity FROM products JOIN category ON(product_category_Id = categoryid) WHERE categoryid = $1;" << endl;
        S.requestNewPreparedStatement(getProductsByCategoryID, query.str());
    }

    if(!S.getPreparedStatement(getAllCategories)){
        stringstream query;
        query << "SELECT * FROM category;" << endl;
        S.requestNewPreparedStatement(getAllCategories, query.str());
    }


}

