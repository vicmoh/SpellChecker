/**************************
 * Name: Vicky Mohammad
 * ID: 0895381
 **************************/

//import libraries
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "hashTable.h"

/**Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
*@return pointer to the hash table
*@param size size of the hash table
*@param hashFunction function pointer to a function to hash the data
*@param destroyData function pointer to a function to delete a single piece of data from the hash table
*@param printNode function pointer to a function that prints out a data element of the table
**/
HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char* key), void (*destroyData)(void *data), void (*printNode)(void *toBePrinted)){
    //create a new table
    HTable *newTable = malloc(sizeof(HTable));

    //init the size
    newTable->size = size;
    newTable->table = malloc(sizeof(Node*)*size);
    newTable->destroyData = destroyData;
    newTable->hashFunction = hashFunction;
    newTable->printNode = printNode;

    //init the table will null to prevent seg fault
    for(int x=0; x < size; x++){
        newTable->table[x] = NULL;
    }//end for

    //return the new table
    return newTable;
}//end func

/**Function for creating a node for the hash table.
*@pre Node must be cast to void pointer before being added.
*@post Node is valid and able to be added to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data is a generic pointer to any data type.
*@return returns a node for the hash table
**/
Node *createNode(char* key, void *data){
    //create a new node
    Node *newNode = malloc(sizeof(Node));
    //init the new node
    newNode->key = key;
    newNode->data = data;
    newNode->next = NULL;
    //return the new node
    return newNode;
}//end func

/** Deletes the entire hash table and frees memory of every element.
*@pre Hash Table must exist.
*@param hashTable pointer to hash table containing elements of data
**/
void destroyTable(HTable *hashTable){
    //declare variable
    Node* tempNode = NULL;
    Node* nodeTobeDeleted = NULL;
    //if the table is not empty then free the node
    if(hashTable != NULL){
        //check every node
        for(int x=0; x < hashTable->size; x++){
            tempNode = hashTable->table[x];
            //go through the table until null
            while(tempNode != NULL){
                nodeTobeDeleted = tempNode;
                tempNode = tempNode->next;
                //free the each element on the table and the data
                hashTable->destroyData(nodeTobeDeleted->data);
                free(nodeTobeDeleted);
            }//end while
        }
    }else if(hashTable == NULL){
        //if the hash table is empty then return
        return;
    }//end if

    //free the table
    free(hashTable->table);
    free(hashTable);
}//end func

/**Inserts a Node in the hash table.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data pointer to generic data that is to be inserted into the list
**/
void insertData(HTable *hashTable, char* key, void *data){
    //if its already exist
    if(lookupData(hashTable, key) != NULL){
        printf("The word '%s' already exist.\n", (char*)key);
        return;
    }//end if

    //if the table is empty
    if(hashTable == NULL){
        printf("Hash table is empty.\n");
        return;
    }//end if

    //if the hash is greater than the table size or smaller than 0
    int index = hashNode(hashTable->size, key);
    if(index < 0 || index > hashTable->size){
        printf("The hash index is out of bound.\n");
        return;
    }//end if

    //input it at the word end of the list at the index if collision happens
    Node* newNode = createNode(key, data);
    if(hashTable->table[index] != NULL && hashTable->table[index]->key != key){
        //declare a temp node for inserting the new node
        Node* iterateNode;
        iterateNode = hashTable->table[index];
        //loop until the end of the list
        while(iterateNode->next != NULL){
            iterateNode = iterateNode->next;
        }//end if
        //once iterate node is the end of the list, add a new node
        iterateNode->next = newNode;
        printf("The word '%s' has been added at index %d.\n", (char*)newNode->data, index);
        return;
    }//end if

    //if nothing is in the list just add it to the new node
    if(hashTable->table[index] == NULL || hashTable->table[index]->key == key){
        //added to the hashtable
        hashTable->table[index] = newNode;
        printf("The word '%s' has been added at index %d.\n", (char*)newNode->data, index);
        return;
    }//end if
}//end func

/** THIS FUNCTION IS NOT MANDATORY, users call this function to insert a Node in the hash table.
* It's meant as a wrapper for insertData so the users don't need to generate the key when adding.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param data pointer to generic data that is to be inserted into the list
**/
void insertDataInMap(HTable *hashTable, void *data){
    insertData(hashTable, (char*)data, data);
}//end func

/**Function to remove a node from the hash table 
 *@pre Hash table must exist and have memory allocated to it
 *@post Node at key will be removed from the hash table if it exists.
 *@param hashTable pointer to the hash table struct
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 **/
void removeData(HTable *hashTable, char* key){
    //set the varibales
    int index = hashNode(hashTable->size, key);
    Node *currentNode = hashTable->table[index];
    Node *prevNode = hashTable->table[index];
    Node *nextNode = hashTable->table[index];
    Node *nodeTobeDeleted;

    //if its already exist
    if(lookupData(hashTable, key) == NULL){
        printf("The word '%s' doesn't exist.\n", (char*)key);
        return;
    }//end if

    //check if there is something in the list
    if(hashTable->table[index] != NULL){
        //case when the first word is what im looking for
        if(strcmp(hashTable->table[index]->key, key) == 0){
            nextNode = currentNode->next;
            printf("Removing the word '%s' from dictionary.\n", (char*)currentNode->data);
            free(currentNode);
            hashTable->table[index] = nextNode;
        }else{
            //loop until null or find the word
            while(currentNode != NULL){
                //check if its what im looking for
                if(strcmp(currentNode->key, key) == 0){
                    //if found delete the data
                    nextNode = currentNode->next;
                    prevNode->next = nextNode;
                    nodeTobeDeleted = currentNode;
                    printf("Removing the word '%s' from dictionary.\n", (char*)nodeTobeDeleted->data);
                    nodeTobeDeleted->data = NULL;
                    nodeTobeDeleted = NULL;
                    free(nodeTobeDeleted);
                }//end if
                prevNode = currentNode;
                currentNode = currentNode->next;
            }//end while
        }//end if
    }else if(hashTable->table[index] == NULL){
        //if the list is emppty
        printf("The index %d is empty.\n", index);
    }else{
        //the key may be out of bound
        return;
    }//end if
}//end func

/**Function to return the data from the key given.
 *@pre The hash table exists and has memory allocated to it
 *@param hashTable pointer to the hash table containing data nodes
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 *@return returns a pointer to the data in the hash table. Returns NULL if no match is found.
 **/
void *lookupData(HTable *hashTable, char* key){
    //set the varibales
    int index = hashNode(hashTable->size, key);
    Node *iterateNode = hashTable->table[index];

    //check if there is something in the list
    if(hashTable->table[index] != NULL){
        while(iterateNode != NULL){
            //check if its what im looking for
            if(strcmp(iterateNode->key, key) == 0){
                //if found return
                return iterateNode->data;
            }//end if
            iterateNode = iterateNode->next;
        }//end while
    }else{
        return NULL;
    }//end if
    return NULL;
}//end func


/**
 *function of hash the words
 *@param tableSize for the size of the table
 *@param key for the word being hashed
 */
int hashNode(size_t tableSize, char* key){
    key = lowerCase(key); 
    //declare variable
    int total = 0;
    //loop each character add each of them
    for(int x=0; x<strlen(key); x++){
        total = total + (key[x]*x+strlen(key));
    }//end for
    return total % tableSize;
}//end func

/**
 *destroy the data on the node
 *(to be honest this is just a dummy function to initialize the table)
 *(im not really using this as it is optional)
 *@param *data for the data to be destroyed
 */
void destroyNodeData(void *data){
    //free the data
    free(data);
}//end func

/**
 *print the node of the data
 *@param *toBePrinted the data of node to be printed
 */
void printNodeData(void *toBePrinted){
    printf("%s", (char*)toBePrinted);
}//end func

/**
 *print all any available data in the hash table
 *@param hashTable where you pass the hash table to be printed
 */
void printList(HTable *hashTable){
    printf("Printing list... \n");
    
    //loop through the hash and print each
    for(int x=0; x < hashTable->size; x++){
        //if the hash table is not null then print the element
        if(hashTable->table[x] != NULL){
            //set the starting point
            Node* tempNode = hashTable->table[x];
            //run through the list
            if(tempNode != NULL) {
                /*move forward using next pointer*/
                while(tempNode != NULL) {
                    //print (tempNode);
                    printf("<%d>:<%s>:<%s>\n", x, (char*)tempNode->key, (char*)tempNode->data);
                    tempNode = tempNode->next;
                }/*end while*/
            }else{
                //if the list is null print that its empty
                printf("The list is empty.\n");
            }//end if
        }//end if
    }//end for
}//end func

/**
 *change to lower case
 *@param string for the string to change to lowercaser
 */
char * lowerCase(char * string){
    for(int x=0; x <strlen(string);x++){
        string[x] = tolower(string[x]);
    }//end if
    return string;
}//end func 