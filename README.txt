Student Information
####################
<Vicky Mohammad>
<0895381>

Program Description
####################
<Program simulatees a traffic light using linklist>

Additonal Program  Details
####################
Progam simulates a spell check dictionary using hash functions 

How to run the program
####################
<1) go to the directory on the program
 2) type: "make" to install the program
 3) then type: "./bin/runMe ./assets/fileName.txt" to run the program>

How to run the test
####################
<1) go to the directory on the program
 2) type: "make" to install the program
 3) then type: "make runTest" to run the program>

Assumption
####################
-the data files must be a txt
-the program must input a file in command line at start or it will exit
-dont enter any symbols to the program
-asuming that the output has <..> for option 4

Collision method
####################
-for the collision method if the key generate an index with 
that has something all readyy exist. I am using the seperate 
chaining methid where it creates a node of a linklist at that 
index if something already exist. hence there can be more than 
one item at the colision. since my hash function is mostly unique 
to almost every word, to prevent a change of less collision, i made 
the table size bigger number around 99999, to prevent colision happening. 
The smaller the table size the change of the colisiong to happen. hence, 
i made the size big enough to no have collsion if collision does occur, 
then i simply add in the same index. To look at the data, you can simply hash 
the word and go to the index, and iterate through the nodes of the linklist if 
there is more than one words in that index, and check if they are the 
same.   
