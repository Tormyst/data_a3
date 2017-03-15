#include "IOfunctions.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iomanip>

std::vector<std::string> readLine(std::string s);
// Input function
std::unique_ptr<Database> readCSV(const std::string inputFile, const std::string testFile)
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

    dataFile.close();
    // Add test file if there is a file name here.
    if(!testFile.empty()){
        dataFile.open(testFile);

        if(dataFile.fail()){
            std::cerr << "ERROR: File " << testFile <<  " could not be open" << std::endl;
            return NULL;
        }
        // To skip past header line
        getline(dataFile, line);

        while(std::getline(dataFile, line)){
            if(!line.empty())
                d->addData(line,true);
        }
    }


    return d;
}

// Output function
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

void prittyPrintID3(std::shared_ptr<Database> db, id3::Node root, std::string filename, int target){
    std::filebuf ruleFile;
    ruleFile.open(filename, std::ios::out);
    std::ostream fileOut(&ruleFile);

    fileOut << std::setprecision(2) << std::fixed
            << "Summary:" << std::endl
            << "Total rows in the original set: " << db->tuppleCount() << std::endl
            << "The selected measures: Target=" << db->getHeader(target) << std::endl
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
            << std::endl
            << "Tree:" << std::endl;

    root.toStream(fileOut);

    if(db->createTestDataset().size() > 0){
        int matchCount = 0;
        int notMatchCount = 0;
        fileOut << "Test data:" << std::endl;
        for(auto a : db->createTestDataset()){
            int actual = (*a)[target];
            int tval = root.test(a);

            if(actual == tval){
                fileOut << "Correct: ";
                matchCount++;
            }
            else{
                fileOut << "Incorrect: ";
                notMatchCount++;
            }
            fileOut << "Actual:" << db->decode(target,actual) << " Tree: " << db->decode(target, tval) << std::endl;
        }

        fileOut << "Count that match: " <<  matchCount << std::endl;
        fileOut << "Count that did not match: " <<  notMatchCount << std::endl;
    }
}

std::vector<std::string> readLine(std::string s){
    std::stringstream ss(s);
    std::vector<std::string> splitLine;
    std::string v;
    while(ss >> v)
        splitLine.push_back(v);
    return splitLine;
}
