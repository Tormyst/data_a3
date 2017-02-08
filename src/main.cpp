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

ostream& operator<< (ostream &out, const vector<int> v){
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

    unique_ptr<Database> db = readCSV(argv[1]);

    vector<FrequentSet> frequencies_current = db->getFirstFrequentSets();
    vector<FrequentSet> frequencies_next;
    i = 1;
    while(i < db->colCount){
        for(auto first_f = frequencies_current.begin(); first_f != frequencies_current.end(); first_f++){
            for(auto second_f = first_f; second_f != frequencies_current.end(); second_f++){
                FrequentSet combination = first_f->combine(*second_f);
                if(!FrequentSet::isNull(combination)) {
                    combination = db->setCount(combination);
                    frequencies_next.push_back(combination);
                    cout << "Combining sets with a value of " << combination.getFrequency() << ", and a fiter of "
                         << combination.getFilter(db->colCount) << endl;
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
