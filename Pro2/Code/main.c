#include "Dijkstra.h"
#include "Fibonacci heap.h"
#include "Pairing heap.h"
#include "Binomial heap.h"
#include <time.h>

int main(void)
{
	int maxNode, sorNode, numFind;
	int beginTime, endTime;
	Edge *edge = ReadFile(&maxNode); //Read map from file.
	if (edge != NULL)
	{
		printf("Enter sourse node between 1 and %d:\n", maxNode - 1); 
		scanf_s("%d", &sorNode); //Choose source node.
		while (sorNode > maxNode - 1 || sorNode < 1) //Check if the sourse node is legal.
		{
			printf("You can only choose sorNode between 1 and %d \nPlease input again:", maxNode - 1);
			scanf_s("%d", &sorNode);
		}
		while (true)
		{
			printf("Enter the number of nodes you want to find(0 means all nodes):(Program will find numFind nearest nodes)\n");
			scanf_s("%d", &numFind);
			if (numFind > maxNode - 1  || numFind < 0) //Check if the number of target node is legal.
			{
				printf("You can only choose numFind between 1 and %d\n", maxNode - 1);
				continue;
			}
			if (numFind == 0) //0 means all nodes.
				numFind = maxNode - 1;
			beginTime = clock();
				DijkstraWithFib(edge, maxNode, sorNode, numFind);
			endTime = clock();
			printf("Fibonacci heap || Number of nodes: %d || Time: %dms\n", numFind, endTime - beginTime);
			beginTime = clock();
				DijkstraWithPair(edge, maxNode, sorNode, numFind);
			endTime = clock();
			printf("Pairing heap   || Number of nodes: %d || Time: %dms\n", numFind, endTime - beginTime);
			beginTime = clock();
				DijkstraWithBin(edge, maxNode, sorNode, numFind);
			endTime = clock();
			printf("Binomial heap  || Number of nodes: %d || Time: %dms\n", numFind, endTime - beginTime);
		}
	}
	system("pause");
}

