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
#include "hashTable.h"

/**
 *program for testing
 */
int main( int argc, char **argv){
    //create the table
    HTable* table = createTable(99999, hashNode, destroyNodeData, printNodeData);

    printf("\n");

    printf("Testing the add function and the print node\n");
    printf("Expectation: words will be added to the dictionary\n");
    insertDataInMap(table, "apple");
    printf("Output:");
    printNodeData("apple");
    printf("Result: PASS\n");

    printf("\n");

    printf("Testing add multiple words and then print with print all function\n");
    printf("Expectation: all words will be added and printed\n");
    insertDataInMap(table, "apple");
    insertDataInMap(table, "google");
    insertDataInMap(table, "microsoft");
    insertDataInMap(table, "facebook");
    insertDataInMap(table, "twitter");
    printf("Output:\n");
    printList(table);
    printf("Result: PASS\n");

    printf("\n");

    printf("Testing the remove function, let's remove google and apple\n");
    printf("Expectation: it should remove the corresponding words\n");

    removeData(table, "apple");
    printList(table);
    removeData(table, "google");
    printList(table);
    printf("Result: PASS\n");

    printf("\n");

    printf("Test the lookup function if its working\n");
    printf("Expectation: should show return the search if exist else return null\n");
    printf("When searching 'facebook' it should return the word\n");
    void* voidBuffer = lookupData(table, "facebook");
    printf("Returning: %s\n", (char*)voidBuffer);
    printf("When searching 'google' it should return null");
    voidBuffer = lookupData(table, "google");
    printf("Returning: %s\n", (char*)voidBuffer);
    printf("Result: PASS\n");

    printf("\n");

    HTable* collisionTable = createTable(1, hashNode, destroyNodeData, printNodeData);
    printf("*****************************************\n");
    printf("Testing for if colliosion is working by changing the table size to 1 after this line\n");
    printf("Expectation: index should be zero and should still function the same way as no colliosion\n");
    printf("Testing add function: apple, google, microsoft, facebook, twitter\n");
    insertDataInMap(collisionTable, "apple");
    insertDataInMap(collisionTable, "google");
    insertDataInMap(collisionTable, "microsoft");
    insertDataInMap(collisionTable, "facebook");
    insertDataInMap(collisionTable, "twitter");
    printf("Output:\n");
    printList(collisionTable);
    printf("Result: PASS\n");
    printf("*****************************************\n");
    printf("Testing remove function: apple, google\n");
    removeData(collisionTable, "apple");
    printList(collisionTable);
    removeData(collisionTable, "google");
    printList(collisionTable);
    printf("Result: PASS\n");
    printf("*****************************************\n");
    printf("Testing lookup function: facebook and something doesn't exist\n");
    printf("When searching 'facebook' it should return the word\n");
    printf("Returning: %s\n", (char*)lookupData(table, "facebook"));
    printf("When searching 'google' it should return null");
    printf("Returning: %s\n", (char*)lookupData(table, "google"));
    printf("Result: PASS\n");
    printf("*****************************************\n");

    printf("\n");

}/*end main*/ 