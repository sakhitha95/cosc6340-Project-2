#include <iostream>
#include <stdio.h>

using namespace std;

//string sqlQuery = "";
string sqlQuery = "CREATE TABLE T ( C1 INT, C2 CHAR(5), C3 INT, PRIMARY KEY(C1));";
string scriptFile = "";
//string scriptFile = "file";

string const CREATE_TABLE = "CREATE TABLE ";
string const INSERT_INTO = "INSERT INTO ";
string const SELECT = "SELECT ";
string const SHOW_TABLE = "SHOW TABLE";
string const QUIT = "QUIT;";

void parseSQLQuery(string SQL) {
    if (SQL.find_first_of("C") == 0) {
        cout << "create" << endl;
        if (SQL.find_first_of(CREATE_TABLE) == 0) {

        }
    } else if (SQL.find_first_of("I") == 0) {
        cout << "insert" << endl;
    } else if (SQL.find_first_of("S") == 0) {
        cout << "select" << endl;
    }
}

void parseScriptFile(string scriptFile) {
    cout << scriptFile << endl;
}

void commandLineSQLInput(string SQL) {
    cout << SQL << endl;
    while (true) {
        // for production
//        SQL = "";
//        cout << "SQL > ";
//        getline(cin, SQL);
//        SQL = toupper(SQL);

        if (SQL.find(QUIT) == 0) {
            if (SQL.length() == QUIT.length()) {
                cout << "Finished.";
                break;
            } else {
                cout << "Bad query. Try again.";
            }
        }

        parseSQLQuery(SQL);

        // for testing
        SQL = "";
        cout << "SQL > ";
        getline(cin, SQL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: dbms script=<filename> OR dbms \"<SQL query>\"" << endl;
        if (!sqlQuery.empty()) {
            cout << "Running on internal sql query" << endl;
            commandLineSQLInput(sqlQuery);
        } else if (!scriptFile.empty()) {
            cout << "Running on internal sql script" << endl;
            parseScriptFile(scriptFile);
        }
        return 0;
    }

    string firstArg = argv[1];
    if (firstArg.find("script") != string::npos) {
        char* scriptFile = strtok((char*)firstArg.c_str(), "=");
//        cout << scriptFile << endl;
        parseScriptFile(scriptFile);
    } else {
        commandLineSQLInput(argv[1]);
    }

    return 0;
}