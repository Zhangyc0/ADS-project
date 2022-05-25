#include"Dijkstra.h"
Edge AddEdge(Edge start, int weight, int destination)
{
	Edge newEdge = (Edge)malloc(sizeof(struct EdgeNode));
	newEdge->weight = weight;
	newEdge->destination = destination;
	if (start == NULL)  //The orignal  list is empty.
	{
		newEdge->next = NULL;
		start = newEdge;
	}
	else                 //The orignal  list is not empty. Insert the new node in the head.
	{
		newEdge->next = start;
		start = newEdge;
	}
	return start;
}

Edge *ReadFile(int *maxNode)
{
	FILE *fp;
	char StrLine[150];
	if ((fp = fopen("map.txt", "r")) == NULL)
	{
		printf("Open file error!\n");
		return NULL;
	}
	printf("Loading file...");
	while (!feof(fp) && StrLine[0] != 'p')
	{
		fgets(StrLine, 1024, fp);  //Read one line
	}
	char *p = strtok(StrLine, " ");  //Split string.
	for (int i = 0; i < 2; i++)
	{
		p = strtok(NULL, " "); //Jump 'p' and 'sp'.
	}
	*maxNode = (int)atof(p) + 1; //Get the number of nodes.

	Edge *edge = (Edge*)malloc(sizeof(Edge)*(*maxNode));
	for (int i = 0; i < *maxNode; i++)
		edge[i] = NULL;
	fgets(StrLine, 1024, fp);  //Read one line
	while (!feof(fp))
	{
		if (StrLine[0] == 'a')
		{
			p = strtok(StrLine, " "); //Split the string.
			int departure = (int)atof(strtok(NULL, " "));
			int destination = (int)atof(strtok(NULL, " "));
			int weight = (int)atof(strtok(NULL, " "));
			edge[departure] = AddEdge(edge[departure], weight, destination);
		}
		fgets(StrLine, 1024, fp);  //Read one line
	}
	printf("\nRead completely!\n");
	fclose(fp);
	return edge;
}



void DijkstraWithFib(Edge *edge, int maxNode, int sorNode, int numFind)
{
	int curFind = 0;
	FibHeap fibheap = InitialHeap();
	FibNode *Distance = (FibNode*)malloc(sizeof(FibNode)*maxNode);
	for (int i = 1; i < maxNode; i++) 
	{
		Distance[i] = InitialFibNode(Infinity, i);
	}
	Edge pedge = edge[sorNode]; 
	while (pedge != NULL)  //Deal with the sourse node.
	{
		Distance[pedge->destination]->value = pedge->weight;
		FibInsertNode(fibheap, Distance[pedge->destination]);  //Insert the nodes linked to sourse node to heap.
		pedge = pedge->next;
	}
	while (IsFibEmpty(fibheap) == false)
	{
		int minNode = fibheap->min->vertex; // min is the shortest node
		//printf("%d is found with distance %d\n", minNode, Distance[minNode]->value);
		curFind++;
		if (curFind == numFind)
			break;
		FibDeleteMin(fibheap); //Get the nearest node.
		pedge = edge[minNode];

		while (pedge != NULL)
		{
			if (Distance[pedge->destination]->value == Infinity) //Check if the node is known.
			{
				Distance[pedge->destination]->value = Distance[minNode]->value + pedge->weight;
				FibInsertNode(fibheap, Distance[pedge->destination]);
			}
			else
			{
				if (Distance[minNode]->value + pedge->weight < Distance[pedge->destination]->value)  //Relaxation operation 
					FibDecrease(fibheap, Distance[pedge->destination], Distance[minNode]->value + pedge->weight);
			}
			pedge = pedge->next;
		}
	}
	for (int i = 1; i < maxNode; i++) //Free memory.
		free(Distance[i]);
	free(Distance);
}

void DijkstraWithPair(Edge *edge, int maxNode, int sorNode, int numFind)
{
	int curFind = 0;
	PairHeap pairheap = NULL;
	PairHeap *Distance = (PairHeap*)malloc(sizeof(PairHeap)*maxNode);
	for (int i = 1; i < maxNode; i++)
	{
		Distance[i] = InitialPairHeap(Infinity, i);
	}
	Edge pedge = edge[sorNode]; //Get the nearest node.
	while (pedge != NULL)
	{
		Distance[pedge->destination]->value = pedge->weight;
		pairheap = PairInsert(pairheap, Distance[pedge->destination]);  //Insert the nodes linked to sourse node to heap.
		pedge = pedge->next;
	}
	while (IsPairEmpty(pairheap) == false)
	{
		int minNode = pairheap->vertex; // min is the shortest node
		//printf("%d is found with distance %d\n", minNode, Distance[minNode]->value);
		curFind++;
		if (curFind == numFind)
			break;
		pairheap = PairDeleteMin(pairheap);
		pedge = edge[minNode];

		while (pedge != NULL)
		{
			if (Distance[pedge->destination]->value == Infinity) //Check if the node is known.
			{
				Distance[pedge->destination]->value = Distance[minNode]->value + pedge->weight;
				pairheap = PairInsert(pairheap, Distance[pedge->destination]);
			}
			else
			{
				if (Distance[minNode]->value + pedge->weight < Distance[pedge->destination]->value)
					pairheap = PairDecrease(pairheap, Distance[pedge->destination], Distance[minNode]->value + pedge->weight);  //Relaxation operation 
			}
			pedge = pedge->next;
		}
	}
	for (int i = 1; i < maxNode; i++) //Free memory.
		free(Distance[i]);
	free(Distance);
}

void DijkstraWithBin(Edge *edge, int maxNode, int sorNode, int numFind)
{
	int curFind = 0;
	BinHeap binheap = NULL;
	BinHeap *Distance = (BinHeap*)malloc(sizeof(BinHeap)*maxNode);
	for (int i = 1; i < maxNode; i++)
	{
		Distance[i] = InitialBinNode(Infinity, i);
	}
	Edge pedge = edge[sorNode]; //Deal with the sourse node.
	while (pedge != NULL)
	{
		Distance[pedge->destination]->value = pedge->weight;
		binheap = BinInsert(binheap, Distance[pedge->destination]);
		pedge = pedge->next;
	}
	while (IsBinEmpty(binheap) == false)
	{
		int minNode = BinGetMin(binheap)->vertex; // min is the shortest node
		//printf("%d is found with distance %d\n", minNode, Distance[minNode]->value);
		curFind++;
		if (curFind == numFind)
			break;
		binheap = BinDeleteMin(binheap); //Get the neareast node.
		pedge = edge[minNode];

		while (pedge != NULL)
		{
			if (Distance[pedge->destination]->value == Infinity) //Check if the node is known.
			{
				Distance[pedge->destination]->value = Distance[minNode]->value + pedge->weight;
				binheap = BinInsert(binheap, Distance[pedge->destination]);
			}
			else
			{
				if (Distance[minNode]->value + pedge->weight < Distance[pedge->destination]->value)
					BinDecrease(binheap, Distance[pedge->destination], Distance[minNode]->value + pedge->weight,Distance);  //Relaxation operation 
			}
			pedge = pedge->next;
		}
	}
	for (int i = 1; i < maxNode; i++)  //Free memory.
		free(Distance[i]);
	free(Distance);
}


