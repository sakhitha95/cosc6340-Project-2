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
const int OPEN_EXIT_SHOW_SIZE = 4;
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
 Parse the line in and call the appropiate functions
 *******************************************************************************/
void Parser::parse(string sLineIn)
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
    else if (findInsertInto(sLineIn))
    {
      printf("| INSERT INTO was found in this line, executed.\n");
    }
    else if (findShow(sLineIn))
    {
      printf("| SHOW was found in this line, executed.\n");
    }
    else if (findWrite(sLineIn))
    {
      printf("| WRITE was found in this line, executed.\n");
    }
    else if (findOpen(sLineIn))
    {
      printf("| OPEN was found in this line, executed.\n");
    }
    else if (findClose(sLineIn))
    {
      printf("| CLOSE was found in this line, executed.\n");
    }
    else if (findExit(sLineIn))
    {
      printf("| EXIT was found in this line, executed.\n");
    }
    else if (findArrow(sLineIn))
    {
      printf("| <- was found in this line, executed.\n");
    }
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

/*******************************************************************************
 Writes the relation information to a file
 *******************************************************************************/
bool Parser::writeToFile(string sFilename)
{
  std::fstream outputFile;
  //open the file and write the contents of the class vector in there
  outputFile.open(sFilename + ".db");
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
    size_t iPosEnd1 = sLineIn.find("VALUES FROM RELATION", iPosStart + 1);
    size_t iPosEnd2 = sLineIn.find("VALUES FROM", iPosStart + 1);

    //Execute if values from relation is found
    if (iPosEnd1 != std::string::npos)
    {
      //Get the name of the table from the string
      string sTableNameOut = sLineIn.substr(iPosStart + VAL_FROM_REL_SIZE,
          iPosEnd1 - VAL_FROM_REL_SIZE);
      sTableNameOut = cleanSpaces(sTableNameOut);
      cout << sTableNameOut << endl;

      //reposition the iterators to get the row values
      iPosStart = iPosEnd1 + 1;
      iPosEnd1 = sLineIn.find("(");

      if (iPosEnd1 != std::string::npos)
      {
        //Get the row attributes from the string
        string sTableNameIn = sLineIn.substr(iPosStart + VAL_FROM_REL_SIZE,
            iPosEnd1 - VAL_FROM_REL_SIZE - 2);
        sTableNameIn = cleanSpaces(sTableNameIn);

        iPosStart = iPosEnd1;

        string sRestOfLine = sLineIn.substr(iPosStart, iPosEnd1);

        sRestOfLine = removeSpaces(sRestOfLine);

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
      sTableName = cleanSpaces(sTableName);
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
bool Parser::findShow(string sLineIn)
{
  size_t iPosStart = sLineIn.find("SHOW");

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + OPEN_EXIT_SHOW_SIZE);
    sTableName = cleanSpaces(sTableName);

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
 Function that sees if WRITE is in the string and executes the command
 *******************************************************************************/
bool Parser::findWrite(string sLineIn)
{
  size_t iPosStart = sLineIn.find("WRITE");

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + WRITE_CLOSE_SIZE);
    sTableName = cleanSpaces(sTableName);

    //call the function to display table
    writeToFile(sTableName);

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if OPEN is in the string and executes the command
 *******************************************************************************/
bool Parser::findOpen(string sLineIn)
{
  size_t iPosStart = sLineIn.find("OPEN");

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + WRITE_CLOSE_SIZE);
    sTableName = cleanSpaces(sTableName);

    //call the function to display table
    readFromFile(sTableName + ".db");

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if CLOSE is in the string and executes the command
 *******************************************************************************/
bool Parser::findClose(string sLineIn)
{
  size_t iPosStart = sLineIn.find("CLOSE");

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + WRITE_CLOSE_SIZE);
    sTableName = cleanSpaces(sTableName);

    vValuesRead.clear();

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if EXIT is in the string and executes the command
 *******************************************************************************/
bool Parser::findExit(string sLineIn)
{
  size_t iPosStart = sLineIn.find("EXIT");

  if (iPosStart != std::string::npos)
  {
    printf("Exiting.. \n");

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
 Function that sees if <- is in the string and executes the command
 *******************************************************************************/
bool Parser::findArrow(string sLineIn)
{
  size_t iPosStart = sLineIn.find("<-");

  if (iPosStart != std::string::npos)
  {
    string sTableNameOut = sLineIn.substr(0, iPosStart);
    sTableNameOut = cleanSpaces(sTableNameOut);

    string sRestOfLine = sLineIn.substr(iPosStart + DOUBLE_OP_SIZE);
    sRestOfLine = removeSpaces(sRestOfLine);

    op(sTableNameOut, sRestOfLine);
    select(sTableNameOut, sRestOfLine);

    //WE NEED THE TREE HERE!!!!!!!

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Handle the operation from the query
 *******************************************************************************/
void Parser::op(string sNewTableName, string sRestOfLine)
{
  size_t iPosAdd = sRestOfLine.find("+");
  size_t iPosSub = sRestOfLine.find("-");
  size_t iPosMul = sRestOfLine.find("*");

  if (iPosAdd != std::string::npos)
  {
    string sFirst = sRestOfLine.substr(0, iPosAdd);
    sFirst = cleanSpaces(sFirst);

    string sLast = sRestOfLine.substr(iPosAdd + 1);
    sLast = removeSpaces(sLast);

//    e.setUnion(sFirst, sLast, sNewTableName);
  }
  else if (iPosSub != std::string::npos)
  {
    string sFirst = sRestOfLine.substr(0, iPosSub);
    sFirst = cleanSpaces(sFirst);

    string sLast = sRestOfLine.substr(iPosSub + 1);
    sLast = removeSpaces(sLast);

//    e.setDifference(sFirst, sLast, sNewTableName);
  }
  else if (iPosMul != std::string::npos)
  {
    string sFirst = sRestOfLine.substr(0, iPosMul);
    sFirst = cleanSpaces(sFirst);

    string sLast = sRestOfLine.substr(iPosMul + 1);
    sLast = removeSpaces(sLast);
//    e.crossProduct(sFirst, sLast, sNewTableName);
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

/*******************************************************************************
 Function that finds the <- and returns the string of everything after it.
 *******************************************************************************/
/*
 string Parser::getAfterArrow(string sLineIn)
 {
 size_t iPosStart = sLineIn.find("<-");
 if (iPosStart!=std::string::npos)
 {
 string sAfterArrow = sLineIn.substr(iPosStart + 2);
 sAfterArrow = removeSpaces(sAfterArrow);
 printf("THE PARAMETERS ARE %s\n", sAfterArrow.c_str());
 return sAfterArrow;
 }
 else
 {
 return sError;
 }
 }
 */
/*******************************************************************************
 Function that inserts everything after <- into a tree.
 *******************************************************************************/
//Update function may need another function to parse because <- operator is not 
//present
//and there can be cases of multiple conditions. May modify this function later 
//for that case
//if needs be.
/*Parser::treeNode * Parser::createTree(string sLineIn)
 {
 string sParameters = getAfterArrow(sLineIn);
 treeNode *nodeStart;
 treeNode *nodeA;
 treeNode *nodeB;
 string sTemp;
 if( sParameters == sError ) //Invalid Input Checking
 {
 cout << "Invalid Parameters" << endl;
 return NULL;
 }


 for(int i = 0; i < sLineIn.size(); i++)
 {
 if(isalpha(sLineIn[i]))
 {
 sTemp = sTemp + sLineIn[i];
 }
 }
 //Adding values to tree.... Needs work.
 //Need to first identify precedence... Which identifier should be done first
 //before the others. Least precedence would be name of table.

 //Highest precedence should be non-symbolic operations, such as selection,
 //followed by symbolic operations, then symbolic comparator, and then
 //values/names.

 //We will need multiple tree check functions in order to insert the values into
 //the tree in the right order...
 //There should be a separate function that for each operation that will be
 //looked for and then those values will be inserted into the tree first.

 //Need a function to determine whether or not a set of parenthesis are
 //part of an operation. Non-operational parenthesis will determine highest
 //precedence...

 return nodeStart;



 }*/


/*******************************************************************************
 Function that traverses the current tree and prints out values
 *******************************************************************************/
/*
 void Parser::traversal(treeNode *start)
 {
 if( start != NULL ){
 traversal(start->leftChild);	//Visits Left subtree
 cout << start->data;  // Displays Data
 traversal(start->rightChild);    //Visits Right Subtree
 }

 }
 */

//bool isColumnName(string sIn, Table & t);

/*void comparison(vector<string> & vTokens, int & iTokenIndex, Table & relation)
{
  string operand0;
  string operand1;
  string op;

  string tableName = relation.getTableName();

  if (vTokens[iTokenIndex] == "(")
  {
    iTokenIndex++;
  }

  operand0 = vTokens[iTokenIndex];
  iTokenIndex++;

  op = vTokens[iTokenIndex];
  iTokenIndex++;

  operand1 = vTokens[iTokenIndex];
  iTokenIndex++;

  cout << endl << operand0 << " " << op << " " << operand1 << endl;

  //attribute name and literal
  if (isColumnName(operand0, relation) && !isColumnName(operand1, relation))
  {

    *//*e.selection(tableName, tableName + "2", op,  operand0, operand1)
     e.dropTable(tableName);

     //rename new table to old name
     e.renameTable(sTableNameIn + " 2", sNewTableName);*//*
  }
  //void Engine::selection(string sTableNameIn, string sTableNameOut,
  // string sOperator, string sColumn, string sAttribute)

}*/

/*void Parser::evalCondition(vector<string> vTokens, string relationName)
{
  int iTokenIndex = 0;

  removeBlankTokens(vTokens);
  Table relation = e.getTable(relationName);

  //starting with conjunction
  comparison(vTokens, iTokenIndex, relation);
}*/

/*bool isColumnName(string sIn, Table & t)
{
  std::vector < std::tuple<int, std::string, bool, std::string> > vColumnName;

  vColumnName = t.getColumnNames();

  for (int i = 0; i < vColumnName.size(); i++)
  {
    if (get < 1 > (vColumnName[i]) == sIn)
      return true;
  }

  return false;
}*/
