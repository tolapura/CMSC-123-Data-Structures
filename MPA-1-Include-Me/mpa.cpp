#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* stub
bool checkIfFileName(char* line){
    """ char* -> bool

    returns true if a line from the input file has a filename (eg. "sample.h)
    """

    return false;
*/

bool checkIfFileName(char* line){
    return (line[0] == '#' && line[9] == '"');
}

/* stub
char* splitString(char* line){
    """ char* -> char*

    returns the file name given a line from an input file
    (eg. #include "sample.h" to sample.h)
    """
    return ""
*/

char* splitString(char* line){
    char* fileName = malloc(100);
    int i, j;
    for(i = 10, j = 0; line[i] != '"'; i++, j++){
        fileName[j] = line[i];
    }
    fileName[j] = '\0';
    return fileName;
}

/* stub
bool check(char* line){
    """ char* -> bool

    returns true if a file name has already existed.
    """
    return false;
*/

bool check(char* line){
    FILE* fileNames = fopen("checkList.out", "a+");
    char filename[100];
    while(fgets(filename, 100, fileNames) != NULL){
        int i;
        for (i = 0; filename[i] != '\n'; i++);
        filename[i] = '\0';
        if(strcmp (line, filename) == 0){
            return false;
        }
    }
    fprintf(fileNames, "%s\n", line);
    return true;
}

/* stub
void openfile(char* filename, FILE* outputFile){
    """ char*, FILE* ->

    opens a file.
    """
    // returns nothing
*/

void openfile(char* filename, FILE* outputFile){
    FILE* newFile;
    char line[100];

    newFile = fopen(filename, "r");

    while (fgets(line, 100, newFile) != NULL){
        if (checkIfFileName(line)){
            char* fileName = splitString(line);
            if(check(fileName)){
                openfile(fileName, outputFile);
            }
        } else {
            fprintf(outputFile, "%s", line);
        }
    }
    fprintf(outputFile, "\n");
}

int main(){
    FILE* inputFile;
    FILE* outputFile;
    char line[100];
    inputFile = fopen("inputFile.cpp", "r");
    outputFile = fopen("outputFile.out", "w");

    if (inputFile == NULL){
        printf("File does not exist.");
    }

    if (outputFile == NULL){
        printf("File does not exist.");
    }

    while (fgets(line, 100, inputFile) != NULL){
        if (checkIfFileName(line)){
            char* fileName = splitString(line);
            openfile(fileName, outputFile);
        } else {
            fprintf(outputFile, "%s", line);
        }
    }
    return 0;
}
