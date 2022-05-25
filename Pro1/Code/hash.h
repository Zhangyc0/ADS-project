#ifndef _HASH_H_
#define _HASH_H_

#include <string>
using namespace std;

/*
 * it's a function to convert string to hash value
 *---------------------------------------------------------------
 * Input:
 * word: the string to convert
 * base: the hash base
 * 
 * returns: the word's hash value
*/
long simHash(string word, int base);
#define HASH_SIZE 2e9

#endif