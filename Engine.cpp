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
#include "Catalogtable.h"
/*******************************************************************************
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
 *******************************************************************************/

vector<Table> vTableList;
vector<Catalogtable> cataloglist;//stores catalogtables in main memory

void Engine::createTable(string sTableNameIn,
                         vector<tuple<string, string, int, bool> > vColumnNamesIn,
                         /*std::tuple<int, int, int> specs,*/
                         vector<string> vKeys)
{

    Table t(sTableNameIn);
    Catalogtable c;
    c.setName(sTableNameIn);//calling funtion to set table name
    for (size_t i = 0; i < vColumnNamesIn.size()-1; ++i)
    {
        string sName = get < 0 > (vColumnNamesIn[i]);
        string sType = get < 1 > (vColumnNamesIn[i]);
        int length = get < 2 > (vColumnNamesIn[i]);
        bool bKey = get < 3 > (vColumnNamesIn[i]);
        c.setColumns(make_tuple(sName,sType, length,bKey));
        t.addColumn(make_tuple(i, sName, bKey, sType, length));
    }
    
    //t.addSpecs(specs);

    for (size_t i = 0; i < vKeys.size(); ++i)
    {
        t.setPrimaryKey(vKeys[i]);
        c.setPrimaryKey(vKeys[i]);
    }

    //push table into the table list

    vTableList.push_back(t);
    cataloglist.push_back(c);
}

void Engine::executeSelect() // add the parameters you need
{
	// put t.addRow() here
}

/****************************************************************************
   Adds a row to the specified table
   ****************************************************************************/
void Engine::addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn)
{
	cout << "addRow" << endl;
	ofstream out;
	out.open("test.tbl", ios::binary | ios::out);
	
	int num = 1453659877;
	string hiStr = "hi";
	
	Engine::writeStringToFile(hiStr, out);
	Engine::writeIntToFile(num, out);
	out.close();
	

	ifstream in;
	char* hi = new char[hiStr.length()+1];
	char* xC = new char[to_string(num).length()+1];
	
	in.open("test.tbl", ios::binary | ios::in);
	in.read(hi, sizeof(char)*(hiStr.length()+1));
	in.read(xC, sizeof(char)*(to_string(num).length()+1));
	cout << "back in " << hi << endl;
	cout << "xC " << xC << endl;

	int x = Engine::convertCharToInt(xC);
	cout << "x num " << x << endl;

    for (size_t i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            //vTableList[i].addRow(vRowIn);
            return;
        }
    }
}
/*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
void Engine::displayTable(string sTableNameIn)
{
    for (size_t i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            return;
        }
    }
    printf("| The table was not found\n");
}

/*****************************************************************************
   Print out all table schemas
   ****************************************************************************/
void Engine::displayTableSchemas()
{
	//cout << "Grab data from catalog" << endl;
	for (size_t i = 0; i < vTableList.size(); ++i)
    {
        //if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            //return;
        }
    }
}

void Engine::writeStringToFile(string val, ofstream& out)
{
	char* valOut = new char[val.length()+1];
	for (size_t i = 0; i < val.length(); i++) {
		valOut[i] = val[i];
		//cout << "valOut[i] " << valOut[i] << endl;
	}
	valOut[val.length()] = '\0';
	
	out.write(valOut, sizeof(char)*(val.length()+1));
}

void Engine::writeIntToFile(int num, ofstream& out)
{
	string numStr = to_string(num);
	char* numC = new char[numStr.length()+1];
	for (size_t i = 0; i < numStr.length(); i++) {
		numC[i] = numStr[i];
		//cout << "numC[i] " << numC[i] << endl;
	}
	numC[numStr.length()] = '\0';
	
	out.write(numC, sizeof(char)*(numStr.length()+1));
}

int Engine::convertCharToInt(char* val)
{
	string xStr;
	for (size_t i = 0; i < strlen(val); i++) {
		xStr[i] = val[i];
		//cout << "xStr[i] " << xStr[i] << endl;
	}
	return stoi(xStr);
}

void Engine::writetofile()
{
    
    ofstream outfile;
    outfile.open("cat11.txt",ios::out|ios::app);
    for(size_t i=0; i<cataloglist.size();++i){
        //std::string name=cataloglist[i].getTableName();
        outfile<<"tablename="<<cataloglist[i].getTableName()<<'\n';
        std::vector<std::tuple<std::string,std::string,int> > col;
        col=cataloglist[i].getColumns();
        outfile<<"column=";
        for(size_t j=0;j< col.size();++j){
            if(j<col.size()-1)
            outfile<<get<0>(col[j])<<":"<<get<1>(col[j])<<"("<<get<2>(col[j])<<")"<<",";
            else
                outfile<<get<0>(col[j])<<":"<<get<1>(col[j])<<"("<<get<2>(col[j])<<")";
        }
        std::vector<std::string> primarykey;
        primarykey=cataloglist[i].getPrimaryKey();
        outfile<<"\n"<<"primarykey=";
        for(size_t k=0;k<primarykey.size();++k){
            if(k<primarykey.size()-1)
            outfile<<primarykey[k]<<",";
            else
                outfile<<primarykey[k];
        }
        int recordsize;
        cataloglist[i].calculateRecordSize();
        recordsize=cataloglist[i].getRecordSize();
        outfile<<"\n"<<"recordsize="<<recordsize;
        int totalsize;
        cataloglist[i].calculateTotalRecordSize();
        totalsize=cataloglist[i].getTotalRecordSize();
        outfile<<"\n"<<"totalsize"<<totalsize;
        int nrecords;
        nrecords=cataloglist[i].getNrecords();
        outfile<<"\n"<<"records="<<nrecords<<"\n";
    }
    
    outfile.close();
    
}

void Engine::read(string tableName){
    
    ifstream infile;
    int present=0;
    infile.open("cat11.txt",ios::in);
    for(size_t i=0;i<cataloglist.size();++i)
    {
        if(cataloglist[i].getTablename()==tableName)
        present=1;
    }
    if(present!=1){
        Catalogtable ob;
        string line;
        int count=0;
        while(getline(infile,line)){
            std::size_t f;
            if((f=line.find("tablename"))!=std::string::npos)
            {
                //cout<<line;
                //cout<<"gr";
                count=1;
                std::size_t f1;
                if((f1=line.find("=",f+8))!=std::string::npos){
                    //	cout<<f1;
                    string tname=line.substr(f1+1,string::npos);
                    ob.setName(tname);
                }
            }
            else if(count==1)
            {
                
                count=2;
                std::size_t f1;
                std::size_t f2;
                if((f1=line.find("="))!=std::string::npos){
                    cout<<f1;
                    string coln=line.substr(f1+1,string::npos);
                    std::size_t f6;
                    std::size_t f5;
                    f2=line.find(",",f1+1);
                    //vector<tuple<std::string,std::string,int,bool>> colname;
                    string coltemp;
                    
                    coltemp=line.substr(f1+1,f2-f1-1);
                    // cout<<coltemp<<"1111"<<"\n";
                    std::size_t f3;
                    f3=line.find(":");
                    f5=line.find("(");
                    
                    f6=line.find(")");
                    //cout<<line.substr(f5+1,f6-f5-1);
                    int c2=std::stoi(line.substr(f5+1,f6-f5-1));
                    //cout<<c2;
                    ob.setColumns(make_tuple(line.substr(f1+1,f3-f1-1),line.substr(f3+1,f2-f3-1),c2,false));
                    while(f2!=string::npos)
                    {
                        string coln=line.substr(f2+1,string::npos);
                        std::size_t f4;
                        f4=line.find(",",f2+1);
                        string coltemp;
                        
                        coltemp=line.substr(f2+1,f4-f2-1);
                        //cout<<coltemp<<"\n";
                        f3=line.find(":",f2+1);
                        f5=line.find("(",f2+1);
                        f6=line.find(")",f2+1);
                        int c1=std::stoi(line.substr(f5+1,f6-f5-1));
                        //cout<<c1;
                        ob.setColumns(make_tuple(line.substr(f2+1,f3-f2-1),line.substr(f3,f4-f3-1),c1,false));
                        f2=f4;
                        if(f2==line.size()-1)
                        {
                            cout<<"hei";
                            break;
                        }
                    }
                    
                }
            }
            
            else if(count==2){
                cout<<line;
                count=3;
                std::size_t f1;
                std::size_t f2;
                if((f1=line.find("="))!=std::string::npos){
                    
                    string coln=line.substr(f1+1,string::npos);
                   
               
                    f2=line.find(",",f1+1);
                    //std::vector<std::string> primkey;
                    string coltemp;
                    
                    coltemp=line.substr(f1+1,f2-f1-1);
                    
                    cout<<coltemp<<"\n";
                   // primkey.push_back(coltemp);
                    ob.setPrimaryKey(coltemp);
                    while(f2!=string::npos)
                    { cout<<"prime";
                        string coln=line.substr(f2+1,string::npos);
                        std::size_t f4;
                        f4=line.find(",",f2+1);
                        string coltemp;
                        
                        coltemp=line.substr(f2+1,f4-f2-1);
                        cout<<coltemp;
                        ob.setPrimaryKey(coltemp);
                        f2=f4;
                        if(f2==line.size()-1)
                        {
                            cout<<"hei";
                            break;
                        }
                    }
                    
                }
            }
            else if(count==3){
                cout<<"Asdfas";
                cout<<line;
                count=4;
                std::size_t f1;
                std::size_t f2;
                if((f1=line.find("="))!=std::string::npos){
                    
                    string coln=line.substr(f1+1,string::npos);
                    
                    f2=line.find(",",f1+1);
                    int recordsize;
                    
                    
                    recordsize=std::stoi(line.substr(f1+1,f2-f1-1));
                    ob.setTotalRecordSize(recordsize);
                    cout<<recordsize<<"\n";
                }
            }
            else if(count==4){
                
                cout<<line;
                count=5;
                std::size_t f1;
                std::size_t f2;
                if((f1=line.find("="))!=std::string::npos){
                    
                    string coln=line.substr(f1+1,string::npos);
                    f2=line.find(",",f1+1);
                    int totalsize;
                    
                    
                    totalsize=std::stoi(line.substr(f1+1,f2-f1-1));
                    ob.setTotalRecordSize(totalsize);
                    cout<<totalsize<<"\n";
                }
                
            }
            else if(count==5){
                
                cout<<line;
                count=0;
                std::size_t f1;
                std::size_t f2;
                if((f1=line.find("="))!=std::string::npos){
                    
                    string coln=line.substr(f1+1,string::npos);
                    f2=line.find(",",f1+1);
                    int records;
                    
                    
                    records=std::stoi(line.substr(f1+1,f2-f1-1));
                    ob.setNrecord(records);
                    cout<<records<<"\n";
                }
                
            }
            
            
            
            line.clear();
            
        }
        
    }
    
    infile.close();
    



}