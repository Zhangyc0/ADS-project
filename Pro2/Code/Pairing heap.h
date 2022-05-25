#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct PairingNode* PairHeap,*PairNode;
struct PairingNode {
	int vertex;
	int value;
	PairHeap child;
	PairHeap sibling;
	PairHeap Prev;
};

PairNode InitialPairHeap(int value, int vertex); //Initial the heap(Create a node).
PairHeap PairMerge(PairHeap pairheap1, PairHeap pairheap2); //Merge two pairing heap.
PairHeap PairInsert(PairHeap pairheap, PairNode pairnode); 
PairHeap PairDeleteMin(PairHeap pairheap);  //Delete the min node and call CombineSiblings().
PairHeap CombineSiblings(PairHeap pairheap); //Merge the nodes in one lists.
PairHeap PairDecrease(PairHeap pairheap, PairNode pairnode, int value);
bool IsPairEmpty(PairHeap pairheap);