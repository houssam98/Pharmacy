//
// Created by houssam on 2017.04.26..
//

#ifndef PHARMACY_COMMANDS_H
#define PHARMACY_COMMANDS_H

#include <iostream>
#include <string>

using std::string;

class Commands {

protected:

    const static std::string userLogin;

public:

    static void InitPreparedStatements();
    static string userLoginf();
};


#endif //PHARMACY_COMMANDS_H
