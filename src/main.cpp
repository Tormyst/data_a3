#include <iostream>

#include "../include/loadCSV.h"
using namespace std;

int main(int argc, char** argv){
    int i;
    unique_ptr<Database> db;
    cout << "argc: " << argc << endl;
    for(i = 0; i < argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    if(argc >= 2){
        db = readCSV(argv[1]);
        cout << *db;
    }
    return EXIT_SUCCESS;
}
