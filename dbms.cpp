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

const int CREATE_TABLE_SIZE = 12;
const int INSERT_INTO_SIZE = 11;
const int WRITE_CLOSE_SIZE = 5;
const int DELETE_FROM_SIZE = 11;
const int UPDATE_SIZE = 5;
const int WHERE_SIZE = 5;
const int SET_SIZE = 3;
const int OPEN_EXIT_SHOW_SIZE = 4;
const int SINGLE_OP_SIZE = 1;
const int DOUBLE_OP_SIZE = 2;
const int VALUES_FROM_SIZE = 11;
const int VAL_FROM_REL_SIZE = 20;
const int PRIMARY_KEY_SIZE = 11;

/*******************************************************************************
 Function that sees if the parenthesis are balanced in a line
 *******************************************************************************/
bool checkParenthesis(string sLineIn)
{
    int iBalance = 0;

    for (int i = 0; i < sLineIn.length(); ++i)
    {
        if (sLineIn[i] == '(')
        {
            iBalance++;
        }
        else if (sLineIn[i] == ')')
        {
            iBalance--;
        }
        if (iBalance < 0)
        {
            return false;
        }
    }

    if (iBalance == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
 Remove any additional spaces from the string
 *******************************************************************************/
string cleanSpaces(string sLineIn)
{
    string sOut = "";
    for (int i = 0; i < sLineIn.length(); ++i)
    {
        //Append the value from the string into the return string, if its alpha
        if (isalnum(sLineIn[i]) || sLineIn[i] == '_' || sLineIn[i] == '/')
        {
            sOut += sLineIn[i];
        }
    }

    return sOut;
}

/*******************************************************************************
 Function that sees if CREATE TABLE is in the string and executes the command
 correct format = CREATE TABLE () PRIMARY KEY ()
 *******************************************************************************/
bool findCreateTable(string sLineIn)
{
    size_t iPosStart = sLineIn.find("CREATE TABLE");

    //Execute if create table was found in the string
    if (iPosStart != std::string::npos)
    {
        size_t iPosEnd = sLineIn.find("(", iPosStart + 1);

        //execute if '(' was found in the string
        if (iPosEnd != std::string::npos)
        {
            //get the table name
            string sTableName = sLineIn.substr(iPosStart + CREATE_TABLE_SIZE,
                                               iPosEnd - CREATE_TABLE_SIZE - 1);

            cout << "table name " << sTableName << endl;

            //reposition the position values
            iPosStart = iPosEnd + 1;
            iPosEnd = sLineIn.find(", PRIMARY KEY", iPosStart + 1);
            int primaryKeyExtra = 2;
            if (iPosEnd == string::npos) {
                int primaryKeyExtra = 0;
                iPosEnd = sLineIn.find("PRIMARY KEY", iPosStart + 1);
            }

            //Execute if primary key was found in string
            if (iPosEnd != std::string::npos)
            {
                //get the column names
                string sColumns = sLineIn.substr(iPosStart,
                                                 iPosEnd - iPosStart);

                cout << "columns " << sColumns << endl;

                //reposition the position values
                iPosStart = iPosEnd + 1 + PRIMARY_KEY_SIZE + primaryKeyExtra;
                iPosEnd = sLineIn.find(")", iPosStart + 1);

                //execute if ')' was found in the string
                if (iPosEnd != std::string::npos)
                {
                    //get the primary keys
                    string sPrimaryKeys = sLineIn.substr(iPosStart,
                                                         iPosEnd - iPosStart);

                    cout << "primary keys " << sPrimaryKeys << endl;

                    //remove the spaces from the name of the table
                    sTableName = cleanSpaces(sTableName);

                    //call the create table function after the helper functions
//          e.createTable(sTableName, createColVector(sColumns),
//              createVector(sPrimaryKeys));

                    return true;
                }
            }
        }
    }

    return false;
}

/*******************************************************************************
 Parse the line in and call the appropiate functions
 *******************************************************************************/
void parse(string sLineIn)
{
    //Declare and initialize variables
    string sTemp;

    //Output the line we are working with so we know we have the parsing correct
    printf("\n%s\n", sLineIn.c_str());

    if (sLineIn[0] == '\n')
    {
        sLineIn.erase(0, 1);
    }

    if (checkParenthesis(sLineIn))
    {
        if (findCreateTable(sLineIn))
        {
            printf("| CREATE TABLE was found in this line, executed.\n");
        }
//        else if (findInsertInto(sLineIn))
//        {
//            printf("| INSERT INTO was found in this line, executed.\n");
//        }
//        else if (findDeleteFrom(sLineIn))
//        {
//            printf("| DELETE FROM was found in this line, executed.\n");
//        }
//        else if (findUpdate(sLineIn))
//        {
//            printf("| UPDATE was found in this line, executed.\n");
//        }
//        else if (findShow(sLineIn))
//        {
//            printf("| SHOW was found in this line, executed.\n");
//        }
        else
        {
            printf("| None of the lines executed\n");
        }
    }
    else
    {
        printf("| The line is incorrect\n");
    }

}

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

        parse(SQL);

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