
#include <sstream>

#include "../Headers/DBMS.hpp"
#include <algorithm>
#include <set>
#include <iostream>
#include <string.h>

#ifndef vcout //verbose cout.
#define vcout if(false) cout
#endif

using namespace std;

namespace Utils {

    template<typename T> std::vector<T *> copyDynamicVector(const std::vector<T *> & v) {
        vector<T *> ret;
        for (int i = 0; i < v.size(); i++)
            ret.push_back(new T(*v[i]));
        return ret;
    }

    double tenPower(const long n) {
        double ret = 1.0;
        if(n < 0)
            for(int i = 0 ; i<(0-n) ; i++)
                ret/=10;
        else if(n > 0)
            for(int i = 0 ; i<n ; i++)
                ret*=10;
        return ret;
    }

    bool isInt(const string& s) {
        if(s.empty())
            return true;

        auto it = s.begin();
        if(*it == '-')
            it++;   //if it's negative, ignore the first character ('-')

        for( ; it != s.end() ; it++)
            if(!isdigit(*it))
                return false;

        return true;
    }

    bool isDouble(const string & s) {
        if(s.empty())
            return true;

        auto it = s.begin();
        if(*it == '-')
            it++;   //if it's negative, ignore the first character ('-')

        bool foundDot = false;

        for( ; it != s.end() ; it++) {
            if(*it == '.') {
                if(foundDot)
                    return false;   //more than one dot found!
                foundDot = true;
                continue;
            }
            if(!isdigit(*it))
                return false;
        }

        return true;
    }

    double stod(const std::string &s) {
        if(!isDouble(s))
            throw logic_error("Tried to get double but it's not double.");

        unsigned long dotIndex = s.find('.');
        if(dotIndex == s.npos)
            dotIndex = s.length();
        double ret = 0;
        /*if(dotIndex == s.npos)  //doesn't have a dot -> integer
            return atoi(s.c_str());*/

        bool minus = (*s.begin() == '-');

        double pt = tenPower((int)dotIndex - s.length());

        for(string::const_reverse_iterator rit = s.rbegin() ; rit != s.rend() ; rit++) {
            if(isdigit(*rit)) {
                //cout << "rit=" << *rit << " ret=" << ret << " pt=" << pt << " +=" << pt*(*rit-'0') << endl;
                ret += (pt*(*rit-'0'));
                pt*=10;
            }
            //pt*=10;
        }

        if(dotIndex != s.length())
            ret*=10;

        return minus?-ret:ret;
    }

    bool s2b(string const& s)
    { //returns true if _s is "true" or "t". this function IS NOT case sensitive
        string _s(s);
        transform(_s.begin(),_s.end(),_s.begin(),::tolower); //tolower every char in the string
        if(_s=="true" || _s=="t")
            return true;
        else if(_s=="false" || _s=="f")
            return false;
        else
            throw logic_error("\"" + s + "\" cannot be converted to boolean!");
    }

    int max(int a, int b) {
        return a>b?a:b;
    }

    int getNumberOfArgs(std::string const &query) {
        if (query.empty())
            return 0;
        query.length();
        set<int> args;
        for(int i = 0 ; i<query.length()-1 /*the last character is never an argument so -1*/ ; i++) {
            if(query[i] == '$') {
                string n;
                while (isdigit(query[i + 1])) {
                    n += query[i + 1];
                    i++;
                }
                if (!n.empty()) {
                    args.insert(atoi(n.c_str()));
                } else {
                    i++; //yes, I want to increment i by 2 in this case because if I find an empty dollar sign, than the next character will never be an argument
                }
            }
        }
        return (int) args.size();
    }
}

//------------------------------------------ Tuple ------------------------------------------//

Tuple::Tuple(const vector<string *> &v) : values(Utils::copyDynamicVector(v)) {}

Tuple::~Tuple() {
    for(string* s : values)
        if(s)
            delete s;
}

Tuple::Tuple(const Tuple &o) : values(Utils::copyDynamicVector(o.values)) {}

vector<string> Tuple::getValues() const {
    //create a copy of "values" and return it
    vector<string> ret;
    for(string* s : values)
        ret.push_back(string(*s));
    return ret;
}

//User must check if a value is NULL before trying to get the value
string Tuple::getString(unsigned int index) const {
    if(index < 0 || index >= values.size())
        throw out_of_range("tuple");
    return string(*values.at(index));
}

//User must check if a value is NULL before trying to get the value
int Tuple::getInt(unsigned int index) const {
    if(index < 0 || index >= values.size())
        throw out_of_range("tuple");
    const string* s = values.at(index);
    if(!Utils::isInt(*s))
        throw logic_error("Tried to get int but it's not int.");
    return atoi(s->c_str());
}

//User must check if a value is NULL before trying to get the value
double Tuple::getDouble(unsigned int index) const {
    if(index < 0 || index >= values.size())
        throw out_of_range("tuple");
    const string* s = values.at(index);
    return Utils::stod(*s);
}

//User must check if a value is NULL before trying to get the value
bool Tuple::getBool(unsigned int index) const {
    if(index < 0 || index >= values.size())
        throw out_of_range("tuple");
    return Utils::s2b(*values.at(index));
}

//------------------------------------------ SQLResultTable ------------------------------------------//

SQLResultTable::SQLResultTable(const PGresult *pGresult) : tuples(getTuplesFromPGresult(pGresult)),
                                                           columnNames(getColumnNamesFromPGresult(pGresult)),
                                                           printedTable(getPrintedTable(pGresult)) {}

vector<Tuple*> SQLResultTable::getTuplesFromPGresult(const PGresult *pgr) {
    unsigned long n = (unsigned long)Utils::max(PQntuples(pgr),0);
    unsigned long columns = (unsigned long)Utils::max(PQnfields(pgr),0);
    vector<Tuple *> ret;
    for(int i = 0; i<n ; i++) {
        vector<string *> t;
        for(int j = 0 ; j<columns ; j++)
        {
            if(PQgetisnull(pgr,i,j))
                t.push_back(NULL);
            else
                t.push_back(new string(PQgetvalue(pgr,i,j)));
        }
        ret.push_back(new Tuple(t));
    }
    return ret;
}

vector<std::string> SQLResultTable::getColumnNamesFromPGresult(const PGresult *pgr) {
    unsigned long columns = (unsigned long)Utils::max(PQnfields(pgr),0);
    vector<string> ret;
    for(int i = 0; i<columns ; i++)
        ret.push_back(PQfname(pgr,i));
    return ret;
}

SQLResultTable::~SQLResultTable() {
    for(Tuple* t : tuples) {
        if(t)
            delete t;
    }
}

string SQLResultTable::getPrintedTable(const PGresult *pgr) {
    char *out;
    size_t size; //not important. contains the size of the out string

    FILE *temp = open_memstream(&out, &size);

    PQprintOpt opts = {0};
    opts.header = 1;    //don't show the number of rows
    opts.align = 1;
    opts.fieldSep = (char *) "|";

    PQprint(temp, pgr, &opts);

    fclose(temp);
    string ret(out);
    free(out);
    return ret;
}

SQLResultTable::SQLResultTable(SQLResultTable const &origin) : tuples(Utils::copyDynamicVector(origin.tuples)),
                                                               columnNames(origin.columnNames) {}

unsigned long SQLResultTable::getNumberOfTuples() const {
    return tuples.size();
    //auto err = PQresultStatus(pGresult);
    //return (err == PGRES_COMMAND_OK || err == PGRES_TUPLES_OK) ? PQntuples(pGresult) : 0;
}

unsigned long SQLResultTable::getNumberOfColumns() const {
    return columnNames.size();
    //auto err = PQresultStatus(pGresult);
    //return (err == PGRES_COMMAND_OK || err == PGRES_TUPLES_OK) ? PQnfields(pGresult) : 0;
}

string SQLResultTable::getColumnName(unsigned int n) const {
    return n >= getNumberOfColumns() ? NULL : columnNames.at(n);
}

const vector<string>& SQLResultTable::getColumnNames() const {
    return columnNames;
}

std::vector<Tuple> SQLResultTable::getTuples() const {
    vector<Tuple> ret;
    for (int i = 0; i < getNumberOfTuples(); i++) {
        ret.push_back(Tuple(*tuples[i]));
    }
    return ret;
}

bool SQLResultTable::isEmpty() const {
    return !getNumberOfTuples();
}

void SQLResultTable::print(ostream &outStream) const {
    outStream << printedTable;
}

//------------------------------------------ SQLResult ------------------------------------------//

SQLResult::SQLResult(PGresult * r) : cmdMessage(PQcmdStatus(r)),
                                     status(PQresultStatus(r)),
                                     errorMessage(PQresultErrorMessage(r)),
                                     resultTable(SQLResultTable(r)) {
    PQclear(r);
}

SQLResult::~SQLResult() {
    //PQclear(res);
}

SQLResult::SQLResult(SQLResult const& origin) : cmdMessage(origin.cmdMessage),
                                                status(origin.status),
                                                errorMessage(origin.errorMessage),
                                                resultTable(origin.resultTable) {}

std::string SQLResult::getCommandMessage() const {
    return cmdMessage;
}

std::string SQLResult::getErrorMessage() const {
    return errorMessage;
}

bool SQLResult::hasError() const {
    return errorMessage.size() > 0 || status == PGRES_BAD_RESPONSE || status == PGRES_NONFATAL_ERROR ||
           status == PGRES_FATAL_ERROR;
}

bool SQLResult::hasTableResult() const {
    return status == PGRES_TUPLES_OK;
}

const SQLResultTable& SQLResult::getResultTable() const {
    return resultTable;
}

//------------------------------------------ PreparedStatement ------------------------------------------//

PreparedStatement::PreparedStatement(string const &name, string const &declaration) : name(name),
                                                                                      declaration(declaration),
                                                                                      _temp((char **) malloc(
                                                                                              Utils::getNumberOfArgs(
                                                                                                      declaration) *
                                                                                              sizeof(char *))) {
    if (!S.getPreparedStatement(name)) {
        PGresult *res = PQprepare(S.conn, name.c_str(), declaration.c_str(), Utils::getNumberOfArgs(declaration), NULL);
        ExecStatusType r = PQresultStatus(res);
        if(r != PGRES_COMMAND_OK && r != PGRES_TUPLES_OK) {
            //throw SQL_Error(PQresultErrorMessage(res));
            cerr << PQerrorMessage(S.conn);
            //throw SQL_Error(PQerrorMessage(SQLServer::server().conn));
        }
        S.preparedStatements.insert(make_pair(name,this));
        //S.preparedStatements.insert(pair<string, PreparedStatement *>(name, this));
    }
}

SQLResult PreparedStatement::run(const std::vector<std::string> &args) const {
    const int n = Utils::getNumberOfArgs(declaration);
    if(args.size() != n)
        throw SQL_Error("Prepared statement's arguments don't match the number of arguments that the prepared statement should receive.");
    for(int i = 0 ; i < n ; i++)
        _temp[i] = (char *) args[i].c_str();

    return SQLResult(
            PQexecPrepared(SQLServer::server().conn, name.c_str(), n, (const char *const *) _temp, NULL, NULL, 0));
}

PreparedStatement::~PreparedStatement() {
    if (_temp)
        free(_temp);
}

//------------------------------------------ SQLServer ------------------------------------------//

SQLServer::SQLServer() //construtor
{
    //start();
}

SQLServer::~SQLServer() //destrutor
{
    stop();
}

void SQLServer::start() {
    if (conn && PQstatus(conn) != CONNECTION_BAD)
        return;

    cout << "Starting SQL server" << endl;
    stringstream temp;
    string host = "localhost";
    string port = "5432";
    string username = "houssam";
    string password = "houssam123";
    string dbname = "Houssam";
    temp << "host='" << host << "' port='" << port << "' user='" << username;
    temp << "' password='" << password << "' dbname='" << dbname << "'";
    conn = PQconnectdb(temp.str().c_str());

    if (!conn) {
        cerr << "Couldn't connect do the DB." << endl;
        exit(-1);
    }

    if (PQstatus(conn) != CONNECTION_OK) {
        cerr << "Couldn't connect do the DB. Error: " << endl;
        cerr << PQerrorMessage(conn) << endl;
        exit(-1);
    }
    // res=NULL;
    vcout << "DBMS successfully started." << endl;
}

void SQLServer::stop() {
    if (PQstatus(conn) != CONNECTION_BAD)
        PQfinish(conn);
    conn = NULL;
    for(auto ps : preparedStatements) {
        if(ps.second)
            delete(ps.second);
    }
    preparedStatements.clear();
    //clog("SQL server stopped");
}

PGresult *SQLServer::executeSQL(string const &sql) {
    PGresult *res = PQexec(conn, sql.c_str());
    if (!(PQresultStatus(res) == PGRES_COMMAND_OK || PQresultStatus(res) == PGRES_TUPLES_OK))
        throw SQL_Error(res);

    return res;
}

void SQLServer::printResult(PGresult *result, int client_socket, int hide_num_rows) {
    /*for (int row = 0; row < PQntuples(res); row++)
    cout << PQgetvalue(res, row, 0) << ' ' << PQgetvalue(res, row, 1) << endl;*/
    //PQdisplayTuples(result,stdout,1,"|",1,hide_num_rows);
    char *out;
    size_t size; //not important. contains the size of the out string
    FILE *temp = open_memstream(&out, &size);
    PQprintOpt opts = {0};

    opts.header = !hide_num_rows;
    opts.align = 1;
    opts.fieldSep = (char *) "|";

    PQprint(temp, result, &opts);
    fclose(temp);
    //Network::server().writeline(client_socket, "");
    //Network::server().writeline(client_socket, out, false);
    cout << PQerrorMessage(S.conn) << endl << out << endl;
    free(out);
}

void SQLServer::requestNewPreparedStatement(std::string const &name, std::string const &declaration) {
    if(getPreparedStatement(name))
        return;
    new PreparedStatement(name,declaration);    //the new is VERY important because it makes the this pointer (saved in the map of PreparedStatement*'s) be permanent until the delete instruction. The constructor automatically adds the object to the map.
    //cerr << PQerrorMessage(S.conn) << "\n";
}

const PreparedStatement *SQLServer::getPreparedStatement(std::string const &name) const {
    auto it = S.preparedStatements.find(name);
    if (it == S.preparedStatements.end())
        return NULL;
    return it->second;
}

//------------------------------------------ SQL_Error ------------------------------------------//

SQL_Error::SQL_Error(PGresult *e) : err(e) {}

SQL_Error::SQL_Error(const SQL_Error &e) : err(e.err) {}

SQL_Error::SQL_Error(const std::string &s) { cerr << s << endl; }

SQL_Error::~SQL_Error() {
    //PQclear(err);
}

//------------------------------------------ TupleConversionError ------------------------------------------//

TupleConversionError::TupleConversionError(const std::string &err) : logic_error(err) {}