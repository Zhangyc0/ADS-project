#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct FibonacciNode *FibNode;
struct FibonacciNode{
	int vertex;
    int degree;
    int value;
    FibNode right;
    FibNode left;
    FibNode parent;
    FibNode child;
    bool mark;
};

typedef struct FibonacciHeap *FibHeap;
struct FibonacciHeap{
    FibNode min;
    int maxDegree;
    int keyNum;
    FibNode *cons;
};

FibHeap InitialHeap(void);  //Initial the heap.
FibNode InitialFibNode(int value, int vertex);  //Create a new node.
void FibInsertNode(FibHeap fibheap, FibNode fibnode); //Insert a node into fibonacci heap.
void FibAddBefore(FibNode fibnode1, FibNode fibnode2); //add node 1 before node2
FibHeap FibHeapMerge(FibHeap fibheap1, FibHeap fibheap2); 
bool IsFibEmpty(FibHeap fibheap);
FibNode FibHeapMin(FibHeap fibheap); //Return the least node.
void FibDecrease(FibHeap fibheap, FibNode fibnode, int value); //Change the value of a certain node.
void FibTranstoRoot(FibHeap fibheap, FibNode fibnode);  //Move the node to root.
void FibDeleteMin(FibHeap fibheap);
void FibNeaten(FibHeap fibheap);  //Merge the nodes of same degrees.

