#include "Binomial heap.h"


BinHeap InitialBinNode(int value, int vertex)
{
	BinHeap binheap = (BinHeap)malloc(sizeof(struct BinomialNode));
	binheap->child = NULL;
	binheap->parent = NULL;
	binheap->sibling = NULL;
	binheap->degree = 0;
	binheap->value = value;
	binheap->vertex = vertex;
	return binheap;
}

BinHeap BinLinked(BinHeap binheap, BinHeap child)
{
	child->parent = binheap;
	child->sibling = binheap->child;
	binheap->child = child;
	binheap->degree++;
	return binheap;
}

BinHeap BinCombineOrder(BinHeap binheap1, BinHeap binheap2) 
{
	BinNode ptr1 = binheap1, ptr2 = binheap2;
	BinHeap binBegin = NULL;
	BinHeap *binheap = &binBegin;
	while (ptr1 != NULL && ptr2 != NULL)   //Merge two lists in increase order.
	{
		if (ptr1->degree <= ptr2->degree)
		{
			*binheap = ptr1;
			ptr1 = ptr1->sibling;
		}
		else
		{
			*binheap = ptr2;
			ptr2 = ptr2->sibling;
		}
		binheap = &((*binheap)->sibling);
	}
	if (ptr1 == NULL)
		*binheap = ptr2;
	else
		*binheap = ptr1;
	return binBegin;
}

BinHeap BinMerge(BinHeap binheap1, BinHeap binheap2)
{
	BinHeap binheap = BinCombineOrder(binheap1, binheap2); //First step, merge them in increase order.
	if (binheap == NULL)
		return NULL;
	BinNode p_prev, p, p_sib;
	p_prev = NULL;
	p = binheap;
	p_sib = p->sibling;
	while (p_sib != NULL)
	{
		if (p->degree != p_sib->degree || p_sib->sibling != NULL && p_sib->degree == p_sib->sibling->degree)  //In this case, forms a(p)-b or a(p)-a-a will be skipped. 
		{
			p_prev = p;
			p = p_sib;
		}
		else  //Need to merge.
		{
			if (p->value <= p_sib->value)         //In this case, a(p)-b, b will be a child of a.(value(a)<=value(b))
			{
				p->sibling = p_sib->sibling;  //p_sib will be romoved.
				p = BinLinked(p, p_sib);
			}
			else                                      //In this case, a(p)-b, a will be a child of b.(value(a)>value(b))
			{
				if (p_prev == NULL)
					binheap = p_sib;
				else
					p_prev->sibling = p_sib;
				p_sib = BinLinked(p_sib, p);         //p will be romeved.
				p = p_sib;
			}
		}
		p_sib = p->sibling;
	}
	return binheap;
}

BinHeap* BinGetMin2(BinHeap binheap)
{
	if (binheap->sibling == NULL)
		return NULL;
	else
	{
		BinHeap* p = (BinHeap*)malloc(sizeof(BinHeap) * 2);  //Used to storage min position.
		p[0] = NULL;
		p[1] = binheap;
		BinNode ptr, ptr_prev;  //Used to travel the link;
		ptr_prev = NULL;
		ptr = binheap;
		while (ptr!= NULL)
		{
			if (ptr->value < p[1]->value)
			{
				p[0] = ptr_prev;
				p[1] = ptr;
			}
			ptr_prev = ptr;
			ptr = ptr->sibling;
		}
		return p;
	}
}

BinHeap BinDeleteMin(BinHeap binheap)
{
	if (binheap == NULL)
		return NULL;
	else
	{
		BinHeap* min = BinGetMin2(binheap); //Get the min node and its previous node.
		if (min == NULL)            //Check if the min node is the first node.
			return binheap->child;
		BinHeap binMin_prev = min[0], binMin = min[1];
		if (binMin_prev == NULL)
			binheap = binheap->sibling;
		else
			binMin_prev->sibling = binMin->sibling;
		BinNode childList = binMin->child;
		BinNode reverse = NULL;
		BinNode temp;
		while (childList != NULL)    //Reverse the list.
		{
			temp = childList->sibling;
			if (reverse == NULL)
			{
				reverse = childList;
				reverse->sibling = NULL;
			}
			else
			{
				childList->sibling = reverse;
				reverse = childList;
			}
			childList = temp;
		}
		free(min);
		return BinMerge(binheap, reverse);
	}
}

BinHeap BinGetMin(BinHeap binheap)
{
	if (binheap == NULL)
		return NULL;
	else
	{
		BinNode ptr = binheap;
		BinNode temp = ptr;
		while (ptr != NULL)
		{
			if (ptr->value < temp->value)
				temp = ptr;
			ptr = ptr->sibling;
		}
		return temp;
	}
}

BinHeap BinInsert(BinHeap binheap, BinNode binnode)
{
	return BinMerge(binheap, binnode);
}

void BinDecrease(BinHeap binheap, BinNode binnode, int value, BinHeap* NodeArray)
{
	binnode->value = value;
	BinNode parent, child;
	parent = binnode->parent;
	child = binnode;
	while (parent != NULL && parent->value > child->value) //Exchange the position between child and parent.
	{
		int temp_value, temp_vertex;
		BinNode temp = NodeArray[child->vertex];   //Change the Distance array.
		NodeArray[child->vertex] = NodeArray[parent->vertex];
		NodeArray[parent->vertex] = temp;
		temp_value = child->value;
		temp_vertex = child->vertex;
		child->value = parent->value;
		child->vertex = parent->vertex;
		parent->value = temp_value;
		parent->vertex = temp_vertex;
		child = parent;
		parent = parent->parent;
	}
}

bool IsBinEmpty(BinHeap binheap)
{
	return binheap == NULL;
}

