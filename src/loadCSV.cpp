#include "loadCSV.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iomanip>

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

void prittyPrint(std::shared_ptr<Database> db, std::vector<Rule>& r, std::string filename,
                 double min_sup, double min_con){
    std::filebuf ruleFile;
    ruleFile.open(filename, std::ios::out);
    std::ostream fileOut(&ruleFile);

    fileOut << std::setprecision(2) << std::fixed
            << "Summary:" << std::endl
            << "Total rows in the original set: " << db->tuppleCount() << std::endl
            << "Total rules discovered: " << r.size() << std::endl
            << "The selected measures: Support=" << min_sup << " Confidence=" << min_con << std::endl
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
            << std::endl
            << "Rules:" << std::endl
            << std::endl;

    for(int i= 0; i < r.size(); i++){
        fileOut << "Rule #" << (i + 1) << ": (Support=" << (r[i].getFrequencyCount() / db->tuppleCount())
                << ", Confidence=" << r[i].getConfidence() << ")" << std::endl;
        r[i].prittyPrint(fileOut, db);
    }



}

std::vector<std::string> readLine(std::string s){
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    return vstrings;
}
