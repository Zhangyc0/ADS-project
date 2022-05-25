/* 
 * "wzj.cpp" is a file to interact with other collaborators and
 * provide them with function interfaces (only the functions in this file 
 * interact with other collaborators)
 *---------------------------------------------------------------
 * functions:
 * Word checkword(long hashnum);
 * void newword(Word pointer, long hashnum);
 * long hashword(string word);
 * void getAllPtr();
 * 
*/

#include "wzj.h"

/*
 * it's a function to find the word with hashnum, and tell whether existing.
 * If existing, tell where(pointer);
 *---------------------------------------------------------------
 * Input:
 * hashnum: the word ID to identify and find the pointer storing infomation about it
 * 
 * returns: pointer(type Word), pointing at memory storing infomation about word
*/
Word checkword(long hashnum)
{
    return inFind(hashnum);
}

/*
 * it's a function to add a node to B+ tree, more user-friendly index build 
 *---------------------------------------------------------------
 * Input:
 * pointer: (type Word), pointing at memory storing infomation about the word identified by hashnum
 * hashnum: the word ID to identify and find the pointer storing infomation about word
 * 
 * returns: void
*/
void newword(Word pointer, long hashnum)
{
    static int flag = 1;
    
    if(flag){
        treeInitial();
        flag = 0;
    }
    inInsert(hashnum, pointer);
}

/*
 * it's a function to convert string to hash value
 *---------------------------------------------------------------
 * Input:
 * word: the string to convert
 * 
 * returns: the word's hash value
*/
long hashword(string word)
{
    int base = 31;
    int hash;
    Word p;

    hash = simHash(word, base);
    while(1){       //Check for conflicts, if conflict, then Quadratic hash until no conflict
        p = inFind(hash);   
        if(!p){
            break;
        }
        if(p->name != word){
            base += 2;
            hash = simHash(word, base);
        }
        else{
            break;
        }
    }
    
    return hash;
}

/*
 * it's a function to traverse the entire B+ tree and 
 * return all pointers hanging at the bottom to the caller
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void getAllPtr()
{
    ergodicLeaf();  //Call to jump to "BplusTree.cpp"
    return;
}