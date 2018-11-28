//
// Created by houss on 4/26/2017.
//

#ifndef PHARMACY_CUSTOMER_HPP
#define PHARMACY_CUSTOMER_HPP


#include <iostream>

class Customer {

protected:

    //Products
    const static std::string getProductFromID;
    const static std::string getProductFromName;
    const static std::string getProductPriceByName;
    const static std::string getProductID;
    const static std::string getProductName;
    const static std::string getProductDetailsByName;
    const static std::string getProductIMG;
    const static std::string getProductQuantityByName;
    const static std::string getProductQuantityByID;
    const static std::string getProductCategoryID;
    const static std::string getNumberOfProducts;
    const static std::string getProductPriceByID;
    const static std::string getProductByDescription;
    const static std::string getAllProductsByCategoryID;
    const static std::string getAllProductsByCategoryName;

public:

    void static InitPreparedStatements();
    void static userCustomerf();

    virtual void static getProductFromIDf();
    virtual void static getProductFromNamef();

    void static getProductPriceByNamef();
    void static getProductIDf();
    void static getProductNamef();
    void static getProductDetailsByNamef();
    void static getProductIMGf();
    void static getProductQuantityByNamef();
    void static getProductQuantityByIDf();
    void static getProductCategoryIDf();
    void static getNumberOfProductsf();
    void static getProductPriceByIDf();

    virtual void static getProductByDescriptionf();

    void static getAllProductsByCategoryIDf();
    void static getAllProductsByCategoryNamef();

};


#endif //PHARMACY_CUSTOMER_HPP
