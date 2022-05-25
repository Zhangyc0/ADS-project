#include"Fibonacci heap.h"
#include<time.h>

FibHeap InitialHeap(void)
{
    FibHeap fibheap = (FibHeap)malloc(sizeof(struct FibonacciHeap));
    fibheap->min = NULL;
    fibheap->maxDegree = 0; 
    fibheap->keyNum = 0;
    fibheap->cons = NULL;
	return fibheap;
}

FibNode InitialFibNode(int value, int vertex)
{
	FibNode fibnode = (FibNode)malloc(sizeof(struct FibonacciNode));
	fibnode->child = NULL;
	fibnode->parent = NULL;
	fibnode->left = fibnode;
	fibnode->right = fibnode;
	fibnode->vertex = vertex;
	fibnode->value = value;
	fibnode->degree = 0;
	fibnode->mark = false;
	return fibnode;
}

void FibInsertNode(FibHeap fibheap, FibNode fibnode)
{
	if (fibnode == NULL)  //Fibnode is illeagal
		return;
	else if (fibheap->keyNum == 0)  //Fibnode is the first member of the fibonacci heap. 
		fibheap->min = fibnode;
	else
	{
		FibNode curMin = fibheap->min;
		FibAddBefore(fibnode, curMin);  //Insert fibnode to the left of the min node.
		if (fibnode->value < curMin->value)
			fibheap->min = fibnode;
	}
	fibheap->keyNum++; //Update
}

void FibAddBefore(FibNode fibnode1, FibNode fibnode2) //-fibnode1- and -fibnode2- become -fibnode1-fibnode2-
{
	fibnode1->left = fibnode2->left;  
	fibnode2->left->right = fibnode1;
	fibnode1->right = fibnode2;
	fibnode2->left = fibnode1;
}

FibHeap FibHeapMerge(FibHeap fibheap1, FibHeap fibheap2)
{
	if (fibheap1 == NULL) //Check if fibheap1 or fibheap2 is null.
		return fibheap2;
	else if (fibheap2 == NULL)
		return fibheap1;
	else
	{
		if (fibheap1->maxDegree < fibheap2->maxDegree) //Let fibheap1's maxDegree bigger than fibheap2.
		{
			FibHeap temp = fibheap1;
			fibheap1 = fibheap2;
			fibheap2 = temp;
		}
		if (fibheap1->min == NULL)
		{
			fibheap1->keyNum = fibheap2->keyNum;
			fibheap1->maxDegree = fibheap2->maxDegree;
		}
		else if (fibheap2->min != NULL) //Merge two fibonacci heap.
		{
			FibNode temp;
			FibNode fibnode1 = fibheap1->min, fibnode2 = fibheap2->min;
			temp = fibnode1->right;
			fibnode1->right = fibnode2->right;
			fibnode2->right->left = fibnode1;
			fibnode2->right = temp;
			temp->left = fibnode2;
			if (fibnode1->value > fibnode2->value)
				fibheap1->min = fibheap2->min;
			fibheap1->maxDegree += fibheap2->maxDegree;
		}
		free(fibheap2->cons);
		free(fibheap2);
		return fibheap1; //fibheap2 has been merged into fibheap1.
	}
}

bool IsFibEmpty(FibHeap fibheap)
{
	if (fibheap->min  == NULL)
		return true;
	else
		return false;
}

FibNode FibHeapMin(FibHeap fibheap)
{
	return fibheap->min;
}

void FibDecrease(FibHeap fibheap, FibNode fibnode, int value)
{
	if (fibheap == NULL || fibheap->min == NULL || fibnode == NULL)
		return;
	fibnode->value = value;
	FibNode parent = fibnode->parent;
	if (parent != NULL && parent->value > fibnode->value)
	{
		FibTranstoRoot(fibheap, fibnode);  //if fibnode's value is bigger than its parent, move it to root.
	}
	if (fibheap->min->value > fibnode->value)
		fibheap->min = fibnode;
}

void FibTranstoRoot(FibHeap fibheap, FibNode fibnode)
{
	FibNode parent = fibnode->parent;   
	if (parent == NULL)
		return;
	fibnode->right->left = fibnode->left;  //Delete fibnode from left-fibnode-right
	fibnode->left->right = fibnode->right;
	if (fibnode->right == fibnode)       //Update parent node
		parent->child = NULL;
	else
		parent->child = fibnode->right;
	parent->degree--;
	FibAddBefore(fibnode, fibheap->min);   //Update fibnode information
	fibnode->parent = NULL;
	fibnode->mark = false;
	if (parent->mark == false)  //Determine whether the fibnode needs to be moved to the root
		parent->mark = true;
	else
		FibTranstoRoot(fibheap, parent);
}

void FibDeleteMin(FibHeap fibheap)
{
	if (fibheap == NULL || fibheap->min == NULL)
		return;
	FibNode min = fibheap->min;
	while (min->child != NULL)  //Add all children of min to root-link
	{
		FibNode child = min->child;
		child->right->left = child->left;  //Delete min from left-fibnode-right
		child->left->right = child->right;
		if (child->right == child)
			min->child = NULL;
		else
			min->child = child->right;
		FibAddBefore(child, min);
		child->parent = NULL;
	}
	min->right->left = min->left;  //Delete min
	min->left->right = min->right;
	fibheap->min = (fibheap->keyNum == 1) ? NULL : min->right;
	fibheap->keyNum--;
	FibNeaten(fibheap);
}

void FibNeaten(FibHeap fibheap)
{
	if (fibheap == NULL || fibheap->min == NULL)
		return;
	fibheap->maxDegree = (int)(log2((double)(fibheap->keyNum)) + 1);
	fibheap->cons = (FibNode*)malloc(sizeof(FibNode)*(fibheap->maxDegree + 1)); //Allocate an array to combine heaps with the same degrees.
	for (int i = 0; i < fibheap->maxDegree + 1; ++i)
		fibheap->cons[i] = NULL;
	while (fibheap->min != NULL)  //Combine heaps with the same degrees.
	{
		FibNode curMin = fibheap->min;  //Get the current heap.
		int curDegree = curMin->degree;
		if (curMin->right == curMin)
			fibheap->min = NULL;
		else
		{
			fibheap->min = curMin->right;
			curMin->right->left = curMin->left;
			curMin->left->right = curMin->right;
		}
		curMin->left = curMin->right = curMin;  //Isolate this node.

		while (fibheap->cons[curDegree] != NULL)  //Add current heap to array cons. If there is a collision.
		{
			FibNode SameDegree = fibheap->cons[curDegree]; 
			if (SameDegree->value < curMin->value)  
			{
				FibNode temp = SameDegree;
				SameDegree = curMin;
				curMin = temp;
			}
			SameDegree->right->left = SameDegree->left;
			SameDegree->left->right = SameDegree->right;
			if (curMin->child == NULL)       //Make SameDegree be curMin's children
				curMin->child = SameDegree;
			else
				FibAddBefore(SameDegree, curMin->child);
			SameDegree->parent = curMin;
			SameDegree->mark = false;
			curMin->degree++;
			fibheap->cons[curDegree] = NULL;
			curDegree++;
		}
		fibheap->cons[curDegree] = curMin;
	}
	fibheap->min = NULL;
	for (int i = 0; i < fibheap->maxDegree + 1; ++i) //Copy the heap from cons to fibheap.
	{
		if (fibheap->cons[i] != NULL)
		{
			if (fibheap->min == NULL)
				fibheap->min = fibheap->cons[i];
			else
			{
				FibAddBefore(fibheap->cons[i], fibheap->min);
				if (fibheap->cons[i]->value < fibheap->min->value)
					fibheap->min = fibheap->cons[i];
			}
		}
	}
	free(fibheap->cons); //Free memory.
}



