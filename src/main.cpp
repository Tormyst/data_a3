#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

#include "loadCSV.h"
#include "apriori.h"

void displayHelp(std::string name, int exitCode) {
    std::cerr << "Usage: " << name << " <Data File> <Minimum Support> <Minimum Confidence> [<Output File>]" << std::endl
         << "       " << name << " -h " << std::endl
         << "lists to the file Rules all the rules for the given data file." << std::endl
         << "Only those rules with a larger support and confidence percentage then indicated." << std::endl
         << std::endl
         << "Data File: The path to the data file to be used." << std::endl
         << "           The first row is expected to be the headers of each column." << std::endl
         << "           The rest of the file should have the same amount of input data in each row." <<  std::endl
         << "Minimum Support: A value between 0 and 1, this should be the percentage of the minimum support." << std::endl
         << "           The large the number, the fewer rules will be created.  As well, as a faster process." << std::endl
         << "Minimum Confidence: A value between 0 and 1, this should be the percentage of the minimum confidence." << std::endl
         << "           The large the number, the fewer rules will be created." << std::endl
         << "Output File: Specifies an output file [Default: Rules]" << std::endl
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
    std::string filename;
    if(argc == 4){
        filename = "Rules";
    }
    else if(argc == 5){
        filename = argv[4];
    }
    else{
        std::cerr << "ERROR: Invalid number of arguments." << std::endl;
        displayHelp(argv[0], 1);
    }


    double min_sup;
    double min_con;
    try {
        min_sup = std::stof(argv[2]);
        min_con = std::stof(argv[3]);
        if(min_con > 1.0 || min_con < 0.0 || min_sup > 1.0 || min_sup < 0.0) {
            throw std::invalid_argument("Value not between 0.0 and 1.0.");
        }
    }
    catch(std::invalid_argument e){
        std::cerr << "ERROR: Invalid arguments for Minimum Support and Minimum Confidence" << std::endl;
        displayHelp(argv[0], 2);
    }

    std::shared_ptr<Database> db = readCSV(argv[1]);
    std::vector<Rule> r = apriori(db, min_sup, min_con);

    prittyPrint(db, r, filename, min_sup, min_con);

    return EXIT_SUCCESS;
}
