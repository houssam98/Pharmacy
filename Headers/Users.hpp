//
// Created by houss on 4/25/2017.
//

#ifndef PHARMACY_USERS_HPP
#define PHARMACY_USERS_HPP

#include <iostream>
#include <sstream>

class Users {

    const static std::string insertUser;
    const static std::string changeSalaryByUserID;
    const static std::string getContactDetailsByName;
    const static std::string changeUserPassword;

public:

    void static InitPreparedStatements();

};


#endif //PHARMACY_USERS_HPP
