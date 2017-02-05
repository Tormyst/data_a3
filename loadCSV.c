#include <stdio.h>
#define BUFFER_SIZE 0xff

int readCSV(const char* inputFile, char delimiter, char**** database)
{
    FILE* dataFile; 
    char* line = NULL;
    size_t len = 0;

    dataFile = fopen( inputFile, "r" );
    if(dataFile == NULL){
        fprintf(stderr, "ERROR: File %s could not be open\n", inputFile);
        return 1;
    }
    while(EOF!=getline(&line, &len, dataFile))
        printf("%s", line);
    return 0;
}
