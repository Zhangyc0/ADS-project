#include "wzj.h"
#include "tyfile.h"
#include <iostream>
using namespace std;

int main()
{
    checkfile();
    //if the word.txt exists, then read it.
    //else scan all the files and store it in a word.txt
    input();
    return 0;
}

/*

Example1:
CHARMIAN


Example2:
Excellent falsehood! Why did he marry Fulvia, and not love her? I'll seem the fool I am not; Antony Will be himself. MARK ANTONY But stirr'd by Cleopatra. Now, for the love of Love and her soft hours, Let's not confound the time with conference harsh.

Example3:
Let me be married to three kings in a forenoon, and widow them all: let me have a child at fifty, to whom Herod of Jewry may do homage: find me to marry me with Octavius Caesar, and companion me with my mistress. Soothsayer You shall outlive the lady whom you serve. CHARMIAN O excellent! I love long life better than figs. Soothsayer You have seen and proved a fairer former fortune Than that which is to approach. CHARMIAN Then belike my children shall have no names: prithee, how many boys and wenches must I have? Soothsayer If every of your wishes had a womb. And fertile every wish, a million. 
*/