//============================================================================
// Name        : lab3.cpp
// Author      : Philippe Gelinas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include "graph.h"
using namespace std;

int main() {

	CGraph * G = new(CGraph);


	for(int i = 0; i<G->N; i++)
	{
		printf("\nNode:%d voisin:%d ",G->graph[i].id,G->graph[i].nb_nodes);

		for(auto it = G->graph[i].nodes.begin(); it!=G->graph[i].nodes.end();it++)
		{
			printf("\nid=%d value=%d", it->id, it->value);
		}
	}

	return 0;
}
