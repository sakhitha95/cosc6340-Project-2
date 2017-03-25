/*******************************************************************************
 File: Engine.cpp
 Authors: Gustavo Pedroso UIN: 423002834
 Levi Clark      UIN: 520007880
 Terry Chen      UIN: 121007055
 Daniel He       UIN: 620006827
 Department of Computer Science
 Texas A&M University
 Date  : 2014-02-18
 Formatting: * 80 pt width is used for code, for the most part
 * Hungarian naming convention is used for variables
 * Comments are applied for explanations
 * Spacing and brackets are applied for readability
 This file contains the implementation for the engine
 *******************************************************************************/

#include "Engine.h"

/*******************************************************************************
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
 *******************************************************************************/

vector<Table> vTableList;

void Engine::createTable(string sTableNameIn,
                         vector<tuple<string, string, bool> > vColumnNamesIn,
                         vector<string> vKeys)
{

    Table t(sTableNameIn);

    for (int i = 0; i < vColumnNamesIn.size()-1; ++i)
    {
        string sName = get < 0 > (vColumnNamesIn[i]);
        string sType = get < 1 > (vColumnNamesIn[i]);
        bool bKey = get < 2 > (vColumnNamesIn[i]);

        t.addColumn(make_tuple(i, sName, bKey, sType));
    }

    for (int i = 0; i < vKeys.size(); ++i)
    {
        t.setPrimaryKey(vKeys[i]);
    }

    //push table into the table list

    vTableList.push_back(t);
}
/*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
void Engine::displayTable(string sTableNameIn)
{
    for (int i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            return;
        }
    }
    printf("| The table was not found\n");
}
/****************************************************************************
   Adds a row to the specified table
   ****************************************************************************/
void Engine::addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn)
{
    for (int i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].addRow(vRowIn);
            return;
        }
    }
}
