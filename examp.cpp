
#include <fstream>


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
void setName(std::string tablename)
    {
      tablename = tablename;
    }

    //Display function
    void displayTable();
void setColumns(vector<tuple<string, string, int> > vColumnNamesIn){
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
};
using namespace std;
class Person{
public: string name;
};

int main () {
  ofstream myfile;
  myfile.open ("example.txt",ios::out|ios::app);
Person p1;
Person p2;
Person p3;
vector<Person> o;
vector<Person> r;
o.push_back(p1);
o.push_back(p2);
o.push_back(p3);
o[1].name=(string)("Swetha");
o[0].name=(string)("Sakhitha");
o[2].name=(string)("sg");
//myfile.write((char *)&p1,sizeof(p1));
myfile<<"Name:" ;
 myfile << o[0].name<<'\n';
myfile<<"Name:" ;
 myfile << o[1].name<<'\n';
myfile<<"Name:" ;
 myfile << o[2].name<<'\n';
  myfile.close();

ifstream file;
Person r1;
file.open ("example.txt",ios::in);
//file.read((char *)&p2,sizeof(p2));
string line;
while(getline(file,line)){
std::size_t f;
if((f=line.find("Sakhitha"))!=std::string::npos)
{
cout<<line;
cout<<"gr";
}
line.clear();

}
//file>>p2.name;
file.close();

vector<Catalogtable> cataloglist;

std::string sTableNameIn="T";
Catalogtable ob;
std::vector<tuple<std::string,std::string,int> > vColumnNamesIn;
vColumnNamesIn.push_back(make_tuple("C1","INT",4));
std::vector<std::string> vKeys;
vKeys.push_back("C1");
ob.setName(sTableNameIn);
ob.setColumns(vColumnNamesIn);
ob.setPrimaryKey("C1");
 cataloglist.push_back(ob);

ofstream outfile;
outfile.open("catalog.txt",ios::out|ios::app);
for(int i=0; i< cataloglist.size();++i){
outfile<<"tablename="<<cataloglist[i].getTablename()<<'\n';
std::vector<std::tuple<std::string,std::string,int> > col;
col=cataloglist[i].getColumns();
outfile<<"column:";
for(int j=0;j<col.size();++j){
outfile<<get<0>(col[j])<<":"<<get<0>(col[j])<<",";
}
std::vector<std::string> primarykey;
primarykey=cataloglist[i].getPrimaryKey();
outfile<<"primarykey:";
for(int k=0;k<primarykey.size();++k){
outfile<<primarykey[k]<<",";
}
int recordsize;
recordsize=cataloglist[i].getRecordSize();
outfile<<"recordsize="<<recordsize;
int totalsize;
totalsize=cataloglist[i].getTotalRecordSize();
outfile<<"totalsize"<<totalsize;
int nrecords;
nrecords=cataloglist[i].getNrecords();
outfile<<"records="<<nrecords;
}

outfile.close();
ifstream infile;
int present=0;
infile.open("catalog.txt",ios::in);
for(int i=0;i<cataloglist.size();++i)
{
if(cataloglist[i].getTablename()=="T")
present=1;
}
if(present==1){
Catalogtable ob1;

string line;
int count=0;
while(getline(infile,line)){
std::size_t f;
if((f=line.find("tablename"))!=std::string::npos)
{
cout<<line;
cout<<"gr";
count=1;
}
else if(count==1)
{
cout<<line;
count=2;
}
else if(count==2){
cout<<line;
count=3;
}

line.clear();

}
}


infile.close();

  return 0;
}
