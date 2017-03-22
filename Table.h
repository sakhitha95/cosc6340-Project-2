/*******************************************************************************
 File: Table.h

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

 This file contains the header for the table attributes
 *******************************************************************************/

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>

using namespace std;

class Table
{
private:
  std::vector<std::tuple<int, std::string, bool, std::string> > vColumnName;
  std::vector<std::vector<std::tuple<int, std::string> > > vRows;
  std::string sTableName;

public:
  //constructors
  Table()
  {
  }
  ;

  //Constructor that takes in a name for the table
  Table(std::string sTableNameIn)
  {
    sTableName = sTableNameIn;
  }

  //Display function
  void displayTable();

  //Setters
  void setPrimaryKey(std::string sKeyIn);

  void removePrimaryKey(std::string sKeyIn);

  //rename the class table to parameter name
  void rename(std::string sNewName);

  //add a column to the class vector
  void addColumn(std::tuple<int, std::string, bool, std::string> s);

  //add a row to the row vector
  void addRow(std::vector<std::tuple<int, std::string> > v);

  //find the row and delete it from the vector
  void deleteRow(std::vector<std::tuple<int, std::string> > vRowIn);

  //Getters
  std::string getTableName();

  std::vector<std::tuple<int, std::string, bool, std::string> > getColumnNames();

  std::vector<std::vector<std::tuple<int, std::string> > > getRows();

  std::tuple<int, std::string, bool, std::string> getColumnIndex(
      std::string sColumnNameIn);

  std::vector<std::tuple<int, std::string> > getRow(int iIndex);

  std::vector<std::string> getColumnValues(int iIndex);

};

#endif
