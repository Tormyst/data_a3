#include <iostream>

#include "../include/loadCSV.h"

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

std::ostream& operator<< (std::ostream &out, const std::vector<int> v){
    out << "[ ";
    bool comma = false;
    for (auto i : v){
        if(comma) out << ", ";
        else comma = true;
        out << i;
    }
    out << " ]";
    return out;
}

int main(int argc, char** argv){
    int i;

    for(i = 0; i < argc; i++){
        if(!strncmp("-h", argv[i], 2)) // -h == argv[i]
            displayHelp(argv[0], 0);
    }
    if(argc != 4){
        displayHelp(argv[0], 1);
    }

    std::unique_ptr<Database> db = readCSV(argv[1]);

    std::vector<FrequentSet> frequencies_current = db->getFirstFrequentSets();
    std::vector<FrequentSet> frequencies_next;
    i = 1;
    while(i < db->colCount){
        for(auto first_f = frequencies_current.begin(); first_f != frequencies_current.end(); first_f++){
            for(auto second_f = first_f; second_f != frequencies_current.end(); second_f++){
                FrequentSet combination = first_f->combine(*second_f);
                if(!FrequentSet::isNull(combination)) {
                    combination = db->setCount(combination);
                    frequencies_next.push_back(combination);
                    std::cout << "Combining sets with a value of " << combination.getFrequency() << ", and a fiter of "
                         << combination.getFilter(db->colCount) << std::endl;
                }
            }
        }
        if(frequencies_current.size() > 1){
            frequencies_current = frequencies_next;
        }
        i++;
    }




    return EXIT_SUCCESS;
}
