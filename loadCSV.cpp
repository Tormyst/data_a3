#include "loadCSV.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

vector<string> readLine(string s){
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    return vstrings;
}

unique_ptr<database> readCSV(const string inputFile)
{
    ifstream dataFile;
    unique_ptr<database> d(new database());
    dataFile.open(inputFile);
    if(dataFile.fail()){
        cerr << "ERROR: File " << inputFile <<  " could not be open" << endl;
        return NULL;
    }
    string line;
    getline(dataFile, line);
    d->titles = readLine(line);

    while(getline(dataFile, line)){
        d->data.push_back(readLine(line));
    }

    return d;
}
