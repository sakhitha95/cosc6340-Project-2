


#ifndef GIT2_CATALOGTABLE_H
#define GIT2_CATALOGTABLE_H
#include <fstream>

#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>


using namespace std;

class Catalogtable{
    private:
    std::string tablename;
    vector<tuple<string, string, int> > columns;//tupele<columnsname,data type, size>
    std::vector<std::string> primarykey;
    int recordsize;
    int totalsize;
    int Nrecords=0;
    public:
    Catalogtable()
    {
    }
    void setName(std::string tablename1)
    {
        tablename=tablename1;
    }
    
    //Display function
    void displayTable();
    void setColumns(tuple<string, string, int, bool>  vColumnNamesIn)//sets the columns // It has to be changed to the required format
    {
      
            
            columns.push_back(make_tuple( get < 0 > (vColumnNamesIn), get < 1 > (vColumnNamesIn),get < 2 > (vColumnNamesIn)));
      
    }
    std::string getTableName()
    {
        return tablename;
    }
    
    std::vector<std::tuple<std::string,std::string,int> > getColumns()
    {
        return columns;
    }
    std::string getTablename()
    {
        return tablename;
    }
    
    std::vector<std::string> getPrimaryKey()
    {
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
        for (size_t i = 0; i < columns.size(); ++i){
            if ((std::get < 1 > (columns[i])).compare("INT"))
                count=count+4;
            else
                count=count+std::get < 2 > (columns[i]);
        }
        recordsize=count;
    }
    void setRecordSize(int rsize){
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
    void setTotalRecordSize(int size){
        recordsize=size;
    }
    int getNrecords()
    {
        return Nrecords;
    }
    void incrementNrecord()
    {
        Nrecords=Nrecords+1;
    }
    void decrementNrecord()
    {
        if(Nrecords!=0)
        Nrecords=Nrecords-1;
    }
        void setNrecord(int nrec)
    {
        Nrecords=nrec;
    }
};// end of class catalogtable
using namespace std;
class Person{
    public: string name;
};

#endif //GIT2_TABLE_H
