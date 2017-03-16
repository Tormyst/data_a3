#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

#include "IOfunctions.h"
#include "id3.h"

void displayHelp(std::string name, int exitCode) {
    std::cerr << "Usage: " << name << " <Data File>" << std::endl
              << "       " << name << " <Data File> <Classifier Target>" << std::endl
              << "       " << name << " <Data File> <Classifier Target> <Test File>" << std::endl
              << "       " << name << " -h " << std::endl
              << "lists to the file Rules all the rules for the given data file." << std::endl
              << "Only those rules with a larger support and confidence percentage then indicated." << std::endl
              << std::endl
              << "Data File: The path to the data file to be used." << std::endl
              << "           The first row is expected to be the headers of each column." << std::endl
              << "           The rest of the file should have the same amount of input data in each row." <<  std::endl
              << "Test File: The path to the test file to be used." << std::endl
              << "           The first row is expected to be the same as the data file, however, this is not checkd." << std::endl
              << "           The rest of the file should contain data similer to the data file." <<  std::endl
              << "           Values unique to the test file should not break the program, however are not garantied to work correctly." <<  std::endl
              << "Classifier Target: Selects a column of the dataset to be used as the target." << std::endl
              << "           ID3 only works on binary values.  " << std::endl
              << "           A target will be disqualified if there are not 2 values found in the Target." << std::endl
              << "Option:" << std::endl
              << "     -h Print this menu." << std::endl;
    exit(exitCode);
}

int main(int argc, char** argv){
    int i;

    for(i = 0; i < argc; i++){
        if(!strncmp("-h", argv[i], 2)) // -h == argv[i]
            displayHelp(argv[0], 0);
    }
    int target;
    std::shared_ptr<Database> db = argc == 4 ? readCSV(argv[1], argv[3]) : readCSV(argv[1]);
    bool notSet = true;
    if(argc == 2){
        std::vector<int> valid;
        std::cout << "Pick a target attribute: "<< std::endl;
        for(i = 0; i < db->colCount; i++) {
            valid.push_back(i);
            std::cout << "\t" << valid.size() << ". " << db->getHeader(i);
            if(db->getClassUniqueCount(i) == 2) {
                std::cout << "     Binary";
            }
            std::cout << std::endl;
        }
        while(notSet){
            std::cout << "Target: ";
            std::cin >> target;
            if(std::cin.fail() || target <= 0 || target >valid.size() )
            {
                std::cout << "Sorry, did not quite catch that.  Please enter the integer associated with your selection." << std::endl;
            }
            else{
                target = valid[target - 1];
                notSet = false;
            }

        }
    }
    else if(argc == 3 || argc == 4){

        for(i = 0; i < db->colCount; i++) {
            if( db->getHeader(i) == argv[2]) {
                target = i;
                notSet = false;
                break;
            }
        }
    }
    else{
        std::cerr << "ERROR: Invalid number of arguments." << std::endl;
        displayHelp(argv[0], 1);
    }

    if(notSet){
        std::cerr << "ERROR: Invalid value for target" << std::endl;
        displayHelp(argv[0], 2);
    }

    id3::Node tree = id3::createTree(db,target);

    prittyPrintID3(db, tree, "Rules", target);

    return EXIT_SUCCESS;
}
