#include <stdio.h>
#include <stdlib.h>

#include "loadCSV.h"

int main(int argc, char** argv){
    int i;
    char*** db;
    printf("argc: %d\n", argc);
    for(i = 0; i < argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    if(argc >= 2){
        int err = readCSV(argv[1], ' ', &db);
        if(err){
            fprintf(stderr, "Could not read CSV file. Stoping.\n");
            exit(err);
        }
    }
    return EXIT_SUCCESS;
}
