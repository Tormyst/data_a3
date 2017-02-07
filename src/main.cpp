#include <iostream>

#include "../include/loadCSV.h"
using namespace std;

void displayHelp(string name, int exitCode) {
    cerr << "Usage: " << name << " <Data File> <Minimum Support> <Minimum Confidence> [<Output File>]" << endl
         << "       " << name << " -h " << endl
         << "lists to the file Rules all the rules for the given data file." << endl
         << "Only those rules with a larger support and confidence percentage then indicated." << endl
         << endl
         << "Data File: The path to the data file to be used." << endl
         << "           The first row is expected to be the headers of each column." << endl
         << "           The rest of the file should have the same amount of input data in each row." <<  endl
         << "Minimum Support: A value between 0 and 1, this should be the percentage of the minimum support." << endl
         << "           The large the number, the fewer rules will be created.  As well, as a faster process." << endl
         << "Minimum Confidence: A value between 0 and 1, this should be the percentage of the minimum confidence." << endl
         << "           The large the number, the fewer rules will be created." << endl
         << "Output File: Specifies an output file [Default: Rules]" << endl
         << "Option:" << endl
         << "     -h Print this menu." << endl;
    exit(exitCode);
}

int main(int argc, char** argv){
    int i;
    unique_ptr<Database> db;
    cout << "argc: " << argc << endl;
    for(i = 0; i < argc; i++){
        if(!strncmp("-h", argv[i], 2)) // -h == argv[i]
            displayHelp(argv[0], 0);
    }
    if(argc != 4){
        displayHelp(argv[0], 1);
    }



    return EXIT_SUCCESS;
}
