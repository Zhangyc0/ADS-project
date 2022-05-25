/* 
 * "hash.cpp" is a file to handle all operations related to the hash
 *---------------------------------------------------------------
 * functions:
 * long simHash(string word, int base)
*/
#include "hash.h"

/*
 * it's a function to convert string to hash value
 *---------------------------------------------------------------
 * Input:
 * word: the string to convert
 * base: the hash base
 * 
 * returns: the word's hash value
*/
long simHash(string word, int base)
{
    long hash = 0;
    int strln = word.length();
    
    for(int i = 0; i < strln; i++)
    hash = (hash * base % (int)(HASH_SIZE) + (word[i] - 'a')) % (int)(HASH_SIZE);
    
    return hash;
}