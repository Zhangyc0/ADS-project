#ifndef _BPLUSTREE_H_
#define _BPLUSTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string>
using namespace std;

#define ORDER 3

typedef struct word* Word;  //Word is a pointer type other collaborators need

typedef struct Node* Nodeptr;
typedef enum { leaf, key } Nodetype; // Node type include "leaf" and "key"

typedef struct Hash{
    long value;
    Word pointer;
}Hash;

typedef struct Node{
    Nodeptr child[ORDER + 1];   //the node's children's pointer in B+ tree
    Nodeptr parent;     //the node's parent's pointer in B+ tree
    int num;            //the number of child of key; or the number of element of leaf
    long min;           //the min ID of the node of this subtree whose root is this node
    Hash content[ORDER + 1];  // store every node's values, if node is leaf, the Hash.pointer store sth we need
    Nodetype type;      // node's type, leaf or key(not leaf)
}Node;

/*
 * it's a function to insert a node to the B+ tree
 *---------------------------------------------------------------
 * Input: 
 * root: the root of the tree(subtree) to be inserted
 * digit: a part of the node(Hash)
 * pointer: a part of the node(Hash)
 * 
 * returns: root, the modified node
*/
Nodeptr insert(Nodeptr root, long digit, Word pointer);

/*
 * it's a function to insert a digit and pointer to the sorted array(type Hash)
 *---------------------------------------------------------------
 * Input: 
 * num: the number of values in array
 * a[]: the name(pointer) of array
 * digit: the digit to be inserted
 * pointer: the pointer to be inserted
 * 
 * returns: i, the index of the inserting location
*/
int insert_arr(int num, Hash a[], long digit, Word pointer);

/*
 * it's a function to check whether the node of B+ tree satisfies B+ tree's property
 * if not, split the node and modify it to satisfies B+ tree's property
 *---------------------------------------------------------------
 * Input: 
 * root: the input node to be checked and modified
 * 
 * returns: root, the modified node
*/
Nodeptr checkAndSplit(Nodeptr root);

/*
 * it's a function to find a Node identified by a hash(digit)
 *---------------------------------------------------------------
 * Input: 
 * digit: a hash identifying the node of B+ tree
 * root: the root of tree(subtree)
 * 
 * returns: if find the node, then return the pointer(type Word) stored in this node
 *          if not find, return NULL
*/
Word Find(long digit, Nodeptr root);

/*
 * it's a function to provide an interface to "wzj.cpp"
 *---------------------------------------------------------------
 * Input: 
 * digit: a part of the node(Hash) to be insertd
 * pointer: a part of the node(Hash) to be insertd
 * 
 * returns: void
*/
void inInsert(long digit, Word pointer);

/*
 * it's a function to provide an interface to "wzj.cpp"
 *---------------------------------------------------------------
 * Input: 
 * digit: the ID of each node
 * 
 * returns: void
*/
Word inFind(int digit);

/*
 * it's a function to Initial the empty B+ tree
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void treeInitial();

/*
 * it's a function to traverse the entire B+ tree and 
 * return all pointers hanging at the bottom to the caller
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void ergodicLeaf();

/*
 * it's a function to traverse the entire B+ tree and 
 * return all pointers hanging at the bottom to the caller.
 * Every time finding a leaf then call function "wordIntotxt",
 * and give the pointer to it
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void outToTxt(Nodeptr root);


#endif