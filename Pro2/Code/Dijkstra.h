#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<limits.h>
#include"Fibonacci heap.h"
#include"Pairing heap.h"
#include"Binomial heap.h"

#define Infinity INT_MAX

typedef struct EdgeNode* Edge;
struct EdgeNode{
	int weight;   //The distance between two nodes.
	int destination;  
	Edge next;
};

Edge AddEdge(Edge start, int weight, int destination);  //Create n list to storage information from map.(n is the number of nodes.)
Edge *ReadFile(int *maxNode);    //Read map from a file.
void DijkstraWithFib(Edge *edge, int maxNode, int sorNode, int numFind);  //Implement Dijstra algorithm with Fibonacci heap.
void DijkstraWithPair(Edge *edge, int maxNode, int sorNode, int numFind); //Implement Dijstra algorithm with Pairing heap.
void DijkstraWithBin(Edge *edge, int maxNode, int sorNode, int numFind);  //Implement Dijstra algorithm with Binomail heap.

