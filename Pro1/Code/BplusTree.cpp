/* 
 * "BpulsTree.cpp" is a file to handle all operations related to the B + tree
 *---------------------------------------------------------------
 * functions:
 * Nodeptr insert(Nodeptr root, long digit, Word pointer);
 * int insert_arr(int num, Hash a[], long digit, Word pointer);
 * Nodeptr checkAndSplit(Nodeptr root);
 * Word Find(long digit, Nodeptr root);
 * void inInsert(long digit, Word pointer);
 * Word inFind(int digit);
 * void treeInitial();
 * void ergodicLeaf();
 * void outToTxt(Nodeptr root);
 * 
*/

#include "BplusTree.h"
#include "tyfile.h"

Nodeptr treeRoot;

/*
 * it's a function to Initial the empty B+ tree
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void treeInitial()
{
    treeRoot = (Nodeptr)malloc(sizeof(struct Node));
    treeRoot->parent = NULL;
    treeRoot->num = 0;
    treeRoot->type = leaf;
}

/*
 * it's a function to provide an interface to "wzj.cpp"
 *---------------------------------------------------------------
 * Input: 
 * digit: the ID of each node
 * 
 * returns: void
*/
Word inFind(int digit)
{
    return Find(digit, treeRoot);
}

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
Word Find(long digit, Nodeptr root)
{
    int k;
    while(root){
        if(root->type == key){
            for(k = 0; k < root->num - 1; k++){
                if(digit < root->content[k].value){
                    break;
                }
            }
            root = root->child[k];
        }
        else{
            for(k = 0; k < root->num; k++){
                if(digit == root->content[k].value){
                    return root->content[k].pointer;
                }
                if(digit < root->content[k].value){
                    break;
                }
            }
            break;
        }
    }

    return NULL;
}

/*
 * it's a function to provide an interface to "wzj.cpp"
 *---------------------------------------------------------------
 * Input: 
 * digit: a part of the node(Hash) to be insertd
 * pointer: a part of the node(Hash) to be insertd
 * 
 * returns: void
*/
void inInsert(long digit, Word pointer)
{
    treeRoot = insert(treeRoot, digit, pointer);
}

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
Nodeptr insert(Nodeptr root, long digit, Word pointer)
{
    int k;

    if(root->type == key){
        for(k = 0; k < root->num - 1; k++){
            if(digit < root->content[k].value){
                break;
            }
        }
        root->child[k] = insert(root->child[k], digit, pointer);
    }
    else if(root->type == leaf){
        if(insert_arr(root->num, root->content, digit, pointer) >= 0){
            root->num++;
            root->min = root->content[0].value;
            Nodeptr p = root;
            while(p->parent){
                if(p->min < p->parent->min){
                    p->parent->min = p->min;
                }
                else{
                    break;
                }
                p = p->parent;
            }
        }
        else{

        }
    }
    root = checkAndSplit(root);

    return root;
}

/*
 * it's a function to check whether the node of B+ tree satisfies B+ tree's property
 * if not, split the node and modify it to satisfies B+ tree's property
 *---------------------------------------------------------------
 * Input: 
 * root: the input node to be checked and modified
 * 
 * returns: root, the modified node
*/
Nodeptr checkAndSplit(Nodeptr root)
{
    
    if(root->num > ORDER){
        Nodeptr p = (Nodeptr)malloc(sizeof(struct Node));
        p->type = root->type;
        p->num = root->num / 2;
        root->num -= p->num;
        if(root->type == leaf){
            for(int i = 0; i < p->num; i++){
                p->content[i] = root->content[root->num + i];
            }
            p->min = p->content[0].value;
        }
        else{
            for(int i = 0; i < p->num; i++){
                p->child[i] = root->child[root->num + i];
                p->child[i]->parent = p;
            }
            for(int i = 0; i < p->num - 1; i++){
                p->content[i].value = p->child[i + 1]->min;
            }
            p->min = p->child[0]->min;
        }
        if(root->parent){
            p->parent = root->parent;
            int index = insert_arr(p->parent->num - 1, p->parent->content, p->min, NULL);
            for(int i = p->parent->num; i > index + 1; i--){
                p->parent->child[i] = p->parent->child[i - 1];
            }
            p->parent->child[index + 1] = p;
            p->parent->num++;
        }
        else{
            Nodeptr newroot = (Nodeptr)malloc(sizeof(struct Node));
            root->parent = newroot;
            p->parent = newroot;
            newroot->num = 2;
            newroot->min = root->min;
            newroot->content[0].value = p->min;
            newroot->type = key;
            newroot->parent = NULL;
            newroot->child[0] = root;
            newroot->child[1] = p;
            return newroot;
        }  
    }

    return root;

}

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
int insert_arr(int num, Hash a[], long digit, Word pointer)
{
    int i = 0;
    while((a[i].value < digit) && (i < num)){
        i++;
    }
    if(i == num){
        a[i].value = digit;
        a[i].pointer = pointer;
    }
    else if(a[i].value == digit){
        printf("Insert newword failed! Hashnum %ld is duplicated\n", digit);
        exit(0);
    }
    else{
        for(int j = num; j > i; j--){
            a[j] = a[j - 1];
        }
        a[i].value = digit;
        a[i].pointer = pointer;
    }

    return i;
}
queue<Nodeptr> ptrQueue;

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
void outToTxt(Nodeptr root)
{
    if (!root) return;
	Nodeptr p;
    ptrQueue.push(root);
	int curFloor = 1;
    int nextFloor = 0;
	while (!ptrQueue.empty()) {
		p = ptrQueue.front();
        ptrQueue.pop();
		if (p->type == key) {
            curFloor--;
            for(int i = 0; i < p->num; i++){
                ptrQueue.push(p->child[i]);
            }
            nextFloor += p->num;
			if (curFloor == 0) {
                curFloor = nextFloor;
                nextFloor = 0;
			}
		}
		else {
			for(int i = 0; i < p->num; i++){
                wordIntotxt(p->content[i].pointer);
            }
		}
	}

    return;
}

/*
 * it's a function to traverse the entire B+ tree and 
 * return all pointers hanging at the bottom to the caller
 *---------------------------------------------------------------
 * Input: void
 * 
 * returns: void
*/
void ergodicLeaf()
{
    outToTxt(treeRoot);

    return;
}









