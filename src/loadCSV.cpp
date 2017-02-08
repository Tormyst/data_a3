#include "../include/loadCSV.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include<iterator>

using namespace std;

vector<string> readLine(string s);

unique_ptr<Database> readCSV(const string inputFile)
{
    ifstream dataFile;
    dataFile.open(inputFile);
    if(dataFile.fail()){
        cerr << "ERROR: File " << inputFile <<  " could not be open" << endl;
        return NULL;
    }
    string line;
    getline(dataFile, line);
    unique_ptr<Database> d(new Database(readLine(line)));

    while(getline(dataFile, line)){
        if(!line.empty())
            d->addData(line);
    }

    return d;
}

vector<string> readLine(string s){
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    return vstrings;
}