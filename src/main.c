/**************************
 * Name: Vicky Mohammad
 * ID: 0895381
 **************************/

/*import library*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "hashTable.h"

//macros
#define TRUE 1
#define FALSE 0

int userInputToInt(char* input){
    //declare var
    int num;
    //ask for user input
    input[0] = '\0';
    fgets(input, 100, stdin);
    input[strlen(input)-1] = '\0';
    num = atoi(input);
    //return
    return num;
}//end func

char* userInput(char* input){
    //ask for user input
    input[0] = '\0';
    fgets(input, 100, stdin);
    input[strlen(input)-1] = '\0';
    //return
    return input;
}//end func

//main program
int main( int argc, char **argv){
    //declare var for file
    char const* const fileName = argv[1];
    FILE* filePointer;
    filePointer = fopen(fileName, "r");
    int numOfLine = 0;
    char wordBeingAdded[99]; 
    //declrare variable
    char input[99];
    char* stringBuffer;
    int menu = 0;
    HTable * table = createTable(999999, hashNode, destroyNodeData, printNodeData);

    /*if file doesnt exist*/
    if(filePointer == NULL) {
        printf("No such file\n");
        return 0;
    }/*end if*/

    numOfLine = numOfLine + 1;
    fscanf(filePointer, "%s\n", wordBeingAdded);
    /*scan until end of file*/
    while(!feof(filePointer)){
        numOfLine = numOfLine + 1;
        fscanf(filePointer, "%s\n", wordBeingAdded);
        //add to the hash
        stringBuffer = malloc(sizeof(char)*strlen(wordBeingAdded+1));
        strcpy(stringBuffer, wordBeingAdded);
        insertDataInMap(table, stringBuffer);
    }/*end while*/
    fclose(filePointer);

    //loop the menu until exit
    do{
        //ask the user for the enu
        printf("1) Add a word to Dictionary\n");
        printf("2) Remove a word from Dictionary\n");
        printf("3) Spell Check a file\n");
        printf("4) Show Dictionary Words\n");
        printf("5) Quit\n");
        menu = userInputToInt(input);
        //if user choose an option
        if(menu == 1){
            //ask the user to add a word
            printf("Enter a single word to add to the Dictionary:\n");
            //ask for user input
            scanf("%s", input);
            getchar();
            stringBuffer = malloc(sizeof(char)*strlen(input+1));
            strcpy(stringBuffer, input);
            //call the api to add the word
            //and prompt the user for failure or success on adding 
            printf("input: %s\n", stringBuffer);
            insertDataInMap(table, stringBuffer);
        }else if(menu == 2){
            //ask the user to remove a word
            printf("Enter a single word to remove to the Dictionary:\n");
            //ask for user input
            scanf("%s", input);
            getchar();
            stringBuffer = malloc(sizeof(char)*strlen(input+1));
            strcpy(stringBuffer, input);
            //call the api to remove the word
            //prompt the user for failure or success on adding
            printf("input: %s\n", stringBuffer);
            removeData(table, stringBuffer);
        }else if(menu == 3){
            char wordToCheck[99];
            int correctWords = 0;
            int incorrectWords = 0;
            numOfLine = 0;
            FILE* filePointer;
            //ask the user of the file name to spell checked
            printf("Enter a filename to be spell checked:\n");
            scanf("%s", input);
            getchar();
            stringBuffer = malloc(sizeof(char)*strlen(input+1));
            strcpy(stringBuffer, input);
            filePointer = fopen(stringBuffer, "r");
            /*if file doesnt exist*/
            if(filePointer == NULL) {
                printf("No such file\n");
            }else{
                printf("File processed by Spell Check <%s>\n", stringBuffer);
                numOfLine = numOfLine + 1;
                fscanf(filePointer, "%s\n", wordBeingAdded);
                /*scan until end of file*/
                while(!feof(filePointer)){
                    numOfLine = numOfLine + 1;
                    fscanf(filePointer, "%s", wordToCheck);
                    stringBuffer = malloc(sizeof(char)*strlen(wordToCheck+1));
                    strcpy(stringBuffer, wordToCheck);
                    //check and count the number if correct words
                    char* voidBuffer = (char*)lookupData(table, wordToCheck);
                    //printf("%s, %s\n", voidBuffer , stringBuffer);
                    if(voidBuffer == NULL){
                        incorrectWords++;
                        printf("The word '%s' was not found in the dictionary\n",wordToCheck);
                    }else{
                        correctWords++;
                    }//end if
                }/*end while*/
                fclose(filePointer);
                printf("Summary:\n");
                printf("Correctly spelt words: %d\n", correctWords);
                printf("Incorrectly spelt words: %d\n", incorrectWords);
                printf("Enter any key to return to menu.\n");
            }//end if
        }else if(menu == 4){
            //show the dictioary in the 
            printList(table);
        }else if(menu == 5){
            //exit the program
            printf("Exiting program...\n");
            destroyTable(table);
            return 0;
        }//end if
    }while(menu != 5); 

    //exit the program
    return 0;
}/*end main*/ 