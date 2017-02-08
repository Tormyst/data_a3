#include "../include/loadCSV.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include<iterator>

std::vector<std::string> readLine(std::string s);

std::unique_ptr<Database> readCSV(const std::string inputFile)
{
    std::ifstream dataFile;
    dataFile.open(inputFile);
    if(dataFile.fail()){
        std::cerr << "ERROR: File " << inputFile <<  " could not be open" << std::endl;
        return NULL;
    }
    std::string line;
    getline(dataFile, line);
    std::unique_ptr<Database> d(new Database(readLine(line)));

    while(std::getline(dataFile, line)){
        if(!line.empty())
            d->addData(line);
    }

    return d;
}

std::vector<std::string> readLine(std::string s){
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    return vstrings;
}
