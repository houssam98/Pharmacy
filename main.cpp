#include <iostream>
#include "Headers/DBMS.hpp"
#include "Users/Commands.h"
#include "Users/Admin.hpp"


using namespace std;


int main() {

    S.start();

    Admin::InitPreparedStatements();
    Commands::InitPreparedStatements();

   string usertype = Commands::userLoginf();
    if(1) {
        if (usertype.compare("customer") == 0) { Admin::userCustomerf(); }
        if (usertype.compare("employee") == 0) { Admin::userEmployeef(); }
        if (usertype.compare("manager") == 0) { Admin::userManager(); }
        if (usertype.compare("admin") == 0) { Admin::userAdmin(); }
    }

return 0;
}
    /*S.start();

    Products::InitPreparedStatements();

    try {
        const PreparedStatement *ps = S.getPreparedStatement("GET_ALL_PRODUCTS_BY_CATEGORY_ID");
        if(!ps)
        {
            cout << "couldn't find the ps" << endl;
            return 1;
        }
        SQLResult sqlResult = ps->run({"1"});
        if(sqlResult.hasTableResult()) {
            const SQLResultTable &sqlResultTable = sqlResult.getResultTable();
            //cout << sqlResult << endl;
            cout << "\nProduct ID: " << sqlResultTable[0] ->getString(0) << endl;
            cout << "Product Name: " <<  sqlResultTable[0] ->getString(1) << endl;
            cout << "Product Details: " <<  sqlResultTable[0] ->getString(2) << endl;
            cout << "Product IMG: " <<  sqlResultTable[0] ->getString(3) << endl;
            cout << "Product Quantity: " << sqlResultTable[0] ->getString(4) << endl;
            cout << "Product Category ID: " << sqlResultTable[0] ->getString(5) << endl;
            cout << "Product Price: " << sqlResultTable[0] ->getString(6) << "\n" << endl;
            //cout << sqlResult << endl;
            cout << "Product ID: " << sqlResultTable[1] ->getString(0) << endl;
            cout << "Product Name: " <<  sqlResultTable[1] ->getString(1) << endl;
            cout << "Product Details: " <<  sqlResultTable[1] ->getString(2) << endl;
            cout << "Product IMG: " <<  sqlResultTable[1] ->getString(3) << endl;
            cout << "Product Quantity: " << sqlResultTable[1] ->getString(4) << endl;
            cout << "Product Category ID: " << sqlResultTable[1] ->getString(5) << endl;
            cout << "Product Price: " << sqlResultTable[1] ->getString(6) << endl;
        }
    } catch (...) {
        cerr << "exception" << endl;
    } */

