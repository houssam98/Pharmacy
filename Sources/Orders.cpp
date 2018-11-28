//
// Created by houss on 4/25/2017.
//

#include "../Headers/Orders.hpp"
#include "../Headers/DBMS.hpp"

using namespace std;

const std::string Orders::addOrder = "ADD_ORDER";
const std::string Orders::removeOrderByName = "REMOVE_ORDER";
const std::string Orders::updateOrderQuantity = "UPDATE_ORDER_QUANTITY";
const std::string Orders::getOrdersTotalPrice = "GET_ORDERS_TOTAL_PRICE";
const std::string Orders::getEachOrderTotalPrice = "GET_EACH_ORDER_TOTAL_PRICE";

void Orders::InitPreparedStatements() {

    if(!S.getPreparedStatement(addOrder)){
        stringstream query;
        query << "INSERT INTO orders VALUES (default, $1, $2, $3, $4);" << endl;
        S.requestNewPreparedStatement(addOrder, query.str());
    }

    if(!S.getPreparedStatement(removeOrderByName)){
        stringstream query;
        query << "DELETE FROM orders WHERE productname LIKE $1;" << endl;
        S.requestNewPreparedStatement(removeOrderByName, query.str());
    }

    if(!S.getPreparedStatement(updateOrderQuantity)){
        stringstream query;
        query << "UPDATE orders SET productquantity = $1 WHERE productname LIKE $2;" << endl;
        S.requestNewPreparedStatement(updateOrderQuantity, query.str());
    }

    if(!S.getPreparedStatement(getOrdersTotalPrice)){
        stringstream query;
        query << "SELECT SUM (Price*productQuantity) FROM Products JOIN orders USING (productId)" << endl;
        S.requestNewPreparedStatement(getOrdersTotalPrice, query.str());
    }

    if(!S.getPreparedStatement(getEachOrderTotalPrice)){
        stringstream query;
        query << "SELECT orderID, SUM (Price*productQuantity) FROM Products JOIN orders USING (productId) GROUP BY orderID" << endl;
        S.requestNewPreparedStatement(getEachOrderTotalPrice, query.str());
    }

}