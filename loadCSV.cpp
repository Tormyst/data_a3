#include "loadCSV.h"

#include <iostream>
#include <sstream>
#include <fstream>

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

    // TEST
    cout << "Count of Data: " << d->tuppleCount() << endl;
    vector<int> v = {-1, -1, -1, -1, -1};
    cout << "Count of No Filter: " << d->setCount(v) << endl;
    v = {0, 0, 0, 0, 0};
    cout << "Count of all 0: " << d->setCount(v) << endl;
    v = {0, -1, -1, -1, -1};
    cout << "Count of first element 0: " << d->setCount(v) << endl;

    return d;
}

vector<string> readLine(string s){
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    return vstrings;
}
