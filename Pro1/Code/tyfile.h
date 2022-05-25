#ifndef _TYFILE_H_
#define _TYFILE_H_

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>//stringstream
#include<io.h>
#include<fstream>
#include<direct.h>  
#include<ctype.h>
#include<map>
#include<unordered_set>
#include<list>
#include<cstdio>
#include<time.h>

using namespace std;
#define fileMaxNumber 88

struct wordInFile {
    int fileID;//index of the fie in file list
    int time;//times of appearing time in the file
    string sentence;//First sentense in the file with word
};

struct word {
    string name;
    int times;
    long filenum;
    struct wordInFile* filelist[fileMaxNumber];
};

//struct for bucket sort before output
struct OutTopFile
{
    int Bucket = 0;
    int ID;
    string sentence; 
};

/*
 *it's a function to initializing pointers and variables
 *---------------------------------------------------------------
 * Input:
 * temp: wordInFile pointer 
 * 
 * returns: void
*/
void initWordInFile(struct wordInFile* temp);

/*
 *it's a function to initializing pointers and variables
 *---------------------------------------------------------------
 * Input:
 * temp: word pointer 
 * 
 * returns: void
*/
void initWord(struct word* temp);

/*
 *it's a function to open all files and scan after obtaining the file name.
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void getAllFiles();

/*
 *it's a function to find the file name based on the ID of the file
 *---------------------------------------------------------------
 * Input: 
 * fileid: int
 * returns: string of file name
*/
string outputFileName(int fileid) ;

/*
 *it's a function to read in and build the stop words in a set
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
bool stop_words();

/*
 *it's a function to Split the input string into words, 
and store the queried word results in the wordspr dynamic 
array for return.
 *---------------------------------------------------------------
 * Input: 
 * line: the string which user input
 * wordsptr: answer asset with all word pointer
 * returns: void 
*/
void handleInput(string line, vector<struct word*>& wordsptr);

/*
 *it's a function to Open the file, read it sentence by sentence, 
    split the sentences, and restore the words to the roots. Find out 
    whether this word exists in the word tree. If it exists, increase 
    its occurrence times by one. If it does not exist, insert it into 
    the word tree
 *---------------------------------------------------------------
 * Input: 
 * filename: the string of file name
 * fileid: index if file in file list
 * returns: void 
*/
void readFile(string filename, int fileid);

/*
 *it's a function to Scan the files, find out all the 
    files under the relative path folder, and save the file
    name into the file list.
 *---------------------------------------------------------------
 * Input: 
 * filesName: the string of file name
 * path: the path of file that can be absolute path or relative path, 
 * which is specified as relative path in this document
 * 
 * returns: void (actually the filesName is the return value)
*/
void getFileName(string path, vector<string>& filesName);

/*
 *it's a function to Store the structure of a word into a TXT file.
 *---------------------------------------------------------------
 * Input: 
 * wordc: word struct pointer
 * returns: void 
*/
void wordIntotxt(struct word* wordc);

/*
 *it's a function to reload the structure of a word from a TXT file.
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
void txtRestore();


/*
 *it's a function to Confirm whether the document has been
    scanned before. If so, start from word Txt, if not scanned, 
    scan and establish a word tree to create word Txt file and 
    save it
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
void checkfile();

/*
 *it's a function to Overloaded operator for sort function. 
    The size comparison algorithm can be specified as the 
    method we need
 *---------------------------------------------------------------
 * Input: two Specific types of variables
 * returns: The result of comparation (True or False)
*/
bool cmp(struct OutTopFile a, struct OutTopFile b);

/*
 *it's a function to Input a line of string to be searched, 
    get the processed word pointer, calculate the weight of each 
    search result for it, and output the specified number of 
    query results
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
void input();

#endif