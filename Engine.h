/*******************************************************************************
 File: Engine.h
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
 This file contains the header for the engine
 *******************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Table.h"

using namespace std;

class Engine {
	private:
	    //Declare private variables

	public:

	    //Declare class methods
	    Engine() {};

	    void createTable(string sTableNameIn,
	                     vector<tuple<string, string, int, bool> > vColumnNamesIn,
	                     /*tuple<int, int, int > vSpecs,*/
	                     vector<string> vKeys);
	    void displayTable(string sTableNameIn);
	    void displayTableSchemas();
	    void executeSelect();
	    void addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn);
	    
	    static void writeStringToFile(string val, ofstream& out);
     static void writetofile();
     static void read(string);
	    static void writeIntToFile(int val, ofstream& out);
	    static int convertCharToInt(char* val);

	};

#endif

