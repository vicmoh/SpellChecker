/**************************
 * Name: Vicky Mohammad
 * ID: 0895381
 **************************/

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>

/**
*Node of the hash table. 
**/
typedef struct Node
{
    char* key; ///< integer that represents a piece of data in the table (eg 35->"hello")
    void *data; ///< pointer to generic data that is to be stored in the hash table
    struct Node *next; ///< pointer to the next Node if a collision is detected
} Node;

/**
*Hash table structure
**/
typedef struct HTable HTable;
struct HTable
{
    size_t size; ///< number that represents the size of the hash table
    Node **table; ///< array that contains all of the table nodes
    void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the hash table
    int (*hashFunction)(size_t tableSize, char* key); ///< function pointer to a function to hash the data 
    void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the table

    /**A function pointer for add is not mandatory, just a suggestion for adding. 
    * Assigned as &insertDataInMap when initializing a map.
    * Allows overloading of function names to use standard naming conventions, similar to the object oriented approach.
    **/
    void (*add) (struct HTable *hashTable, void *data); ///< function pointer for users to add a data element to the map.
};


/**Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
*@return pointer to the hash table
*@param size size of the hash table
*@param hashFunction function pointer to a function to hash the data
*@param destroyData function pointer to a function to delete a single piece of data from the hash table
*@param printNode function pointer to a function that prints out a data element of the table
**/
HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char* key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted));

/**Function for creating a node for the hash table.
*@pre Node must be cast to void pointer before being added.
*@post Node is valid and able to be added to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data is a generic pointer to any data type.
*@return returns a node for the hash table
**/
Node *createNode(char* key, void *data);

/** Deletes the entire hash table and frees memory of every element.
*@pre Hash Table must exist.
*@param hashTable pointer to hash table containing elements of data
**/
void destroyTable(HTable *hashTable);  

/**Inserts a Node in the hash table.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data pointer to generic data that is to be inserted into the list
**/
void insertData(HTable *hashTable, char* key, void *data);

/** THIS FUNCTION IS NOT MANDATORY, users call this function to insert a Node in the hash table.
* It's meant as a wrapper for insertData so the users don't need to generate the key when adding.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param data pointer to generic data that is to be inserted into the list
**/
void insertDataInMap(HTable *hashTable, void *data);

/**Function to remove a node from the hash table 
 *@pre Hash table must exist and have memory allocated to it
 *@post Node at key will be removed from the hash table if it exists.
 *@param hashTable pointer to the hash table struct
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 **/
void removeData(HTable *hashTable, char* key);

/**Function to return the data from the key given.
 *@pre The hash table exists and has memory allocated to it
 *@param hashTable pointer to the hash table containing data nodes
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 *@return returns a pointer to the data in the hash table. Returns NULL if no match is found.
 **/
void *lookupData(HTable *hashTable, char* key);

int hashNode(size_t tableSize, char* key);

void destroyNodeData(void *data);

void printNodeData(void *toBePrinted);

void printList(HTable *hashTable);

/**
 *change to lower case
 *@param string for the string to change to lowercaser
 */
char * lowerCase(char * string);

#endif