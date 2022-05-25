#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct BinomialNode *BinHeap, *BinNode;
struct BinomialNode {
	int value;
	int vertex;
	int degree;
	BinHeap parent;
	BinHeap child;
	BinHeap sibling;
};
BinHeap InitialBinNode(int value, int vertex); //Create a new node.
BinHeap BinLinked(BinHeap binheap, BinHeap child);  //Link child node with binomial heap.
BinHeap BinCombineOrder(BinHeap binheap1, BinHeap binheap2); //Merge two lists in increase order.
BinHeap BinMerge(BinHeap binheap1, BinHeap binheap2); //Merge two lists and combine subtrees with same degrees
BinHeap* BinGetMin2(BinHeap binheap); //Get the min node and its previous node.
BinHeap BinDeleteMin(BinHeap binheap); //Delete min node.
BinHeap BinGetMin(BinHeap binheap);  //Get the min node.
BinHeap BinInsert(BinHeap binheap, BinNode binnode); //Insert a new node to heap.
void    BinDecrease(BinHeap binheap, BinNode binnode, int value, BinHeap* NodeArray);  //Decrease the value of one certain node.
bool    IsBinEmpty(BinHeap binheap);  //Judge if the heap is empty.