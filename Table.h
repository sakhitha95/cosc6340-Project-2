//
// Created by amirreza shirani on 3/11/17.
//

#ifndef GIT2_TABLE_H
#define GIT2_TABLE_H
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "fstream"
using namespace std;

class Table
{
private:
    //sequence num, column name, isPrimary, stype, block size,
    vector<tuple<int, string, bool, string, int > > vColumnName;

    //vector<vector<tuple<int, string> > > vRows;
    //vector<string> primaryKey;

    //recordSize, totalSize, numOfRecords
    tuple<int, int, int> vSpecs;

    string sTableName;

public:
    //constructors
    Table()
    {};

    //Constructor that takes in a name for the table
    Table(string sTableNameIn)
    {
        sTableName = sTableNameIn;
    }

    //Display function
    void displayTable();

    //Setters
    void setPrimaryKey(string sKeyIn)
    {
        for (int i = 0; i < vColumnName.size(); ++i)
        {
            //Execute if the column name is equal to the parameter name
            if (get < 1 > (vColumnName[i]) == sKeyIn)
            {
                //set the boolean value in the column tuple to true, to show it is key
                get < 2 > (vColumnName[i]) = true;
                return;
            }
        }

        printf("| Primary Key was not set\n");
    }

    //add a column to the class vector
    void addColumn(tuple<int, string, bool, string, int> s)
    {
        vColumnName.push_back(s);
    }
    void addSpecs(tuple<int, int, int > d){
        vSpecs = d;
    }

    //add a row to the row vector
    void addRow(vector<tuple<int, string> > v)
    {
        ofstream outfile;
        string fileName= sTableName +".tbl";
        outfile.open(fileName, ios::binary | ios::out);

        for (int i = 0; i < vColumnName.size()-1; ++i)
        {
            //string sName = get < 0 > (vColumnName[i]);
            //string sType = get < 1 > (vColumnName[i]);
            int bSize= get < 4 > (vColumnName[i]);
            outfile.write((char*)&(get<1>(v[i])), bSize);
        }

        outfile.close();

    }

    //Getters
    string getTableName()
    {
        return sTableName;
    }

    tuple<int, string, bool, string> getColumnIndex(string sColumnNameIn);

    vector<tuple<int, string> > getRow(int iIndex);

    vector<string> getColumnValues(int iIndex);

};

#endif //GIT2_TABLE_H
