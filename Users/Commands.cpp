//
// Created by houssam on 2017.04.26..
//

#include "Commands.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include "../Headers/DBMS.hpp"
#include "Customer.hpp"



using namespace std;

const std::string Commands::userLogin = "USER_LOGIN";

void Commands::InitPreparedStatements() {
    if (!S.getPreparedStatement(userLogin)) {
        stringstream query;
        query << "SELECT username, passwordone, usertype FROM users WHERE username LIKE $1" << endl;
        S.requestNewPreparedStatement(userLogin, query.str());
    }
}

string Commands::userLoginf(){

    std::string username;
    std::string sqlusername;
    std::string sqlpassword;
    std::string password;
    std::string sqlusertype;
    cout << "\n\n\n\t\t\t\tUsername: ";
    cin >> username;
    cout << "\t\t\t\tPassword: ";
    cin >> password;
    const PreparedStatement *ps = S.getPreparedStatement("USER_LOGIN");
    SQLResult sqlResult = ps->run({"%" + username + "%"});
    if (sqlResult.hasTableResult()) {
        const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
        sqlusername = sqlResultTable[0]->getString(0);
        sqlpassword = sqlResultTable[0]->getString(1);
        sqlusertype = sqlResultTable[0]->getString(2);
        cout << "\n\n\t\t\t\t\t\t\tSuccessful login!\n\n\n" ;
    }
    else {
        cout << "Unable to login!" <<endl;
        cout << "Please check the username/password again!";
    }
    if (username == sqlusername && password == sqlpassword) return sqlusertype;
}

