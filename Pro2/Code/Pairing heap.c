#include "Pairing heap.h"

PairNode InitialPairHeap(int value, int vertex)
{
	PairNode pairnode = (PairNode)malloc(sizeof(struct PairingNode));
	pairnode->child = NULL;
	pairnode->Prev = NULL;
	pairnode->sibling = NULL;
	pairnode->value = value;
	pairnode->vertex = vertex;
	return pairnode;
}

PairHeap PairMerge(PairHeap pairheap1, PairHeap pairheap2)
{
	if (pairheap1 == NULL)
		return pairheap2;
	else if (pairheap2 == NULL)
		return pairheap1;
	else  //Add pairnode2 to pairnode1.
	{
		if(pairheap1->value > pairheap2->value) //Let node1_pre linked to node2 
		{
			PairNode heap1_prev = pairheap1->Prev;
			pairheap2->Prev = heap1_prev;
			if (heap1_prev != NULL)
			{
				if (heap1_prev->child == pairheap1)
					heap1_prev->child = pairheap2;
				else
					heap1_prev->sibling = pairheap2;
			}
			PairNode temp = pairheap1;        //Exchange node1 and node2 to unified form with "else" part. 
			pairheap1 = pairheap2;
			pairheap2 = temp;
		}
		else                                     //Let node2->sibling linked to node1
		{
			PairNode heap2_sibling = pairheap2->sibling;
			pairheap1->sibling = heap2_sibling;
			if (pairheap1->sibling != NULL)
				heap2_sibling->Prev = pairheap1;
		}
		PairNode heap1_child = pairheap1->child;
		pairheap1->child = pairheap2;
		pairheap2->Prev = pairheap1;
		pairheap2->sibling = heap1_child;
		if (pairheap2->sibling != NULL)
			heap1_child->Prev = pairheap2;
		return pairheap1;
	}
}

PairHeap PairInsert(PairHeap pairheap, PairNode pairnode)
{
	if (pairheap == NULL)
		return pairnode;
	else
	    return PairMerge(pairheap, pairnode); //Call PairMerge to merge them.
}

PairHeap PairDeleteMin(PairHeap pairheap)
{
	if (pairheap == NULL || pairheap->child == NULL)
		return NULL;
	else
	{
		PairHeap firstSibling = pairheap->child;
		firstSibling->Prev = NULL;
		return CombineSiblings(firstSibling); //After we delete the min node, we need to Combine the sibling nodes.
	}
}

PairHeap CombineSiblings(PairHeap pairheap)
{
	PairNode heap_next = pairheap->sibling;
	PairNode porign = pairheap;
	while (pairheap != NULL)  //The first round from left to right.
	{
		porign = PairMerge(pairheap, heap_next);
		pairheap = porign->sibling;
		heap_next = (pairheap == NULL ? NULL : pairheap->sibling);
		if (heap_next == NULL)
			break;
	}
	if (pairheap != NULL)
		porign = pairheap;
	PairNode heap_prev = porign->Prev;
	while (heap_prev != NULL) //The second round from ight to left.
	{
		porign = PairMerge(heap_prev, porign);
		heap_prev = porign->Prev;
	}
	return porign;
}

PairHeap PairDecrease(PairHeap pairheap, PairNode pairnode, int value)
{
	pairnode->value = value;
	if (pairnode != pairheap)
	{
		PairNode node_prev = pairnode->Prev;
		if (node_prev->child == pairnode)
			node_prev->child = pairnode->sibling;
		else
			node_prev->sibling = pairnode->sibling;
		if (pairnode->sibling != NULL)
			pairnode->sibling->Prev = node_prev;
		pairnode->Prev = pairnode->sibling = NULL;
		pairheap = PairMerge(pairnode, pairheap);
	}
	return pairheap;
}

bool IsPairEmpty(PairHeap pairheap)
{
	if (pairheap == NULL)
		return true;
	else
		return false;
}
