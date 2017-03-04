#include <iostream>
#include <stdio.h>

using namespace std;

void parseScriptFile(string scriptFile) {
    cout << scriptFile << endl;
}

void commandLineSQLInput(string SQL) {
    cout << SQL << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: dbms script=<filename> OR dbms \"<SQL query>\"" << endl;
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