#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string.h> 

#define FILESIZE 80000000
#define AMT_OF_FILES 1
#define VSIZE FILESIZE*AMT_OF_FILES
#define TESTSIZE 10
#define LOWER -100
#define UPPER 100

char* concat(const char *s1, const char *s2);
void runProgram(int* arr1, int* arr2, int* arr3);
void performTest(int testsize, int* arr1, int* arr2, int* arr3);
void readAllFiles(int* arr1, int* arr2, int* arr3, int numOfValues);
void readFile(char* fileName, int* arr, int numOfValues, int n);
void createAllFiles(int numOfValues, int upper, int lower);
void createFile(char* fileName, int numOfValues, int upper, int lower);

int main(int argc, char* argv[]){
    int vsize = VSIZE;
    int fileSize = FILESIZE;
    int amountOfFiles = AMT_OF_FILES;
    int testsize = TESTSIZE;
    int lower = LOWER;
    int upper = UPPER;
    srand(time(0));
    createAllFiles(AMT_OF_FILES, UPPER, LOWER); //COMMENT THIS LINE OUT IF YOU ARE NOT CREATING THE X,Y,Z COMPONENT FILES, USUALLY THIS MEANS ALWAYS KEEP THIS COMMENTED

    int myid, size;
    int i;
    int *X, *Y, *Z;
    int *results;
    X =  (int *) calloc (vsize,sizeof(int));
    Y =  (int *) calloc (vsize,sizeof(int));
    Z =  (int *) calloc (vsize,sizeof(int));
    //results = (int *) malloc (testsize*sizeof(int));
    
    readAllFiles(X, Y, Z, amountOfFiles); 
    runProgram(X, Y, Z);


    free(X);
    free(Y);
    free(Z);
    //free(results);

    return 0;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void runProgram(int* arr1, int* arr2, int* arr3){
    char* input = (char*)malloc(256*sizeof(char));
  	char* buffer = (char*)malloc(256*sizeof(char));
  	do{
        printf("Enter the number of vectors to add, type Exit to stop:\n");
        scanf("%s", input);
        fgets(buffer, 256, stdin);
        if(strcmp(input, "Exit") != 0){
            printf("Beginning Vector Addition - Serial, for %d vectors...\n", atoi(strtok(input, "\n")));
            performTest(atoi(strtok(input, "\n")), arr1, arr2, arr3);
        }
    }while((strcmp(strtok(input, "\n"), "Exit") != 0));
    free(input);
    free(buffer);
}

void performTest(int testsize, int* arr1, int* arr2, int* arr3){
    clock_t begin = clock();
    int X_SUMMATION = 0;
    int Y_SUMMATION = 0;
    int Z_SUMMATION = 0;

    for(int i = 0; i < testsize; i++){
        X_SUMMATION = X_SUMMATION + arr1[i];
    }

    for(int i = 0; i < testsize; i++){
        Y_SUMMATION = Y_SUMMATION + arr2[i];
    }

    for(int i = 0; i < testsize; i++){
        Z_SUMMATION = Z_SUMMATION + arr3[i];
    }
    printf("Summation of X components: %d\nSummation of Y components: %d\nSummation of Z components: %d\n", X_SUMMATION, Y_SUMMATION, Z_SUMMATION);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Execution time in seconds: %f\n", time_spent);
}

void readAllFiles(int* arr1, int* arr2, int* arr3, int numOfValues){
    char* fileNumber = (char *) malloc (numOfValues*(sizeof(char*)));
    for(int i = 1; i <= numOfValues; i++){
        sprintf(fileNumber, "%d", i);
        readFile(concat(concat("x", fileNumber),".txt"), arr1, FILESIZE, i);
        readFile(concat(concat("y", fileNumber),".txt"), arr2, FILESIZE, i);
        readFile(concat(concat("z", fileNumber),".txt"), arr3, FILESIZE, i);
    }
    free(fileNumber);
}

void readFile(char* fileName, int* arr, int numOfValues, int n){
    n = (n - 1) * FILESIZE;
    FILE *fp;
    fp = fopen(fileName, "r");
    printf("Reading from %s\n", fileName);
    for(int i = 0; i < numOfValues; i++){
        fscanf(fp, "%d", &arr[i + n]);
        //printf("Reading from %s, value is : %d\n", fileName, arr[i]);
    }
    fclose(fp);    
    
}

void createAllFiles(int numOfValues, int upper, int lower){
    printf("Creating X, Y, Z files...\n");
    char* fileNumber = (char *) malloc (numOfValues*(sizeof(char*)));
    for(int i = 1; i <= numOfValues; i++){
        sprintf(fileNumber, "%d", i);
        printf("Creating file: %s\n", concat(concat("x", fileNumber),".txt"));
        createFile(concat(concat("x", fileNumber),".txt"), FILESIZE, upper, lower);
        printf("Creating file: %s\n", concat(concat("y", fileNumber),".txt"));
        createFile(concat(concat("y", fileNumber),".txt"), FILESIZE, upper, lower);
        printf("Creating file: %s\n", concat(concat("z", fileNumber),".txt"));
        createFile(concat(concat("z", fileNumber),".txt"), FILESIZE, upper, lower);

    }
    free(fileNumber);
}

void createFile(char* fileName, int numOfValues, int upper, int lower){
    FILE *fp;
    fp = fopen(fileName, "w+");
    for(int i = 0; i < numOfValues; i++){
        fprintf(fp, "%d\n", rand() % (upper - lower + 1) + lower);
    }
    //fprintf("\n");
    fclose(fp);
}