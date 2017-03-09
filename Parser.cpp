/*******************************************************************************
 File: Parser.cpp

 Authors: Gustavo Pedroso UIN: 423002834
 Levi Clark      UIN: 520007880
 Terry Chen      UIN: 121007055
 Daniel He       UIN: 620006827

 Department of Computer Science
 Texas A&M University
 Date  : 2/2/2014

 Formatting: * 80 pt width is used for code, for the most part
 * Hungarian naming convention is used for variables
 * Comments are applied for explanations
 * Spacing and brackets are applied for readability

 This file contains the implementation for the parser
 *******************************************************************************/

#include "Parser.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
//#include "../../Downloads/DBMS-master/Engine.h"
using namespace std;

const int CREATE_TABLE_SIZE = 12;
const int INSERT_INTO_SIZE = 11;
const int WRITE_CLOSE_SIZE = 5;
const int DELETE_FROM_SIZE = 11;
const int UPDATE_SIZE = 5;
const int WHERE_SIZE = 5;
const int SET_SIZE = 3;
const int SHOW_TABLE_SIZE = 10;
const int SINGLE_OP_SIZE = 1;
const int DOUBLE_OP_SIZE = 2;
const int VALUES_FROM_SIZE = 11;
const int VAL_FROM_REL_SIZE = 20;
const int PRIMARY_KEY_SIZE = 11;

//Array of String identifiers for non-symbolic operations
static const string expr[] =
{ "select", "project", "rename", "natural-join" };

//Array of String identifiers for symbolic comparisons
static const string operant[] =
{ "==", "!=", "<=", ">=", "<", ">" };

//Array of Char identifiers for symbolic operations
static const char symExpr[] =
{ '+', '-', '*' };

//Array of all symbols
static const string allOp[] =
{ "==", "!=", "<=", ">=", "<", ">", "+", "-", "*" };

const string sError = "ERR:: INVALID INPUT";

/*******************************************************************************
 Read a file and call parse function on each line read
 *******************************************************************************/
bool Parser::readFromFile(string sFileName)
{
  ifstream fhIn; //file handler
  string sLineIn; //Hold the line that is read off file
  int iCount = 0;

  //Open the file and validate it opened properly
  fhIn.open(sFileName.c_str());

  if (!fhIn)
  {
    //Output error message
    printf("|--------------------------------------");
    printf("-----------------------------------------\n");
    printf("| ERROR, file did not open, exiting...\n");
    return false; //Ends function
  }

  //Reading the first line from the file
  getline(fhIn, sLineIn, ';');

  //Formatting
  printf("\n|--------------------------------------");
  printf("-----------------------------------------\n");

  //Loop to read in file information
  while (!fhIn.eof() /*&& iCount < 20*/)
  {
    //Keep a record of lines for writing to file
    vValuesRead.push_back(sLineIn);

    //Parse the line of text and interpret it
    parse(sLineIn);

    //Prepare to loop again, read in next record & update
    getline(fhIn, sLineIn, ';');

    //Increase the counter
    iCount++;
  }

  //Close the file
  fhIn.close();
  return true;
}

/*******************************************************************************
 Writes the relation information to a file
 *******************************************************************************/
bool Parser::writeToFile(string sFilename)
{
  std::fstream outputFile;
  //open the file and write the contents of the class vector in there
  //outputFile.open(sFilename + ".db");
  for (int i = 0; i < vValuesRead.size(); ++i)
  {
    outputFile << vValuesRead[i] << '\n';
  }
  outputFile.close();
  return true;
}

/*******************************************************************************
 Remove any additional spaces from the string
 *******************************************************************************/
string Parser::cleanSpaces(string sLineIn)
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
 Remove any additional spaces from the string
 *******************************************************************************/
string Parser::removeSpaces(string sLineIn)
{
  string sOut = "";
  for (int i = 0; i < sLineIn.length(); ++i)
  {
    //Apend any values that are not spaces
    if (sLineIn[i] != ' ')
    {
      sOut += sLineIn[i];
    }
  }

  return sOut;
}

/*******************************************************************************
 Parse the line in and call the appropiate functions
 *******************************************************************************/
int Parser::parse(string sLineIn)
{
  //Declare and initialize variables
  //string sTemp;

  //Output the line we are working with so we know we have the parsing correct
  //printf("\n%s\n", sLineIn.c_str());
cout << sLineIn << endl;
  if (checkParenthesis(sLineIn))
  {
  	cout << "parenthesis ok" << endl;
    if (findCreateTable(sLineIn)) {
        printf("| CREATE TABLE was found in this line, executed.\n");
    } else if (findInsertInto(sLineIn)) {
   	  	cout << "Insert Into found" << endl;
	} else if (findQuit(sLineIn)) {
        cout << "Finished;" << endl;
        return 0;
    } else if (findShowTable(sLineIn)) { // needs to go before findShowTable
        cout << "Show table" << endl;
    } else if (findShowTables(sLineIn)) {
    	cout << "Show tables" << endl;
    } else {
      	printf("| None of the lines executed\n");
    }
  } else {
  	printf("| The line is incorrect\n");
  }

	return 1;
}

/*******************************************************************************
 Function that sees if CREATE TABLE is in the string and executes the command
 correct format = CREATE TABLE () PRIMARY KEY ()
 *******************************************************************************/
bool Parser::findCreateTable(string sLineIn)
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
 Function that sees if INSERT INTO is in the string and executes the command
 handles both INSERT FROM and INSERT FROM RELATION
 *******************************************************************************/
bool Parser::findInsertInto(string sLineIn)
{
    size_t iPosStart = sLineIn.find("INSERT INTO");

    if (iPosStart != std::string::npos)
    {
	    cout << "insert into found" << endl;
        iPosStart += 11;
        size_t iPosEnd1 = sLineIn.find("VALUES", iPosStart);
        size_t iPosEnd2 = sLineIn.find("VALUES FROM", iPosStart + 1);

        //Execute if values from relation is found
        if (iPosEnd1 != std::string::npos)
        {
            //Get the name of the table from the string
            string sTableNameOut = sLineIn.substr(iPosStart,
                                                  iPosEnd1 - iPosStart);
            //sTableNameOut = cleanSpaces(sTableNameOut);
            //cout << sTableNameOut << endl;

            //reposition the iterators to get the row values
            iPosStart = sLineIn.find("("); + 1;
            iPosEnd1 = sLineIn.find(")");

            if (iPosEnd1 != std::string::npos)
            {
                //Get the row attributes from the string
                string values = sLineIn.substr(iPosStart,
                                                     iPosEnd1 - iPosEnd1);
                //values = cleanSpaces(values);
                //cout << "values " << values << endl;

                iPosStart = iPosEnd1;

//                string sRestOfLine = sLineIn.substr(iPosStart, iPosEnd1);

//                sRestOfLine = removeSpaces(sRestOfLine);

                //WE NEED THE TREE HERE!!!!!!!!!

                //Clean up and add the row to the table
                //e.addRow(sTableNameOut, createRowVector(sRow));

                return false;
            }
        }
            //Execute if values from is found
        else if (iPosEnd2 != std::string::npos)
        {
            //Get the name of the table from the string
            string sTableName = sLineIn.substr(iPosStart + VALUES_FROM_SIZE,
                                               iPosEnd2 - VALUES_FROM_SIZE);
            //sTableName = cleanSpaces(sTableName);
            cout << sTableName << endl;

            //reposition the iterators to get the row values
            iPosStart = iPosEnd2 + 1;
            iPosEnd2 = sLineIn.find(")");

            if (iPosEnd2 != std::string::npos)
            {
                //Get the row attributes from the string
                string sRow = sLineIn.substr(iPosStart + VALUES_FROM_SIZE,
                                             iPosEnd2 - VALUES_FROM_SIZE - 2);

                //Clean up and add the row to the table
//        e.addRow(sTableName, createRowVector(sRow));

                return true;
            }
        }
    }

    return false;
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findShowTable(string sLineIn)
{
  size_t iPosStart = sLineIn.find("SHOW TABLE");

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + SHOW_TABLE_SIZE);
    sTableName = cleanSpaces(sTableName);
    
    cout << "table name " << sTableName << endl;

    //call the function to display table
//    e.displayTable(sTableName);

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findShowTables(string sLineIn)
{
  size_t iPosStart = sLineIn.find("SHOW TABLES;");

  if (iPosStart != std::string::npos)
  {
	cout << "found show table" << endl;

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findQuit(string sLineIn)
{
	cout << sLineIn << endl;
  size_t iPosStart = sLineIn.find("QUIT;");

  if (iPosStart != string::npos)
  {
    cout << "quit" << endl;

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if the parenthesis are balanced in a line
 *******************************************************************************/
bool Parser::checkParenthesis(string sLineIn)
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
 Function that does the select
 *******************************************************************************/
void Parser::select(string sNewTableName, string sRestOfLine)
{
  size_t iPos = sRestOfLine.find("select");

  if (iPos != std::string::npos)
  {
    size_t iParenth1 = sRestOfLine.find("(");
    size_t iParenth2 = sRestOfLine.find(")", iParenth1 + 1);
    string sValues = removeSpaces(
        sRestOfLine.substr(iParenth1 + 1, iParenth2 - iParenth1));
    string sTableNameIn = cleanSpaces(sRestOfLine.substr(iParenth2 + 1));
//    vector < string > vValues = makeTokens(sValues);

    if (sTableNameIn == sNewTableName)
    {
//      if (vValues[0] == "Date")
      {
//        e.selection(sNewTableName, sTableNameIn + " 2", vValues[1], vValues[0],
//            vValues[2] + vValues[3] + vValues[4] + vValues[5] + vValues[6]);
      }
//      else
//      {
//        e.selection(sNewTableName, sTableNameIn + " 2", vValues[1], vValues[0],
//            vValues[2]);
//      }

      //delete old table
//      e.dropTable(sTableNameIn);

      //rename new table to old name
//      e.renameTable(sTableNameIn + " 2", sNewTableName);
    }
    else
    {
//      if (vValues[0] == "Date")
//      {
//        e.selection(sTableNameIn, sNewTableName, vValues[1], vValues[0],
//            vValues[2] + vValues[3] + vValues[4] + vValues[5] + vValues[6]);
//      }
//      else
//      {
//        e.selection(sTableNameIn, sNewTableName, vValues[1], vValues[0],
//            vValues[2]);
//      }

    }
  }
}

