#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <limits>

#include "IOfunctions.h"
#include "NaiveBayes.h"

void displayHelp(std::string name, int exitCode) {
    std::cerr << "Usage: " << name << " <Data File> <Test File>" << std::endl
              << "       " << name << " <Data File> <Test File> <Classifier Target> " << std::endl
              << "       " << name << " -h " << std::endl
              << "Creates a decision tree based on the ID3 algorithm." << std::endl
              << "If no Classifier target is given, user will be prompted." << std::endl
              << "If a test file is given, a list of the results will be contained in the output file along with the tree" << std::endl
              << "The output tree will be saved in a file called Rules." << std::endl
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

    if(argc == 3){
        target = -1;
    }
    else if(argc == 4) {
        target = targetNameToInt(argv[1], argv[3]);
        if(target == -1)
            std::cerr << "Error: Target name not recognised.  Entering interactive mode" << std::endl;
    }
    else {
        std::cerr << "ERROR: Invalid number of arguments." << std::endl;
        displayHelp(argv[0], 1);
    }

    std::shared_ptr<Database> db = readCSV(argv[1], argv[2], target);

    auto t = NaiveBayes::Setup(db,target);

    prittyPrintNaiveBayes(db, t, "Rules", target);

    return EXIT_SUCCESS;
}
