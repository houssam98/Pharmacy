//
// Created by houss on 4/25/2017.
//

#ifndef PHARMACY_CATEGORY_HPP
#define PHARMACY_CATEGORY_HPP

#include <iostream>
#include <sstream>
#include <string>

class Category {

    const static std::string insertCategory;
    const static std::string getProductsByCategoryID;
    const static std::string getAllCategories;

public:

    void InitPreparedStatements();
};


#endif //PHARMACY_CATEGORY_HPP
