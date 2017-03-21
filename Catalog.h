#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Catalogtable{
private:
std::string tablename;
std::vector<std::tuple<std::string,std::string,int> > columns;
std::vector<std::string> primarykey;
int recordsize;
int totalsize;
int Nrecords;
public:
Catalogtable()
{
}
Catalogtable(std::string tablename)
    {
      tablename = tablename;
    }

    //Display function
    void displayTable();
void setColumns(vector<tuple<string, string, bool> > vColumnNamesIn){
for (int i = 0; i < vColumnNamesIn.size()-1; ++i)
    {
      
columns.push_back(make_tuple( get < 0 > (vColumnNamesIn[i]), get < 1 > (vColumnNamesIn[i]),1));
}
}

std::vector<std::tuple<std::string,std::string,int> > getColumns()
{
return columns;
}
std::string getTablename()
{
return tablename;
}

std::vector<std::string> getPrimaryKey(){
return primarykey;
}

    //Setters
    void setPrimaryKey(std::string sKeyIn)
    {
	primarykey.push_back(sKeyIn);

    }
void calculateRecordSize()
{
int count=0;
for (int i = 0; i < columns.size(); ++i){
if ((std::get < 1 > (columns[i])).compare("INT"))
count=count+4;
else
count=count+1;
}
recordsize=count;
}
void giveRecordSize(int rsize){
recordsize=rsize;
}
int getRecordSize()
{
return recordsize;
}
int getTotalRecordSize()
{
return totalsize;
}
void calculateTotalRecordSize()
{
totalsize=recordsize*Nrecords;
}
void giveTotalRecordSize(int size){
recordsize=size;
}
void incrementNrecord()
{
Nrecords=Nrecords+1;
}
void decrementNrecord()
{
if(Nrecord!=0)
Nrecords=Nrecords-1;
}
}
#endif
