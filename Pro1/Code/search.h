#ifndef _WZJ_H_
#define _WZJ_H_

#include "BplusTree.h"
#include "hash.h"
#include "tyfile.h"
using namespace std;

/*
 * it's a function to find the word with hashnum, and tell whether existing.
 * If existing, tell where(pointer);
 *---------------------------------------------------------------
 * Input:
 * hashnum: the word ID to identify and find the pointer storing infomation about it
 * 
 * returns: pointer(type Word), pointing at memory storing infomation about word
*/
Word checkword(long hashnum);

/*
 * it's a function to add a node to B+ tree, more user-friendly index build 
 *---------------------------------------------------------------
 * Input:
 * pointer: (type Word), pointing at memory storing infomation about the word identified by hashnum
 * hashnum: the word ID to identify and find the pointer storing infomation about word
 * 
 * returns: void
*/
void newword(Word pointer, long hashnum);

/*
 * it's a function to convert string to hash value
 *---------------------------------------------------------------
 * Input:
 * word: the string to convert
 * 
 * returns: the word's hash value
*/
long hashword(string word);

/*
 * it's a function to traverse the entire B+ tree and 
 * return all pointers hanging at the bottom to the caller
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void getAllPtr();

#endif