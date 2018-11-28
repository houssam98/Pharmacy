//
// Created by luisp on 2017.04.25..
//

#ifndef PHARMACY_PRODUCTS_HPP
#define PHARMACY_PRODUCTS_HPP

#include <iostream>

class Products {

    const static std::string insertProduct;
    const static std::string getProductFromID;
    const static std::string getProductFromName;
    const static std::string getProductPriceByName;
    const static std::string getProductID;
    const static std::string getProductName;
    const static std::string getProductDetailsByName;
    const static std::string getProductIMG;
    const static std::string getProductQuantityByName;
    const static std::string getProductCategoryID;
    const static std::string getNumberOfProducts;
    const static std::string getProductPriceByID;
    const static std::string getProductByDescription;
    const static std::string changeProductPriceByName;
    const static std::string changeProductPriceByID;
    const static std::string changeProductQuantityByName;
    const static std::string changeProductQuantityByID;
    const static std::string getAllProductsByCategoryID;
    const static std::string getAllProductsByCategoryName;


public:

    void static InitPreparedStatements();

};


#endif //PHARMACY_PRODUCTS_HPP
