//
// Created by houss on 4/25/2017.
//

#include "../Headers/Users.hpp"
#include "../Headers/DBMS.hpp"


using namespace std;

const std::string Users::insertUser = "INSERT_USER";
const std::string Users::changeSalaryByUserID = "CHANGE_SALARY_BY_USER_ID";
const std::string Users::getContactDetailsByName = "GET_CONTACT_DETAILS_BY_USER_ID";
const std::string Users::changeUserPassword = "CHANGE_USER_PASSWORD";


void Users::InitPreparedStatements() {

    if (!S.getPreparedStatement(insertUser)) {
        stringstream query;
        query << "INSERT INTO users VALUES (default, $1, $2, $3, $4, %5, %6);" << endl;
        S.requestNewPreparedStatement(insertUser, query.str());
    }

    if (!S.getPreparedStatement(changeSalaryByUserID)) {
        stringstream query;
        query << "UPDATE users SET salary = $1 WHERE userid = $2;" << endl;
        S.requestNewPreparedStatement(changeSalaryByUserID, query.str());
    }

    if (!S.getPreparedStatement(getContactDetailsByName)) {
        stringstream query;
        query << "SELECT fullname, email, mobilephone FROM users WHERE fullname LIKE $1;" << endl;
        S.requestNewPreparedStatement(getContactDetailsByName, query.str());
    }

    if (!S.getPreparedStatement(changeUserPassword)) {
        stringstream query;
        query << "UPDATE users SET passwordone = $1 WHERE userid = $2;" << endl;
        S.requestNewPreparedStatement(changeUserPassword, query.str());
    }
}