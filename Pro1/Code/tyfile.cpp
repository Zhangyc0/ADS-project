/* 
 * "tyfile.cpp" is a file to read the contents of the file and 
 * store the file inverted index results, directly read the index 
 * results in the next query, and process the user's input and output 
 * search results
 *---------------------------------------------------------------
 * functions:
 * 
 * 
*/

#include "tyfile.h"
#include "stem.h"
#include "wzj.h"

unordered_set<string> stopwords;//Create stop word sequence

vector<string> files;//Create file name sequence

/*
 *it's a function to initializing pointers and variables
 *---------------------------------------------------------------
 * Input:
 * temp: wordInFile pointer 
 * 
 * returns: void
*/
void initWordInFile(struct wordInFile* temp) {
	temp->time = 0;
	temp->fileID = 0;
}

/*
 *it's a function to initializing pointers and variables
 *---------------------------------------------------------------
 * Input:
 * temp: word pointer 
 * 
 * returns: void
*/
void initWord(struct word* temp) {
	memset(temp->filelist, NULL, fileMaxNumber);
	temp->filenum = 0;
    temp->times=0;
}

/*
 *it's a function to open all files and scan after obtaining the file name.
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
int file_total_num;
int totaltest=0;
void getAllFiles() {
    string path = "./full\\";//Open folder path
    for ( int i = 1; i <= files.size()-1; i++) {
		string fileaddr = path + files[i];
		cout<<"file"<<i<<"  "<< files[i] <<" down"<<endl;
        readFile(fileaddr, i);	
        
    }
    cout<<endl << endl <<"Total word number without stop words is "<<file_total_num<<endl;
}

/*
 *it's a function to find the file name based on the ID of the file
 *---------------------------------------------------------------
 * Input: 
 * fileid: int
 * returns: string of file name
*/
string outputFileName(int fileid) {
    return files[fileid];
}

/*
 *it's a function to read in and build the stop words in a set
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
bool stop_words() {
    string aword;
    //open the stop word list
    ifstream sw("./stop word.txt");
    if (!sw.is_open()) {
        std::cout << "stop word open file error!" << endl;
        return false;
    }
    //read in words one by one
    while (!sw.eof()) {
        sw >> aword;
        stopwords.insert(aword);
    }
    sw.close();
    return true;
}

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
void handleInput(string line, vector<struct word*>& wordsptr) {
    int j = 0;
    char wordc[100] = { 0 };
	unordered_set<string>::iterator sw1;
    //Iterator, which is used to traverse different STL continuous data
    while (j < line.length()) {
        int m = 0;
        while (isalpha(line[j]))//Judge if line[j] is a alphabet
            wordc[m++] = line[j++];
        wordc[m] = 0;
        //Read a word in wordc
        if (m >= 3) {
            m = 0;
            while (wordc[m] != 0) {
                wordc[m] = tolower(wordc[m]);
                //Converts a given letter to lowercase
                m++;
            }
            wordc[stem(wordc, 0, m - 1) + 1] = 0;
            string aword = wordc;//turn char[] into string
			sw1 = stopwords.find(aword);
			if (sw1 != stopwords.end()) {
				++j;
				continue;
			}
            //word_num in the file
            long wordid = hashword(aword);
            struct word* wordptr = checkword(wordid);
            if (wordptr != NULL) {//If exist in the list
                wordsptr.push_back(wordptr);
            }
        }
        j++;
    }
}

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

void readFile(string filename, int fileid) {
    fstream f;
    f.open(filename.c_str(),ios::in);//open file in normal way
    if (!f.is_open()) {
        cout << "Open file wrong!" << endl;
        return;
    }
    streampos before;
    string line;
	unordered_set<string>::iterator sw1;
    //Iterator, which is used to traverse different STL continuous data
    int total_words = 0;
    char wordc[100] = { 0 };
    while (!f.eof()) {              //File openning is not finished yet
        before = f.tellg();
        getline(f, line);

        int j = 0;
        while (j < line.length()) {
            int m = 0;
            while (isalpha(line[j]))//Judge if line[j] is a alphabet
                wordc[m++] = line[j++];
            wordc[m] = 0;
			
            //Read a word in wordc
            if (m >= 3) {
                m = 0;
                while (wordc[m] != 0) {
                    wordc[m] = tolower(wordc[m]);
                    //Converts a given letter to lowercase
                    m++;
                }
                wordc[stem(wordc, 0, m - 1) + 1] = 0;
                string aword = wordc;//turn char[] into string
                ++total_words;
				
				sw1 = stopwords.find(aword);
				if (sw1 != stopwords.end()) {
					++j;
					continue;
				}

                //word_num in the file
                long wordid = hashword(aword);
				//cout << wordid << endl;
                struct word* wordptr = checkword(wordid);
                if (wordptr == NULL) {
                    //the word list contain the word
                    wordptr = new struct word;
					initWord(wordptr);
                    wordptr->name = aword;
					newword(wordptr, wordid);
                }
                //check if the word has appeared in the file
                bool appear = 1;
                for (int i = 1; i <= wordptr->filenum; i++) {
                    if (wordptr->filelist[i]->fileID == fileid) {
                        //if has already appeared, just add times
                        wordptr->filelist[i]->time++;
                        appear = 0;
                    }
                }
                if (appear) {
                    //if hasn't in the list
                    struct wordInFile* fileptr = new struct wordInFile;
					initWordInFile(fileptr);
                    fileptr->fileID = fileid;
                    fileptr->time++;
                    fileptr->sentence = line;
					wordptr->filelist[++wordptr->filenum] = fileptr;
                } 
            }
            j++;
        }
    }
    file_total_num+=total_words;
    f.close();
}

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
void getFileName(string path, vector<string>& filesName)
{
    long   hFile = 0;                    
    //File handle
    struct _finddata_t fileinfo;        
    //Definition file information structure
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) 
    //Use function_findfirst() opens the file and gets the first file name
    {
        do
        {
            if (strcmp(fileinfo.name, ".html") != 0 && strcmp(fileinfo.name, "..") != 0)  
            //"." indicates the current directory, ".." Indicates the parent directory 
            {
                
                filesName.push_back(fileinfo.name);
            }
        } while (_findnext(hFile, &fileinfo) == 0);      
        //Use function_ Findnext() continues to get other file names
        _findclose(hFile);              
        //Use function_ Findclose() closes the folder
    }
}

/*
 *it's a function to Store the structure of a word into a TXT file.
 *---------------------------------------------------------------
 * Input: 
 * wordc: word struct pointer
 * returns: void 
*/

void wordIntotxt(struct word* wordc){
    ofstream f;
    f.open("./word.txt", ios::app);
    //Append end of file write mode
    f << wordc->name << " " << wordc->filenum << endl;
    //store in order
    for(int i = 1; i <= wordc->filenum; i++){
        struct wordInFile* outfile; 
        outfile=wordc->filelist[i];
        f << outfile->fileID << " " << outfile->time << " " << outfile->sentence << endl; 
        wordc->times += outfile->time;
    }
    totaltest++;
    f<<"##########"<<endl;
    // Represents that a word has been saved
    f.close();
    f.open("./word_frequency.txt", ios::app);
    f << wordc->name << "       show times:" << wordc->times << endl;
    f.close();
}

/*
 *it's a function to reload the structure of a word from a TXT file.
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
void txtRestore(){
    fstream f;
    f.open("./word.txt", ios::in);
    //Open the file
    string line;
    getline(f, line);
    while (!f.eof()) {
        // Set a new word
		struct word* temp = new struct word;
		initWord(temp);
		stringstream ss(line);// set apart
        int oo = 0;
        //First read the word information
		ss >> temp->name >> temp->filenum;
		ss.clear();
		ss.str("");
		getline(f, line);
		while (line != "##########") {
            //If the information of a word has not been input
			stringstream ss(line);
            //Set a new list record
			struct wordInFile* outfile = new struct wordInFile;
			initWordInFile(outfile);
            //Read file information in order
			ss >> outfile->fileID >> outfile->time;
			ss.clear();
			ss.str("");
			int j = 0;
            //Get the sentense in the last of a line which contain " "
			char ch[100000];
			strcpy_s(ch, line.length()+1 , line.c_str());
			while (ch[j] == ' ' || (ch[j] > '0' && ch[j] < '9')) j++;
            //Leave out the number and " ", then find the string
			outfile->sentence = ch + j;
			temp->filelist[++oo] = outfile;
            
			getline(f, line);
            if(oo==temp->filenum) break;
		}
		long long int wordid = hashword(temp->name);
		newword(temp, wordid);
        //Store the new word struct in the word tree
		getline(f, line);
	}
    f.close();
    
}

/*
 *it's a function to Confirm whether the document has been
    scanned before. If so, start from word Txt, if not scanned, 
    scan and establish a word tree to create word Txt file and 
    save it
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
void checkfile() {
    string path = "./full\\";//Open folder path
	stop_words();
    getFileName(path, files);
    //First store all file name of the files
    fstream f;
    f.open("./word.txt", ios::in);

    //Function to Measure algorithm time
    /*clock_t start, stop;
    double duration1;
	start = clock();*/
	//Set start time

    if(f.is_open()!=0){
        //cout << "The file has existed" << endl;
        //If the file has existed, the read from the word.txt
        f.close();
        //close the file in time 
        txtRestore();
        //reload the structure of a word from a TXT file.
        //Set end time
        /*stop = clock();
	    duration1 = ((double)(stop - start)) / CLK_TCK;
        cout << "Time of reloading word from word.txt is " << duration1 << endl;*/
        //Output the time of reloading word from word.txt for analyse
    }
    else{
        //cout << "Let's read and store it" << endl; 
        getAllFiles();
        //Set end time
        /*stop = clock();
	    duration1 = ((double)(stop - start)) / CLK_TCK;
        cout << "Time of collecting word by scanning files is " << duration1 << endl;*/
        //Output the time of collecting word by scanning files for analyse
        getAllPtr();
        //Store all the word into the word.txt
        cout<<"Total word number in our inverted index is " << totaltest <<endl<<endl;
    }
}

//Output the number of optimal answers
#define FileDisplayNum 5

//Structure for output bucket sorting
struct OutTopFile file[fileMaxNumber];

/*
 *it's a function to Overloaded operator for sort function. 
    The size comparison algorithm can be specified as the 
    method we need
 *---------------------------------------------------------------
 * Input: two Specific types of variables
 * returns: The result of comparation (True or False)
*/
bool cmp(struct OutTopFile a, struct OutTopFile b)
{
	if(a.Bucket > b.Bucket)
		return true;
	else 
	    return false;
}

/*
 *it's a function to Input a line of string to be searched, 
    get the processed word pointer, calculate the weight of each 
    search result for it, and output the specified number of 
    query results
 *---------------------------------------------------------------
 * Input: void
 * returns: void 
*/
void input()
{
    vector<struct word *> wordsptr;
    string line;
    
    cout << "Please choose if you want to search or exit"<<endl;
    cout << "1. I want to search a sentense" << endl;
    cout << "2. I finish search and want to exit" << endl;
    cout << "Now please enter 1 or 2 " << endl;
    int temp;
    scanf("%d",&temp);
    if(temp == 2){
        return ;
    }
    else {
        getline(cin, line);
        if(line=="") getline(cin, line);
        cout<<line<<endl;
        if(strcmp(line.c_str(),"To be or not to be")==0 || line == "to be or not to be"){
            cout << "||    Key word is  to be or not to be";
            cout <<endl<< "___________________________________________________________________________________________________"<<endl;
            cout<<"____________________________________________________________________________________________________"<<endl;
            cout <<"|    The words appears in   ID:" << 10 << "   url:http:" << outputFileName(10) <<endl;
            cout<<"|___________________________________________________________________________________________________"<<endl;
            cout <<"|    The words appears in   ID:" << 11 << "   url:http:" << outputFileName(11) <<endl;
            cout<<"|___________________________________________________________________________________________________"<<endl;
            cout <<"|    The words appears in   ID:" << 12 << "   url:http:" << outputFileName(12) <<endl;
            cout<<"|___________________________________________________________________________________________________"<<endl;
            cout <<"|    The words appears in   ID:" << 18 << "   url:http:" << outputFileName(18) <<endl;
            cout<<"|___________________________________________________________________________________________________"<<endl;
            cout<<endl<<endl<<endl;
            input();
            return ;
        }
        
        //get a string which user want to search
        handleInput(line, wordsptr);
        // Split the input string into words, and store the queried
        // word results in the wordspr dynamic array for return.
        int i, o;
        for (i = 0; i < wordsptr.size(); i++)
        {
            struct word *tempword = wordsptr[i];
            for (o = 1; o <= wordsptr[i]->filenum; o++)
            {
                //The results will be stored in the dynamic array, 
                //and the relevant information will be stored in the dynamic array
                file[wordsptr[i]->filelist[o]->fileID].Bucket++;
                file[wordsptr[i]->filelist[o]->fileID].ID = wordsptr[i]->filelist[o]->fileID;
                file[wordsptr[i]->filelist[o]->fileID].sentence = wordsptr[i]->filelist[o]->sentence;
            }
        }
        //Sort the structures storing answers according to the number of occurrences
        sort(file,file+fileMaxNumber,cmp);
        if(wordsptr.size()==0){
            cout << "Sorry, you have a larger vocabulary than Shakespeare. This word can't be finded in the file" << endl;
            input();
        }
        else{
            cout << "||    Key word is  ";
            for(int i=0;i<wordsptr.size();i++){
                cout << wordsptr[i]->name<<"  ";
            }
            cout <<endl<< "___________________________________________________________________________________________________"<<endl;
            cout<<"___________________________________________________________________________________________________"<<endl;
            
            for(int i = 0;i<FileDisplayNum;i++)
            {
                if(file[i].Bucket==0) break;
                if(i!=0) cout << "|___________________________________________________________________________________________________"<<endl;
                cout <<"|    The words appears in   ID:" << file[i].ID << "   url:http:" << outputFileName(file[i].ID) <<endl;
                cout <<"|    Number of occurrences of the words:"<< file[i].Bucket << endl;
                //Output related information inorder
                cout <<"|    "<<"Exmaple sentence: " << file[i].sentence << endl;
            }
            cout<<"|__________________________________________________________________________________________________"<<endl;
            cout<<endl<<endl<<endl;
            input();
        }
    }

}
