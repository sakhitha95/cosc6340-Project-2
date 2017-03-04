#include <iostream>
#include <stdio.h>

using namespace std;

void parseScriptFile(string scriptFile) {

}

void commandLineSQLInput(string SQL) {
    cout << SQL << endl;
}

int main(int argc, char *argv[]) {
//    cout << "Hello, World!" << endl;

    if (argc != 2) {
        cout << "usage: dbms script=<filename> OR dbms \"<SQL query>\"" << endl;
    }

    string firstArg = argv[1];
    if (firstArg.find("script") == 0) {
        char* scriptFile = strtok((char*)firstArg.c_str(), "+");
        parseScriptFile(scriptFile[1] + "");
    } else {
        commandLineSQLInput(argv[1]);
    }

    return 0;
}