//
// Created by houss on 4/25/2017.
//

#ifndef PHARMACY_ORDERS_HPP
#define PHARMACY_ORDERS_HPP

#include <iostream>
#include <sstream>


class Orders {

    const static std::string addOrder;
    const static std::string removeOrderByName;
    const static std::string updateOrderQuantity;
    const static std::string getOrdersTotalPrice;
    const static std::string getEachOrderTotalPrice;

public:

    void static InitPreparedStatements();

};


#endif //PHARMACY_ORDERS_HPP
