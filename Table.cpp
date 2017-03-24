/*******************************************************************************
 File: Table.cpp

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

 This file contains the table implementation file
 *******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "Table.h"

const int COLUMN_WIDTH = 20;
fstream outputFile;

/*******************************************************************************
 Display the table
 *******************************************************************************/
void Table::displayTable()
{
  // Print the lines of the table for a pretty output
  cout << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    cout << "-----------------------";
  }
  cout << "\n";

  cout << " | " << sTableName << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    cout << "+----------------------";
  }
  cout << "\n";

  // Determine how far to space the column bars
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //get the column values for printing
    string sColName = get < 1 > (vColumnName[i]);
    bool bPrimaryKey = get < 2 > (vColumnName[i]);

    //see if it is a primary key, for formatting
    if (bPrimaryKey)
    {
      cout << " | " << setw(COLUMN_WIDTH) << left
                << "*" + sColName + "*";
    }
    else
    {
      cout << " | " << setw(COLUMN_WIDTH) << left << sColName;
    }

  }
  cout << "\n ";

  // Print the row dividers for the number of columns
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    cout << "+----------------------";
  }
  cout << "\n";

//  for (int i = 0; i < vRows.size(); ++i)
//  {
//
//    for (int a = 0; a < vColumnName.size(); ++a)
//    {
//      for (vector<tuple<int, string> >::iterator current =
//              vRows[i].begin(); current != vRows[i].end(); ++current)
//      {
//        if (get < 0 > (*current) == get < 0 > (vColumnName[a]))
//        {
//          string sCurrent = get < 1 > (*current);
//          if (sCurrent.size() > COLUMN_WIDTH)
//          {
//            sCurrent.resize(COLUMN_WIDTH);
//          }
//          cout << " | " << setw(COLUMN_WIDTH) << left
//                    << sCurrent;
//
//          break;
//        }
//      }
//    }
//
//    cout << "\n ";
//    for (int y = 0; y < vColumnName.size(); ++y)
//    {
//      cout << "+----------------------";
//    }
//    cout << "\n";
//  }
//  cout << "\n";
}

/*******************************************************************************
 This function returns the index of the column or -1 if the column is not found
 and the type of the column
 *******************************************************************************/
tuple<int, string, bool, string> Table::getColumnIndex(
        string sColumnNameIn)
{
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //Execute if the column was found
    if (get < 1 > (vColumnName[i]) == sColumnNameIn)
    {
      int iColumnIndex = get < 0 > (vColumnName[i]);
      bool bColumnKey = get < 2 > (vColumnName[i]);
      string sColumnType = get < 3 > (vColumnName[i]);

      return make_tuple(iColumnIndex, sColumnType, bColumnKey, sColumnType);
    }
  }

  printf("| We didnt find it\n");
  //The column was not found
  return make_tuple(-1, "n/a", false, "n/a");
}


/*******************************************************************************
 This function takes the index of a column and returns the values of the column
 *******************************************************************************/
vector<tuple<int, string> > Table::getRow(int iIndex)
{
  ifstream infile;
  streampos pos;
  string fileName = sTableName + ".tbl";
  infile.open(fileName, ios::binary | ios::in);


  vector < tuple<int, string> > vReturn;
  if(iIndex*get<0>(vSpecs)< get<1>(vSpecs) and iIndex<get<2>(vSpecs)){

    infile.seekg(iIndex*get<0>(vSpecs), ios::beg);
    for (int i = 0; i< vColumnName.size()-1; ++i){
      string sName = get < 1 > (vColumnName[i]);
      int bSize= get < 4 > (vColumnName[i]);
      infile.read((char *)&sName, bSize);
      vReturn.push_back(make_tuple( i,sName));
    }

  }else cout<<"index is out of range"<<endl;

  return vReturn;
}

